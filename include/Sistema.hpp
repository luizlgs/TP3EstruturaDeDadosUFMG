#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include "../include/Compra.hpp"
#include "../include/Reposicao.hpp"
#include "../include/Produto.hpp"
#include "../include/Usuario.hpp"
#include <string>

class Sistema
{
private:
    Usuario *_usuarios;
    Produto *_produtos;
    Compra *_compras;
    Reposicao *_reposicoes;
    int _numUsuarios;
    int _numProdutos;
    int _numCompras;
    int _numReposicoes;


public:
    Sistema();
    ~Sistema();

    //getters
    Usuario *getUsuarios() const;
    Produto *getProdutos() const;
    Compra *getCompras() const;
    Reposicao *getReposicoes() const;


    //other methods
    void adicionarUsuario(Usuario *usuario);
    void adicionarProduto(Produto *produto);
    void adicionarCompra(Compra *compra);
    void adicionarReposicao(Reposicao *reposicao);
    int *redimensionarVetorInt(int *vetor, int numElementos);
    std::string *redimensionarVetorString(std::string *vetor, int numElementos);

    //consulta de usuarios
    void consultaUsuarios(std::string *nome_atributos, std::string *valor_atributos, int numatributos);
    void consultaUsuarios(std::string *nome_atributos, int *valor_atributos, int numatributos);


};

#endif