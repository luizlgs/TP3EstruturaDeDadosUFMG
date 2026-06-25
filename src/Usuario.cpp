#include "../include/Usuario.hpp"

int Usuario::_contador = 0;

Usuario::Usuario(std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade) : 
_nome(nome), _idade(idade), _cidade(cidade), _estado(estado), _nacionalidade(nacionalidade), _qtd_produtos(0) {
    _id = _contador;
    _contador++;
}

Usuario::Usuario() : _nome(""), _idade(0), _cidade(""), _estado(""), _nacionalidade(""), _qtd_produtos(0) {}

Usuario::~Usuario(){}

int Usuario::getId() const {
    return _id;
}

std::string Usuario::getNome() const {
    return _nome;
}

int Usuario::getIdade() const {
    return _idade;
}

std::string Usuario::getCidade() const {
    return _cidade;
}

std::string Usuario::getEstado() const {
    return _estado;
}

std::string Usuario::getNacionalidade() const {
    return _nacionalidade;
}

int Usuario::getQtdProdutos() const{
    return _qtd_produtos;
}


//other methods
void Usuario::adicionarProduto(int qtd){
    _qtd_produtos+=qtd;
}