#include "abb.h"
#include <iostream>

bool abb::inserir(int x) { 
    bool inseriu = false;
    if(valor < x) {
        if(dir == nullptr) {
            dir = new abb(x);
            tamanho_dir = 1;
            inseriu = true;
        } else {
            inseriu = dir->inserir(x);
            tamanho_dir = dir->qnt_nos();
        }
    }

    if(valor > x) {
        if(esq == nullptr) {
            esq = new abb(x);
            tamanho_esq = 1;
            inseriu = true;
        } else {
            inseriu = esq->inserir(x);
            tamanho_esq = esq->qnt_nos();
        }
    }

    int alt_esq = 0;
    int alt_dir = 0;
    if(esq != nullptr) alt_esq = esq->altura;
    if(dir != nullptr) alt_dir = dir->altura;
    altura = 1 + std::max(alt_esq, alt_dir);    

    return inseriu;
}

abb* abb::remover(int x, abb* sub) {
    if(sub == nullptr) {
        return nullptr;
    }

    if(x < sub->valor) {
        sub->esq = remover(x, sub->esq);
    } else if(x > sub->valor) {
        sub->dir = remover(x, sub->dir);
    } else {
        if(sub->esq == nullptr) {
            return sub->dir;
        } else if(sub->dir == nullptr) {
            return sub->esq;
        } else {
            abb* novo_no = sub->esq;
            while(novo_no->dir != nullptr) {
                novo_no = novo_no->dir;
            }
            sub->valor = novo_no->valor;
            sub->esq = remover(sub->valor, sub->esq);
        }   
    }

    int alt_esq = 0;
    int alt_dir = 0;
    if(sub->esq != nullptr) alt_esq = sub->esq->altura;
    if(sub->dir != nullptr) alt_dir = sub->dir->altura;
    sub->altura = 1 + std::max(alt_esq, alt_dir);

    sub->tamanho_esq = 0;
    sub->tamanho_dir = 0;
    if(sub->esq != nullptr) sub->tamanho_esq = sub->esq->qnt_nos();
    if(sub->dir != nullptr) sub->tamanho_dir = sub->dir->qnt_nos();

    return sub;
}

bool abb::remover(int x) {
    int nos_antes = qnt_nos();
    remover(x, this);
    return qnt_nos() < nos_antes;
}

int abb::qnt_nos() {
    return tamanho_esq + tamanho_dir + 1;
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
    std::cout << std::left << no->valor 
            << "(" << no->tamanho_esq << ", " << no->tamanho_dir << ")" 
            << " - (" << no->altura << ")" 
            << std::endl;
    
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

// TODO testar
bool abb::ehCheia(){
    return qnt_nos() == pow(2, altura) - 1;
}

// TODO testar
bool abb::ehCompleta(){
    return qnt_nos() >= pow(2, altura - 1);
}
