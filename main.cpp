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

// Inicialización del tablero
void inicializarTablero(char tablero[tamañoTablero][tamañoTablero]) {
    tablero[0][0] = BLACK_ROOK;
    tablero[0][1] = BLACK_KNIGHT;
    tablero[0][2] = BLACK_BISHOP;
    tablero[0][3] = BLACK_QUEEN;
    tablero[0][4] = BLACK_KING;
    tablero[0][5] = BLACK_BISHOP;
    tablero[0][6] = BLACK_KNIGHT;
    tablero[0][7] = BLACK_ROOK;

    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[1][i] = BLACK_PAWN;
    }

    for (int fila = 2; fila < 6; fila = fila + 1) {
        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {
            tablero[fila][columna] = '*';
        }
    }

    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[6][i] = WHITE_PAWN;
    }

    tablero[7][0] = WHITE_ROOK;
    tablero[7][1] = WHITE_KNIGHT;
    tablero[7][2] = WHITE_BISHOP;
    tablero[7][3] = WHITE_QUEEN;
    tablero[7][4] = WHITE_KING;
    tablero[7][5] = WHITE_BISHOP;
    tablero[7][6] = WHITE_KNIGHT;
    tablero[7][7] = WHITE_ROOK;
}

// Impresión del tablero con coordenadas numéricas
void imprimirTablero(char tablero[tamañoTablero][tamañoTablero]) {
    std::cout << "  ";
    for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {
        std::cout << (columna + 1) << " ";
    }
    std::cout << std::endl;

    for (int fila = 0; fila < tamañoTablero; fila = fila + 1) {
        int numFila = tamañoTablero - fila;
        std::cout << numFila << " ";

        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {
            std::cout << tablero[fila][columna] << " ";
        }
        std::cout << std::endl;
    }
}

// Verifica si una pieza es blanca
bool esPiezaBlanca(char pieza) {
    return pieza == WHITE_PAWN || pieza == WHITE_ROOK || pieza == WHITE_KNIGHT || pieza == WHITE_BISHOP || pieza == WHITE_QUEEN || pieza == WHITE_KING;
}

// Verifica si una pieza es negra
bool esPiezaNegra(char pieza) {
    return pieza == BLACK_PAWN || pieza == BLACK_ROOK || pieza == BLACK_KNIGHT || pieza == BLACK_BISHOP || pieza == BLACK_QUEEN || pieza == BLACK_KING;
}

// Verifica si las coordenadas están dentro del tablero
bool dentroDelTablero(int fila, int columna) {
    return fila >= 0 && fila < tamañoTablero && columna >= 0 && columna < tamañoTablero;
}

// Movimiento del peón
bool moverPeon(char tablero[tamañoTablero][tamañoTablero], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino, bool turnoBlanco) {
    char pieza = tablero[filaOrigen][columnaOrigen];
    int direccion = turnoBlanco ? -1 : 1;
    char piezaDestino = tablero[filaDestino][columnaDestino];

    if (columnaOrigen == columnaDestino) {
        if (tablero[filaDestino][columnaDestino] == '*' && filaDestino == filaOrigen + direccion) {
            return true;
        }
        if (turnoBlanco && filaOrigen == 6 && filaDestino == 4 && tablero[5][columnaOrigen] == '*' && tablero[4][columnaOrigen] == '*') {
            return true;
        }
        if (turnoBlanco == false && filaOrigen == 1 && filaDestino == 3 && tablero[2][columnaOrigen] == '*' && tablero[3][columnaOrigen] == '*') {
            return true;
        }
    }
    else if (std::abs(columnaDestino - columnaOrigen) == 1 && filaDestino == filaOrigen + direccion) {
        if (turnoBlanco && esPiezaNegra(piezaDestino)) {
            return true;
        }
        if (turnoBlanco == false && esPiezaBlanca(piezaDestino)) {
            return true;
        }
    }
    return false;
}

// (Más funciones de movimiento por pieza se incluirán aquí más adelante)

int main() {
    char tablero[tamañoTablero][tamañoTablero];
    inicializarTablero(tablero);

    bool turnoBlanco = true;
    bool juegoActivo = true;

    while (juegoActivo) {
        imprimirTablero(tablero);
        if (turnoBlanco) {
            std::cout << "Turno de las blancas" << std::endl;
        }
        else {
            std::cout << "Turno de las negras" << std::endl;
        }

        int filaOrigen, columnaOrigen, filaDestino, columnaDestino;
        std::cout << "Introduce fila y columna de origen (1-8): ";
        std::cin >> filaOrigen >> columnaOrigen;
        std::cout << "Introduce fila y columna de destino (1-8): ";
        std::cin >> filaDestino >> columnaDestino;

        filaOrigen = tamañoTablero - filaOrigen;
        columnaOrigen = columnaOrigen - 1;
        filaDestino = tamañoTablero - filaDestino;
        columnaDestino = columnaDestino - 1;

        if (dentroDelTablero(filaOrigen, columnaOrigen) == false || dentroDelTablero(filaDestino, columnaDestino) == false) {
            std::cout << "Coordenadas fuera del tablero." << std::endl;
            continue;
        }

        char pieza = tablero[filaOrigen][columnaOrigen];

        if (pieza == '*' || (turnoBlanco && esPiezaBlanca(pieza) == false) || (turnoBlanco == false && esPiezaNegra(pieza) == false)) {
            std::cout << "No puedes mover esa pieza." << std::endl;
            continue;
        }

        bool movimientoValido = false;

        if (pieza == WHITE_PAWN || pieza == BLACK_PAWN) {
            movimientoValido = moverPeon(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino, turnoBlanco);
        }

        // Aquí se añadirán las verificaciones para otras piezas...

        if (movimientoValido == false) {
            std::cout << "Movimiento inválido." << std::endl;
            continue;
        }

        if ((turnoBlanco && esPiezaNegra(tablero[filaDestino][columnaDestino])) || (turnoBlanco == false && esPiezaBlanca(tablero[filaDestino][columnaDestino]))) {
            if (tablero[filaDestino][columnaDestino] == BLACK_KING || tablero[filaDestino][columnaDestino] == WHITE_KING) {
                std::cout << "El rey ha sido capturado. Fin del juego." << std::endl;
                juegoActivo = false;
            }
        }

        tablero[filaDestino][columnaDestino] = pieza;
        tablero[filaOrigen][columnaOrigen] = '*';

        if ((pieza == WHITE_PAWN && filaDestino == 0) || (pieza == BLACK_PAWN && filaDestino == 7)) {
            tablero[filaDestino][columnaDestino] = turnoBlanco ? WHITE_QUEEN : BLACK_QUEEN;
        }

        turnoBlanco = turnoBlanco == false;
    }

    return 0;
}

