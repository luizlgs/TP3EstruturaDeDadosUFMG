#include "../include/Produto.hpp"

int Produto::_contador = 0;

Produto::Produto(std::string nome, double preco, int quantidade, std::string categoria, std::string marca, std::string condicao) : 
_nome(nome), _preco(preco), _quantidade(quantidade), _categoria(categoria), _marca(marca), _condicao(condicao) {
    _id = _contador;
    _contador++;
}

Produto::Produto() : _nome(""), _preco(0.0), _quantidade(0), _categoria(""), _marca(""), _condicao("") {
}

Produto::~Produto(){}

//getters

int Produto::getId() const{
    return _id;
}

std::string Produto::getNome() const{
    return _nome;
}

double Produto::getPreco() const{
    return _preco;
}

int Produto::getQuantidade() const{
    return _quantidade;
}

std::string Produto::getCategoria() const{
    return _categoria;
}

std::string Produto::getMarca() const{
    return _marca;
}

std::string Produto::getCondicao() const{
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

void Produto::adiciona_estoque(int quantidade){
    _quantidade += quantidade;
}
