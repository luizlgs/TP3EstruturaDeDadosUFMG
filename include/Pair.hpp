#ifndef PAIR_HPP
#define PAIR_HPP

class Pair {
private:
    int _indice;
    int _valor;
public:
    Pair(int indice, int valor);
    ~Pair();

    //getters
    int getIndice() const;
    int getValor() const;
};


#endif