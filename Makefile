CXX = g++

# flags de compilação: 
# -Wall e -Wextra ativam avisos de erro comuns
# -std=c++17 define a versão do C++
# -Iinclude diz ao compilador onde procurar os arquivos .hpp
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# diretórios do projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# nome do executável final
TARGET = $(BIN_DIR)/tp3.out

# Encontra os arquivos .cpp na pasta src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Cria a lista de arquivos .o na pasta obj
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão (executada ao rodar apenas 'make')
all: $(TARGET)

# linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# compilar cada arquivo objeto .o a partir do respectivo .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# limpar o projeto (remove os .o e o executável)
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/tp3.out

# Declara que all e clean não são arquivos reais
.PHONY: all clean