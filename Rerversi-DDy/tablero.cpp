#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "colores.hpp"
#include "utilidades.hpp"
using namespace std;

char tablero[TAM_TABLERO][TAM_TABLERO];

// Geometria del tablero en pantalla. Se dejan como constantes de archivo
// para que el dibujo, el resaltado del cursor y la animacion de volteo
// usen siempre las mismas coordenadas.
static const int EJE_X = 55;
static const int EJE_Y = 17;
static const int ANCHO_CELDA = 5;
static const int ALTO_CELDA = 2;

void inicializarTablero() {
    for (int i = 0; i < TAM_TABLERO; ++i)
        for (int j = 0; j < TAM_TABLERO; ++j)
            tablero[i][j] = ' ';
    tablero[3][3] = 'O';
    tablero[3][4] = 'X';
    tablero[4][3] = 'X';
    tablero[4][4] = 'O';
}

bool esMovimientoValido(int fila, int col, char jugador) {
    if (tablero[fila][col] != ' ') return false;

    char oponente = (jugador == 'X') ? 'O' : 'X';

    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int x = fila + dx, y = col + dy;

            bool hayOponente = false;

            while (x >= 0 && x < TAM_TABLERO && y >= 0 && y < TAM_TABLERO && tablero[x][y] == oponente) {
                x += dx; y += dy; hayOponente = true;

            }
            if (hayOponente && x >= 0 && x < TAM_TABLERO && y >= 0 && y < TAM_TABLERO && tablero[x][y] == jugador)
                return true;
        }
    return false;
}

void aplicarMovimiento(int fila, int col, char jugador) {
    tablero[fila][col] = jugador;

    char oponente = (jugador == 'X') ? 'O' : 'X';

    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int x = fila + dx, y = col + dy;
            bool hayOponente = false;

            while (x >= 0 && x < TAM_TABLERO && y >= 0 && y < TAM_TABLERO && tablero[x][y] == oponente) {
                x += dx; y += dy; hayOponente = true;
            }

            if (hayOponente && x >= 0 && x < TAM_TABLERO && y >= 0 && y < TAM_TABLERO && tablero[x][y] == jugador) {
                int nx = fila + dx, ny = col + dy;
                while (tablero[nx][ny] == oponente) {
                    tablero[nx][ny] = jugador;
                    nx += dx; ny += dy;
                }
            }
        }
}

bool hayMovimientosValidos(char jugador) {
    for (int i = 0; i < TAM_TABLERO; ++i)
        for (int j = 0; j < TAM_TABLERO; ++j)
            if (esMovimientoValido(i, j, jugador))
                return true;
    return false;
}

// FUNCIONES GRÁFICAS Y DE JUEGO

void dibujarTitulo() {
    EstablecerColor(NEGRO, VERDE);
   MoverCursor(35, 3);
    cout << "ooooooooo.   oooooooooooo oooooo     oooo oooooooooooo ooooooooo.    .oooooo..o ooooo ";
    MoverCursor(35, 4);
    cout << "888   `Y88. `888'     `8  `888.     .8'  `888'     `8 `888   `Y88. d8P'    `Y8 `888' ";
    MoverCursor(35, 5);
    cout << "888   .d88'  888           `888.   .8'    888          888   .d88' Y88bo.       888  ";
    MoverCursor(35, 6);
    cout << "888ooo88P'   888oooo8       `888. .8'     888oooo8     888ooo88P'   `\"Y8888o.   888  ";
    MoverCursor(35, 7);
    cout << "888`88b.     888    \"        `888.8'      888    \"     888`88b.         `\"Y88b  888  ";
    MoverCursor(35, 8);
    cout << "888  `88b.   888       o      `888'       888       o  888  `88b.  oo     .d8P  888  ";
    MoverCursor(35, 9);
    cout << "o888o  o888o o888ooooood8       `8'       o888ooooood8 o888o  o888o 8\"\"88888P'  o888o ";

}
// Dibuja una linea horizontal completa del tablero (indice b va de 0 a
// TAM_TABLERO, donde 0 es el borde superior y TAM_TABLERO el borde inferior).
// Si esa linea toca la celda donde esta el cursor, el segmento y las
// esquinas correspondientes a esa columna se dibujan en azul; el fondo de
// la celda nunca cambia de color, solo el color de la linea.
static void dibujarLineaHorizontal(int b, int cursorY, int cursorX) {
    bool esSuperior = (b == 0);
    bool esInferior = (b == TAM_TABLERO);
    bool tocaFila = (b == cursorY || b == cursorY + 1);

    MoverCursor(EJE_X, EJE_Y + b * (ALTO_CELDA + 1));

    EstablecerColor(VERDE, (tocaFila && cursorX == 0) ? AZUL : BLANCO);
    if (esSuperior) cout << (char)ESI;
    else if (esInferior) cout << (char)EII;
    else cout << (char)195;

    for (int j = 0; j < TAM_TABLERO; j++) {
        EstablecerColor(VERDE, (tocaFila && j == cursorX) ? AZUL : BLANCO);
        for (int k = 0; k < ANCHO_CELDA; k++) cout << (char)BH;

        bool esUltima = (j == TAM_TABLERO - 1);
        bool juntaResaltada = tocaFila && (j == cursorX || j + 1 == cursorX);
        EstablecerColor(VERDE, juntaResaltada ? AZUL : BLANCO);
        if (esUltima) {
            if (esSuperior) cout << (char)ESD;
            else if (esInferior) cout << (char)EID;
            else cout << (char)180;
        } else {
            if (esSuperior) cout << (char)194;
            else if (esInferior) cout << (char)193;
            else cout << (char)197;
        }
    }
}

