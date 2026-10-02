#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include "colores.hpp"
#include "utilidades.hpp"
#include "tablero.hpp"
#include "menu.hpp"
using namespace std;

int main() {
    MaximizarVentana();
    EstablecerColor(NEGRO, BLANCO);
    system("cls");

    std::string Jugador_1, Jugador_2;
    char buffer[30];

    CambiarCursor(ENCENDIDO);


    CambiarCursor(APAGADO);

    string Titulos_del_Menu[4] = {
        "Jugar",
        "Instrucciones",
        "Cr\202ditos",
        "Salir"
    };

    while (true) {
        Menu mainMenu(Titulos_del_Menu, 4, 0, 4);
        int selectedOption = mainMenu.run();

        system("cls");
        EstablecerColor(NEGRO, BLANCO);

        switch (selectedOption) {
            case 0:  JugarJuego(); break;
            case 1:  MostrarInstrucciones(); break;
            case 2:  MostrarCreditos(); break;
            case 3:
            case -1:
                system("cls");
                MoverCursor(30, 15);
                cout << "\255Gracias por jugar Reversi!" << endl;
                return 0;
        }
    }
}
