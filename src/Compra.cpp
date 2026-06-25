#include "../include/Compra.hpp"

int Compra::_contador = 0;

Compra::Compra(unsigned int timestamp, int idUsuario, int *idProdutos, int *quantidades, int numProdutos) :
_timestamp(timestamp), _idUsuario(idUsuario), _idProdutos(idProdutos), _quantidades(quantidades), _numprodutos(numProdutos) {
    _id = _contador;
    _contador++;
}

Compra::Compra() : _timestamp(0), _idUsuario(0), _idProdutos(nullptr), _quantidades(nullptr), _numprodutos(0) {
    _id = _contador;
    _contador++;
}

Compra::~Compra() {
    delete[] _idProdutos;
    delete[] _quantidades;
}

int Compra::getId() const {
    return _id;
}

unsigned int Compra::getTimestamp() const {
    return _timestamp;
}

int Compra::getIdUsuario() const {
    return _idUsuario;
}

int *Compra::getIdProdutos() const {
    return _idProdutos;
}

int *Compra::getQuantidades() const {
    return _quantidades;
}

int Compra::getNumProdutos() const {
    return _numprodutos;
}

