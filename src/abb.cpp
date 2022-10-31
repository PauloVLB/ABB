#include "abb.h"
#include <iostream>

bool abb::inserir(int x) {
    if(valor < x) {
        if(dir == nullptr) {
            dir = new abb(x);
            return true;
        } else {
            return dir->inserir(x);
        }
    }

    if(valor > x) {
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