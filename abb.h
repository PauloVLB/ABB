#ifndef ARVORE_H
#define ARVORE_H

#include <string>

using std::string;

class abb {
    private:
        abb* esq;
        abb* dir;
        int tamanho_esq;
        int tamanho_dir;
        int valor;
        int altura;

    public:
        abb(int valor, abb* esq, abb* dir) : valor(valor), esq(esq) , dir(dir) {}

        // perguntas:
        // se pode usar bibliotecas
        // exemplo de arquivos de entrada
        // preferencia: arvore + metodos ou arvore & metodos?

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


