#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include "../include/Compra.hpp"
#include "../include/Reposicao.hpp"
#include "../include/Produto.hpp"
#include "../include/Usuario.hpp"
#include "../include/Pair.hpp"
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#define TAM_MAX_INICIAL_VETORES 20

class Sistema {
private:
    Usuario **_usuarios; // id, nome, idade, cidade, estado, nacionalidade
    Pair *_usuarios_nome;
    Pair *_usuarios_idade;
    Pair *_usuarios_cidade;
    Pair *_usuarios_estado;
    Pair *_usuarios_nacionalidade;

    Produto **_produtos; // id, nome, categoria, marca, condicao
    Pair *_produtos_nome;
    Pair *_produtos_marca;
    Pair *_produtos_condicao;


    Compra **_compras; // id, timestamp, id_usuario, id_produto
    Pair *_compras_id_usuario;
    Pair *_compras_id_produto;


    Reposicao **_reposicoes; // id, timestamp, id_produto
    Pair *_compras_timestamp;
    Pair *_id_produto;


    int *_numUsuarios;
    int *_numProdutos;
    int *_numCompras;
    int *_numReposicoes;
    
public:
    Sistema();
    ~Sistema();

    //getters
    Usuario **getUsuarios() const;
    Produto **getProdutos() const;
    Compra **getCompras() const;
    Reposicao **getReposicoes() const;
    int *getNumProdutos() const;


    //metodos de adicao de objetos no sistema
    void adicionarUsuario(Usuario *usuario);
    void adicionarProduto(Produto *produto);
    void adicionarCompra(Compra *compra);
    void adicionarReposicao(Reposicao *reposicao);

    //algoritmo de redimensionamento para ter vetores de tamanhos dinamicos
    template <typename R>
    R redimensionar(R *vetor, int numElementos){
    R *novoVetor = new R[numElementos+10];
        for(int i = 0; i < numElementos; i++) {
            novoVetor[i] = vetor[i];
        }
        delete[] vetor;
        vetor = novoVetor;
    }

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

    //algoritmo de pesquisa binaria baseado nos pairs de um atributo (retorna o intervalo de pair que possuem o valor procurado)
    int *pesquisaPair(Pair *pairs, std::string valor, int inicio, int final);
    //algoritmo para adicionar uma pair na lista de forma ordenada
    void adicionaPair(Pair *pair, Pair pair_adicionado, int *tamPair);

};

#endif