#include <iostream>
#include <fstream>
#include <sstream>
#include "abb.h"

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cerr << "Você deve passar APENAS dois arquivos como parâmetro.\n";
        std::cerr << "\t param1: Arquivo de descrição da árvore;\n";
        std::cerr << "\t param2: Arquivo com as opreações a serem realizadas;\n";
        std::cerr << "\t Exemplo: ./executavel param1 param2.\n";

        return 1;
    }

    std::string nome_arquivo_descricao = argv[1];
    std::string nome_arquivo_operacoes = argv[2];

    std::fstream arquivo_descricao(nome_arquivo_descricao);
    if(!arquivo_descricao.is_open()) {
        std::cerr << "Erro ao ler arquivo de descrição.\n";
        return 1;
    }

    std::fstream arquivo_operacoes(nome_arquivo_operacoes);

    if(!arquivo_operacoes.is_open()) {
        std::cerr << "Erro ao ler arquivo de operações.\n";
        return 1;
    }

    std::string descricao_arvore;
    getline(arquivo_descricao, descricao_arvore);

    std::stringstream ss(descricao_arvore);
    
    std::string chave_str;
    bool eh_raiz = 1;
    abb* arvore;
    while(ss >> chave_str) {
        int chave = stoi(chave_str);
        if(eh_raiz) {
            arvore = new abb(chave); // nova raiz
            eh_raiz = 0;
            std::cout << "Na teoria inseriu o " << chave << std::endl;
            continue;
        }
        if(arvore->inserir(chave)) {
            std::cout << "Na teoria inseriu o " << chave << std::endl;
        } else {
            std::cout << "Não inseriu o " << chave << std::endl;
        }
    }

    //std::string pre = arvore->pre_ordem();
    //std::cout << pre << std::endl; // teste de pre_ordem

    //arvore->imprimeArvore(1);
    //arvore->imprimeArvore(2);
    // double x = -1;
    // if(arvore->media(41)){
    //     x = arvore->media(41).value();
    // }

    std::cout << arvore->ehCompleta() << '\n';

    // std::cout << "media: " << x << std::endl;
    // std::cout << arvore->enesimoElemento(4) << "\n";
    

    return 0; // DEBUG

    std::string operacao;

    while(getline(arquivo_operacoes, operacao)) {
        std::cout << operacao << '\n';
    }
}