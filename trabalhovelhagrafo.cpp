#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    char player;
    vector<Node*> children;
};

//imprime tabuleiro
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

//criar nó
Node* createNode(char player) {
    Node* newNode = new Node;
    newNode->player = player;
    return newNode;
}

//constrói grafo
void buildGameGraph(Node* currentNode, vector<vector<char>>& board, char currentPlayer);

//verifica vencedor
bool checkWin(char player, const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

//verifica empate
bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ')
                return false;
        }
    }
    return true;
}

//função principal para jogar
void playGame(Node* currentNode, vector<vector<char>>& board, char currentPlayer) {
    printBoard(board);

    if (checkWin('X', board)) {
        cout << "Jogador X venceu!" << endl;
        return;
    } else if (checkWin('O', board)) {
        cout << "Jogador O venceu!" << endl;
        return;
    } else if (checkDraw(board)) {
        cout << "Empate!" << endl;
        return;
    }

    cout << "Jogador " << currentPlayer << ", insira a linha (0-2) e coluna (0-2) separadas por espaço: ";
    int row, col;
    cin >> row >> col;

    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;

        for (Node* child : currentNode->children) {
            if (child->player == currentPlayer) {
                playGame(child, board, (currentPlayer == 'X') ? 'O' : 'X');
                break;
            }
        }

        board[row][col] = ' ';
    } else {
        cout << "Posição ocupada. Tente novamente." << endl;
    }
}

//função que constroi o grafo do jogo
void buildGameGraph(Node* currentNode, vector<vector<char>>& board, char currentPlayer) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = currentPlayer;
                Node* childNode = createNode((currentPlayer == 'X') ? 'O' : 'X');
                currentNode->children.push_back(childNode);
                buildGameGraph(childNode, board, (currentPlayer == 'X') ? 'O' : 'X');
                board[i][j] = ' ';
            }
        }
    }
}

int main() {
    Node* root = createNode('X');
    vector<vector<char>> board(3, vector<char>(3, ' '));

    buildGameGraph(root, board, 'O'); // Constrói o grafo iniciando com a jogada do jogador 'O'
    playGame(root, board, 'X');       // Inicia o jogo com o jogador 'X'
    for (Node* child : root->children) {
        delete child;
    }
    delete root;
    return 0;
}
