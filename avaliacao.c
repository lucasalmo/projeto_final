#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char data[11]; // formato: "dd/mm/yyyy"
    char tipo[50];
    float resultado;
} Exame;

typedef struct AVLNode {
    Exame exame;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

AVLNode* createNode(Exame exame) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->exame = exame;
    node->left = node->right = NULL;
    node->height = 1;
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

    if (strcmp(exame.nome, node->exame.nome) < 0)
        node->left = insert(node->left, exame);
    else if (strcmp(exame.nome, node->exame.nome) > 0)
        node->right = insert(node->right, exame);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(exame.nome, node->left->exame.nome) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(exame.nome, node->right->exame.nome) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(exame.nome, node->left->exame.nome) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

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

void searchByDate(AVLNode* root, char* data) {
    if (root == NULL)
        return;

    searchByDate(root->left, data);

    if (strcmp(data, root->exame.data) == 0) {
        printf("Exame encontrado: %s, Data: %s, Tipo: %s, Resultado: %.2f\n", root->exame.nome, root->exame.data, root->exame.tipo, root->exame.resultado);
    }

    searchByDate(root->right, data);
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
    AVLNode* root = NULL;
    Exame exame1 = {"Joao", "01/01/2023", "Sangue", 90.5};
    Exame exame2 = {"Maria", "02/01/2023", "Urina", 85.0};
    Exame exame3 = {"Pedro", "03/01/2023", "Sangue", 88.0};

    root = insert(root, exame1);
    root = insert(root, exame2);
    root = insert(root, exame3);

    printf("Busca por nome 'Maria':\n");
    searchByName(root, "Maria");

    printf("\nBusca por data '01/01/2023':\n");
    searchByDate(root, "01/01/2023");

    int count = 0;
    float average = calculateAverage(root, "Sangue", &count);
    if (count > 0) {
        printf("\nMédia dos resultados de exames do tipo 'Sangue': %.2f\n", average / count);
    } else {
        printf("\nNenhum exame do tipo 'Sangue' encontrado.\n");
    }

    return 0;
}