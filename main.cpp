#include <iostream>



#define tamañoTablero 8

#define WHITE_ROOK 'R'
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_QUEEN 'Q'
#define WHITE_KING 'K'
#define WHITE_PAWN 'P'

#define BLACK_ROOK 'r'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_QUEEN 'q'
#define BLACK_KING 'k'
#define BLACK_PAWN 'p'



void inicializarTablero(char tablero[tamañoTablero][tamañoTablero]) {

    //Negras
    tablero[0][0] = BLACK_ROOK;
    tablero[0][1] = BLACK_KNIGHT;
    tablero[0][2] = BLACK_BISHOP;
    tablero[0][3] = BLACK_QUEEN;
    tablero[0][4] = BLACK_KING;
    tablero[0][5] = BLACK_BISHOP;
    tablero[0][6] = BLACK_KNIGHT;
    tablero[0][7] = BLACK_ROOK;


    //Peones negros
    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[1][i] = BLACK_PAWN;
    }


    //Casillas vacías
    for (int fila = 2; fila < 6; fila = fila + 1) {
        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {
            tablero[fila][columna] = '*';
        }
    }


    //Peones blancos
    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[6][i] = WHITE_PAWN;
    }


    //Blancas
    tablero[7][0] = WHITE_ROOK;
    tablero[7][1] = WHITE_KNIGHT;
    tablero[7][2] = WHITE_BISHOP;
    tablero[7][3] = WHITE_QUEEN;
    tablero[7][4] = WHITE_KING;
    tablero[7][5] = WHITE_BISHOP;
    tablero[7][6] = WHITE_KNIGHT;
    tablero[7][7] = WHITE_ROOK;

}



void imprimirTablero(char tablero[tamañoTablero][tamañoTablero]) {

    std::cout << "  ";
    for (int col = 0; col < tamañoTablero; col = col + 1) {
        std::cout << (col + 1) << " ";
    }
    std::cout << std::endl;

    
    for (int fila = 0; fila < tamañoTablero; fila = fila + 1) {

        int numFila = tamañoTablero - fila;
        std::cout << numFila << " ";

        for (int col = 0; col < tamañoTablero; col = col + 1) {
            std::cout << tablero[fila][col] << " ";
        }
        std::cout << std::endl;
    }
}



int main() {

    char tablero[tamañoTablero][tamañoTablero];

    inicializarTablero(tablero);

    imprimirTablero(tablero);

    return 0;

}
