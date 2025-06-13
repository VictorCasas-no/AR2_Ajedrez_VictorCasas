#include <iostream>

#define tamañoTablero 8         //Defino tamaño del tablero

//Defino piezas blancas
#define WHITE_ROOK 'R'          
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_QUEEN 'Q'
#define WHITE_KING 'K'
#define WHITE_PAWN 'P'

//Defino piezas negras
#define BLACK_ROOK 'r'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_QUEEN 'q'
#define BLACK_KING 'k'
#define BLACK_PAWN 'p'

//////////////////////////////////////////////////////////////////////////////////

void inicializarTablero(char tablero[tamañoTablero][tamañoTablero]) {       //Inicio función

    // Negras
    tablero[0][0] = BLACK_ROOK;         //Defino posición de la pieza
    tablero[0][1] = BLACK_KNIGHT;       //Defino posición de la pieza
    tablero[0][2] = BLACK_BISHOP;       //Defino posición de la pieza
    tablero[0][3] = BLACK_QUEEN;        //Defino posición de la pieza
    tablero[0][4] = BLACK_KING;         //Defino posición de la pieza
    tablero[0][5] = BLACK_BISHOP;       //Defino posición de la pieza
    tablero[0][6] = BLACK_KNIGHT;       //Defino posición de la pieza
    tablero[0][7] = BLACK_ROOK;         //Defino posición de la pieza

    // Peones negros
    for (int i = 0; i < tamañoTablero; i = i + 1) {         //Creo un bucle con i que recorre toda la columna de los peones...
        tablero[1][i] = BLACK_PAWN;                         //y les otorga el valor
    }

    // Casillas vacías
    for (int fila = 2; fila < 6; fila = fila + 1) {         //Creo un bucle con i que recorre las filas del medio
        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {         //Creo otro para las columnas
            tablero[fila][columna] = '*';                                               //y allá donde pase, les pone *
        }   
    }

    // Peones blancos
    for (int i = 0; i < tamañoTablero; i = i + 1) {         //Creo un bucle con i que recorre toda la columna de los peones...
        tablero[6][i] = WHITE_PAWN;                         //y les otorga el valor
    }

    // Blancas      
    tablero[7][0] = WHITE_ROOK;         //Defino posición de la pieza
    tablero[7][1] = WHITE_KNIGHT;       //Defino posición de la pieza
    tablero[7][2] = WHITE_BISHOP;       //Defino posición de la pieza
    tablero[7][3] = WHITE_QUEEN;        //Defino posición de la pieza
    tablero[7][4] = WHITE_KING;         //Defino posición de la pieza
    tablero[7][5] = WHITE_BISHOP;       //Defino posición de la pieza
    tablero[7][6] = WHITE_KNIGHT;       //Defino posición de la pieza
    tablero[7][7] = WHITE_ROOK;         
}

//////////////////////////////////////////////////////////////////////////////////

