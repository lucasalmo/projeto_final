#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char data[20]; // formato: "dd/mm/yyyy hh:mm:ss"
    char tipo[50];
    float resultado;
} Exame;

typedef struct AVLNode {
    Exame exame;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct AVLNode* ApontadorAVL;

typedef struct Celula* ApontadorCelula;

typedef struct Celula {
    char data[20];
    ApontadorAVL AVL;
    ApontadorCelula prox;
    ApontadorCelula ante;
} Celula;

ApontadorCelula inicioLista;

int CriarListaVazia() {
    inicioLista = NULL;
    return 1;
}

int InsInicio (Celula celula) {
    ApontadorCelula ins, aux1, aux2;
    ins = (ApontadorCelula) malloc(sizeof(Celula));
    aux1 = inicioLista;
    aux2 = inicioLista;

    if (ins == NULL) {
        return 0;
    }
    else {
        memcpy(ins -> data, celula.data, strlen(celula.data)+1);
        ins -> AVL = celula.AVL; 
        if (inicioLista == NULL) {
            ins -> prox = ins;
            ins -> ante = ins;
        }
        else if(aux1 -> prox != aux1){
            aux2 = aux2 -> ante;
            ins -> ante = ins;
            aux2 -> prox = ins;
            aux1 -> ante = ins;
            ins -> prox = inicioLista;
        }
        else if(aux1 -> prox == aux1){
            aux1 -> ante = ins;
            aux1 -> prox = ins;
            ins -> prox = inicioLista;
            ins -> ante = inicioLista;
        }
        inicioLista = ins;
        return 1;
    }
}

int InsFinal (Celula celula) {
    ApontadorCelula ins, count, aux;

    if (inicioLista == NULL)
        return (InsInicio (celula));
    else{
        ins = (ApontadorCelula) malloc(sizeof(Celula));
        if (ins == NULL) {
            return 0;
        }
        else{
            memcpy(ins -> data, celula.data, strlen(celula.data)+1);
            ins -> AVL = celula.AVL; 
            ins -> prox = NULL;
            count = inicioLista;
            aux = inicioLista;
            if (count -> prox != inicioLista){
                aux = aux -> ante;
                ins -> prox = inicioLista;
                aux -> prox = ins;
                ins -> ante = aux;
                count -> ante = ins;
            }
            else{
                ins -> prox = inicioLista;
                ins -> ante = inicioLista;
                count -> prox = ins;
                count -> ante = ins;
            }
            return 1;
        }
    }
}

Celula CriarCelula(char data[20], ApontadorAVL AVL){
    Celula celula;
    
    memcpy(celula.data, data, strlen(data)+1);
    celula.AVL = AVL;
    celula.prox = NULL;
    celula.ante = NULL;
    
    return celula;
}

AVLNode* createNode(Exame exame) {
    Celula celula;
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->exame = exame;
    node->left = node->right = NULL;
    node->height = 1;
    celula = CriarCelula(exame.data, node);
    InsFinal(celula);
    return node;
}

int height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

AVLNode* insert(AVLNode* node, Exame exame) {
    if (node == NULL)
        return createNode(exame);

    // Comparação para encontrar a posição do nó
    if (strcmp(exame.nome, node->exame.nome) < 0)
        node->left = insert(node->left, exame);
    else if (strcmp(exame.nome, node->exame.nome) > 0)
        node->right = insert(node->right, exame);
    else {
        // Colisão detectada - o nome já existe, então atualizamos o exame
        // Você pode atualizar outras informações aqui conforme necessário
        memcpy(&node->exame, &exame, sizeof(Exame));
        return node;
    }

    // Atualiza a altura do nó atual
    node->height = 1 + max(height(node->left), height(node->right));

    // Verifica o balanceamento para decidir se uma rotação é necessária
    int balance = getBalance(node);

    // Se o nó ficar desbalanceado, há 4 casos a serem considerados

    // Caso 1: Rotação simples à direita
    if (balance > 1 && strcmp(exame.nome, node->left->exame.nome) < 0)
        return rightRotate(node);

    // Caso 2: Rotação simples à esquerda
    if (balance < -1 && strcmp(exame.nome, node->right->exame.nome) > 0)
        return leftRotate(node);

    // Caso 3: Rotação dupla à esquerda-direita
    if (balance > 1 && strcmp(exame.nome, node->left->exame.nome) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Rotação dupla à direita-esquerda
    if (balance < -1 && strcmp(exame.nome, node->right->exame.nome) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void searchByName(AVLNode* root, char* nome) {
    if (root == NULL)
        return;

    if (strcmp(nome, root->exame.nome) == 0) {
        printf("Exame encontrado: %s, Data: %s, Tipo: %s, Resultado: %.2f\n", root->exame.nome, root->exame.data, root->exame.tipo, root->exame.resultado);
        return;
    }

    if (strcmp(nome, root->exame.nome) < 0)
        searchByName(root->left, nome);
    else
        searchByName(root->right, nome);
}

void searchByDate(char* data) {
    
    ApontadorCelula apontador = inicioLista;
    if (strcmp(data, apontador -> data) == 0){
        ApontadorAVL AVL = apontador -> AVL;
        printf("Exame encontrado: %s, Data: %s, Tipo: %s, Resultado: %.2f\n", AVL->exame.nome, AVL->exame.data, AVL->exame.tipo, AVL->exame.resultado);
        return;
    }
    
    int soma = 0, soma2 = 0, soma3 = 0;
    for (int i = 0; apontador -> data[i] != '\0'; i++){
        soma += apontador -> data[i];
    }
    for (int y = 0; apontador -> prox -> data[y] != '\0'; y++){
        soma2 += apontador -> prox -> data[y];
    }
    for (int z = 0; apontador -> ante -> data[z] != '\0'; z++){
        soma3 += apontador -> ante -> data[z];
    }
    
    int temp1, temp2;
    temp1 = soma - soma2;
    if(temp1 < -1){
        temp1 = temp1 *(-1);
    }
    temp2 = soma - soma3;
    if(temp2 < -1){
        temp2 = temp2 *(-1);
    }
    
    if (temp1 > temp2){
        apontador = apontador -> prox;
        while (strcmp(data, apontador -> data) != 0 && apontador != inicioLista){
            apontador = apontador -> prox;
        }
        if (strcmp(data, apontador -> data) == 0){
            ApontadorAVL AVL = apontador -> AVL;
            printf("Exame encontrado: %s, Data: %s, Tipo: %s, Resultado: %.2f\n", AVL->exame.nome, AVL->exame.data, AVL->exame.tipo, AVL->exame.resultado);
            return;
        }
    }
    else{
        apontador = apontador -> ante;
        while (strcmp(data, apontador -> data) != 0 && apontador != inicioLista){
            apontador = apontador -> ante;
        }
        if (strcmp(data, apontador -> data) == 0){
            ApontadorAVL AVL = apontador -> AVL;
            printf("Exame encontrado: %s, Data: %s, Tipo: %s, Resultado: %.2f\n", AVL->exame.nome, AVL->exame.data, AVL->exame.tipo, AVL->exame.resultado);
            return;
        }
    }
}

float calculateAverage(AVLNode* root, char* tipo, int* count) {
    if (root == NULL)
        return 0;

    float leftSum = calculateAverage(root->left, tipo, count);
    float rightSum = calculateAverage(root->right, tipo, count);

    if (strcmp(tipo, root->exame.tipo) == 0) {
        (*count)++;
        return leftSum + rightSum + root->exame.resultado;
    }

    return leftSum + rightSum;
}

int main() {
    CriarListaVazia();
    AVLNode* root = NULL;
    Exame exame1 = {"Joao", "01/01/2023 02:33:59", "Sangue", 90.5};
    Exame exame2 = {"Maria", "02/01/2023 09:58:01", "Urina", 85.0};
    Exame exame3 = {"Pedro", "03/01/2023 10:59:08", "Sangue", 88.0};

    root = insert(root, exame1);
    root = insert(root, exame2);
    root = insert(root, exame3);

    printf("Busca por nome 'Joao':\n");
    searchByName(root, "Joao");

    printf("\nBusca por data '03/01/2023 10:59:08':\n");
    searchByDate("03/01/2023 10:59:08");

    int count = 0;
    float average = calculateAverage(root, "Sangue", &count);
    if (count > 0) {
        printf("\nMédia dos resultados de exames do tipo 'Sangue': %.2f\n", average / count);
    } else {
        printf("\nNenhum exame do tipo 'Sangue' encontrado.\n");
    }

    return 0;
}
