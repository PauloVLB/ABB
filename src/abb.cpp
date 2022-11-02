#include "abb.h"
#include <iostream>

bool abb::inserir(int x) {
    int alt_esq = 0;
    int alt_dir = 0;
    if(esq != nullptr)alt_esq = esq->altura;
    if(dir != nullptr)alt_dir = dir->altura;
    altura = 1 + std::max(alt_esq,alt_dir);
    if(valor < x) {
        if(dir == nullptr) {
            dir = new abb(x);
            tamanho_dir = 1;
            return true;
        } else {
            bool inseriu = dir->inserir(x);
            tamanho_dir = dir->tamanho_dir + dir->tamanho_esq + 1;
            return inseriu;
        }
    }

    if(valor > x) {
        if(esq == nullptr) {
            esq = new abb(x);
            tamanho_esq = 1;
            return true;
        } else {
            bool inseriu = esq->inserir(x);
            tamanho_esq = esq->tamanho_esq + esq->tamanho_esq + 1;
            return inseriu;
        }
    }

    return false;
}

bool abb::remover(int x) {
    if(x < valor) {
        if(esq != nullptr && esq->valor == x) {
            esq = nullptr;
            return true;
        }
        return esq->remover(x);
    }

    if(x > valor) {
        if(dir != nullptr && dir->valor == x) {
            dir = nullptr;
            return true;
        }
        return dir->remover(x);
    }
}

string abb::pre_ordem() {
    string ordem = "";

    std::stack<abb> pilha;

    pilha.push(*this);

    while(!pilha.empty()) {
        abb topo = pilha.top(); pilha.pop();

        ordem += std::to_string(topo.valor) + " ";

        if(topo.dir != nullptr) pilha.push(*topo.dir);
        if(topo.esq != nullptr) pilha.push(*topo.esq);
    }

    return ordem;
}

void abb::formato1(int qnt_tabs, int espaco, abb *no) {
    std::cout << string(qnt_tabs, '\t');
    std::cout.width(espaco);
    std::cout.fill('-');
    //std::cout << std::left << no->valor << std::endl;
    std::cout << std::left << no->valor << "(" << no->tamanho_esq << ", " << no->tamanho_dir << ")" << std::endl;
    
    if(no->esq != nullptr) {
        formato1(qnt_tabs + 1, espaco - 6, no->esq);
    }

    if(no->dir != nullptr) {
        formato1(qnt_tabs + 1, espaco - 6, no->dir);
    }
}

void abb::formato2(abb *no) {
    if(no != this) std::cout << " "; 
    std::cout << "(";
    std::cout << no->valor;

    if(no->esq != nullptr) {
        formato2(no->esq);
    }

    if(no->dir != nullptr) {
        formato2(no->dir);
    }

    std::cout << ")";
}


void abb::imprimeArvore(int s) {
    if(s == 1) {
        formato1(0, 36, this);
    } else {
        formato2(this);
    }
}

std::optional<abb*> abb::busca(int x){
    if(x == valor)return this;
    if(tamanho_esq == 0 && tamanho_dir == 0){
        return {};
    }else{
        if(valor < x){
            return dir->busca(x);
        }else{
            return esq->busca(x);
        }
    }
}
std::optional<int> abb::enesimoElemento(int n){
    if(n < 1 || n > (1 + tamanho_esq + tamanho_dir)) return {};
    if(n == tamanho_esq + 1)return valor;
    else{
        if(n <= tamanho_esq) return esq->enesimoElemento(n);
        else{
            return dir->enesimoElemento(n - tamanho_esq - 1);
        }
    }
}
std::optional<int> abb::posicao(int x){
    if(x == valor) return tamanho_esq+1;
    if(tamanho_esq == 0 && tamanho_dir == 0){
        return {};
    }else{
        if(x < valor) return esq->posicao(x);
        if(x > valor){
            auto y = dir->posicao(x);
            if(y.has_value()){
                return tamanho_esq + 1 + y.value();
            }else{
                return {};
            }
        } 
    }

    return {}; // warning
}

std::optional<int> abb::mediana(){
    return enesimoElemento(ceil((double)(1+this->tamanho_esq+this->tamanho_dir)/(double)2));
}

std::optional<int> abb::mediana(){
    return enesimoElemento(ceil((double)(1+this->tamanho_esq+this->tamanho_dir)/(double)2)).value();
}

// TODO testar
std::optional<double> abb::media(int x){
    auto aux = busca(x);
    if(aux.has_value()){
        abb* raiz{aux.value()};
        std::stack<abb*> s;
        int valor{0};
        int quantidade{1+raiz->tamanho_esq+raiz->tamanho_dir};
        s.push(raiz);
        while(not s.empty()){
            abb* atual{s.top()};
            s.pop();
            if(atual->dir != nullptr){
                s.push(atual->dir);
            }
            valor += atual->valor;
            if(atual->esq != nullptr){
                s.push(atual->esq);
            }
        }
        return ((double)valor/(double)quantidade);
    }else{
        return {};
    }
}

void abb::calcularAltura(abb* raiz){
    if(raiz->esq == nullptr and raiz->dir == nullptr){
        raiz->altura = 1;
    }
    if(raiz->esq != nullptr and raiz->dir != nullptr){
        calcularAltura(raiz->esq);
        calcularAltura(raiz->dir);
        raiz->altura += std::max(raiz->esq->altura,raiz->dir->altura);
    }
    else if(raiz->dir != nullptr){
        calcularAltura(raiz->dir);
        raiz->altura += raiz->dir->altura;
    }else if(raiz->esq != nullptr){
        calcularAltura(raiz->esq);
        raiz->altura += raiz->esq->altura;
    }
}

// TODO testar
bool abb::ehCheia(){
    calcularAltura(this);
    int quantidade_maxima_nos{(int) pow(2,this->altura)-1};
    std::stack<abb*> s;
    s.push(this);
    int quantidade_nos{0};
    while(not s.empty()){
        abb* atual{s.top()};
        s.pop();
        ++quantidade_nos;
        if(atual->dir != nullptr){
            s.push(atual->dir);
        }
        if(atual->esq != nullptr){
            s.push(atual->esq);
        }
    }
    return quantidade_maxima_nos == quantidade_nos;
}

// TODO testar
bool abb::ehCompleta(){
    calcularAltura(this);
    int quantidade_nos_internos{(int) pow(2,this->altura-1)-1};
    std::stack<abb*> s;
    s.push(this);
    int quantidade_nos{0};
    while(not s.empty()){
        abb* atual{s.top()};
        s.pop();
        if(atual->altura > 1){
            ++quantidade_nos;
        }
        if(atual->dir != nullptr and atual->altura > 1){
            s.push(atual->dir);
        }
        if(atual->esq != nullptr and atual->altura > 1){
            s.push(atual->esq);
        }
    }
    return quantidade_nos_internos == quantidade_nos;
}
