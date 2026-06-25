#include "../include/Pair.hpp"

Pair::Pair(int indice, int valor) : _indice(indice), _valor(valor) {}

int Pair::getIndice() const {
    return _indice;
}

int Pair::getValor() const {
    return _valor;
}

