#include <iostream>
#include <conio.h>
#include "colores.hpp"
#include "utilidades.hpp"
#include "tablero.hpp"
#include "menu.hpp"
using namespace std;

Menu::Menu(const string Titulos_del_Menu[], int count, int x, int y)
    : Opcion_Seleccionada(0), Eje_de_las_X(x), Eje_de_las_Y(y), Contador(count) {
    for (int i = 0; i < count && i < 10; i++)
        Opciones_menu[i] = Titulos_del_Menu[i];
}

void Menu::MostrarTitulo() {
    dibujarTitulo();
}

void Menu::DibujarOpcion(int indice, bool seleccionada) {
    int Opcion_en_X = 75 - (int)Opciones_menu[indice].length() / 2;
    int Opcion_en_Y = 21 + indice * 3;
    int Ancho_caja = (int)Opciones_menu[indice].length() + 6;
    int Alto_caja = 3;
    int Caja_en_X = Opcion_en_X - 3;
    int Caja_en_Y = Opcion_en_Y - 1;

    if (seleccionada) {
        EstablecerColor(NEGRO, ROJO);
        MoverCursor(Caja_en_X, Caja_en_Y);
        cout << (char)ESI;
        for (int j = 0; j < Ancho_caja - 2; j++) cout << (char)BH;
        cout << (char)ESD;
        for (int j = 1; j < Alto_caja - 1; j++) {
            MoverCursor(Caja_en_X, Caja_en_Y + j); cout << (char)BV;
            MoverCursor(Caja_en_X + Ancho_caja - 1, Caja_en_Y + j); cout << (char)BV;
        }
        MoverCursor(Caja_en_X, Caja_en_Y + Alto_caja - 1);
        cout << (char)EII;
        for (int j = 0; j < Ancho_caja - 2; j++) cout << (char)BH;
        cout << (char)EID;

        EstablecerColor(NEGRO, GRISCLARO);
        MoverCursor(Opcion_en_X, Opcion_en_Y);
        cout << Opciones_menu[indice];
    } else {
        // Se borra el area completa de la caja (para que no queden restos del
        // recuadro rojo) y se vuelve a mostrar la opcion en su estilo normal.
        EstablecerColor(NEGRO, BLANCO);
        for (int j = 0; j < Alto_caja; j++) {
            MoverCursor(Caja_en_X, Caja_en_Y + j);
            for (int k = 0; k < Ancho_caja; k++) cout << ' ';
        }
        MoverCursor(Opcion_en_X, Opcion_en_Y);
        cout << Opciones_menu[indice];
    }
}

void Menu::MostrarOpciones() {
    for (int i = 0; i < Contador; i++) DibujarOpcion(i, i == Opcion_Seleccionada);
}

void Menu::DibujarMenu() {
    system("cls");
    EstablecerColor(NEGRO, BLANCO);
    MostrarTitulo();
    MostrarOpciones();
}

void Menu::moveUp() {
    if (Opcion_Seleccionada > 0) {
        int anterior = Opcion_Seleccionada;
        Opcion_Seleccionada--;
        DibujarOpcion(anterior, false);
        DibujarOpcion(Opcion_Seleccionada, true);
    }
}

void Menu::moveDown() {
    if (Opcion_Seleccionada < Contador - 1) {
        int anterior = Opcion_Seleccionada;
        Opcion_Seleccionada++;
        DibujarOpcion(anterior, false);
        DibujarOpcion(Opcion_Seleccionada, true);
    }
}

int Menu::getOpcionSleccionada() const {
    return Opcion_Seleccionada;
}

int Menu::run() {
    CambiarCursor(APAGADO);
    DibujarMenu();
    while (true) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 224 || key == 0) {
                key = _getch();
                switch (key) {
                    case KEY_UP: moveUp(); break;
                    case KEY_DOWN: moveDown(); break;
                }
            } else if (key == KEY_ENTER) return Opcion_Seleccionada;
            else if (key == KEY_ESC) return -1;
        }
    }
}
