#include "../include/Sistema.hpp"

Sistema::Sistema() : 
_usuarios(nullptr), _produtos(nullptr), _compras(nullptr), _reposicoes(nullptr), 
_numUsuarios(0), _numProdutos(0), _numCompras(0), _numReposicoes(0) {}

Sistema::~Sistema() {
    delete[] _usuarios;
    delete[] _produtos;
    delete[] _compras;
    delete[] _reposicoes;
}

//getters
Usuario *Sistema::getUsuarios() const {
    return _usuarios;
}

Produto *Sistema::getProdutos() const {
    return _produtos;
}

Compra *Sistema::getCompras() const {
    return _compras;
}

Reposicao *Sistema::getReposicoes() const {
    return _reposicoes;
}

//other methods
void Sistema::adicionarUsuario(Usuario *usuario) {
    Usuario *novoArray = new Usuario[_numUsuarios + 1];
    for (int i=0; i<_numUsuarios; i++) {
        novoArray[i] = _usuarios[i];
    }
    novoArray[_numUsuarios] = *usuario;
    delete[] _usuarios;
    _usuarios = novoArray;
    _numUsuarios++;
}

void Sistema::adicionarProduto(Produto *produto) {
    Produto *novoArray = new Produto[_numProdutos + 1];
    for (int i=0; i<_numProdutos; i++) {
        novoArray[i] = _produtos[i];
    }
    novoArray[_numProdutos] = *produto;
    delete[] _produtos;
    _produtos = novoArray;
    _numProdutos++;
}

void Sistema::adicionarCompra(Compra *compra) {
    Compra *novoArray = new Compra[_numCompras + 1];
    for (int i=0; i<_numCompras; i++) {
        novoArray[i] = _compras[i];
    }
    novoArray[_numCompras] = *compra;
    delete[] _compras;
    _compras = novoArray;
    _numCompras++;
}

void Sistema::adicionarReposicao(Reposicao *reposicao) {
    Reposicao *novoArray = new Reposicao[_numReposicoes + 1];
    for (int i=0; i<_numReposicoes; i++) {
        novoArray[i] = _reposicoes[i];
    }
    novoArray[_numReposicoes] = *reposicao;
    delete[] _reposicoes;
    _reposicoes = novoArray;
    _numReposicoes++;
}

void Sistema::consultaUsuarios(std::string *nome_atributos, std::string *valor_atributos, int numatributos) {
    for(int i=0; i<_numUsuarios; i++){
    }
}




//redimensionamento de vetores 
//-------------------------------------------------------------------------------------------
int *Sistema::redimensionarVetorInt(int *vetor, int numElementos) {
    int *novoVetor = new int[numElementos + 10];
    for (int i = 0; i < numElementos; i++) {
        novoVetor[i] = vetor[i];
    }
    delete[] vetor;
    return novoVetor;
}

std::string *Sistema::redimensionarVetorString(std::string *vetor, int numElementos) {
    std::string *novoVetor = new std::string[numElementos + 10];
    for (int i = 0; i < numElementos; i++) {
        novoVetor[i] = vetor[i];
    }
    delete[] vetor;
    return novoVetor;
}

//-------------------------------------------------------------------------------------------
