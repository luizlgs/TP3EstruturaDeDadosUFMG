#ifndef COMPRA_HPP
#define COMPRA_HPP
#include <string>

class Compra
{
private:
    static int _contador;
    int _id;
    unsigned int _timestamp;
    int _idUsuario;
    int *_idProdutos;
    int *_quantidades;
    int _numprodutos;

public:
    Compra(unsigned int timestamp, int idUsuario, int *idProdutos, int *quantidades, int numProdutos);
    Compra();
    ~Compra();

    //getters
    int getId() const;
    unsigned int getTimestamp() const;
    int getIdUsuario() const;
    int *getIdProdutos() const;
    int *getQuantidades() const;
    int getNumProdutos() const;
    
};

#endif