void imprimirTablero(char tablero[tamañoTablero][tamañoTablero]) {          //Inicio la función

    std::cout << "  ";                                                      //Espacio libre entre líneas para que se vea mejor
    for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {     //Creo bucle para las columnas exteriores que recorre el tamaño del tablero
        std::cout << (columna + 1) << " ";                                      //Crea espacios entre cada valor
    }
    std::cout << std::endl;             //Acaba líneas

    for (int fila = 0; fila < tamañoTablero; fila = fila + 1) {             //Bucle que recorre las columnas y filas y hace un recuento con numeros y los imprime

        int numFila = tamañoTablero - fila;                                 
        std::cout << numFila << " ";
        for (int columna = 0; columna < tamañoTablero; columna = columna + 1) {     
            std::cout << tablero[fila][columna] << " ";                             //Imprime el tablero
        }
        std::cout << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////

bool esPiezaBlanca(char pieza) {                //Función para comprobar si la pieza es blanca

    if (pieza >= 'A' && pieza <= 'Z') {
        return true;
    }
    return false;

}

//////////////////////////////////////////////////////////////////////////////////

bool esPiezaNegra(char pieza) {                 //Función para comprobar si la pieza es negra

    if (pieza >= 'a' && pieza <= 'z') {
        return true;
    }
    return false;

}

//////////////////////////////////////////////////////////////////////////////////


bool esDentroTablero(int fila, int columna) {                   //Función para comprobar que lo que introduzca el jugador es correcto (dentro del tablero)

    if (fila >= 0 && fila < tamañoTablero && columna >= 0 && columna < tamañoTablero) {
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////

bool caminoLibreHorizontal(char tablero[tamañoTablero][tamañoTablero], int fila, int columnaInicio, int columnaFin) {       //Función para comprobar que a los lados de la ficha que se vaya a mover hay espacio

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

bool caminoLibreVertical(char tablero[tamañoTablero][tamañoTablero], int columna, int filaInicio, int filaFin) {            //Función para comprobar que alante de la ficha que se vaya a mover hay espacio

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

bool caminoLibreDiagonal(char tablero[tamañoTablero][tamañoTablero], int filaInicio, int columnaInicio, int filaFin, int columnaFin) {      //Función para comprobar que en diagonal a la ficha que se vaya a mover hay espacio

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


bool esMovimientoValido(char tablero[tamañoTablero][tamañoTablero], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {       //Función para comprobar que los movimientos finales son válidos

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

    if ((esBlanca && esPiezaBlanca(destino)) || (esNegra && esPiezaNegra(destino))) {       //Condicional para comprobar si se intenta comer pieza a sí mismo
        return false;
    }

    int filaDelta = filaDestino - filaOrigen;
    int columnaDelta = columnaDestino - columnaOrigen;

    //Movimiento válido según los peones
    if (pieza == WHITE_PAWN || pieza == BLACK_PAWN) {
        int direccion = (pieza == WHITE_PAWN) ? -1 : 1;
        int filaInicio = (pieza == WHITE_PAWN) ? 6 : 1;

        //Movimiento alante 1 casilla
        if (columnaDelta == 0 && filaDelta == direccion && destino == '*') {
            return true;
        }

        //Movimiento alante 2 casillas (solo la primera vez que se mueve)
        if (columnaDelta == 0 && filaDelta == 2 * direccion && destino == '*') {

            int filaIntermedia = filaOrigen + direccion;

            if (tablero[filaIntermedia][columnaOrigen] == '*' && filaOrigen == filaInicio) {
                return true;
            }

        }

        //Comer en diagonal
        if ((columnaDelta == 1 || columnaDelta == -1) && filaDelta == direccion && destino != '*') {
            return true;
        }

        return false;
    }

    //Movimeinto para las torres
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

    //Movimiento para los alfiles
    if (pieza == WHITE_BISHOP || pieza == BLACK_BISHOP) {

        if (abs(filaDelta) == abs(columnaDelta)) {
            if (caminoLibreDiagonal(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino) == true) {
                return true;
            }
        }
        return false;
    }

    //Movimiento para las damas
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

    //Movimiento para los caballos
    if (pieza == WHITE_KNIGHT || pieza == BLACK_KNIGHT) {

        if ((abs(filaDelta) == 2 && abs(columnaDelta) == 1) || (abs(filaDelta) == 1 && abs(columnaDelta) == 2)) {
            return true;
        }
        return false;
    }

    //Movimiento para los reyes
    if (pieza == WHITE_KING || pieza == BLACK_KING) {

        if ((abs(filaDelta) <= 1) && (abs(columnaDelta) <= 1)) {
            return true;
        }
        return false;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////

void jugar(char tablero[tamañoTablero][tamañoTablero]) {        //Función del juego

    bool turnoBlanco = true;

    while (true) {

        imprimirTablero(tablero);

        std::cout << "Turno de las ";                           //Turnos
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

            std::cout << "Introduce fila de origen (1-8): ";                //Pedir ficha que mover
            std::cin >> filaOrigen;
            std::cout << "Introduce columna de origen (1-8): ";
            std::cin >> columnaOrigen;                              

            filaOrigen = tamañoTablero - filaOrigen;
            columnaOrigen = columnaOrigen - 1;

            if (esDentroTablero(filaOrigen, columnaOrigen) == false) {                  //Comprobación de si está en el tablero
                std::cout << "Posición de origen fuera del tablero. Intenta de nuevo." << std::endl;
                continue;
            }

            char pieza = tablero[filaOrigen][columnaOrigen];
            if (pieza == '*') {                                         //Comprobación de si es un espacio en blanco
                std::cout << "No hay pieza en la posición de origen. Intenta de nuevo." << std::endl;
                continue;
            }

            if (turnoBlanco == true && !esPiezaBlanca(pieza)) {         //Comprobación de si es blanca la que quiere mover (siendo turno de las blancas)
                std::cout << "Esa pieza no es blanca. Intenta de nuevo." << std::endl;
                continue;
            }

            if (turnoBlanco == false && !esPiezaNegra(pieza)) {         //Comprobación de si es negra la que quiere mover (siendo turno de las negras)
                std::cout << "Esa pieza no es negra. Intenta de nuevo." << std::endl;
                continue;
            }

            break;
        }

        bool movimientoValido = false;

        while (movimientoValido == false) {

            std::cout << "Introduce fila de destino (1-8): ";           //Pide el destino de la ficha elegida una vez es válida
            std::cin >> filaDestino;
            std::cout << "Introduce columna de destino (1-8): ";
            std::cin >> columnaDestino;

            filaDestino = tamañoTablero - filaDestino;
            columnaDestino = columnaDestino - 1;                        //-1 porque la máquina trabaja de 0 a 7 y nosotros de 1 a 8

            if (esDentroTablero(filaDestino, columnaDestino) == false) {        //Comprobación si la posición final está en el tablero
                std::cout << "Posición de destino fuera del tablero. Intenta de nuevo." << std::endl;
                continue;
            }

            if (esMovimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino) == true) {  //Valida si el movimiento es posible o no según las normas anteriores
                movimientoValido = true;
            }
            else {
                std::cout << "Movimiento no válido para esa pieza. Intenta de nuevo." << std::endl;
            }
        }


        //Registro del movimiento de la pieza
        char piezaMover = tablero[filaOrigen][columnaOrigen];
        tablero[filaDestino][columnaDestino] = piezaMover;
        tablero[filaOrigen][columnaOrigen] = '*';


        //Cambio de turno
        if (turnoBlanco == true) {
            turnoBlanco = false;
        }
        else {
            turnoBlanco = true;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////


int main() {                //Núcleo principal del juego
    char tablero[tamañoTablero][tamañoTablero];

    inicializarTablero(tablero);
    jugar(tablero);

    return 0;
}


