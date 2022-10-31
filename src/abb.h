#ifndef ARVORE_H
#define ARVORE_H

#include <string>
#include <stack>
#include <queue>

using std::string;

class abb {
    private:
        abb* esq = nullptr;
        abb* dir = nullptr;
        int tamanho_esq = 0;
        int tamanho_dir = 0;
        int valor;
        int altura;
    public:
        abb();
        abb(int valor, abb* esq = nullptr, abb* dir = nullptr) : valor(valor), esq(esq) , dir(dir) {}

        int busca(int x);
        bool inserir(int x);
        bool remover(int x);

        int enisimoElemento(int n);

        int posicao(int x);

        int mediana();

        double media(int x);

        bool ehCheia();

        bool ehCompleta();

        string pre_ordem();

        void imprimeArvore(int s);
};

#endif


