#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>

using Maze = std::vector<std::vector<char>>;

struct Position {
    int row;
    int col;
};

Maze maze;
int num_rows;
int num_cols;
Position start_pos;
std::stack<Position> path_stack;

// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return {-1, -1};
    }
    
    file >> num_rows >> num_cols;
    maze.resize(num_rows, std::vector<char>(num_cols));
    Position start{-1, -1};
    
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            file >> maze[i][j];
            if (maze[i][j] == 'e') {
                start = {i, j};
                path_stack.push(start);
            }
        }
    }
    
    file.close();
    return start;
}

// Função para imprimir o labirinto corretamente
void print_maze(const Position& current) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Delay para visualização

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            if (i == current.row && j == current.col) {
                std::cout << 'o' << ' '; // Marca a posição atual com 'o'
            } else {
                std::cout << maze[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    return (row >= 0 && row < num_rows && col >= 0 && col < num_cols && (maze[row][col] == 'x' || maze[row][col] == 's'));
}

// Função principal para a busca automática da saída
bool walk() {
    while (!path_stack.empty()) {
        Position current = path_stack.top();
        path_stack.pop();

        // Se encontrou a saída, termina a busca
        if (maze[current.row][current.col] == 's') {
            print_maze(current);
            std::cout << "Saída encontrada!" << std::endl;
            return true;
        }

        // Marca a posição anterior como visitada ('.')
        if (maze[current.row][current.col] != 'e') {
            maze[current.row][current.col] = '.'; 
        }

        // Exibe o labirinto atualizado
        print_maze(current);

        // Movimentos: baixo, direita, cima, esquerda
        std::vector<Position> moves = {
            {current.row + 1, current.col}, // Baixo
            {current.row, current.col + 1}, // Direita
            {current.row - 1, current.col}, // Cima
            {current.row, current.col - 1}  // Esquerda
        };

        for (const auto& move : moves) {
            if (is_valid_position(move.row, move.col)) {
                path_stack.push(move);
            }
        }
    }
    return false;
}

int main() {
    start_pos = load_maze("labirinto.txt");
    if (start_pos.row == -1 || start_pos.col == -1) {
        std::cerr << "Posição inicial não encontrada no labirinto." << std::endl;
        return 1;
    }
    
    bool found_exit = walk();
    if (!found_exit) {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }
    
    return 0;
}
