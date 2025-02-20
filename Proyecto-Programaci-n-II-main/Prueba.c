#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
int VerificarID_Materia(const char *code, const char *name) {
    char buffer[100];
    char *campo;
    FILE *fpMaterias = fopen("Lista_Asignaturas.txt", "r");
    if (fpMaterias == NULL) {
        printf("Error al abrir el archivo de materias.\n");
        return 0;
    }

    // Convertir el código y el nombre de la materia a minúsculas
    char codeLower[10];
    char nameLower[40];
    
    // Convertir código a minúsculas
    for (int i = 0; code[i]; i++) {
        codeLower[i] = tolower(code[i]);
    }
    codeLower[strlen(code)] = '\0'; // Asegurar que la cadena esté terminada correctamente

    // Convertir nombre de la materia a minúsculas
    for (int i = 0; name[i]; i++) {
        nameLower[i] = tolower(name[i]);
    }
    nameLower[strlen(name)] = '\0'; // Asegurar que la cadena esté terminada correctamente

    // Leer línea por línea del archivo de materias
    while (fgets(buffer, sizeof(buffer), fpMaterias) != NULL) {
        char idMateria[10];
        char nombreMateria[40];
        
        // Obtener el primer token (ID de la materia)
        campo = strtok(buffer, ";");
        if (campo != NULL) {
            strncpy(idMateria, campo, sizeof(idMateria));
            idMateria[sizeof(idMateria) - 1] = '\0'; // Asegurar el fin de cadena
            // Eliminar salto de línea si existe
            size_t len = strlen(idMateria);
            if (len > 0 && idMateria[len - 1] == '\n') {
                idMateria[len - 1] = '\0';
            }
        }

        // Obtener el segundo token (Nombre de la materia)
        campo = strtok(NULL, ";");
        if (campo != NULL) {
            strncpy(nombreMateria, campo, sizeof(nombreMateria));
            nombreMateria[sizeof(nombreMateria) - 1] = '\0'; // Asegurar el fin de cadena
            // Eliminar salto de línea si existe
            size_t len = strlen(nombreMateria);
            if (len > 0 && nombreMateria[len - 1] == '\n') {
                nombreMateria[len - 1] = '\0';
            }
        }

        // Convertir la materia leída del archivo a minúsculas
        char idMateriaLower[10];
        char nombreMateriaLower[40];
        
        for (int i = 0; idMateria[i]; i++) {
            idMateriaLower[i] = tolower(idMateria[i]);
        }
        idMateriaLower[strlen(idMateria)] = '\0'; // Asegurar que la cadena esté terminada correctamente

        for (int i = 0; nombreMateria[i]; i++) {
            nombreMateriaLower[i] = tolower(nombreMateria[i]);
        }
        nombreMateriaLower[strlen(nombreMateria)] = '\0'; // Asegurar que la cadena esté terminada correctamente

        // Debugging: Imprimir las cadenas comparadas
        printf("Comparando: '%s' '%s' con '%s' '%s'\n", codeLower, nameLower, idMateriaLower, nombreMateriaLower);

        // Comparar el ID y el nombre de la materia
        if (strcmpi(idMateriaLower, codeLower) == 0 && strcmpi(nombreMateriaLower, nameLower) == 0) {
            printf("Coincidencia encontrada.\n");
            fclose(fpMaterias);
            return 1; // Coincidencia encontrada
        }
    }
    

    fclose(fpMaterias);
    return 0; // No se encontró coincidencia
}
*/


#include <stdio.h>
#include <stdlib.h>


struct {
    int matricula;
    char nombre[30];
    int edad;
} alumno;

// Funciones del programa
void crear_arch();
void llenar_arch();
void mostrar_arch();
void buscar_clave();
void mayor_edad();
void eliminar_matricula();
void sumar_edad();
void modificar_registro();

void mostrar_menu() {
    system("cls");
    printf("\033[1;36m\n\t\tMenu Principal\n\n\033[0m");
    printf("1. Crear archivo.\n");
    printf("2. Ingresar datos.\n");
    printf("3. Mostrar datos.\n");
    printf("4. Buscar por matricula.\n");
    printf("5. Mostrar mayores a una edad.\n");
    printf("6. Eliminar matricula.\n");
    printf("7. Sumar 50 a la edad.\n");
    printf("8. Modificar registro.\n");
    printf("9. Salir.\n");
    printf("\nIngrese una opcion: ");
}

int main() {
    int opcion = 0;
    do {
        mostrar_menu();
        scanf("%i", &opcion);
        getchar();

        switch (opcion) {
            case 1: crear_arch(); break;
            case 2: llenar_arch(); break;
            case 3: mostrar_arch(); break;
            case 4: buscar_clave(); break;
            case 5: mayor_edad(); break;
            case 6: eliminar_matricula(); break;
            case 7: sumar_edad(); break;
            case 8: modificar_registro(); break;
            case 9: printf("\033[1;32mHasta luego...\033[0m\n"); break;
            default: printf("\033[1;31mError. Ingrese una opción válida.\033[0m\n");
        }
    } while (opcion != 9);
    return 0;
}

void crear_arch() {
    system("cls");
    FILE *archdisco = fopen("C:\\C\\alumnos2.txt", "w");
    printf("\033[1;32mArchivo creado exitosamente.\033[0m\n");
    fclose(archdisco);
    system("pause");
}