// Dibuja una de las filas de una ficha (fila 0 = mitad superior, fila 1 =
// mitad inferior), usando caracteres de bloque para que se vea como una
// ficha real en vez de la letra 'O'. Si la casilla esta vacia solo pinta
// el fondo verde de la casilla.
static void dibujarSegmentoFicha(char ficha, int fila) {
    if (ficha != 'X' && ficha != 'O') {
        EstablecerColor(VERDE, BLANCO);
        cout << "     ";
        return;
    }
    Color colorFicha = (ficha == 'X') ? NEGRO : BLANCO;
    char c = (fila == 0) ? (char)BLOQUE_SUP : (char)BLOQUE_INF;
    EstablecerColor(VERDE, colorFicha);
    cout << c << c << c << c << c;
}

void dibujarTablero(int cursorX, int cursorY) {
    MoverCursor(EJE_X + 2, EJE_Y - 1);
    EstablecerColor(NEGRO, BLANCO);
    for (int j = 0; j < TAM_TABLERO; j++) cout << " " << (char)('A' + j) << "    ";

    for (int i = 0; i < TAM_TABLERO; ++i) {
        dibujarLineaHorizontal(i, cursorY, cursorX);

        MoverCursor(EJE_X - 2, EJE_Y + i * (ALTO_CELDA + 1) + 1);
        EstablecerColor(NEGRO, BLANCO);
        cout << i + 1;

        for (int k = 0; k < ALTO_CELDA; k++) {
            MoverCursor(EJE_X, EJE_Y + i * (ALTO_CELDA + 1) + 1 + k);
            for (int b = 0; b <= TAM_TABLERO; b++) {
                bool bordeResaltado = (i == cursorY) && (b == cursorX || b == cursorX + 1);
                EstablecerColor(VERDE, bordeResaltado ? AZUL : BLANCO);
                cout << (char)BV;
                if (b < TAM_TABLERO) dibujarSegmentoFicha(tablero[i][b], k);
            }
        }
    }

    dibujarLineaHorizontal(TAM_TABLERO, cursorY, cursorX);
    EstablecerColor(NEGRO, BLANCO);
}

// Anima el volteo de una ficha capturada: la "encoge" hasta una linea
// delgada del color anterior y luego la "expande" de nuevo con el color
// del jugador que capturo, simulando que la ficha gira sobre si misma.
static void animarVolteo(int fila, int col, char nuevaFicha) {
    int x = EJE_X + col * (ANCHO_CELDA + 1) + 1;
    int y0 = EJE_Y + fila * (ALTO_CELDA + 1) + 1;

    Color colorAnterior = (nuevaFicha == 'X') ? BLANCO : NEGRO;
    Color colorNuevo = (nuevaFicha == 'X') ? NEGRO : BLANCO;

    int anchos[] = { 5, 3, 1, 1, 3, 5 };
    for (int paso = 0; paso < 6; paso++) {
        int ancho = anchos[paso];
        Color color = (paso < 3) ? colorAnterior : colorNuevo;
        int relleno = (ANCHO_CELDA - ancho) / 2;

        for (int f = 0; f < ALTO_CELDA; f++) {
            MoverCursor(x, y0 + f);
            EstablecerColor(VERDE, BLANCO);
            for (int s = 0; s < relleno; s++) cout << ' ';
            EstablecerColor(VERDE, color);
            for (int s = 0; s < ancho; s++) cout << (char)BLOQUE_LLENO;
            EstablecerColor(VERDE, BLANCO);
            for (int s = 0; s < relleno; s++) cout << ' ';
        }
        Sleep(60);
    }
}

