#include "../include/Sistema.hpp"

int main(){
    std::string line;
    std::string comando;
    Sistema sistema;

    while (std::getline(std::cin, line)){
        if (line.empty())
            continue;

        std::stringstream ss(line);
        ss >> comando;

        if (comando == "U"){
            std::string nome;
            int idade;
            std::string cidade, estado, nacionalidade;
            ss >> nome >> idade >> cidade >> estado >> nacionalidade;
            Usuario *usuario = new Usuario(nome, idade, cidade, estado, nacionalidade);
            sistema.adicionarUsuario(usuario);
            std::cout << "U " << usuario->getId() << std::endl;
        }
        else if (comando == "P"){
            std::string nome;
            double preco;
            int qtd_inicial;
            std::string categoria, marca, condicao;
            ss >> nome >> preco >> qtd_inicial >> categoria >> marca >> condicao;
            Produto *produto = new Produto(nome, preco, qtd_inicial, categoria, marca, condicao);
            sistema.adicionarProduto(produto);
            std::cout << "P " << produto->getId() << std::endl;
        }

        else if (comando == "R"){
            int timestamp;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp;

            int id_atual, quantidade_atual;
            for (int i = 0; ss >> id_atual >> quantidade_atual; i++, numprodutos++){
                if (numprodutos == tamvetores){
                    sistema.redimensionar<int>(ids_produtos, numprodutos);
                    sistema.redimensionar<int>(quantidades, numprodutos);
                    tamvetores += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
                }
                ids_produtos[i] = id_atual, quantidades[i] = quantidade_atual;
            }

            Reposicao *reposicao = new Reposicao(timestamp, ids_produtos, quantidades, numprodutos);
            sistema.adicionarReposicao(reposicao);
            std::cout << "R " << reposicao->getId() << std::endl;
        }

        else if (comando == "C"){
            int timestamp, idUsuario;
            int *ids_produtos = nullptr, *quantidades = nullptr, tamvetores = TAM_MAX_INICIAL_VETORES, numprodutos = 0;
            ids_produtos = new int[tamvetores];
            quantidades = new int[tamvetores];
            ss >> timestamp >> idUsuario;

            bool validacao_compra = true;
            int id_atual, quantidade_atual;
            for (int i = 0; ss >> id_atual >> quantidade_atual && validacao_compra; i++, numprodutos++) {
                // busca o produto pelo id para verificar se a quantidade é valida de acordo com o estoque
                for (int j = 0; j < *sistema.getNumProdutos(); j++){
                    if (sistema.getProdutos()[j]->getId() == id_atual){
                        if (quantidade_atual > sistema.getProdutos()[j]->getQuantidade())
                            validacao_compra = false;
                        break;
                    }
                }

                if (numprodutos == tamvetores){
                    sistema.redimensionar<int>(ids_produtos, numprodutos);
                    sistema.redimensionar<int>(quantidades, numprodutos);
                    tamvetores += 10;
                }
                ids_produtos[i] = id_atual;
                quantidades[i] = quantidade_atual;
            }

            if (!validacao_compra){
                    std::cout << "C INV" << std::endl;
                    delete[] ids_produtos;
                    delete[] quantidades;
                    continue;
            }

            Compra *compra = new Compra(timestamp, idUsuario, ids_produtos, quantidades, numprodutos);
            sistema.adicionarCompra(compra);
            std::cout << "C " << compra->getId() << std::endl;
        }

        else if (comando == "LU"){
            std::string **valores = sistema.coletaFiltros(ss);
            sistema.consultaUsuarios(valores[0], valores[1], std::stoi(valores[2][0]));
        }

        else if (comando == "LP"){
            std::string **valores = sistema.coletaFiltros(ss);
            sistema.consultaProdutos(valores[0], valores[1], std::stoi(valores[2][0]));
        }

        else if (comando == "LC"){
            std::string **valores = sistema.coletaFiltros(ss);
            sistema.consultaCompras(valores[0], valores[1], std::stoi(valores[2][0]));
        }

        else if (comando == "LR"){
            std::string **valores = sistema.coletaFiltros(ss);
            sistema.consultaReposicoes(valores[0], valores[1], std::stoi(valores[2][0]));
        }
    }
}