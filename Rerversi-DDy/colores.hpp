#pragma once

enum {
    ESP=32, BV=179, BH=196, ESI=218, ESD=191, EII=192, EID=217,
    BLOQUE_SUP=220, BLOQUE_INF=223, BLOQUE_LLENO=219
};

enum Color {
    NEGRO = 0,
    AZUL = 9,
    VERDE = 2,
    ROJO = 4,
    GRISCLARO = 7,
    BLANCO = 15
};

enum EstadoCursor {
    APAGADO,
    ENCENDIDO
};

enum ModoCursor {
    MINI = 5,
    NORMAL = 40,
    SOLIDO = 80
};

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;
const int KEY_ESC = 27;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int TAM_TABLERO = 8;
extern char tablero[TAM_TABLERO][TAM_TABLERO];
