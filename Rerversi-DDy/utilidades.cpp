#include <windows.h>
#include "utilidades.hpp"

void MoverCursor(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void EstablecerColor(Color fondo, Color texto) {
    int color = fondo * 16 + texto;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void CambiarCursor(EstadoCursor estado, ModoCursor modo) {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = modo;
    cursor.bVisible = (estado == ENCENDIDO);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void MaximizarVentana() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
void LimpiarPantalla() {
    EstablecerColor(NEGRO, NEGRO);
    system("cls");
}
