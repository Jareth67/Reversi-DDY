#pragma once
#include "colores.hpp"

void MoverCursor(int x, int y);
void EstablecerColor(Color fondo, Color texto);
void CambiarCursor(EstadoCursor estado, ModoCursor modo = NORMAL);
void MaximizarVentana();
void LimpiarPantalla();
