#include <stdio.h>
#include <string.h>
#include "Estructuras.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Students
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//3.1

void showNotes() {
    int idEstudiante;
    printf("Ingrese su ID de estudiante: ");
    scanf("%d", &idEstudiante);

    FILE *Evaluaciones = fopen("Evaluaciones.txt", "r");
    if (Evaluaciones == NULL) {
        printf("Error al abrir el archivo Evaluaciones.txt.\n");
        return;
    }

    char line[256];
    int found = 0;
    char nombreEstudiante[40];
    char asignaturaActual[30] = "";
    float totalMateria = 0.0, totalGeneral = 0.0;
    int totalMaterias = 0;

    printf("+--------------------------------------------------------------------------------------------------------+\n");
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int id;
        char asignatura[30], nombreActividad[30];
        float nota, notaPonderada;

        // Leer campos de la evaluación
        sscanf(line, "%d;%39[^;];%29[^;];%*[^;];%29[^;];%f;%f",
               &id, nombreEstudiante, asignatura, nombreActividad, &nota, &notaPonderada);

        if (id == idEstudiante) {
            if (!found) {
                // Encabezado personalizado con nombre del estudiante e ID
                printf("| %-102s |\n", nombreEstudiante);
                printf("+--------------------------------------------------------------------------------------------------------+\n");
                printf("| %-50s | %-15s  | %-10s  | %-15s |\n", 
                       "Asignatura", "Nombre Actividad", "Nota", "Nota Ponderada");
                printf("+--------------------------------------------------------------------------------------------------------+\n");
                found = 1;
            }

            // Si cambia la asignatura, mostrar el total de la anterior
            if (strcmp(asignaturaActual, asignatura) != 0) {
                if (strcmp(asignaturaActual, "") != 0) {
                    // Mostrar total de la materia
                    printf("| %-50s | %-15s   | %-10s  | Total: %-9.2f|\n", 
                           "", "", "", totalMateria);
                    printf("+--------------------------------------------------------------------------------------------------------+\n");
                }
                // Actualizar asignatura actual y contar materia
                strcpy(asignaturaActual, asignatura);
                totalMateria = 0.0;
                totalMaterias++;
            }

            // Mostrar evaluación
            printf("| %-50s | %-15s   | %-10.2f  | %-15.2f |\n", 
                   asignatura, nombreActividad, nota, notaPonderada);
            totalMateria += notaPonderada;
            totalGeneral += notaPonderada;
        }
    }
    fclose(Evaluaciones);

    // Mostrar el último total de materia
    if (found) {
        printf("| %-50s | %-15s   | %-10s  | Total: %-9.2f|\n", 
               "", "", "", totalMateria);
        printf("+--------------------------------------------------------------------------------------------------------+\n");

        // Mostrar el total general y el promedio general por materia
        if (totalMaterias > 0) {
            printf("| Promedio General: %-84.2f |\n", totalGeneral / totalMaterias);
            printf("+--------------------------------------------------------------------------------------------------------+\n");
        }
    } else {
        printf("| No se encontraron evaluaciones para el ID ingresado.                                                  |\n");
        printf("+--------------------------------------------------------------------------------------------------------+\n");
    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//3.1
int getSubjectName(const char *codigo, char *nombreCompleto) {
    FILE *Asignaturas = fopen("Asignaturas.txt", "r");
    if (Asignaturas == NULL) {
        printf("Error al abrir el archivo Asignaturas.txt.\n");
        return 0;
    }

    char line[256], codigoArchivo[10], nombreArchivo[50];
    int creditos;

    while (fgets(line, sizeof(line), Asignaturas)) {
        sscanf(line, "%9[^;];%49[^;];%d", codigoArchivo, nombreArchivo, &creditos);
        if (strcmp(codigo, codigoArchivo) == 0) {
            strcpy(nombreCompleto, nombreArchivo);
            fclose(Asignaturas);
            return 1; // Código encontrado
        }
    }

    fclose(Asignaturas);
    return 0; // Código no encontrado
}

void trim(char *str) {
    char *start = str;
    while (*start == ' ') start++;  // Eliminar espacios iniciales
    char *end = start + strlen(start) - 1;
    while (end > start && *end == ' ') end--;  // Eliminar espacios finales
    *(end + 1) = '\0';
    memmove(str, start, end - start + 2);  // Copiar resultado limpio al inicio
}

void showNotesAsign() {
    int idEstudiante;
    char codigoAsignatura[10];
    char asignaturaElegida[50];

    printf("Ingrese su ID de estudiante: ");
    scanf("%d", &idEstudiante);

    printf("Ingrese el código de la asignatura: ");
    scanf(" %[^\n]", codigoAsignatura);

    // Obtener el nombre completo de la asignatura desde el código
    if (!getSubjectName(codigoAsignatura, asignaturaElegida)) {
        printf("No se encontró la asignatura con el código '%s'.\n", codigoAsignatura);
        return;
    }

    trim(asignaturaElegida);  // Limpiar espacios del nombre de la asignatura

    FILE *Evaluaciones = fopen("Evaluaciones.txt", "r");
    if (Evaluaciones == NULL) {
        printf("Error al abrir el archivo Evaluaciones.txt.\n");
        return;
    }

    char line[256];
    int found = 0, totalEvaluaciones = 0;
    char nombreEstudiante[40];
    float totalMateria = 0.0;

    printf("+------------------------------------------------------------------------------------+\n");
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int id;
        char asignatura[50], nombreActividad[30];
        float nota, notaPonderada;

        // Leer campos de la evaluación
        sscanf(line, "%d;%39[^;];%49[^;];%*[^;];%29[^;];%f;%f",
               &id, nombreEstudiante, asignatura, nombreActividad, &nota, &notaPonderada);

        trim(asignatura);  // Limpiar espacios del nombre de la asignatura

        // Verificar si coinciden el ID y el nombre completo de la asignatura
        if (id == idEstudiante && strcmp(asignatura, asignaturaElegida) == 0) {
            if (!found) {
                // Encabezado personalizado con el nombre del estudiante y la asignatura
                printf("| %-82s |\n", nombreEstudiante);
                printf("+------------------------------------------------------------------------------------+\n");
                printf("| %-50s | %-10s  | %-15s |\n", 
                       "Nombre Actividad", "Nota", "Nota Ponderada");
                printf("+------------------------------------------------------------------------------------+\n");
                found = 1;
            }

            // Mostrar evaluación
            printf("| %-50s | %-10.2f  | %-15.2f |\n", 
                   nombreActividad, nota, notaPonderada);
            totalMateria += notaPonderada;
            totalEvaluaciones++;
        }
    }
    fclose(Evaluaciones);

    // Mostrar el promedio de la materia
    if (found) {
        printf("+------------------------------------------------------------------------------------+\n");
        if (totalEvaluaciones > 0) {
            printf("| Promedio de la materia: %-58.2f |\n", totalMateria / totalEvaluaciones);
        }
        printf("+------------------------------------------------------------------------------------+\n");
    } else {
        printf("| No se encontraron evaluaciones para la asignatura %-70.2s.|\n", asignaturaElegida);
        printf("+------------------------------------------------------------------------------------+\n");
    }
}


