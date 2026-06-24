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
    int getId() const;
    std::string getNome() const;
    double getPreco() const;
    int getQuantidade() const;
    std::string getCategoria() const;
    std::string getMarca() const;
    std::string getCondicao() const;

    //other methods
    void compra(int quantidade);
    void adiciona_estoque(int quantidade);


};







#endif