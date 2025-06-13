#include <iostream>

#define tamañoTablero 8         //Defino tamaño del tablero

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

// ======================= INICIALIZACIÓN DEL TABLERO =======================

void inicializarTablero(char tablero[tamañoTablero][tamañoTablero]) {
    // Negras
    tablero[0][0] = BLACK_ROOK;
    tablero[0][1] = BLACK_KNIGHT;
    tablero[0][2] = BLACK_BISHOP;
    tablero[0][3] = BLACK_QUEEN;
    tablero[0][4] = BLACK_KING;
    tablero[0][5] = BLACK_BISHOP;
    tablero[0][6] = BLACK_KNIGHT;
    tablero[0][7] = BLACK_ROOK;

    // Peones negros
    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[1][i] = BLACK_PAWN;
    }

    // Casillas vacías
    for (int fila = 2; fila < 6; fila = fila + 1) {
        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {
            tablero[fila][columna] = '*';
        }
    }

    // Peones blancos
    for (int i = 0; i < tamañoTablero; i = i + 1) {
        tablero[6][i] = WHITE_PAWN;
    }

    // Blancas
    tablero[7][0] = WHITE_ROOK;
    tablero[7][1] = WHITE_KNIGHT;
    tablero[7][2] = WHITE_BISHOP;
    tablero[7][3] = WHITE_QUEEN;
    tablero[7][4] = WHITE_KING;
    tablero[7][5] = WHITE_BISHOP;
    tablero[7][6] = WHITE_KNIGHT;
    tablero[7][7] = WHITE_ROOK;
}

//////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////

