#include "../include/Reposicao.hpp"

int Reposicao::_contador = 0;

Reposicao::Reposicao(unsigned int timestamp, int *idProdutos, int *quantidades, int numProdutos) :
_timestamp(timestamp), _idProdutos(idProdutos), _quantidades(quantidades), _numprodutos(numProdutos) {
    _id = _contador;
    _contador++;
}

Reposicao::~Reposicao() {
    delete[] _idProdutos;
    delete[] _quantidades;
}

Reposicao::Reposicao() : _timestamp(0), _idProdutos(nullptr), _quantidades(nullptr), _numprodutos(0) {
    _id = _contador;
    _contador++;
}

int Reposicao::getId() const {
    return _id;
}

unsigned int Reposicao::getTimestamp() const {
    return _timestamp;
}

int *Reposicao::getIdProdutos() const {
    return _idProdutos;
}

int *Reposicao::getQuantidades() const {
    return _quantidades;
}

int Reposicao::getNumProdutos() const {
    return _numprodutos;
}
