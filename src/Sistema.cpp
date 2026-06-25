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

int Sistema::isIn(int idElemento, int arr[], int tamarr){ //retorna -1 se nao estiver no vetor e o indice no vetor se estiver (indice da primeira aparição)
    for(int i=0; i<tamarr; i++){
        if(idElemento == arr[i]){
            return i;
        }
    }
    return -1;
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

void Sistema::insertionSortInt(int *ids, int *qtds, int n) {
    for(int i = 1; i < n; i++){
        int keyId = ids[i], keyQtd = qtds[i], j = i - 1;
        while(j >= 0 && ids[j] > keyId){
            ids[j+1] = ids[j]; qtds[j+1] = qtds[j]; j--;
        }
        ids[j+1] = keyId; qtds[j+1] = keyQtd;
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
    _usuarios[compra->getIdUsuario()]->adicionarProduto(compra->getNumProdutos());
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

            int idUsuario = _usuarios[i]->getId(), quantidade_prod = _usuarios[i]->getQtdProdutos() > 0 ? _usuarios[i]->getQtdProdutos() : 1;
            int *idsProd = new int[quantidade_prod];
            int *qtdsProd = new int[quantidade_prod];
            int numProd = 0; //indice de acesso em idsPro e qtsProd

            for (int j = 0; j < _numCompras; j++){
                if (_compras[j]->getIdUsuario() != idUsuario)
                    continue;
                for (int k = 0; k < _compras[j]->getNumProdutos(); k++){
                    int produto_ja_existe = isIn(_compras[j]->getIdProdutos()[k], idsProd, numProd); // guarda o indice se o elemento esta no array
                    if (produto_ja_existe == -1){ // retorna -1 se nao estiver no array
                        idsProd[numProd] = _compras[j]->getIdProdutos()[k];
                        qtdsProd[numProd] = _compras[j]->getQuantidades()[k];
                        numProd++;
                    }
                    else{
                        qtdsProd[produto_ja_existe] += _compras[j]->getQuantidades()[k];
                    }
                }
            }

            if(numProd > 0){
                insertionSortInt(idsProd, qtdsProd, numProd);
                for(int j = 0; j<numProd; j++){
                    std::cout << "produto_" << j+1 << " " << idsProd[j] << " " << qtdsProd[j];
                    if(j+1 != numProd) std::cout << " ";
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

            for(int j = 0; j < _numCompras; j++){
                    int pos_produto_compras = isIn(idProduto, _compras[j]->getIdProdutos(), _compras[j]->getNumProdutos());
                    if(pos_produto_compras == -1){continue;}
                    int pos_usuario_idsUsuario = isIn(_compras[j]->getIdUsuario(), idsUsuario, numUsuarios);
                    if(pos_usuario_idsUsuario == -1){
                        idsUsuario[numUsuarios] = _compras[j]->getIdUsuario();
                        qtdsUsuario[numUsuarios] = _compras[j]->getQuantidades()[pos_produto_compras];
                        numUsuarios++;
                        continue;
                    }
                    qtdsUsuario[pos_usuario_idsUsuario] += _compras[j]->getQuantidades()[pos_produto_compras];
            }

            if(numUsuarios > 0){
                insertionSortInt(idsUsuario, qtdsUsuario, numUsuarios);
                for(int j = 0; j < numUsuarios; j++){
                    std::cout << "usuario_" << j+1 << " " << idsUsuario[j] << " " << qtdsUsuario[j];
                    if(j+1 != numUsuarios) std::cout << " ";
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

std::string **Sistema::coletaFiltros(std::stringstream& ss){
    int tam_atributos = TAM_MAX_INICIAL_VETORES, num_atributos = 0;
    std::string *nome_atributos = new std::string[tam_atributos];  // nome dos atributos requisitados
    std::string *valor_atributos = new std::string[tam_atributos]; // respectivos valores

    std::string atributo;
    while (ss >> atributo){
        std::string valor;
        ss >> valor;
        if (num_atributos == tam_atributos){
            nome_atributos = redimensionarVetorString(nome_atributos, num_atributos);
            valor_atributos = redimensionarVetorString(valor_atributos, num_atributos);
            tam_atributos += 10; // aumenta o valor de 10 em 10 para evitar desperdicio de memoria e custo computacional
        }
        nome_atributos[num_atributos] = atributo;
        valor_atributos[num_atributos] = valor;
        num_atributos++;
    }
    std::string **valores = new std::string*[3];
    valores[0] = nome_atributos;
    valores[1] = valor_atributos;
    valores[2] = new std::string[1];
    valores[2][0] = std::to_string(num_atributos);

    return valores;
}