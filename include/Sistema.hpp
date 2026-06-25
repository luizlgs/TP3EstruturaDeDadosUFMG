#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include "../include/Compra.hpp"
#include "../include/Reposicao.hpp"
#include "../include/Produto.hpp"
#include "../include/Usuario.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#define TAM_MAX_INICIAL_VETORES 20

class Sistema
{
private:
    Usuario **_usuarios;
    Produto **_produtos;
    Compra **_compras;
    Reposicao **_reposicoes;
    int _numUsuarios;
    int _numProdutos;
    int _numCompras;
    int _numReposicoes;

public:
    Sistema();
    ~Sistema();

    //getters
    Usuario **getUsuarios() const;
    Produto **getProdutos() const;
    Compra **getCompras() const;
    Reposicao **getReposicoes() const;
    int getNumProdutos() const;


    //metodos de adicao de objetos no sistema
    void adicionarUsuario(Usuario *usuario);
    void adicionarProduto(Produto *produto);
    void adicionarCompra(Compra *compra);
    void adicionarReposicao(Reposicao *reposicao);

    //algoritmo de redimimensionamento para ter vetores de tamanhos dinamicos
    int *redimensionarVetorInt(int *vetor, int numElementos);
    std::string *redimensionarVetorString(std::string *vetor, int numElementos);

    //funcao para verificar se e um digito
    bool isDigit(std::string s);

    //funcao que verifica se um elemento esta no array
    int isIn(int idElemento, int arr[], int tamarr);
    //int isIn(int idElemento, int *arr[], int tamarr);

    //funcao de consultas
    void consultaUsuarios(std::string *nome_atributos, std::string *valor_atributos, int numatributos);
    void consultaProdutos(std::string *nome_atributos, std::string *valor_atributos, int numatributos);
    void consultaCompras(std::string *nome_atributos, std::string *valor_atributos, int numatributos);
    void consultaReposicoes(std::string *nome_atributos, std::string *valor_atributos, int numatributos);

    //algoritmo de ordenacao para a consulta de usuarios e produtos
    void insertionSortInt(int *ids, int *qtds, int n);

    //coleta filtros nas consultadas que demandam diferentes atributos
    std::string **coletaFiltros(std::stringstream& ss);


};

#endif