#include "../include/Pair.hpp"

Pair::Pair(int indice, std::string valor) : _indice(indice), _valor(valor) {}
Pair::Pair() : _indice(-1), _valor(std::to_string(-1)) {}

Pair::~Pair() = default;

int Pair::getIndice() const {
    return _indice;
}

std::string Pair::getValor() const {
    return _valor;
}

