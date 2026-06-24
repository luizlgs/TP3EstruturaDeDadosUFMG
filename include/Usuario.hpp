#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

class Usuario
{
private:
    static int _contador;
    int _id;
    std::string _nome;
    int _idade;
    std::string _cidade, _estado, _nacionalidade;

    
public:
    Usuario(std::string nome, int idade, std::string cidade, std::string estado, std::string nacionalidade);
    Usuario();
    ~Usuario();

    //getters
    int getId() const;
    std::string getNome() const;
    int getIdade() const;
    std::string getCidade() const;
    std::string getEstado() const;
    std::string getNacionalidade() const;
    
};



#endif