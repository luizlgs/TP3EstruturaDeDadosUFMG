#include "../include/Produto.hpp"

int Produto::_contador = 0;

Produto::Produto(std::string nome, double preco, int quantidade, std::string categoria, std::string marca, std::string condicao) : 
_nome(nome), _preco(preco), _quantidade(quantidade), _categoria(categoria), _marca(marca), _condicao(condicao) {
    _id = _contador;
    _contador++;
}

Produto::Produto() : _nome(""), _preco(0.0), _quantidade(0), _categoria(""), _marca(""), _condicao("") {
    _id = _contador;
    _contador++;
}

//getters

int Produto::getId() {
    return _id;
}

std::string Produto::getNome() {
    return _nome;
}

double Produto::getPreco() {
    return _preco;
}

int Produto::getQuantidade() {
    return _quantidade;
}

std::string Produto::getCategoria() {
    return _categoria;
}

std::string Produto::getMarca() {
    return _marca;
}

std::string Produto::getCondicao() {
    return _condicao;
}

//other methods

void Produto::compra(int quantidade) {
    if (quantidade <= _quantidade) {
        _quantidade -= quantidade;
    } else {
        throw std::invalid_argument("Quantidade insuficiente em estoque.");
    }
}