void mostrarMensaje(const string& mensaje, int linea) {
    int Ejex = 45;
    int base = EJE_Y + TAM_TABLERO * (ALTO_CELDA + 1) + 2;
    MoverCursor(Ejex, base + linea);
    EstablecerColor(NEGRO, BLANCO);
    string salida = mensaje;
    const size_t ANCHO_LINEA = 90;
    if (salida.size() < ANCHO_LINEA) salida += string(ANCHO_LINEA - salida.size(), ' ');
    cout << salida;
}

    void MostrarInstrucciones() {
    LimpiarPantalla();
    EstablecerColor(NEGRO, VERDE);

    MoverCursor(10, 2);
    cout << " ___ _  _ ___ _____ ___ _   _  ___ ___ ___ ___  _  _ ___ ___";
    MoverCursor(10, 3);
    cout << "|_ _| \\| / __|_   _| _ \\ | | |/ __/ __| _ / _ \\| \\| | __/ __|";
    MoverCursor(10, 4);
    cout << " | || .` \\__ \\ | | |   / |_| | (_| (__ | | (_) | .` | _|\\__ \\";
    MoverCursor(10, 5);
    cout << "|___|_|\\_|___/ |_| |_|_\\\\___/ \\___\\___|___\\___/|_|\\_|___|___/";

    EstablecerColor(NEGRO, GRISCLARO);

    MoverCursor(9, 8);
    cout << "-> Objetivo del juego:";
    MoverCursor(9, 9);
    cout << "   Ganar controlando la mayor\241a de las fichas del tablero al final de la partida.";
    MoverCursor(9, 10);
    cout << "   El jugador con más fichas de su color al finalizar la partida gana.";

    MoverCursor(9, 12);
    cout << "-> El tablero es de 8x8 casillas. (Cada ficha tiene dos caras: blanca y negra)";

    MoverCursor(9, 14);
    cout << "-> El tablero comienza con 4 fichas en el centro:";
    MoverCursor(9, 15);
    cout << "   * Posiciones D4 y E5 con fichas blancas.";
    MoverCursor(9, 16);
    cout << "   * Posiciones D5 y E4 con fichas negras.";
    MoverCursor(9, 17);
    cout << "   * Negro juega primero.";

    MoverCursor(9, 19);
    cout << "-> \250C\242mo se juega?";
    MoverCursor(9, 20);
    cout << "   1. Turnos alternados: Cada jugador coloca una ficha de su color en una casilla vac\241a.";
    MoverCursor(9, 21);
    cout << "   2. Al colocar la ficha, debe capturar al menos una ficha del oponente,";
    MoverCursor(9, 22);
    cout << "      encerr\240ndola entre la nueva ficha colocada y otra ya existente del mismo color,";
    MoverCursor(9, 23);
    cout << "      en l\241nea recta (horizontal, vertical o diagonal).";
    MoverCursor(9, 24);
    cout << "   3. Las fichas capturadas se voltean y cambian al color del jugador que jug\242.";

    MoverCursor(9, 26);
    cout << "-> REGLAS:";
    MoverCursor(9, 27);
    cout << "   1. Un movimiento es obligatorio si es posible capturar. Si no hay jugadas legales, el jugador pasa el turno.";
    MoverCursor(9, 28);
    cout << "   2. Si ning\243n jugador puede mover, el juego termina.";
    MoverCursor(9, 29);
    cout << "   3. No se puede colocar una ficha que no capture ninguna ficha del oponente.";
    MoverCursor(9, 30);
    cout << "   4. No se permite colocar fichas fuera del tablero, en casillas ocupadas, ni en casillas donde no se encierre al oponente.";

    MoverCursor(9, 32);
    cout << "-> Fin del juego:";
    MoverCursor(9, 33);
    cout << "   * El juego se acaba si el tablero est\240 lleno.";
    MoverCursor(9, 34);
    cout << "   * El juego se acaba si ning\243n jugador se puede mover.";

    MoverCursor(9, 36);
    cout << "-> Al final se cuentan las fichas y el jugador con m\240s fichas de su color gana.";

    MoverCursor(10, 40);
    cout << "Presiona cualquier tecla para volver al men\243...";
    _getch();
}

