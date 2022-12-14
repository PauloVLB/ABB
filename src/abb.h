#ifndef ARVORE_H
#define ARVORE_H

#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <math.h>

using std::string;

class abb {
    private:
        abb* esq = nullptr;
        abb* dir = nullptr;
        int tamanho_esq = 0;
        int tamanho_dir = 0;
        int valor;
        int altura = 1;
    public:
        abb();
        abb(int valor, abb* esq = nullptr, abb* dir = nullptr) : valor(valor), esq(esq) , dir(dir) {}
        int getValor();

        std::optional<abb*> busca(int x);
        bool inserir(int x);
        bool remover(int x);
        abb* remover(int x, abb* sub);

        std::optional<int> enesimoElemento(int n);

        std::optional<int> posicao(int x);

        std::optional<int> mediana();

        std::optional<double> media(int x);

        bool ehCheia();

        bool ehCompleta();

        string pre_ordem();

        void imprimeArvore(int s);
    private:
        void formato1(int qnt_tabs, int espaco, abb *no);
        void formato2(abb *no);

        void calcularAltura(abb* raiz);
        int qnt_nos();
};

#endif