void llenar_arch() {
    system("cls");
    printf("Ingrese la matricula: ");
    scanf("%i", &alumno.matricula);
    getchar();
    printf("Ingrese el nombre: ");
    fgets(alumno.nombre, 30, stdin);
    printf("Ingrese la edad: ");
    scanf("%i", &alumno.edad);
    getchar();

    FILE *archdisco = fopen("C:\\C\\alumnos2.txt", "at+");
    fwrite(&alumno, sizeof(alumno), 1, archdisco);
    fclose(archdisco);
    printf("\033[1;32mAlumno ingresado.\033[0m\n");
    system("pause");
}

void mostrar_arch() {
    system("cls");
    FILE *archdisco = fopen("C:\\C\\alumnos2.txt", "at+");

    printf("\033[1;36m\n\t\tLista de Alumnos\n\033[0m");
    printf("\033[1;34m%-10s %-5s\t %-30s\n", "Matricula", "Edad", "Nombre");
    printf("--------------------------------------------------\033[0m\n");

    while (fread(&alumno, sizeof(alumno), 1, archdisco) == 1) {
        printf("%-10d %-5d\t %-30s\n", alumno.matricula, alumno.edad, alumno.nombre);
    }

    fclose(archdisco);
    system("pause");
}

void buscar_clave() {
    system("cls");
    printf("Ingrese la matricula a buscar: ");
    int clave;
    scanf("%d", &clave);
    getchar();
    FILE *archdisco = fopen("C:\\C\\alumnos2.txt", "at+");
    int encontrado = 0;

    while (fread(&alumno, sizeof(alumno), 1, archdisco) == 1) {
        if (clave == alumno.matricula) {
            printf("\033[1;34m\nMatricula: %d\nNombre: %sEdad: %d\n\n\033[0m", alumno.matricula, alumno.nombre, alumno.edad);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("\033[1;31mMatricula no encontrada.\033[0m\n");
    }
    fclose(archdisco);
    system("pause");
}

void mayor_edad() {
    printf("Ingrese la edad mínima: ");
    int age;
    scanf("%i", &age);
    getchar();
    FILE *archdisco = fopen("C:\\C\\alumnos2.txt", "at+");

    printf("\033[1;36m\n\tAlumnos con edad mayor o igual a %d\n\033[0m", age);
    printf("\033[1;34m%-10s %-30s %-5s\n", "Matricula", "Nombre", "Edad");
    printf("--------------------------------------------------\033[0m\n");

    while (fread(&alumno, sizeof(alumno), 1, archdisco) == 1) {
        if (alumno.edad >= age) {
            printf("%-10d %-30s %-5d\n", alumno.matricula, alumno.nombre, alumno.edad);
        }
    }
    fclose(archdisco);
    system("pause");
}

void eliminar_matricula() {
    system("cls");
    printf("Ingrese la matricula a eliminar: ");
    int clave;
    scanf("%i", &clave);
    getchar();

    FILE *arch1 = fopen("C:\\C\\alumnos2.txt", "r+");
    FILE *arch2 = fopen("C:\\C\\temporal.txt", "w");

    int eliminado = 0;
    while (fread(&alumno, sizeof(alumno), 1, arch1) == 1) {
        if (clave != alumno.matricula) {
            fwrite(&alumno, sizeof(alumno), 1, arch2);
        } else {
            eliminado = 1;
        }
    }

    fclose(arch1);
    fclose(arch2);

    remove("C:\\C\\alumnos2.txt");
    rename("C:\\C\\temporal.txt", "C:\\C\\alumnos2.txt");

    if (eliminado) {
        printf("\033[1;32mRegistro eliminado.\033[0m\n");
    } else {
        printf("\033[1;31mMatricula no encontrada.\033[0m\n");
    }

    system("pause");
}

void sumar_edad() {
    system("cls");
    FILE *arch1 = fopen("C:\\C\\alumnos2.txt", "r+");
    FILE *arch2 = fopen("C:\\C\\temporal.txt", "w");

    while (fread(&alumno, sizeof(alumno), 1, arch1) == 1) {
        alumno.edad += 50;
        fwrite(&alumno, sizeof(alumno), 1, arch2);
    }
    fclose(arch1);
    fclose(arch2);

    remove("C:\\C\\alumnos2.txt");
    rename("C:\\C\\temporal.txt", "C:\\C\\alumnos2.txt");

    printf("\033[1;32mSe han sumado 50 años a la edad de todos los alumnos.\033[0m\n");
    system("pause");
}

void modificar_registro() {
    system("cls");
    printf("Ingrese la matricula que desea modificar: ");
    int clave;
    scanf("%i", &clave);
    getchar();

    FILE *arch1 = fopen("C:\\C\\alumnos2.txt", "r+");
    FILE *arch2 = fopen("C:\\C\\temporal.txt", "w");

    int modificado = 0;
    while (fread(&alumno, sizeof(alumno), 1, arch1) == 1) {
        if (clave == alumno.matricula) {
            printf("Nuevo nombre: ");
            fgets(alumno.nombre, 30, stdin);
            printf("Nueva edad: ");
            scanf("%i", &alumno.edad);
            getchar();
            modificado = 1;
        }
        fwrite(&alumno, sizeof(alumno), 1, arch2);
    }

    fclose(arch1);
    fclose(arch2);

    remove("C:\\C\\alumnos2.txt");
    rename("C:\\C\\temporal.txt", "C:\\C\\alumnos2.txt");

    if (modificado) {
        printf("\033[1;32mRegistro modificado.\033[0m\n");
    } else {
        printf("\033[1;31mMatricula no encontrada.\033[0m\n");
    }
    system("pause");
}