#include <iostream>
using namespace std;

struct Node {
    int chave;
    Node* esquerda;
    Node* direita;
    int altura;
};

// Função para obter a altura de um nó
int altura(Node* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

// Função para criar um novo nó
Node* novoNo(int chave) {
    Node* no = new Node();
    no->chave = chave;
    no->esquerda = nullptr;
    no->direita = nullptr;
    no->altura = 1; // novo nó começa com altura 1
    return no;
}

// Fator de balanceamento
int getFB(Node* n) {
    if (n == nullptr) return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// Rotação à direita
Node* rotacaodireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    // Rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Rotação à esquerda
Node* rotacaoesquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    // Rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Inserção em AVL
Node* inserir(Node* no, int chave) {
    // 1. Inserção normal de Árvore Binária de Busca
    if (no == nullptr) return novoNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave);
    else // Chaves iguais não são permitidas
        return no;

    // 2. Atualiza a altura deste nó "pai"
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // 3. Obtém o Fator de Equilíbrio para verificar se desequilibrou
    int fb = getFB(no);

    // CASO 1: Esquerda-Esquerda
    if (fb > 1 && chave < no->esquerda->chave)
        return rotacaodireita(no);

    // CASO 2: Direita-Direita
    if (fb < -1 && chave > no->direita->chave)
        return rotacaoesquerda(no);

    // CASO 3: Esquerda-Direita
    if (fb > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoesquerda(no->esquerda);
        return rotacaodireita(no);
    }

    // CASO 4: Direita-Esquerda
    if (fb < -1 && chave < no->direita->chave) {
        no->direita = rotacaodireita(no->direita);
        return rotacaoesquerda(no);
    }

    return no;
}

// Impressão em ordem
void emOrdem(Node* raiz) {
    if (raiz != nullptr) {
        emOrdem(raiz->esquerda);
        cout << raiz->chave << " ";
        emOrdem(raiz->direita);
    }
}

int main() {
    Node* raiz = nullptr;

    // Inserindo alguns valores
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    cout << "Árvore AVL em ordem: ";
    emOrdem(raiz);
    cout << endl;

    return 0;
}
