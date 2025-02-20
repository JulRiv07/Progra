#include "Estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Funcion que verifica si una linea esta vacia.
int esLineaVacia(const char *linea) {
    // Recorre la línea para verificar si hay caracteres visibles
    while (*linea) {
        if (!isspace(*linea)) {
            return 0; // No está vacía (tiene algún carácter visible)
        }
        linea++;
    }
    return 1; // Está vacía (solo contiene espacios o está completamente vacía)
}

void Pause_Menu(){
    system("pause");
    system("cls");
}