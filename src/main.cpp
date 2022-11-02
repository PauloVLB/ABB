#include <iostream>
#include <fstream>
#include <sstream>
#include "abb.h"

std::vector<std::string> split(const std::string & input_str, char delimiter){
    // Store the tokens.
    std::vector<std::string> tokens;

    // read file line by line
    std::istringstream iss;
    iss.str(input_str);
    std::string token;
    while ( std::getline( iss >> std::ws, token, delimiter ) )
        tokens.push_back( token );

    return tokens;
}

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
    
    arvore->imprimeArvore(1);
    int remover = -32;
    bool removeu = arvore->remover(remover);
    if(removeu) {
        std::cout << "removeu " << remover << std::endl;
    } else {
        std::cout << "não removeu " << remover << std::endl;
    }
    arvore->imprimeArvore(1);

    //std::string pre = arvore->pre_ordem();
    //std::cout << pre << std::endl; // teste de pre_ordem

    //arvore->imprimeArvore(1);
    //arvore->imprimeArvore(2);
    // double x = -1;
    // if(arvore->media(41)){
    //     x = arvore->media(41).value();
    // }

    //std::cout << arvore->ehCompleta() << '\n';

    //std::cout << "media: " << x << std::endl;

    return 0; // DEBUG

    std::string operacao;

    while(getline(arquivo_operacoes, operacao)) {
        /*auto op = split(operacao, ' ');
        if(op[0] == "INSIRA"){
            if(arvore->inserir(std::stoi(op[1]))){
                std::cout << op[1] << " inserido." << std::endl;
            }else{
                std::cout << op[1] << " já existe na arvore." << std::endl;
            }
        }else if(op[0] == "BUSCAR"){
            auto buscando  = arvore->busca(stoi(op[1]));
            abb* buscado;
            if(buscando.has_value()){
                buscado = buscando.value();
                std::cout << "Elemento " << buscado->valor << " encontrado na árvore." << std::endl;
            }else{
                std::cout << "Elemento " << op[1] << " não encontrado na árvore." << std::endl;
            }
        }else if(op[0] == "REMOVA"){

        }else if(op[0] == "ENESIMO"){
            auto buscando  = arvore->enesimoElemento(stoi(op[1]));
            int buscado;
            if(buscando.has_value()){
                buscado = buscando.value();
                std::cout << "O " << op[1] << "º elemento é: " << buscado << std::endl;
            }else{
                std::cout << "Índice do elemento além do alcance da árvore." << std::endl;
            }
        }else if(op[0] == "POSICAO"){
            auto buscando  = arvore->enesimoElemento(stoi(op[1]));
            int buscado;
            if(buscando.has_value()){
                buscado = buscando.value();
                std::cout << "O elemento " << op[1] << "está na posição: " << buscado << std::endl;
            }else{
                std::cout << "Elemento não encontrado na árvore." << std::endl;
            }
        }else if(op[0] == "MEDIANA"){
            std::cout << "A mediana é: " << arvore->mediana() << std::endl;
        }else if(op[0] == "MEDIA"){
            auto buscando  = arvore->enesimoElemento(stoi(op[1]));
            double buscado;
            if(buscando.has_value()){
                buscado = buscando.value();
                std::cout << "A média dos elementos da sub-árvore em que "<<op[1]<< " é raiz vale: " 
            << buscado << std::endl;
            }else{
                std::cout << "Não existe sub-árvore nessa árvore em que "<< op[1] <<" seja raíz." << std::endl;
            }            
        }else if(op[0] == "CHEIA"){

        }else if(op[0] == "COMPLETA"){

        }else if(op[0] == "PREORDEM"){

        }else if(op[0] == "IMPRIMA"){

        }
        std::cout << operacao << '\n';*/
    }
}