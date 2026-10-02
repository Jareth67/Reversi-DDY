#pragma once
#include <string>

void inicializarTablero();
bool esMovimientoValido(int fila, int col, char jugador);
void aplicarMovimiento(int fila, int col, char jugador);
bool hayMovimientosValidos(char jugador);
void dibujarTitulo();
void dibujarTablero(int cursorX, int cursorY);
void mostrarMensaje(const std::string& mensaje, int linea);
void JugarJuego();
void MostrarInstrucciones();
void MostrarCreditos();
