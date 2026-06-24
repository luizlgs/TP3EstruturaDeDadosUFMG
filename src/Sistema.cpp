#include "../include/Sistema.hpp"

Sistema::Sistema() : 
_usuarios(nullptr), _produtos(nullptr), _compras(nullptr), _reposicoes(nullptr), 
_numUsuarios(0), _numProdutos(0), _numCompras(0), _numReposicoes(0) {}

Sistema::~Sistema() {
    delete[] _usuarios;
    delete[] _produtos;
    delete[] _compras;
    delete[] _reposicoes;
}

bool Sistema::isDigit(std::string s){
    for(char c : s){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

//getters
Usuario **Sistema::getUsuarios() const {
    return _usuarios;
}

Produto **Sistema::getProdutos() const {
    return _produtos;
}

Compra **Sistema::getCompras() const {
    return _compras;
}

Reposicao **Sistema::getReposicoes() const {
    return _reposicoes;
}

int Sistema::getNumProdutos() const {
    return _numProdutos;
}

//other methods
void Sistema::insertionSortInt(int *ids, int *qtds, int n) {
    for(int a = 1; a < n; a++){
        int keyId = ids[a], keyQtd = qtds[a], b = a - 1;
        while(b >= 0 && ids[b] > keyId){
            ids[b+1] = ids[b]; qtds[b+1] = qtds[b]; b--;
        }
        ids[b+1] = keyId; qtds[b+1] = keyQtd;
    }
}


void Sistema::adicionarUsuario(Usuario *usuario) {
    Usuario **novoArray = new Usuario*[_numUsuarios + 1];
    for (int i=0; i<_numUsuarios; i++) {
        novoArray[i] = _usuarios[i];
    }
    novoArray[_numUsuarios] = usuario;

    delete[] _usuarios;
    _usuarios = novoArray;
    _numUsuarios++;
}

void Sistema::adicionarProduto(Produto *produto) {
    Produto **novoArray = new Produto*[_numProdutos + 1];
    for (int i=0; i<_numProdutos; i++) {
        novoArray[i] = _produtos[i];
    }
    novoArray[_numProdutos] = produto;
    delete[] _produtos;
    _produtos = novoArray;
    _numProdutos++;
}

void Sistema::adicionarCompra(Compra *compra) {
    Compra **novoArray = new Compra*[_numCompras + 1];
    for (int i=0; i<_numCompras; i++) {
        novoArray[i] = _compras[i];
    }
    novoArray[_numCompras] = compra;
    delete[] _compras;
    _compras = novoArray;
    _numCompras++;

    for(int k = 0; k < compra->getNumProdutos(); k++){
    int idProd = compra->getIdProdutos()[k];
    int qtd = compra->getQuantidades()[k];
    for(int i = 0; i < _numProdutos; i++){
        if(_produtos[i]->getId() == idProd){
            _produtos[i]->compra(qtd);
            break;
            }
        }
    }
}

void Sistema::adicionarReposicao(Reposicao *reposicao) {
    Reposicao **novoArray = new Reposicao*[_numReposicoes + 1];
    for (int i=0; i<_numReposicoes; i++) {
        novoArray[i] = _reposicoes[i];
    }
    novoArray[_numReposicoes] = reposicao;
    delete[] _reposicoes;
    _reposicoes = novoArray;
    _numReposicoes++;

    for(int k = 0; k < reposicao->getNumProdutos(); k++){
    int idProd = reposicao->getIdProdutos()[k];
    int qtd = reposicao->getQuantidades()[k];
    for(int i = 0; i < _numProdutos; i++){
        if(_produtos[i]->getId() == idProd){
            _produtos[i]->adiciona_estoque(qtd);
            break;
        }
    }
}
}

void Sistema::consultaUsuarios(std::string *nome_atributos, std::string *valor_atributos, int numatributos) {
    int compatibilidade = 0, resutados = 1;
    for(int i = 0; i < _numUsuarios; i++){
        for(int j = 0; j < numatributos; j++){
            if(nome_atributos[j] == "id" && _usuarios[i]->getId() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "idade" && _usuarios[i]->getIdade() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "nome" && _usuarios[i]->getNome() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "cidade" && _usuarios[i]->getCidade() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "estado" && _usuarios[i]->getEstado() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "nacionalidade" && _usuarios[i]->getNacionalidade() == valor_atributos[j])
                compatibilidade++;
        }
        if(compatibilidade == numatributos){
            std::cout << "LU resultado_" << resutados << " usuario " << _usuarios[i]->getId() << " " << _usuarios[i]->getNome() << " "  <<
            _usuarios[i]->getIdade() << " " << _usuarios[i]->getCidade() << " " << _usuarios[i]->getEstado() << " " 
            << _usuarios[i]->getNacionalidade() << std::endl;

            int idUsuario = _usuarios[i]->getId();
            int *idsProd = new int[_numCompras * 10 + 1];
            int *qtdsProd = new int[_numCompras * 10 + 1];
            int numProd = 0;

            for(int c = 0; c < _numCompras; c++){
                if(_compras[c]->getIdUsuario() != idUsuario) continue;
                for(int k = 0; k < _compras[c]->getNumProdutos(); k++){
                    int idP = _compras[c]->getIdProdutos()[k];
                    int qtd = _compras[c]->getQuantidades()[k];
                    bool achou = false;
                    for(int m = 0; m < numProd; m++){
                        if(idsProd[m] == idP){ qtdsProd[m] += qtd; achou = true; break; }
                    }
                    if(!achou){ idsProd[numProd] = idP; qtdsProd[numProd] = qtd; numProd++; }
                }
            }

            if(numProd > 0){
                insertionSortInt(idsProd, qtdsProd, numProd);
                for(int m = 0; m < numProd; m++){
                    std::cout << "produto_" << m+1 << " " << idsProd[m] << " " << qtdsProd[m];
                    if(m+1 != numProd) std::cout << " ";
                }
                std::cout << std::endl;
            }
            delete[] idsProd;
            delete[] qtdsProd;
            resutados++;
        }
        compatibilidade = 0;
    }
    if(resutados == 1)
        std::cout << "LU VAZIO" << std::endl;
}

void Sistema::consultaProdutos(std::string *nome_atributos, std::string *valor_atributos, int numatributos){
    int compatibilidade = 0, resutados = 1;
    for(int i = 0; i < _numProdutos; i++){
        for(int j = 0; j < numatributos; j++){
            if(nome_atributos[j] == "id" && _produtos[i]->getId() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "nome" && _produtos[i]->getNome() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "categoria" && _produtos[i]->getCategoria() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "marca" && _produtos[i]->getMarca() == valor_atributos[j])
                compatibilidade++;
            else if(nome_atributos[j] == "condicao" && _produtos[i]->getCondicao() == valor_atributos[j])
                compatibilidade++;
        }
        if(compatibilidade == numatributos){
            std::cout << "LP resultado_" << resutados << " produto " << _produtos[i]->getId() << " " << _produtos[i]->getNome() << " " 
            << std::fixed << std::setprecision(2) << _produtos[i]->getPreco() << " " << _produtos[i]->getQuantidade() << " " 
            << _produtos[i]->getCategoria() << " " << _produtos[i]->getMarca() << " " << _produtos[i]->getCondicao() << std::endl;

            int idProduto = _produtos[i]->getId();
            int *idsUsuario = new int[_numCompras + 1];
            int *qtdsUsuario = new int[_numCompras + 1];
            int numUsuarios = 0;

            for(int c = 0; c < _numCompras; c++){
                for(int k = 0; k < _compras[c]->getNumProdutos(); k++){
                    if(_compras[c]->getIdProdutos()[k] != idProduto) continue;
                    int idU = _compras[c]->getIdUsuario();
                    int qtd = _compras[c]->getQuantidades()[k];
                    bool achou = false;
                    for(int m = 0; m < numUsuarios; m++){
                        if(idsUsuario[m] == idU){ qtdsUsuario[m] += qtd; achou = true; break; }
                    }
                    if(!achou){ idsUsuario[numUsuarios] = idU; qtdsUsuario[numUsuarios] = qtd; numUsuarios++; }
                }
            }

            if(numUsuarios > 0){
                insertionSortInt(idsUsuario, qtdsUsuario, numUsuarios);
                for(int m = 0; m < numUsuarios; m++){
                    std::cout << "usuario_" << m+1 << " " << idsUsuario[m] << " " << qtdsUsuario[m];
                    if(m+1 != numUsuarios) std::cout << " ";
                }
                std::cout << std::endl;
            }
            delete[] idsUsuario;
            delete[] qtdsUsuario;
            resutados++;
        }
        compatibilidade = 0;
    }
    if(resutados == 1)
        std::cout << "LP VAZIO" << std::endl;
}

void Sistema::consultaCompras(std::string *nome_atributos, std::string *valor_atributos, int numatributos){
    int compatibilidade = 0, resutados = 1;
    for(int i=0; i<_numCompras; i++){
        for(int j=0; j<numatributos; j++){
            if(nome_atributos[j] == "id" && _compras[i]->getId() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "timestamp" && _compras[i]->getTimestamp() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "id_usuario" && _compras[i]->getIdUsuario() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "id_produto"){
                int idBuscado = std::stoi(valor_atributos[j]);
                for(int k = 0; k < _compras[i]->getNumProdutos(); k++){
                    if(_compras[i]->getIdProdutos()[k] == idBuscado){
                    compatibilidade++;
                    break;
                    }
                }
}
        }
        if(compatibilidade == numatributos){
            std::cout << "LC resultado_" << resutados << " compra " << _compras[i]->getId() << " timestamp " << _compras[i]->getTimestamp() 
            << " usuario " << _compras[i]->getIdUsuario() << std::endl;
            for(int k=0; k<_compras[i]->getNumProdutos(); k++){
                std::cout << "produto_" << k+1 << " " << _compras[i]->getIdProdutos()[k] << " " << _compras[i]->getQuantidades()[k];
                if(k+1 != _compras[i]->getNumProdutos()) std::cout << " ";
                else  std::cout << std:: endl;
            }
            resutados++;
        }
        compatibilidade = 0;
    }
    if(resutados == 1)
    std::cout << "LC VAZIO" << std::endl;
}

void Sistema::consultaReposicoes(std::string *nome_atributos, std::string *valor_atributos, int numatributos){
    int compatibilidade = 0, resutados = 1;
    for(int i=0; i<_numReposicoes; i++){
        for(int j=0; j<numatributos; j++){
            if(nome_atributos[j] == "id" && _reposicoes[i]->getId() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "timestamp" && _reposicoes[i]->getTimestamp() == std::stoi(valor_atributos[j]))
                compatibilidade++;
            else if(nome_atributos[j] == "id_produto"){
                int idBuscado = std::stoi(valor_atributos[j]);
                for(int k = 0; k < _reposicoes[i]->getNumProdutos(); k++){
                    if(_reposicoes[i]->getIdProdutos()[k] == idBuscado){
                        compatibilidade++;
                        break;
                    }
                }
}
        }
        if(compatibilidade == numatributos){
            std::cout << "LR resultado_" << resutados << " reposicao " << _reposicoes[i]->getId() << " timestamp " 
            << _reposicoes[i]->getTimestamp() << std::endl;
            for(int k=0; k<_reposicoes[i]->getNumProdutos(); k++){
                std::cout << "produto_" << k+1 << " " << _reposicoes[i]->getIdProdutos()[k] << " " << _reposicoes[i]->getQuantidades()[k];
                if(k+1 != _reposicoes[i]->getNumProdutos()) std::cout << " ";
                else  std::cout << std:: endl;
            }
            resutados++;
        }
        compatibilidade = 0;
    }
    if(resutados == 1)
    std::cout << "LR VAZIO" << std::endl;
}




//redimensionamento de vetores 
//-------------------------------------------------------------------------------------------
int *Sistema::redimensionarVetorInt(int *vetor, int numElementos) {
    int *novoVetor = new int[numElementos + 10];
    for (int i = 0; i < numElementos; i++) {
        novoVetor[i] = vetor[i];
    }
    delete[] vetor;
    return novoVetor;
}

std::string *Sistema::redimensionarVetorString(std::string *vetor, int numElementos) {
    std::string *novoVetor = new std::string[numElementos + 10];
    for (int i = 0; i < numElementos; i++) {
        novoVetor[i] = vetor[i];
    }
    delete[] vetor;
    return novoVetor;
}

//-------------------------------------------------------------------------------------------
