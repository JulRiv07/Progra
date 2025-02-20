#include <stdio.h>
#include <string.h>
#include "Estructuras.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Teacher
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.1

void createActivities() {
    Profesor prof;
    int n;

    // Solicitar el ID del profesor
    printf("\nIngrese el ID del profesor: ");
    scanf("%d", &prof.idProfesor);
    getchar();

    // Verificar si el profesor existe en Profesores.txt
    FILE *Profesores = fopen("Profesores.txt", "r");
    if (Profesores == NULL) {
        printf("Error al abrir el archivo Profesores.txt.\n");
        return;
    }

    char line[256];
    int found = 0;

    // Leer el archivo y buscar el profesor
    while (fgets(line, sizeof(line), Profesores)) {
        int idRegistrado;
        char nombreProfesor[50], asignatura[50];
        // Extraer los campos del archivo (idProfesor, nombre, asignatura)
        sscanf(line, "%d;%49[^;];%[^\n]", &idRegistrado, nombreProfesor, asignatura);

        // Si el idProfesor coincide, se guarda el nombre del profesor
        if (idRegistrado == prof.idProfesor) {
            found = 1;
            strcpy(prof.nombre, nombreProfesor); // Solo guardamos el nombre
            break;
        }
    }
    fclose(Profesores);

    // Si no se encontró el profesor
    if (!found) {
        printf("El profesor con ID %d no está registrado.\n", prof.idProfesor);
        return;
    }

    printf("Profesor encontrado: %s (ID: %d)\n", prof.nombre, prof.idProfesor);

    // Calcular el porcentaje acumulado de actividades ya registradas para el profesor
    FILE *Actividades = fopen("Actividades.txt", "a+");
    if (Actividades == NULL) {
        printf("Error al abrir el archivo Actividades.txt.\n");
        return;
    }

    rewind(Actividades);
    int porcentajeAcumulado = 0;

    // Leer las actividades registradas y sumar los porcentajes
    while (fgets(line, sizeof(line), Actividades)) {
        char idActividad[20], nombreActividad[50], nombreProfesor[50];
        int porcentaje, idProfesor;

        // Leer la información de cada actividad
        sscanf(line, "%[^;];%[^;];%d;%d;%[^\n]", idActividad, nombreActividad, &porcentaje, &idProfesor, nombreProfesor);

        // Sumar los porcentajes de las actividades del mismo profesor
        if (idProfesor == prof.idProfesor) {
            porcentajeAcumulado += porcentaje;
        }
    }

    // Mostrar el porcentaje acumulado actual
    printf("El porcentaje actual de actividades registradas para el profesor '%s' (ID: %d) es: %d%%.\n",
           prof.nombre, prof.idProfesor, porcentajeAcumulado);

    // Solicitar el número de actividades que desea crear
    printf("\nIngrese el número de actividades que desea ingresar: ");
    scanf("%d", &n);
    getchar();

    // Ingresar actividades
    for (int i = 0; i < n; i++) {
        Actividad Activ;
        int foundActividad = 0;

        // Ingresar el código de la actividad
        printf("\nIngrese el código de la actividad: ");
        fgets(Activ.IdActividad, sizeof(Activ.IdActividad), stdin);
        Activ.IdActividad[strcspn(Activ.IdActividad, "\n")] = '\0';
        getchar();
        rewind(Actividades);
        while (fgets(line, sizeof(line), Actividades)) {
            char idRegistrado[20];
            int idProfesor;

            // Leer el ID de la actividad y el ID del profesor asociado
            sscanf(line, "%[^;];%*[^;];%*d;%d;%*[^;]", idRegistrado, &idProfesor);

            // Verificar si la actividad ya está registrada para el mismo profesor
            if (strcmp(idRegistrado, Activ.IdActividad) == 0 && idProfesor == prof.idProfesor) {
                printf("La actividad con el código %s ya está registrada para el profesor %s.\n\n",
                       Activ.IdActividad, prof.nombre);
                foundActividad = 1;
                break;
            }
        }

        if (foundActividad) {
            continue; // Saltar al siguiente ciclo si la actividad ya existe
        }

        getchar();
        printf("Ingrese el nombre de la actividad: ");
        fgets(Activ.nombre, sizeof(Activ.nombre), stdin);
        Activ.nombre[strcspn(Activ.nombre, "\n")] = '\0';

        // Ingresar el porcentaje de la actividad
        printf("Ingrese el porcentaje de la actividad: ");
        scanf("%d", &Activ.PorcentajeActividad);
        getchar();

        // Validar que el porcentaje sea válido
        if (Activ.PorcentajeActividad <= 0 || Activ.PorcentajeActividad > 100) {
            printf("El porcentaje debe ser mayor a 0 y menor o igual a 100. Registro cancelado.\n");
            continue;
        }

        // Validar que el porcentaje acumulado no exceda el 100%
        if (porcentajeAcumulado + Activ.PorcentajeActividad > 100) {
            printf("El porcentaje acumulado supera el 100%. Registro cancelado.\n");
            continue;
        }

        // Registrar la actividad
        fprintf(Actividades, "%s;%s;%d;%d;%s\n",
                Activ.IdActividad, Activ.nombre,
                Activ.PorcentajeActividad, prof.idProfesor, prof.nombre);

        porcentajeAcumulado += Activ.PorcentajeActividad;

        // Confirmar la actividad registrada
        printf("Actividad '%s' (código: %s) registrada correctamente para el profesor '%s' (ID: %d).\n",
               Activ.nombre, Activ.IdActividad, prof.nombre, prof.idProfesor);

        // Mostrar el porcentaje acumulado actualizado
        printf("El porcentaje acumulado actual es: %d%%.\n", porcentajeAcumulado);
    }

    fclose(Actividades);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.1.1

void editActivities() {
    Profesor prof;
    int foundProfesor = 0;

    // Solicitar el ID del profesor
    printf("\nIngrese el ID del profesor: ");
    scanf("%d", &prof.idProfesor);
    getchar();

    // Verificar si el profesor existe en Profesores.txt
    FILE *Profesores = fopen("Profesores.txt", "r");
    if (Profesores == NULL) {
        printf("Error al abrir el archivo Profesores.txt.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), Profesores)) {
        int idRegistrado;
        char nombreProfesor[50];
        sscanf(line, "%d;%49[^\n]", &idRegistrado, nombreProfesor);

        if (idRegistrado == prof.idProfesor) {
            foundProfesor = 1;
            strcpy(prof.nombre, nombreProfesor);
            break;
        }
    }
    fclose(Profesores);

    if (!foundProfesor) {
        printf("El profesor con ID %d no está registrado.\n", prof.idProfesor);
        return;
    }

    printf("Profesor encontrado: %s (ID: %d)\n", prof.nombre, prof.idProfesor);

    // Solicitar el código de la actividad a editar
    char codigoActividad[20];
    printf("\nIngrese el código de la actividad que desea editar: ");
    fgets(codigoActividad, sizeof(codigoActividad), stdin);
    codigoActividad[strcspn(codigoActividad, "\n")] = '\0';

    // Abrir el archivo Actividades.txt para lectura
    FILE *Actividades = fopen("Actividades.txt", "r");
    if (Actividades == NULL) {
        printf("Error al abrir el archivo Actividades.txt.\n");
        return;
    }

    // Crear un archivo temporal para almacenar los cambios
    FILE *Temp = fopen("Temp.txt", "w");
    if (Temp == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Actividades);
        return;
    }

    int foundActividad = 0;

    while (fgets(line, sizeof(line), Actividades)) {
        char idActividad[20], nombreActividad[50], nombreProfesor[50];
        int porcentaje, idProfesor;

        // Leer los datos de una actividad
        sscanf(line, "%[^;];%[^;];%d;%d;%[^\n]", idActividad, nombreActividad, &porcentaje, &idProfesor, nombreProfesor);

        // Verificar si la actividad pertenece al profesor especificado
        if (idProfesor == prof.idProfesor && strcmp(idActividad, codigoActividad) == 0) {
            foundActividad = 1;
            printf("\nActividad encontrada: %s (código: %s, porcentaje: %d%%, profesor: %s).\n",
                   nombreActividad, idActividad, porcentaje, nombreProfesor);

            // Solicitar nuevos datos
            printf("Ingrese el nuevo nombre de la actividad (actual: %s): ", nombreActividad);
            fgets(nombreActividad, sizeof(nombreActividad), stdin);
            nombreActividad[strcspn(nombreActividad, "\n")] = '\0';

            printf("Ingrese el nuevo porcentaje de la actividad (actual: %d%%): ", porcentaje);
            scanf("%d", &porcentaje);
            getchar();

            if (porcentaje <= 0 || porcentaje > 100) {
                printf("El porcentaje debe ser mayor a 0 y menor o igual a 100. Edición cancelada.\n");
                fprintf(Temp, "%s", line); // Mantener la línea original sin cambios
                continue;
            }

            // Actualizar la actividad en el archivo temporal
            fprintf(Temp, "%s;%s;%d;%d;%s\n", idActividad, nombreActividad, porcentaje, idProfesor, nombreProfesor);

            printf("Actividad actualizada exitosamente.\n");
        } else {
            // Copiar las actividades no editadas al archivo temporal
            fprintf(Temp, "%s", line);
        }
    }

    fclose(Actividades);
    fclose(Temp);

    if (!foundActividad) {
        printf("No se encontró una actividad con el código '%s' para el profesor '%s' (ID: %d).\n",
               codigoActividad, prof.nombre, prof.idProfesor);
        // Eliminar el archivo temporal si no hubo cambios
        remove("Temp.txt");
    } else {
        // Reemplazar el archivo original por el archivo temporal
        remove("Actividades.txt");
        rename("Temp.txt", "Actividades.txt");
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.1.2

void deleteActivity() {
    Profesor prof;
    int foundProfesor = 0;

    // Solicitar el ID del profesor
    printf("\nIngrese el ID del profesor: ");
    scanf("%d", &prof.idProfesor);
    getchar();

    // Verificar si el profesor existe en Profesores.txt
    FILE *Profesores = fopen("Profesores.txt", "r");
    if (Profesores == NULL) {
        printf("Error al abrir el archivo Profesores.txt.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), Profesores)) {
        int idRegistrado;
        char nombreProfesor[50];
        sscanf(line, "%d;%49[^\n]", &idRegistrado, nombreProfesor);

        if (idRegistrado == prof.idProfesor) {
            foundProfesor = 1;
            strcpy(prof.nombre, nombreProfesor);
            break;
        }
    }
    fclose(Profesores);

    if (!foundProfesor) {
        printf("El profesor con ID %d no está registrado.\n", prof.idProfesor);
        return;
    }
  
    printf("Profesor encontrado: %s (ID: %d)\n", prof.nombre, prof.idProfesor);

    // Solicitar el código de la actividad a eliminar
    char codigoActividad[20];
    printf("\nIngrese el código de la actividad que desea eliminar: ");
    fgets(codigoActividad, sizeof(codigoActividad), stdin);
    codigoActividad[strcspn(codigoActividad, "\n")] = '\0';

    // Abrir el archivo Actividades.txt para lectura
    FILE *Actividades = fopen("Actividades.txt", "r");
    if (Actividades == NULL) {
        printf("Error al abrir el archivo Actividades.txt.\n");
        return;
    }

    // Crear un archivo temporal para almacenar los cambios
    FILE *Temp = fopen("Temp.txt", "w");
    if (Temp == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Actividades);
        return;
    }

    int foundActividad = 0;

    while (fgets(line, sizeof(line), Actividades)) {
        char idActividad[20], nombreActividad[50], nombreProfesor[50];
        int porcentaje, idProfesor;

        // Leer los datos de una actividad
        sscanf(line, "%[^;];%[^;];%d;%d;%[^\n]", idActividad, nombreActividad, &porcentaje, &idProfesor, nombreProfesor);

        // Verificar si la actividad pertenece al profesor especificado
        if (idProfesor == prof.idProfesor && strcmp(idActividad, codigoActividad) == 0) {
            foundActividad = 1;
            printf("\nActividad encontrada: %s (código: %s, porcentaje: %d%%, profesor: %s).\n",
                   nombreActividad, idActividad, porcentaje, nombreProfesor);

            printf("Eliminando actividad...\n");
            // No escribir esta línea en el archivo temporal, lo que efectivamente elimina la actividad
        } else {
            // Copiar las actividades no eliminadas al archivo temporal
            fprintf(Temp, "%s", line);
        }
    }

    fclose(Actividades);
    fclose(Temp);

    if (!foundActividad) {
        printf("No se encontró una actividad con el código '%s' para el profesor '%s' (ID: %d).\n",
               codigoActividad, prof.nombre, prof.idProfesor);
        // Eliminar el archivo temporal si no hubo cambios
        remove("Temp.txt");
    } else {
        remove("Actividades.txt");
        rename("Temp.txt", "Actividades.txt");
        printf("Actividad con el código '%s' eliminada correctamente.\n", codigoActividad);
    }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.1.3

void showActivities() {
    FILE *Actividades = fopen("Actividades.txt", "r");
    if (Actividades == NULL) {
        printf("Error al abrir el archivo Actividades.txt.\n");
        return;
    }

    char line[256];
    int currentProfesorId = -1;
    char currentProfesorName[50];

    printf("\nListado de Actividades Registradas:\n");

    // Encabezado de la tabla con bordes
    printf("+--------------+----------------------+--------------+------------------------+--------------+\n");
    printf("| %-12s | %-20s | %-12s | %-22s | %-12s |\n", "idProfesor", "Nombre", "idActividad", "Nombre Actividad", "Porcentaje");
    printf("+--------------+----------------------+--------------+------------------------+--------------+\n");

    // Leer todas las líneas del archivo
    while (fgets(line, sizeof(line), Actividades)) {
        char idActividad[20], nombreActividad[50], nombreProfesor[50];
        int porcentaje, idProfesor;

        // Separar los datos de la línea actual
        sscanf(line, "%[^;];%[^;];%d;%d;%[^\n]", idActividad, nombreActividad, &porcentaje, &idProfesor, nombreProfesor);

        // Si es un nuevo profesor, actualizamos el ID y nombre del profesor
        // Solo se muestra el nombre del profesor una vez
        if (idProfesor != currentProfesorId) {
            currentProfesorId = idProfesor;
            // Copiar el nombre del profesor para mostrarlo solo una vez
            strncpy(currentProfesorName, nombreProfesor, sizeof(currentProfesorName) - 1);
            currentProfesorName[sizeof(currentProfesorName) - 1] = '\0';  // Asegurarnos de que la cadena esté terminada
        }

        // Imprimir la actividad del profesor
        printf("| %-12d | %-20s | %-12s | %-22s | %-12d |\n", idProfesor, currentProfesorName, idActividad, nombreActividad, porcentaje);
    }

    // Final de la tabla
    printf("+--------------+----------------------+--------------+------------------------+--------------+\n");

    fclose(Actividades);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.2

void asignarNotas() {
    Estudiante est;
    char idActividad[3];
    Profesor prof;
    int n;

    printf("Ingrese el numero de notas que desea asignar: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {

        printf("\nIngrese el ID del profesor: ");
        scanf("%d", &prof.idProfesor);
        getchar();

        // Verificar si el profesor existe en Profesores.txt
        FILE *Profesores = fopen("Profesores.txt", "r");
        if (Profesores == NULL) {
            printf("Error al abrir el archivo Profesores.txt.\n");
            return;
        }

        char line[256];
        int found = 0;

        // Leer el archivo y buscar el profesor
        while (fgets(line, sizeof(line), Profesores)) {
            int idRegistrado;
            char nombreProfesor[30], asignatura[30];

            // Extraer los campos del archivo (idProfesor, nombre, asignatura)
            sscanf(line, "%d;%29[^;];%29[^\n]", &idRegistrado, nombreProfesor, asignatura);

            // Si el idProfesor coincide, se guarda la información
            if (idRegistrado == prof.idProfesor) {
                found = 1;
                strcpy(prof.nombre, nombreProfesor);
                strcpy(prof.nombre_asignatura, asignatura);
                break;
            }
        }
        fclose(Profesores);

        // Si no se encontró el profesor
        if (!found) {
            printf("El profesor con ID %d no está registrado.\n", prof.idProfesor);
            return;
        }

        printf("Profesor encontrado: %s (ID: %d), Asignatura: %s\n", prof.nombre, prof.idProfesor, prof.nombre_asignatura);

        // Solicitar el ID del estudiante
        printf("\nIngrese el ID del estudiante a evaluar: ");
        scanf("%d", &est.idEstudiante);
        getchar();

        // Verificar si el estudiante existe en Estudiantes.txt
        FILE *Estudiantes = fopen("Estudiantes.txt", "r");
        if (Estudiantes == NULL) {
            printf("Error al abrir el archivo Estudiantes.txt.\n");
            return;
        }

        found = 0;

        // Leer el archivo y buscar el estudiante
        while (fgets(line, sizeof(line), Estudiantes)) {
            int idRegistrado;
            char nombreEstudiante[40];
            int semestre;

            // Extraer los campos del archivo (idEstudiante, nombre, semestre, notaTotal)
            sscanf(line, "%d;%39[^;];%d;%f", &idRegistrado, nombreEstudiante, &semestre, &est.notaTotal);

            // Si el idEstudiante coincide, se guarda el nombre del estudiante
            if (idRegistrado == est.idEstudiante) {
                found = 1;
                strcpy(est.nombre, nombreEstudiante);
                break;
            }
        }
        fclose(Estudiantes);

        // Si no se encontró el estudiante
        if (!found) {
            printf("El estudiante con ID %d no está registrado.\n", est.idEstudiante);
            return;
        }

        printf("Estudiante encontrado: %s (ID: %d)\n", est.nombre, est.idEstudiante);

        // Verificar si el estudiante ya tiene el 100% de sus notas
        if (est.notaTotal >= 100.0) {
            printf("El estudiante %s (ID: %d) ya tiene el 100%% de sus notas.\n", est.nombre, est.idEstudiante);
            return;
        }

        // Solicitar el ID de la actividad
        printf("\nIngrese el código de la actividad que desea evaluar: ");
        fgets(idActividad, sizeof(idActividad), stdin);
        idActividad[strcspn(idActividad, "\n")] = '\0';

        // Verificar si la actividad existe en Actividades.txt
        FILE *Actividades = fopen("Actividades.txt", "r");
        if (Actividades == NULL) {
            printf("Error al abrir el archivo Actividades.txt.\n");
            return;
        }

        Actividad Activ;
        found = 0;

        // Leer el archivo y buscar la actividad
        while (fgets(line, sizeof(line), Actividades)) {
            char idRegistrado[3];
            sscanf(line, "%2[^;];%29[^;];%d;%*d;%*[^;]", idRegistrado, Activ.nombre, &Activ.PorcentajeActividad);

            // Si el código de actividad coincide, se obtiene la información
            if (strcmp(idRegistrado, idActividad) == 0) {
                found = 1;
                strcpy(Activ.IdActividad, idRegistrado);
                break;
            }
        }
        fclose(Actividades);

        // Si no se encontró la actividad
        if (!found) {
            printf("La actividad con el código %s no está registrada.\n", idActividad);
            return;
        }

        // Verificar si ya fue evaluada en Evaluaciones.txt
        FILE *Evaluaciones = fopen("Evaluaciones.txt", "a+");
        if (Evaluaciones == NULL) {
            printf("Error al abrir el archivo Evaluaciones.txt.\n");
            return;
        }

        rewind(Evaluaciones);
        found = 0;

        while (fgets(line, sizeof(line), Evaluaciones)) {
            int idEstudiante;
            char idRegistrado[3];

            // Leer la información de evaluaciones
            sscanf(line, "%d;%*[^;];%*[^;];%2[^;];%*f;%*f", &idEstudiante, idRegistrado);

            // Si la actividad ya fue evaluada para el estudiante
            if (idEstudiante == est.idEstudiante && strcmp(idRegistrado, Activ.IdActividad) == 0) {
                printf("La actividad con el código %s ya ha sido evaluada para el estudiante %s.\n",
                    Activ.IdActividad, est.nombre);
                fclose(Evaluaciones);
                return;
            }
        }

        // Solicitar la nota de la actividad
        printf("Ingrese la nota obtenida en la actividad '%s' (código: %s): ", Activ.nombre, Activ.IdActividad);
        scanf("%f", &Activ.notaActividad);
        getchar();

        // Calcular la nota ponderada
        float notaPonderada = (Activ.notaActividad * Activ.PorcentajeActividad) / 100.0;

        // Actualizar la nota total del estudiante
        est.notaTotal += notaPonderada;

        // Registrar la evaluación en Evaluaciones.txt con los detalles requeridos
        fprintf(Evaluaciones, "%d;%s;%s;%s;%s;%.2f;%.2f\n",
                est.idEstudiante, est.nombre, prof.nombre_asignatura, Activ.IdActividad,
                Activ.nombre, Activ.notaActividad, notaPonderada);

        fclose(Evaluaciones);

        printf("Evaluación registrada correctamente para la materia: %s.\n", prof.nombre_asignatura);

    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.2.1

void editNotes() {
    Estudiante est;
    Profesor prof;
    Actividad activ;

    // Solicitar el ID del estudiante
    printf("\nIngrese el ID del estudiante: ");
    scanf("%d", &est.idEstudiante);
    getchar();

    // Solicitar el código de la actividad
    char idActividad[3];
    printf("\nIngrese el código de la actividad: ");
    fgets(idActividad, sizeof(idActividad), stdin);
    idActividad[strcspn(idActividad, "\n")] = '\0';

    // Abrir Evaluaciones.txt
    FILE *Evaluaciones = fopen("Evaluaciones.txt", "r+");
    if (Evaluaciones == NULL) {
        printf("Error al abrir el archivo Evaluaciones.txt.\n");
        return;
    }

    // Archivo temporal para almacenar los datos actualizados
    FILE *tempFile = fopen("TempEvaluaciones.txt", "w");
    if (tempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Evaluaciones);
        return;
    }

    char line[256];
    int found = 0;

    // Leer las evaluaciones existentes
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int idEstudiante;
        char nombreEstudiante[40], nombreAsignatura[30], idRegistrado[3], nombreActividad[30];
        float notaAnterior, notaPonderadaAnterior;

        // Extraer los campos de la evaluación
        sscanf(line, "%d;%39[^;];%29[^;];%2[^;];%29[^;];%f;%f",
               &idEstudiante, nombreEstudiante, nombreAsignatura, idRegistrado,
               nombreActividad, &notaAnterior, &notaPonderadaAnterior);

        // Verificar si coincide con la entrada
        if (idEstudiante == est.idEstudiante && strcmp(idRegistrado, idActividad) == 0) {
            found = 1;

            // Mostrar detalles de la evaluación
            printf("\nEvaluación encontrada para el estudiante '%s', asignatura '%s'.\n",
                   nombreEstudiante, nombreAsignatura);
            printf("Actividad: %s, Nota actual: %.2f, Ponderación: %.2f\n",
                   nombreActividad, notaAnterior, notaPonderadaAnterior);

            // Solicitar la nueva nota
            printf("Ingrese la nueva nota para la actividad '%s': ", nombreActividad);
            float nuevaNota;
            scanf("%f", &nuevaNota);
            getchar();

            // Calcular nueva nota ponderada
            float nuevaNotaPonderada = (nuevaNota * (notaPonderadaAnterior / notaAnterior));

            // Registrar en el archivo temporal
            fprintf(tempFile, "%d;%s;%s;%s;%s;%.2f;%.2f\n",
                    idEstudiante, nombreEstudiante, nombreAsignatura,
                    idRegistrado, nombreActividad, nuevaNota, nuevaNotaPonderada);

            printf("La nota de la actividad '%s' ha sido actualizada a %.2f.\n",
                   nombreActividad, nuevaNota);
        } else {
            // Copiar línea sin cambios al archivo temporal
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(Evaluaciones);
    fclose(tempFile);

    // Si la evaluación no fue encontrada
    if (!found) {
        printf("No se encontró una evaluación para el estudiante con ID %d y actividad %s.\n",
               est.idEstudiante, idActividad);
        remove("TempEvaluaciones.txt");
        return;
    }

    // Reemplazar Evaluaciones.txt con el archivo actualizado
    remove("Evaluaciones.txt");
    rename("TempEvaluaciones.txt", "Evaluaciones.txt");

    printf("La evaluación ha sido actualizada correctamente.\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.2.2

void deleteNote() {
    int idEstudiante;
    char idActividad[3];

    // Solicitar el ID del estudiante
    printf("\nIngrese el ID del estudiante: ");
    scanf("%d", &idEstudiante);
    getchar();

    // Solicitar el código de la actividad
    printf("\nIngrese el código de la actividad: ");
    fgets(idActividad, sizeof(idActividad), stdin);
    idActividad[strcspn(idActividad, "\n")] = '\0';

    // Abrir Evaluaciones.txt
    FILE *Evaluaciones = fopen("Evaluaciones.txt", "r");
    if (Evaluaciones == NULL) {
        printf("Error al abrir el archivo Evaluaciones.txt.\n");
        return;
    }

    // Crear un archivo temporal para almacenar las evaluaciones actualizadas
    FILE *tempFile = fopen("TempEvaluaciones.txt", "w");
    if (tempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Evaluaciones);
        return;
    }

    char line[256];
    int found = 0;

    // Leer las evaluaciones existentes
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int estudianteID;
        char nombreEstudiante[40], nombreAsignatura[30], actividadID[3], nombreActividad[30];
        float notaActividad, notaPonderada;

        // Extraer los campos de la evaluación
        sscanf(line, "%d;%39[^;];%29[^;];%2[^;];%29[^;];%f;%f",
               &estudianteID, nombreEstudiante, nombreAsignatura, actividadID,
               nombreActividad, &notaActividad, &notaPonderada);

        // Si no coincide con la entrada, escribir en el archivo temporal
        if (!(estudianteID == idEstudiante && strcmp(actividadID, idActividad) == 0)) {
            fprintf(tempFile, "%s", line);
        } else {
            found = 1; // Marcar que la evaluación fue encontrada
            printf("Evaluación eliminada: Estudiante '%s', Asignatura '%s', Actividad '%s'.\n",
                   nombreEstudiante, nombreAsignatura, nombreActividad);
        }
    }

    fclose(Evaluaciones);
    fclose(tempFile);

    // Si no se encontró la evaluación
    if (!found) {
        printf("No se encontró una evaluación para el estudiante con ID %d y actividad %s.\n",
               idEstudiante, idActividad);
        remove("TempEvaluaciones.txt");
        return;
    }

    // Reemplazar Evaluaciones.txt con el archivo actualizado
    remove("Evaluaciones.txt");
    rename("TempEvaluaciones.txt", "Evaluaciones.txt");

    printf("La evaluación ha sido eliminada correctamente.\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//2.3

void imprimirNotas() {
     FILE *Evaluaciones = fopen("Evaluaciones.txt", "r");
    if (Evaluaciones == NULL) {
        printf("Error al abrir el archivo Evaluaciones.txt.\n");
        return;
    }

    EstudianteData estudiantes[100];
    int numEstudiantes = 0;

    char line[256];

    // Leer cada línea del archivo y acumular datos por estudiante
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int idEstudiante;
        char nombre[80], idActividad[3], nombreActividad[40];
        float notaActividad, notaPonderada;

        // Leer los datos del archivo según el formato
        sscanf(line, "%d;%79[^;];%*[^;];%2[^;];%39[^;];%f;%f",
               &idEstudiante, nombre, idActividad, nombreActividad, &notaActividad, &notaPonderada);

        // Buscar si el estudiante ya está registrado
        int index = -1;
        for (int i = 0; i < numEstudiantes; i++) {
            if (estudiantes[i].idEstudiante == idEstudiante) {
                index = i;
                break;
            }
        }

        // Si no está registrado, agregar un nuevo estudiante
        if (index == -1) {
            index = numEstudiantes++;
            estudiantes[index].idEstudiante = idEstudiante;
            strcpy(estudiantes[index].nombre, nombre);
            estudiantes[index].sumaPonderada = 0.0;
            estudiantes[index].evaluaciones = 0;
        }

        // Actualizar la suma ponderada y el conteo de evaluaciones del estudiante
        estudiantes[index].sumaPonderada += notaPonderada;
        estudiantes[index].evaluaciones++;
    }

    fclose(Evaluaciones);

    // Imprimir encabezado de la tabla
    printf("+---------------+----------------------------------------------+----------------------+-------------------+-------------------+-------------------+\n");
    printf("| IdStudent     | Nombre                                       | Nombre de Actividad  | Nota Actividad    | Nota Ponderada    | Promedio          |\n");
    printf("+---------------+----------------------------------------------+----------------------+-------------------+-------------------+-------------------+\n");

    // Leer de nuevo para imprimir cada evaluación
    Evaluaciones = fopen("Evaluaciones.txt", "r");
    while (fgets(line, sizeof(line), Evaluaciones)) {
        int idEstudiante;
        char nombre[80], idActividad[3], nombreActividad[40];
        float notaActividad, notaPonderada;

        // Leer los datos del archivo según el formato
        sscanf(line, "%d;%79[^;];%*[^;];%2[^;];%39[^;];%f;%f",
               &idEstudiante, nombre, idActividad, nombreActividad, &notaActividad, &notaPonderada);

        // Obtener el promedio del estudiante
        float total = 0.0;
        for (int i = 0; i < numEstudiantes; i++) {
            if (estudiantes[i].idEstudiante == idEstudiante) {
                total = estudiantes[i].sumaPonderada;
                break;
            }
        }

        // Imprimir cada fila de la tabla
        printf("| %-13d | %-44s | %-20s | %-17.2f | %-17.2f | %-17.2f |\n",
               idEstudiante, nombre, nombreActividad, notaActividad, notaPonderada, total);
    }

    fclose(Evaluaciones);

    // Imprimir línea final de la tabla
    printf("+---------------+----------------------------------------------+----------------------+-------------------+-------------------+-------------------+\n");
}