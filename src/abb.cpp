#include "abb.h"
#include <iostream>

bool abb::inserir(int x) {
    if(valor < x) {
        tamanho_dir++;
        if(dir == nullptr) {
            dir = new abb(x);
            return true;
        } else {
            return dir->inserir(x);
        }
    }

    if(valor > x) {
        tamanho_esq++;
        if(esq == nullptr) {
            esq = new abb(x);
            return true;
        } else {
            return esq->inserir(x);
        }
    }

    return false;
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
    std::cout << std::left << no->valor << std::endl;

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

std::optional<int> abb::busca(int x){
    if(x == valor)return valor;
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
int abb::enesimoElemento(int n){
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
}
