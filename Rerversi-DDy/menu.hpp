#pragma once
#include <string>
class Menu {
private:
    std::string Opciones_menu[10];
    int Contador;
    int Opcion_Seleccionada;
    int Eje_de_las_X, Eje_de_las_Y;

    void DibujarOpcion(int indice, bool seleccionada);

public:
    Menu(const std::string Titulos_del_Menu[], int count, int x, int y);
    void MostrarTitulo();
    void MostrarOpciones();
    void DibujarMenu();
    void moveUp();
    void moveDown();
    int getOpcionSleccionada() const;
    int run();
};