void MostrarCreditos() {
    LimpiarPantalla();
    EstablecerColor(NEGRO, VERDE);


    MoverCursor(10, 2);
    cout << "  ___ ___ ___ ___ ___ _____ ___  ___";
    MoverCursor(10, 3);
    cout << " / __| _ \\ __|   \\_ _|_   _/ _ \\/ __|";
    MoverCursor(10, 4);
    cout << " |(__|   / _|| |) | |  | || (_) \\__ \\";
    MoverCursor(10, 5);
    cout << " \\___|_|_\\___|___/___| |_| \\___/|___/";

    EstablecerColor(NEGRO, GRISCLARO);

    MoverCursor(9, 8);
    cout << "   Programa elaborado como proyecto final de Programaci\242n de Computadoras de";
    MoverCursor(9, 9);
    cout << "   la Licenciatura en Ciencias de la Computaci\242n de la";
    MoverCursor(9, 10);
    cout << "   Universidad de Sonora.";

    MoverCursor(9, 13);
    cout << "   Presentado el 16 de mayo de 2025";

    MoverCursor(9, 15);
    cout << "   Desarrolladores:";
    MoverCursor(9, 16);
    cout << "   * Carlos Jareth Garcia R\240mirez";
    MoverCursor(9, 17);
    cout << "   * Jonathan G\240vez Rojas.";
    MoverCursor(9, 18);
    cout << "   * Miguel Angel Nu\244ez Holguin.";
    MoverCursor(9, 19);
    cout << "   * Jorge Alan Ahumada Herrera.";

    MoverCursor(10, 40);
    cout << "Presiona cualquier tecla para volver al men\243...";
    _getch();
}

// Dibuja una caja rectangular en (cajaX, cajaTopY) y permite escribir texto
// dentro de ella. anchoInterior es, a la vez, el ancho util de la caja y el
// maximo de caracteres permitidos, por lo que el texto nunca se sale del
// cuadro dibujado.
static string LeerNombreEnCaja(int cajaX, int cajaTopY, int anchoInterior) {
    int anchoCaja = anchoInterior + 2;
    int filaContenido = cajaTopY + 1;

    EstablecerColor(NEGRO, ROJO);
    MoverCursor(cajaX, cajaTopY);
    cout << (char)ESI;
    for (int i = 0; i < anchoCaja - 2; i++) cout << (char)BH;
    cout << (char)ESD;

    MoverCursor(cajaX, filaContenido);
    cout << (char)BV;
    MoverCursor(cajaX + anchoCaja - 1, filaContenido);
    cout << (char)BV;

    MoverCursor(cajaX, cajaTopY + 2);
    cout << (char)EII;
    for (int i = 0; i < anchoCaja - 2; i++) cout << (char)BH;
    cout << (char)EID;

    string texto;
    int textoX = cajaX + 1;
    EstablecerColor(NEGRO, BLANCO);
    MoverCursor(textoX, filaContenido);
    CambiarCursor(ENCENDIDO);

    while (true) {
        int tecla = _getch();
        if (tecla == KEY_ENTER) {
            break;
        } else if (tecla == 8) { // Backspace
            if (!texto.empty()) {
                texto.pop_back();
                MoverCursor(textoX + (int)texto.length(), filaContenido);
                cout << ' ';
                MoverCursor(textoX + (int)texto.length(), filaContenido);
            }
        } else if (tecla == 0 || tecla == 224) {
            _getch(); // Se descartan teclas especiales (flechas, F1, etc.)
        } else if (tecla >= 32 && tecla <= 255 && tecla != 127) {
            if ((int)texto.length() < anchoInterior) {
                texto += (char)tecla;
                cout << (char)tecla;
            }
        }
    }

    CambiarCursor(APAGADO);
    return texto;
}

