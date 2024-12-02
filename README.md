# Projeto: Gerenciamento de Exames Médicos

Este projeto tem como objetivo o desenvolvimento de um sistema de gerenciamento de exames médicos utilizando a estrutura de dados **Árvore AVL** para organização dos exames e **Lista Duplamente Encadeada** para organizar as datas dos exames.

## Funcionalidades

O sistema implementa as seguintes funcionalidades:

1. **Árvore AVL**: Armazena os exames em uma estrutura balanceada, permitindo uma busca eficiente por nome dos pacientes.
2. **Lista Duplamente Encadeada**: Armazena as datas dos exames, permitindo a navegação eficiente entre os diferentes exames.
3. **Inserção de Exames**: Exames são inseridos na árvore AVL de acordo com o nome do paciente.
4. **Busca por Nome**: Permite buscar exames pelo nome do paciente na árvore AVL.
5. **Busca por Data**: Permite buscar exames por data na lista duplamente encadeada.
6. **Cálculo de Média de Exames**: Calcula a média dos resultados de exames de um tipo específico (e.g., "Sangue").

## Estruturas de Dados

O código utiliza as seguintes estruturas de dados:

- **Exame**: Armazena as informações do exame, como nome, data, tipo e resultado.
- **AVLNode**: Nó da árvore AVL que armazena um exame e os ponteiros para os filhos esquerdo e direito.
- **Celula**: Nó da lista duplamente encadeada que armazena a data do exame e o ponteiro para a árvore AVL correspondente ao exame.

## Fluxo de Execução

1. **Inserção**: O programa começa com a inserção de exames na árvore AVL. Os exames contêm informações como o nome do paciente, a data do exame, o tipo de exame e o resultado.
2. **Busca por Nome**: O usuário pode buscar um exame por nome, e o sistema retorna as informações do exame correspondente.
3. **Busca por Data**: O sistema permite buscar um exame específico por sua data, utilizando a lista duplamente encadeada para percorrer as datas dos exames.
4. **Cálculo de Média**: O sistema calcula a média dos resultados dos exames de um tipo específico (por exemplo, "Sangue").

## Exemplo de Uso

- **Busca por nome**: O usuário pode buscar um exame específico fornecendo o nome do paciente. O sistema percorre a árvore AVL e retorna os dados do exame correspondente.
  
- **Busca por data**: O sistema busca o exame na lista duplamente encadeada, comparando as datas fornecidas, e retorna o exame correspondente.

- **Cálculo de média**: O sistema calcula a média dos resultados dos exames de um tipo específico. Por exemplo, se o tipo de exame for "Sangue", o programa calcula a média de todos os exames de sangue cadastrados.

## Como Executar

1. **Compilar o Código**:
   Para compilar o código, use o comando:

   ```bash
   gcc -o avaliacao avaliacao.c

2. **Executar o Código**:
    Para executar o código, use o comando:

   ```bash
     ./avaliacao

3. **Testar Funcionalidades**:
   Testar Funcionalidades: O programa realiza a inserção de exames e, em seguida, realiza buscas por nome e por data, além de calcular a média de exames de um tipo específico.
   
   ## Licença

Este projeto está licenciado sob a **GNU General Public License versão 2 (GPL-2.0)**.

---

## O que é a GPL-2.0?

A **GNU General Public License versão 2** é uma licença de software livre criada pela Free Software Foundation. Seu principal objetivo é garantir que um programa licenciado sob seus termos continue sendo livre para todos os usuários e desenvolvedores. A licença assegura os seguintes direitos:

1. **Liberdade de Uso**: Você pode usar o software para qualquer propósito.
2. **Liberdade de Estudo e Modificação**: O código-fonte está disponível, permitindo que você estude como ele funciona e o adapte às suas necessidades.
3. **Liberdade de Compartilhar**: Você pode redistribuir cópias do software original.
4. **Liberdade de Distribuir Modificações**: É permitido distribuir versões modificadas do programa, desde que elas também sejam licenciadas sob a GPL-2.0.

---

## Termos Importantes da GPL-2.0

1. **Código Aberto**: Todo software derivado deve incluir o código-fonte, para garantir que outras pessoas possam estudá-lo e modificá-lo.
2. **Distribuição Sob a Mesma Licença**: Modificações ou redistribuições devem manter a licença GPL-2.0, garantindo que o software continue sendo livre.
3. **Sem Garantias**: O software é distribuído sem garantias, o que significa que os desenvolvedores não se responsabilizam por possíveis problemas ou falhas decorrentes do uso do programa.

---

## Texto Completo da Licença

Você pode encontrar o texto completo da GPL-2.0 no seguinte link:  
[GNU GPL v2.0](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html)

---

Ao adotar a GPL-2.0, asseguramos que este projeto continuará contribuindo para o ecossistema de software livre, permitindo melhorias e compartilhamento por outros desenvolvedores.
