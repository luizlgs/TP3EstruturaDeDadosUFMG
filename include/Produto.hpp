#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
#include <stdexcept>

class Produto
{
private:
    static int _contador;
    int _id;
    std::string _nome;
    double _preco;
    int _quantidade;
    std::string _categoria, _marca, _condicao;

public:
    Produto(std::string _nome, double _preco, int _quantidade, std::string _categoria, std::string _marca, std::string _condicao);
    Produto();
    ~Produto();

    //getters
    int getId();
    std::string getNome();
    double getPreco();
    int getQuantidade();
    std::string getCategoria();
    std::string getMarca();
    std::string getCondicao();

    //other methods
    void compra(int quantidade);


};







#endif