void JugarJuego(){

    LimpiarPantalla();

    const int ANCHO_CAJA_NOMBRE = 30; // tambien es el maximo de caracteres del nombre
    const int ETIQUETA_X = 15;
    const int FILA_J1 = 10;
    const int FILA_J2 = 17;
    string etiqueta1 = "Jugador 1: ";
    string etiqueta2 = "Jugador 2: ";

    EstablecerColor(NEGRO, ROJO);
    MoverCursor(ETIQUETA_X, 4);
    cout << "Reversi";

    EstablecerColor(NEGRO, BLANCO);
    MoverCursor(ETIQUETA_X, FILA_J1);
    cout << etiqueta1;
    MoverCursor(ETIQUETA_X, FILA_J2);
    cout << etiqueta2;

    string Jugador_1 = LeerNombreEnCaja(ETIQUETA_X + (int)etiqueta1.length(), FILA_J1 - 1, ANCHO_CAJA_NOMBRE);
    string Jugador_2 = LeerNombreEnCaja(ETIQUETA_X + (int)etiqueta2.length(), FILA_J2 - 1, ANCHO_CAJA_NOMBRE);

    if (Jugador_1.empty()) Jugador_1 = "Jugador 1";
    if (Jugador_2.empty()) Jugador_2 = "Jugador 2";

    LimpiarPantalla();
    dibujarTitulo();


    inicializarTablero();
    int cursorX = 3, cursorY = 3;
    char jugadorActual = 'X';
    bool juegoTerminado = false;
    while (!juegoTerminado) {
        dibujarTablero(cursorX, cursorY);

        int fichasX = 0, fichasO = 0;
        for (int i = 0; i < TAM_TABLERO; ++i)
            for (int j = 0; j < TAM_TABLERO; ++j) {
                if (tablero[i][j] == 'X') fichasX++;
                if (tablero[i][j] == 'O') fichasO++;
            }
        mostrarMensaje("Fichas -> " + Jugador_1 + ": " + to_string(fichasX) +
                       "   " + Jugador_2 + ": " + to_string(fichasO), 0);

        string nombreJugador = (jugadorActual == 'X') ? Jugador_1 : Jugador_2;
        mostrarMensaje("Turno de: " + nombreJugador + " (" + string(1, jugadorActual) + ")", 1);
        if (!hayMovimientosValidos(jugadorActual)) {
            mostrarMensaje("Sin movimientos. Turno perdido.", 2);
            _getch();
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            if (!hayMovimientosValidos(jugadorActual)) {
                mostrarMensaje("Nadie puede mover. Fin del juego.", 3);
                juegoTerminado = true;
                _getch();
            }
            continue;
        }
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case KEY_UP:    if (cursorY > 0) cursorY--; break;
                case KEY_DOWN:  if (cursorY < TAM_TABLERO - 1) cursorY++; break;
                case KEY_LEFT:  if (cursorX > 0) cursorX--; break;
                case KEY_RIGHT: if (cursorX < TAM_TABLERO - 1) cursorX++; break;
            }
        } else if (tecla == KEY_ENTER) {
            if (esMovimientoValido(cursorY, cursorX, jugadorActual)) {
                char tableroAnterior[TAM_TABLERO][TAM_TABLERO];
                for (int i = 0; i < TAM_TABLERO; ++i)
                    for (int j = 0; j < TAM_TABLERO; ++j)
                        tableroAnterior[i][j] = tablero[i][j];

                aplicarMovimiento(cursorY, cursorX, jugadorActual);

                for (int i = 0; i < TAM_TABLERO; ++i)
                    for (int j = 0; j < TAM_TABLERO; ++j)
                        if (tableroAnterior[i][j] != ' ' && tableroAnterior[i][j] != tablero[i][j])
                            animarVolteo(i, j, tablero[i][j]);

                mostrarMensaje(string(35, ' '), 2);
                jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            } else {
                mostrarMensaje("Movimiento invalido. Intenta otro.", 2);
                _getch();
            }
        } else if (tecla == KEY_ESC) {
            juegoTerminado = true;
        }
    }
    int contadorX = 0, contadorO = 0;
    for (int i = 0; i < TAM_TABLERO; ++i)
        for (int j = 0; j < TAM_TABLERO; ++j) {
            if (tablero[i][j] == 'X') contadorX++;
            if (tablero[i][j] == 'O') contadorO++;
        }
    dibujarTablero(cursorX, cursorY);
  mostrarMensaje("Resultado final : " + Jugador_1 + " (X): " + to_string(contadorX) + " | " +
               Jugador_2 + " (O): " + to_string(contadorO), 3);

if (contadorX > contadorO)
    mostrarMensaje("\255" + Jugador_1 + " gana!", 4);
else if (contadorO > contadorX)
    mostrarMensaje("\255" + Jugador_2 + " gana!", 4);
else
    mostrarMensaje("\255Empate!", 4);
 _getch();
}
