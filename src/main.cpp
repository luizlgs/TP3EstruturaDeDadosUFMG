#include "../include/Sistema.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#define TAM_MAX_INICIAL_VETORES 20

int main()
{
    std::string line;
    std::string comando;
    Sistema sistema;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        ss >> comando;

        if (comando == "U")
        {
            std::string nome;
            int idade;
            std::string cidade, estado, nacionalidade;
            ss >> nome >> idade >> cidade >> estado >> nacionalidade;
            Usuario *usuario = new Usuario(nome, idade, cidade, estado, nacionalidade);
            sistema.adicionarUsuario(usuario);
            std::cout << "U " << usuario->getId() << std::endl;
        }
        else if (comando == "P")
        {
            std::string nome;
            double preco;
            int qtd_inicial;
            std::string categoria, marca, condicao;
            ss >> nome >> preco >> qtd_inicial >> categoria >> marca >> condicao;
            Produto *produto = new Produto(nome, preco, qtd_inicial, categoria, marca, condicao);
            sistema.adicionarProduto(produto);
            std::cout << "P " << produto->getId() << std::endl;
        }

        else if (comando == "R")
        {
            int timestamp;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp;

            int id_atual, quantidade_atual;
            for (int i = 0; ss >> id_atual >> quantidade_atual; i++, numprodutos++)
            {
                if (numprodutos == tamvetores)
                {
                    ids_produtos = sistema.redimensionarVetorInt(ids_produtos, numprodutos);
                    quantidades = sistema.redimensionarVetorInt(quantidades, numprodutos);
                    tamvetores += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                ids_produtos[i] = id_atual, quantidades[i] = quantidade_atual;
            }

            Reposicao *reposicao = new Reposicao(timestamp, ids_produtos, quantidades, numprodutos);
            sistema.adicionarReposicao(reposicao);
            std::cout << "R " << reposicao->getId() << std::endl;
        }

        else if (comando == "C")
        {
            int timestamp, idUsuario;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp >> idUsuario;

            int id_atual, quantidade_atual;
            bool valid = true;
            for (int i = 0; ss >> id_atual >> quantidade_atual; i++, numprodutos++) {
                if (numprodutos == tamvetores)
                {
                    ids_produtos = sistema.redimensionarVetorInt(ids_produtos, numprodutos);
                    quantidades = sistema.redimensionarVetorInt(quantidades, numprodutos);
                    tamvetores += 10;
                }
                ids_produtos[i] = id_atual;
                quantidades[i] = quantidade_atual;

                // busca o produto pelo id para verificar estoque
                Produto **prods = sistema.getProdutos();
                int numProds = sistema.getNumProdutos();
                for (int j = 0; j < numProds; j++) {
                    if (prods[j]->getId() == id_atual)
                    {
                        if (quantidade_atual > prods[j]->getQuantidade())
                            valid = false;
                        break;
                    }
                }
            }

            if (!valid)
            {
                std::cout << "C INV" << std::endl;
                delete[] ids_produtos;
                delete[] quantidades;
                continue;
            }

            Compra *compra = new Compra(timestamp, idUsuario, ids_produtos, quantidades, numprodutos);
            sistema.adicionarCompra(compra);
            std::cout << "C " << compra->getId() << std::endl;
        }

        else if (comando == "LU")
        {
            int tam_atributos = TAM_MAX_INICIAL_VETORES, num_atributos = 0;
            std::string *nome_atributos = new std::string[tam_atributos];  // nome dos atributos requisitados
            std::string *valor_atributos = new std::string[tam_atributos]; // respectivos valores

            std::string atributo;
            while (ss >> atributo)
            {
                std::string valor;
                ss >> valor;
                if (num_atributos == tam_atributos)
                {
                    nome_atributos = sistema.redimensionarVetorString(nome_atributos, num_atributos);
                    valor_atributos = sistema.redimensionarVetorString(valor_atributos, num_atributos);
                    tam_atributos += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                nome_atributos[num_atributos] = atributo;
                valor_atributos[num_atributos] = valor;
                num_atributos++;
            }

            sistema.consultaUsuarios(nome_atributos, valor_atributos, num_atributos);
            delete[] nome_atributos;
            delete[] valor_atributos;
        }

        else if (comando == "LP")
        {
            int tam_atributos = TAM_MAX_INICIAL_VETORES, num_atributos = 0;
            std::string *nome_atributos = new std::string[tam_atributos];  // nome dos atributos requisitados
            std::string *valor_atributos = new std::string[tam_atributos]; // respectivos valores

            std::string atributo;
            while (ss >> atributo)
            {
                std::string valor;
                ss >> valor;
                if (num_atributos == tam_atributos)
                {
                    nome_atributos = sistema.redimensionarVetorString(nome_atributos, num_atributos);
                    valor_atributos = sistema.redimensionarVetorString(valor_atributos, num_atributos);
                    tam_atributos += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                nome_atributos[num_atributos] = atributo;
                valor_atributos[num_atributos] = valor;
                num_atributos++;
            }
            sistema.consultaProdutos(nome_atributos, valor_atributos, num_atributos);
            delete[] nome_atributos;
            delete[] valor_atributos;
        }

        else if (comando == "LC")
        {
            int tam_atributos = TAM_MAX_INICIAL_VETORES, num_atributos = 0;
            std::string *nome_atributos = new std::string[tam_atributos];  // nome dos atributos requisitados
            std::string *valor_atributos = new std::string[tam_atributos]; // respectivos valores

            std::string atributo;
            while (ss >> atributo)
            {
                std::string valor;
                ss >> valor;
                if (num_atributos == tam_atributos)
                {
                    nome_atributos = sistema.redimensionarVetorString(nome_atributos, num_atributos);
                    valor_atributos = sistema.redimensionarVetorString(valor_atributos, num_atributos);
                    tam_atributos += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                nome_atributos[num_atributos] = atributo;
                valor_atributos[num_atributos] = valor;
                num_atributos++;
            }

            sistema.consultaCompras(nome_atributos, valor_atributos, num_atributos);
            delete[] nome_atributos;
            delete[] valor_atributos;
        }

        else if (comando == "LR")
        {
            int tam_atributos = TAM_MAX_INICIAL_VETORES, num_atributos = 0;
            std::string *nome_atributos = new std::string[tam_atributos];  // nome dos atributos requisitados
            std::string *valor_atributos = new std::string[tam_atributos]; // respectivos valores

            std::string atributo;
            while (ss >> atributo)
            {
                std::string valor;
                ss >> valor;
                if (num_atributos == tam_atributos)
                {
                    nome_atributos = sistema.redimensionarVetorString(nome_atributos, num_atributos);
                    valor_atributos = sistema.redimensionarVetorString(valor_atributos, num_atributos);
                    tam_atributos += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                nome_atributos[num_atributos] = atributo;
                valor_atributos[num_atributos] = valor;
                num_atributos++;
            }

            sistema.consultaReposicoes(nome_atributos, valor_atributos, num_atributos);
            delete[] nome_atributos;
            delete[] valor_atributos;
        }
    }
}