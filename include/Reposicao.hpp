#ifndef REPOSICAO_HPP
#define REPOSICAO_HPP
#include <string>

class Reposicao
{
private:
    static int _contador;
    int _id;
    unsigned int _timestamp;
    int *_idProdutos;
    int *_quantidades;
    int _numprodutos;

public:
    Reposicao(unsigned int timestamp, int *idProdutos, int *quantidades, int numProdutos);
    Reposicao();
    ~Reposicao();

    //getters
    int getId() const;
    unsigned int getTimestamp() const;
    int *getIdProdutos() const;
    int *getQuantidades() const;
    int getNumProdutos() const;
};







#endif