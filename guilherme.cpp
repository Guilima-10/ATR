#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>

// Representação do labirinto
using Maze = std::vector<std::vector<char>>;

// Estrutura para representar uma posição no labirinto
struct Position {
    int row; //linha da posição
    int col; //coluna da posição
};

// Variáveis globais
Maze maze;                //matriz do labirinto
int num_rows;             //número de linhas do labirinto
int num_cols;             //número de colunas do labirinto
std::stack<Position> valid_positions; 	//armazena posições válidas a serem exploradas

// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    std::ifstream file(file_name); //le o arquivo
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return {-1, -1};
    }

    file >> num_rows >> num_cols; //lê o número de linhas e colunas do arquivo
    file.ignore(); 	//ignora a quebra de linha no  final

    maze.resize(num_rows, std::vector<char>(num_cols)); 	//redimensiona a matriz do labirinto
    Position start_position = {-1, -1}; 	//posição inicial começa como inválida

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            file.get(maze[i][j]); 		//le todas as posiçções
            if (maze[i][j] == 'e') { 		//acha o e
                start_position = {i, j}; 	//seta a posição inicial
            }
        }
        file.ignore(); //ignora a quebra de linha no final
    }
    file.close(); //fecha o arquivo

    return start_position; //volta pra posição inicial
}

// Função para imprimir o labirinto
void print_maze() {
    //std::this_thread::sleep_for(std::chrono::milliseconds(50)); //coloca um pequeno atraso para melhor visualização
    
    for (const auto& row : maze) { //percorre todas as linhas
        for (char cell : row) { //percorre todas as colunas
            std::cout << cell << ' '; //imprime com um espaço
        }
        std::cout << '\n'; //quebra de linha ao final de cada linha
    }
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    return row >= 0 && row < num_rows && col >= 0 && col < num_cols &&  //verifica se está dentro dos limites do labirinto
           (maze[row][col] == 'x' || maze[row][col] == 's'); //verifica se é um caminho válido ou saída
}