#include "../include/Sistema.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#define TAM_MAX_INICIAL_VETORES 20

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string comando;
    Sistema sistema;


    while(std::getline(std::cin, line)){
        if (line.empty())
            continue;

        std::stringstream ss(line);
        ss >> comando;

        if(comando == "U"){
            std::string nome;
            int idade;
            std::string cidade, estado, nacionalidade;
            ss >> nome >> idade >> cidade >> estado >> nacionalidade;
            Usuario *usuario = new Usuario(nome, idade, cidade, estado, nacionalidade);
            sistema.adicionarUsuario(usuario);
            std::cout << "U " << usuario->getId() << std::endl;
        }
        else if(comando == "P"){
            std::string nome;
            double preco;
            int qtd_inicial;
            std::string categoria, marca, condicao;
            ss >> nome >> preco >> qtd_inicial >> categoria >> marca >> condicao;
            Produto *produto = new Produto(nome, preco, qtd_inicial, categoria, marca, condicao);
            sistema.adicionarProduto(produto);
            std::cout << "P " << produto->getId() << std::endl;
        }

        else if(comando == "R"){
            int timestamp;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp;

            int id_atual, quantidade_atual;
            for(int i = 0; ss >> id_atual >> quantidade_atual; i++, numprodutos++){
                if(numprodutos == tamvetores) {
                    ids_produtos = sistema.redimensionarVetorInt(ids_produtos, numprodutos);
                    quantidades = sistema.redimensionarVetorInt(quantidades, numprodutos);
                    tamvetores += 10; //aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                ids_produtos[i] = id_atual, quantidades[i] = quantidade_atual;
                    
            }

            Reposicao *reposicao = new Reposicao(timestamp, ids_produtos, quantidades, numprodutos);
            sistema.adicionarReposicao(reposicao);
            std::cout << "R " << reposicao->getId() << std::endl;

        }

        else if(comando == "C"){
            int timestamp, idUsuario;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp >> idUsuario;

            int id_atual, quantidade_atual;
            for(int i = 0; ss >> id_atual >> quantidade_atual; i++, numprodutos++){
                if(numprodutos == tamvetores) {
                    ids_produtos = sistema.redimensionarVetorInt(ids_produtos, numprodutos);
                    quantidades = sistema.redimensionarVetorInt(quantidades, numprodutos);
                    tamvetores += 10; //aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                else
                    ids_produtos[i] = id_atual, quantidades[i] = quantidade_atual;
            }

            Compra *compra = new Compra(timestamp, idUsuario, ids_produtos, quantidades, numprodutos);
            sistema.adicionarCompra(compra);
            std::cout << "C " << compra->getId() << std::endl;

        }

        else if(comando == "LU") {
            int tam_atributos_string = TAM_MAX_INICIAL_VETORES, numatributos_string = 0;
            std::string *nome_atributos_string = new std::string[tam_atributos_string]; //para nome, cidade, estado e nacionalidade
            std::string *valor_atributos_string = new std::string[tam_atributos_string]; //respectivos valores
            
            int tam_atributos_int = TAM_MAX_INICIAL_VETORES, numatributos_int = 0;
            std::string *nome_atributos_int = new std::string[tam_atributos_int]; //para id e idade
            int *valor_atributos_int = new int[tam_atributos_int]; //respectivos valores

            std::string atributo;
            while(ss >> atributo){
                if(atributo == "nome" || atributo == "cidade" || atributo == "estado" || atributo == "nacionalidade") {
                    std::string valor;
                    ss >> valor;
                    if(numatributos_string == tam_atributos_string) {
                        nome_atributos_string = sistema.redimensionarVetorString(nome_atributos_string, numatributos_string);
                        valor_atributos_string = sistema.redimensionarVetorString(valor_atributos_string, numatributos_string);
                        tam_atributos_string += 10; //aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                    }
                    nome_atributos_string[numatributos_string] = atributo;
                    valor_atributos_string[numatributos_string] = valor;
                    numatributos_string++;
                }
                else if(atributo == "id" || atributo == "idade") {
                    int valor;
                    ss >> valor;
                    if(numatributos_int == tam_atributos_int) {
                        nome_atributos_int = sistema.redimensionarVetorString(nome_atributos_int, numatributos_int);
                        valor_atributos_int = sistema.redimensionarVetorInt(valor_atributos_int, numatributos_int);
                        tam_atributos_int += 10; //aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                    }
                    nome_atributos_int[numatributos_int] = atributo;
                    valor_atributos_int[numatributos_int] = valor;
                    numatributos_int++;
                }
            }

            

        }
    }
}