bool esPiezaBlanca(char pieza) {
    if (pieza >= 'A' && pieza <= 'Z') {
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////

bool esPiezaNegra(char pieza) {
    if (pieza >= 'a' && pieza <= 'z') {
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////


bool esDentroTablero(int fila, int columna) {
    if (fila >= 0 && fila < tamañoTablero && columna >= 0 && columna < tamañoTablero) {
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////

bool caminoLibreHorizontal(char tablero[tamañoTablero][tamañoTablero], int fila, int columnaInicio, int columnaFin) {
    int paso = 1;
    if (columnaFin < columnaInicio) {
        paso = -1;
    }
    for (int c = columnaInicio + paso; c != columnaFin; c = c + paso) {
        if (tablero[fila][c] != '*') {
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////

bool caminoLibreVertical(char tablero[tamañoTablero][tamañoTablero], int columna, int filaInicio, int filaFin) {
    int paso = 1;
    if (filaFin < filaInicio) {
        paso = -1;
    }
    for (int f = filaInicio + paso; f != filaFin; f = f + paso) {
        if (tablero[f][columna] != '*') {
            return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////

bool caminoLibreDiagonal(char tablero[tamañoTablero][tamañoTablero], int filaInicio, int columnaInicio, int filaFin, int columnaFin) {
    int pasoFila = 1;
    int pasoColumna = 1;
    if (filaFin < filaInicio) {
        pasoFila = -1;
    }
    if (columnaFin < columnaInicio) {
        pasoColumna = -1;
    }

    int fila = filaInicio + pasoFila;
    int columna = columnaInicio + pasoColumna;

    while (fila != filaFin && columna != columnaFin) {
        if (tablero[fila][columna] != '*') {
            return false;
        }
        fila = fila + pasoFila;
        columna = columna + pasoColumna;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////


bool esMovimientoValido(char tablero[tamañoTablero][tamañoTablero], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    if (esDentroTablero(filaOrigen, columnaOrigen) == false || esDentroTablero(filaDestino, columnaDestino) == false) {
        return false;
    }

    char pieza = tablero[filaOrigen][columnaOrigen];
    char destino = tablero[filaDestino][columnaDestino];

    if (pieza == '*') {
        return false;
    }

    bool esBlanca = esPiezaBlanca(pieza);
    bool esNegra = esPiezaNegra(pieza);

    if ((esBlanca && esPiezaBlanca(destino)) || (esNegra && esPiezaNegra(destino))) {
        return false; // No puede capturar pieza propia
    }

    int filaDelta = filaDestino - filaOrigen;
    int columnaDelta = columnaDestino - columnaOrigen;

    // Movimiento válido según tipo de pieza
    if (pieza == WHITE_PAWN || pieza == BLACK_PAWN) {
        int direccion = (pieza == WHITE_PAWN) ? -1 : 1;
        int filaInicio = (pieza == WHITE_PAWN) ? 6 : 1;

        // Movimiento adelante 1 casilla
        if (columnaDelta == 0 && filaDelta == direccion && destino == '*') {
            return true;
        }

        // Movimiento adelante 2 casillas desde posición inicial
        if (columnaDelta == 0 && filaDelta == 2 * direccion && destino == '*') {
            int filaIntermedia = filaOrigen + direccion;
            if (tablero[filaIntermedia][columnaOrigen] == '*' && filaOrigen == filaInicio) {
                return true;
            }
        }

        // Captura diagonal
        if ((columnaDelta == 1 || columnaDelta == -1) && filaDelta == direccion && destino != '*') {
            return true;
        }

        return false;
    }

    if (pieza == WHITE_ROOK || pieza == BLACK_ROOK) {
        if (filaOrigen == filaDestino && columnaOrigen != columnaDestino) {
            if (caminoLibreHorizontal(tablero, filaOrigen, columnaOrigen, columnaDestino) == true) {
                return true;
            }
        }
        if (columnaOrigen == columnaDestino && filaOrigen != filaDestino) {
            if (caminoLibreVertical(tablero, columnaOrigen, filaOrigen, filaDestino) == true) {
                return true;
            }
        }
        return false;
    }

    if (pieza == WHITE_BISHOP || pieza == BLACK_BISHOP) {
        if (abs(filaDelta) == abs(columnaDelta)) {
            if (caminoLibreDiagonal(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino) == true) {
                return true;
            }
        }
        return false;
    }

    if (pieza == WHITE_QUEEN || pieza == BLACK_QUEEN) {
        if (filaOrigen == filaDestino && columnaOrigen != columnaDestino) {
            if (caminoLibreHorizontal(tablero, filaOrigen, columnaOrigen, columnaDestino) == true) {
                return true;
            }
        }
        if (columnaOrigen == columnaDestino && filaOrigen != filaDestino) {
            if (caminoLibreVertical(tablero, columnaOrigen, filaOrigen, filaDestino) == true) {
                return true;
            }
        }
        if (abs(filaDelta) == abs(columnaDelta)) {
            if (caminoLibreDiagonal(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino) == true) {
                return true;
            }
        }
        return false;
    }

    if (pieza == WHITE_KNIGHT || pieza == BLACK_KNIGHT) {
        if ((abs(filaDelta) == 2 && abs(columnaDelta) == 1) || (abs(filaDelta) == 1 && abs(columnaDelta) == 2)) {
            return true;
        }
        return false;
    }

    if (pieza == WHITE_KING || pieza == BLACK_KING) {
        if ((abs(filaDelta) <= 1) && (abs(columnaDelta) <= 1)) {
            return true;
        }
        return false;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////

void jugar(char tablero[tamañoTablero][tamañoTablero]) {
    bool turnoBlanco = true;

    while (true) {
        imprimirTablero(tablero);

        std::cout << "Turno de las ";
        if (turnoBlanco == true) {
            std::cout << "blancas (mayusculas)" << std::endl;
        }
        else {
            std::cout << "negras (minusculas)" << std::endl;
        }

        int filaOrigen = -1;
        int columnaOrigen = -1;
        int filaDestino = -1;
        int columnaDestino = -1;

        while (true) {
            std::cout << "Introduce fila de origen (1-8): ";
            std::cin >> filaOrigen;
            std::cout << "Introduce columna de origen (1-8): ";
            std::cin >> columnaOrigen;

            filaOrigen = tamañoTablero - filaOrigen;
            columnaOrigen = columnaOrigen - 1;

            if (esDentroTablero(filaOrigen, columnaOrigen) == false) {
                std::cout << "Posición de origen fuera del tablero. Intenta de nuevo." << std::endl;
                continue;
            }

            char pieza = tablero[filaOrigen][columnaOrigen];
            if (pieza == '*') {
                std::cout << "No hay pieza en la posición de origen. Intenta de nuevo." << std::endl;
                continue;
            }

            if (turnoBlanco == true && !esPiezaBlanca(pieza)) {
                std::cout << "Esa pieza no es blanca. Intenta de nuevo." << std::endl;
                continue;
            }

            if (turnoBlanco == false && !esPiezaNegra(pieza)) {
                std::cout << "Esa pieza no es negra. Intenta de nuevo." << std::endl;
                continue;
            }

            break;
        }

        bool movimientoValido = false;
        while (movimientoValido == false) {
            std::cout << "Introduce fila de destino (1-8): ";
            std::cin >> filaDestino;
            std::cout << "Introduce columna de destino (1-8): ";
            std::cin >> columnaDestino;

            filaDestino = tamañoTablero - filaDestino;
            columnaDestino = columnaDestino - 1;

            if (esDentroTablero(filaDestino, columnaDestino) == false) {
                std::cout << "Posición de destino fuera del tablero. Intenta de nuevo." << std::endl;
                continue;
            }

            if (esMovimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino) == true) {
                movimientoValido = true;
            }
            else {
                std::cout << "Movimiento no válido para esa pieza. Intenta de nuevo." << std::endl;
            }
        }

        // Mover la pieza
        char piezaMover = tablero[filaOrigen][columnaOrigen];
        tablero[filaDestino][columnaDestino] = piezaMover;
        tablero[filaOrigen][columnaOrigen] = '*';

        // Cambio de turno
        if (turnoBlanco == true) {
            turnoBlanco = false;
        }
        else {
            turnoBlanco = true;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////


int main() {
    char tablero[tamañoTablero][tamañoTablero];

    inicializarTablero(tablero);
    jugar(tablero);

    return 0;
}


