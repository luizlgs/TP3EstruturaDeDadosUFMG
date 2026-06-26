#ifndef PAIR_HPP
#define PAIR_HPP
#include <string>

class Pair {
private:
    int _indice;
    std::string _valor;
public:
    Pair(int indice, std::string valor);
    Pair();
    ~Pair();

    bool operator<(const Pair &p) const{
        if(this->_valor < p.getValor()){
            return true;
        }
        return false;
    }

    //getters
    int getIndice() const;
    std::string getValor() const;
};


#endif