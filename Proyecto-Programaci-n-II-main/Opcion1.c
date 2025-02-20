#include <stdio.h>
#include <string.h>
#include "Estructuras.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Teachers
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.1

void makeTeacher()
{
    int n; 

    printf("\n¿Cuántos profesores desea ingresar? ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++) {

        Profesor prof;
        int NumAsig;

        printf("\nIngrese el ID del docente: ");
        scanf("%i", &prof.idProfesor);

        FILE *Professor = fopen("Profesores.txt", "a+");
        if (Professor == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        char line[256];
        int found = 0;

        rewind(Professor); // Empezar desde el inicio 
        while (fgets(line, sizeof(line), Professor)) {
            int idRegistrado;
            sscanf(line, "%d", &idRegistrado);
            if (idRegistrado == prof.idProfesor) {
                printf("El profesor con ID %d ya se encuentra registrado.\n", prof.idProfesor);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Ingrese el nombre del profesor: ");
            getchar(); 
            fgets(prof.nombre, sizeof(prof.nombre), stdin);
            prof.nombre[strcspn(prof.nombre, "\n")] = '\0'; 

            printf("Número de asignaturas que dicta el profesor: ");
            scanf("%i", &NumAsig);
            getchar();

            for (int j = 1; j <= NumAsig; j++) {

                printf("Ingrese el nombre de la asignatura %i: ", j);
                fgets(prof.nombre_asignatura, sizeof(prof.nombre_asignatura), stdin);
                prof.nombre_asignatura[strcspn(prof.nombre_asignatura, "\n")] = '\0';

                fprintf(Professor, "%d;%s;%s\n", 
                    prof.idProfesor, prof.nombre, prof.nombre_asignatura);
                printf("Registrado correctamente.\n\n", j);

            }
        }

        fclose(Professor); // Cerrar el archivo
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.1.1

void editData() {

    int ID, NumAsig;
    Profesor prof;

    printf("\nIngrese el ID del docente que desea editar: ");
    scanf("%i", &ID);

    FILE *Professor = fopen("Profesores.txt", "r");
    if (Professor == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Professor);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), Professor)) {

        int idRegistrado;
        sscanf(line, "%d", &idRegistrado);

        if (idRegistrado == ID) {

            found = 1;

            printf("Ingrese el nuevo nombre del profesor: ");
            getchar(); 
            fgets(prof.nombre, sizeof(prof.nombre), stdin);
            prof.nombre[strcspn(prof.nombre, "\n")] = '\0';

            printf("Número de asignaturas que dicta el profesor: ");
            scanf("%i", &NumAsig);

            for (int j = 1; j <= NumAsig; j++) {
                getchar();
                printf("Ingrese el nombre de la asignatura %i: ", j);
                fgets(prof.nombre_asignatura, sizeof(prof.nombre_asignatura), stdin);
                prof.nombre_asignatura[strcspn(prof.nombre_asignatura, "\n")] = '\0';

                fprintf(TempFile, "%d;%s;%s\n", 
                    ID, prof.nombre, prof.nombre_asignatura);
            }
        } else {
            fputs(line, TempFile);
        }
    }

    fclose(Professor);
    fclose(TempFile);

    remove("Profesores.txt");
    rename("Temp.txt", "Profesores.txt");

    if (found) {
        printf("Los datos del profesor con ID %d han sido actualizados.\n", ID);
    } else {
        printf("No se encontró un profesor con el ID %d.\n", ID);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.1.2

void deleteTeacher() {

    int ID;
    int found = 0;

    printf("\nIngrese el ID del profesor que desea eliminar: ");
    scanf("%d", &ID);

    FILE *Professor = fopen("Profesores.txt", "r");
    if (Professor == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Professor);
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), Professor)) {
        
        int idRegistrado;
        sscanf(line, "%d", &idRegistrado); 

        if (idRegistrado == ID) {
            found = 1; 
            printf("Eliminando al profesor con ID %d.\n", ID);
            continue; 
        }

        fputs(line, TempFile);
    }

    fclose(Professor);
    fclose(TempFile);

    remove("Profesores.txt");
    rename("Temp.txt", "Profesores.txt");

    if (found) {
        printf("El profesor con ID %d ha sido eliminado exitosamente.\n", ID);
    } else {
        printf("No se encontró un profesor con el ID %d.\n", ID);
    }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.1.3

void showTeachers() {

    FILE *fpTemporal = fopen("Profesores.txt", "r");
    if (fpTemporal == NULL) {
        printf("Error al abrir el archivo para la lectura.\n");
        return;
    }

    char line[256];
    Profesor prof;

    printf("Listado de Profesores:\n");
    printf("+-------+----------------------+---------------------------+\n");
    printf("| %-5s | %-20s | %-25s |\n", "ID", "Nombre", "Asignatura");
    printf("+-------+----------------------+---------------------------+\n");

    while (fgets(line, sizeof(line), fpTemporal)) {
        if (!esLineaVacia(line)) {
            char *campo;

            // Leer y almacenar el ID del profesor
            campo = strtok(line, ";");
            if (campo != NULL) {
                prof.idProfesor = atoi(campo); // Convertir a entero
            }

            // Leer y almacenar el nombre del profesor
            campo = strtok(NULL, ";");
            if (campo != NULL) {
                strncpy(prof.nombre, campo, sizeof(prof.nombre) - 1);
                prof.nombre[sizeof(prof.nombre) - 1] = '\0';
                prof.nombre[strcspn(prof.nombre, "\n")] = '\0'; // Remover salto de línea
            }

            // Leer y almacenar la asignatura
            campo = strtok(NULL, ";");
            if (campo != NULL) {
                strncpy(prof.nombre_asignatura, campo, sizeof(prof.nombre_asignatura) - 1);
                prof.nombre_asignatura[sizeof(prof.nombre_asignatura) - 1] = '\0';
                prof.nombre_asignatura[strcspn(prof.nombre_asignatura, "\n")] = '\0'; // Remover salto de línea
            }

            // Imprimir los datos del profesor en formato de tabla
            printf("| %-5d | %-20s | %-25s |\n", prof.idProfesor, prof.nombre, prof.nombre_asignatura);
        }
    }

    printf("+-------+----------------------+---------------------------+\n");

    fclose(fpTemporal);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Subject
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.2

void makeSubject() {

    int n;
    printf("\nIngrese el numero de materias que desea ingresar: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {

        Asignatura Asign;

        printf("\nIngrese el codigo de la asignatura: ");
        fgets(Asign.idAsignatura, sizeof(Asign.idAsignatura), stdin);
        Asign.idAsignatura[strcspn(Asign.idAsignatura, "\n")] = '\0'; 

        FILE *Asignaturas = fopen("Asignaturas.txt", "r+");
        if (Asignaturas == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        char line[256];
        int found = 0;

        rewind(Asignaturas); 
        while (fgets(line, sizeof(line), Asignaturas)) {
            char idRegistrado[20];
            sscanf(line, "%[^;]", idRegistrado); 
            if (strcmp(idRegistrado, Asign.idAsignatura) == 0) {
                printf("La asignatura con el codigo %s ya se encuentra registrada.\n\n", Asign.idAsignatura);
                found = 1;
                break;
            }

        }

        if (!found) {
            
            getchar(); 
            printf("Ingrese el nombre de la asignatura: ");
            fgets(Asign.nombre, sizeof(Asign.nombre), stdin);
            Asign.nombre[strcspn(Asign.nombre, "\n")] = '\0'; 

            printf("Ingrese la cantidad de creditos que tiene la asignatura: ");
            scanf("%i", &Asign.creditos);
            getchar(); 

            if (Asign.creditos <= 0 && Asign.creditos > 5) {
                printf("La cantidad de créditos debe ser mayor a 0 y menor o igual a 5. Registro cancelado.\n");
                fclose(Asignaturas);
                continue;
            }

            fprintf(Asignaturas, "%s;%s;%i\n", Asign.idAsignatura, Asign.nombre, Asign.creditos);
            printf("Asignatura registrada correctamente.\n\n");

        }

        fclose(Asignaturas);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.2.1

void editSubject(){

    char idSubject[10];
    Asignatura Asign;

    printf("\nIngrese el codigo de la asignatura que desea editar: ");
    scanf("%s", idSubject);

    FILE *Asignaturas = fopen("Asignaturas.txt", "r");
    if (Asignaturas == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Asignaturas);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), Asignaturas)) {
        char idReg[10], nombre[50];
        int creditos;

        sscanf(line, "%[^;];%[^;];%d", idReg, nombre, &creditos);

        if (strcmp(idReg, idSubject) == 0) {
            found = 1;

            getchar();
            printf("Ingrese el nuevo nombre de la asignatura: ");
            fgets(Asign.nombre, sizeof(Asign.nombre), stdin);
            Asign.nombre[strcspn(Asign.nombre, "\n")] = '\0'; 

            printf("Ingrese la cantidad de creditos que tiene la asignatura: ");
            scanf("%d", &Asign.creditos);
            getchar(); 

            if (Asign.creditos <= 0 || Asign.creditos > 5) {
                printf("La cantidad de créditos debe ser mayor a 0 y menor o igual a 5. Registro cancelado.\n");
                fprintf(TempFile, "%s;%s;%d\n", idReg, nombre, creditos);
                continue;
            }

            fprintf(TempFile, "%s;%s;%d\n", idReg, Asign.nombre, Asign.creditos);
        } else {
            fputs(line, TempFile);
        }
    }

    fclose(Asignaturas);
    fclose(TempFile);

    remove("Asignaturas.txt");
    rename("Temp.txt", "Asignaturas.txt");

    if (found) {
        printf("Los datos de la asignatura con codigo %s han sido actualizados.\n", idSubject);
    } else {
        printf("No se encontró la asignatura con codigo %s.\n", idSubject);
    }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.2.2

void deleteSubject() {
    char idSubject[10];
    int found = 0;

    printf("\nIngrese el codigo de la asignatura que desea eliminar: ");
    scanf("%s", idSubject);

    FILE *Asignaturas = fopen("Asignaturas.txt", "r");
    if (Asignaturas == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Asignaturas);
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), Asignaturas)) {
        char idRegistrado[10];
        sscanf(line, "%[^;]", idRegistrado); // Leer el código de la asignatura

        if (strcmp(idRegistrado, idSubject) == 0) {
            found = 1; // Se encontró la asignatura a eliminar
            printf("Eliminando la asignatura con codigo %s.\n", idSubject);
            continue; // Saltar esta línea
        }

        fputs(line, TempFile); // Escribir las demás líneas al archivo temporal
    }

    fclose(Asignaturas);
    fclose(TempFile);

    // Reemplazar el archivo original con el temporal
    remove("Asignaturas.txt");
    rename("Temp.txt", "Asignaturas.txt");

    if (found) {
        printf("Los datos de la asignatura con codigo %s han sido eliminados.\n", idSubject);
    } else {
        printf("No se encontró la asignatura con codigo %s.\n", idSubject);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.2.3

void showSubjects(){

  FILE *fpTemporal = fopen("Asignaturas.txt", "r");
    if (fpTemporal == NULL) {
        printf("Error al abrir el archivo para la lectura.\n");
        return;
    }

    char line[256];
    Asignatura Asign; // Se asume que esta estructura tiene los campos: idAsignatura, nombre y creditos.

    printf("\n\n+-------------------------------------------------------------------+\n");
    printf("|%-60s|\n", "                            Asignaturas                            ");
    printf("+------------+-------------------------------------------+----------+\n");
    printf("| %-10s | %-41s | %-8s |\n", "Codigo", "Nombre", "Creditos");
    printf("+------------+-------------------------------------------+----------+\n");

    while (fgets(line, sizeof(line), fpTemporal)) {

        if (!esLineaVacia(line)) {

            char *campo = strtok(line, ";");
            if (campo != NULL) {
                strncpy(Asign.idAsignatura, campo, sizeof(Asign.idAsignatura) - 1);
                Asign.idAsignatura[sizeof(Asign.idAsignatura) - 1] = '\0';
            }

            campo = strtok(NULL, ";"); 
            if (campo != NULL) {
                strncpy(Asign.nombre, campo, sizeof(Asign.nombre) - 1);
                Asign.nombre[sizeof(Asign.nombre) - 1] = '\0';
            }

            campo = strtok(NULL, ";");
            if (campo != NULL) {
                Asign.creditos = atoi(campo);
            }

            printf("| %-10s | %-41s | %-8d |\n", Asign.idAsignatura, Asign.nombre, Asign.creditos);
        }
    }

    printf("+------------+-------------------------------------------+----------+\n");

    fclose(fpTemporal);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Subject
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.3

void asignSubject() {

    int n;

    printf("\nIngrese cuántas asignaturas desea asignar: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++) {
        Profesor prof;
        Asignatura asign;
        int NumAsig;

        printf("\nIngrese el ID del docente al que quiere asignar la asignatura: ");
        scanf("%i", &prof.idProfesor);

        FILE *Professor = fopen("Profesores.txt", "r");
        if (Professor == NULL) {
            printf("Error al abrir el archivo Profesores.txt.\n");
            return;
        }

        FILE *Asignaturas = fopen("Asignaturas.txt", "r");
        if (Asignaturas == NULL) {
            printf("Error al abrir el archivo Asignaturas.txt.\n");
            fclose(Professor);
            return;
        }

        FILE *Asignaciones = fopen("Asignaciones.txt", "a+");
        if (Asignaciones == NULL) {
            printf("Error al abrir el archivo Asignaciones.txt.\n");
            fclose(Professor);
            fclose(Asignaturas);
            return;
        }

        char line[256];
        int found = 0;

        // Buscar al profesor en el archivo Profesores.txt
        rewind(Professor);
        while (fgets(line, sizeof(line), Professor)) {
            int idRegistrado;
            char nombreProfesor[50], asignaturaProfesor[50];
            sscanf(line, "%d;%49[^;];%49[^\n]", &idRegistrado, nombreProfesor, asignaturaProfesor);

            if (idRegistrado == prof.idProfesor) {
                found = 1;
                strcpy(prof.nombre, nombreProfesor);

                printf("Ingrese el número de asignaturas que desea asignarle al profesor: ");
                scanf("%i", &NumAsig);

                for (int j = 1; j <= NumAsig; j++) {
                    printf("Ingrese el código de la asignatura %i: ", j);
                    scanf("%s", asign.idAsignatura);

                    // Verificar si la asignatura ya está asignada al profesor
                    rewind(Asignaciones);
                    int yaAsignada = 0;
                    while (fgets(line, sizeof(line), Asignaciones)) {
                        int idProfAsignado;
                        char asignaturaAsignada[20];
                        sscanf(line, "%d;%*[^;];%[^;]", &idProfAsignado, asignaturaAsignada);

                        if (idProfAsignado == prof.idProfesor &&
                            strcmp(asignaturaAsignada, asign.idAsignatura) == 0) {
                            yaAsignada = 1;
                            printf("La asignatura '%s' ya está asignada al profesor '%s' (ID: %d).\n",
                                   asign.idAsignatura, prof.nombre, prof.idProfesor);
                            break;
                        }
                    }

                    if (yaAsignada) {
                        continue;
                    }

                    // Buscar la asignatura en el archivo Asignaturas.txt
                    rewind(Asignaturas);
                    int found2 = 0;
                    while (fgets(line, sizeof(line), Asignaturas)) {
                        char idRegistradoA[20], nombreAsignatura[50];
                        int creditos;
                        sscanf(line, "%[^;];%49[^;];%d", idRegistradoA, nombreAsignatura, &creditos);

                        if (strcmp(idRegistradoA, asign.idAsignatura) == 0) {
                            found2 = 1;
                            strcpy(asign.nombre, nombreAsignatura);

                            // Escribir la asignación en el archivo Asignaciones.txt
                            fprintf(Asignaciones, "%d;%s;%s;%s\n",
                                    prof.idProfesor, prof.nombre,
                                    asign.idAsignatura, asign.nombre);

                            printf("Asignatura '%s' (código: %s) asignada al profesor '%s' (ID: %d).\n",
                                   asign.nombre, asign.idAsignatura,
                                   prof.nombre, prof.idProfesor);
                            break;
                        }
                    }

                    if (!found2) {
                        printf("La asignatura con código '%s' no está registrada.\n", asign.idAsignatura);
                    }
                }
                break;
            }
        }

        if (!found) {
            printf("El profesor identificado con ID %d no se encuentra registrado.\n", prof.idProfesor);
        }

        fclose(Professor);
        fclose(Asignaturas);
        fclose(Asignaciones);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.3.1

void editAsign() {

    FILE *Professor = fopen("Profesores.txt", "r");
    if (Professor == NULL) {
        printf("Error al abrir el archivo Profesores.txt.\n");
        return;
    }

    FILE *Asignaciones = fopen("Asignaciones.txt", "r+");
    if (Asignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        fclose(Professor);
        return;
    }

    int idProfesor;
    char codigoAsignatura[20];
    printf("Ingrese el ID del profesor para editar la asignación: ");
    scanf("%d", &idProfesor);

    // Verificar si el profesor existe en el archivo Profesores.txt
    char line[256];
    int profesorEncontrado = 0;
    while (fgets(line, sizeof(line), Professor)) {
        int idRegistrado;
        char nombreProfesor[50];
        sscanf(line, "%d;%49[^\n]", &idRegistrado, nombreProfesor);

        if (idRegistrado == idProfesor) {
            profesorEncontrado = 1;
            printf("Profesor encontrado: %s (ID: %d).\n", nombreProfesor, idRegistrado);
            break;
        }
    }

    if (!profesorEncontrado) {
        printf("El profesor con ID %d no se encuentra registrado.\n", idProfesor);
        fclose(Professor);
        fclose(Asignaciones);
        return;
    }

    printf("Ingrese el código de la asignatura a editar: ");
    scanf("%s", codigoAsignatura);

    // Crear archivo temporal para reescribir Asignaciones.txt
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(Professor);
        fclose(Asignaciones);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), Asignaciones)) {
        int idProfRegistrado;
        char idAsignatura[20], nombreProfesor[50], nombreAsignatura[50];
        sscanf(line, "%d;%49[^;];%19[^;];%49[^\n]", &idProfRegistrado, nombreProfesor, idAsignatura, nombreAsignatura);

        if (idProfRegistrado == idProfesor && strcmp(idAsignatura, codigoAsignatura) == 0) {
            found = 1;
            printf("Asignación encontrada: %s -> %s\n", nombreProfesor, nombreAsignatura);
            printf("Ingrese el nuevo código de la asignatura: ");
            char nuevoCodigo[20];
            scanf("%s", nuevoCodigo);

            printf("Ingrese el nuevo nombre de la asignatura: ");
            char nuevoNombre[50];
            scanf(" %[^\n]s", nuevoNombre);

            fprintf(temp, "%d;%s;%s;%s\n", idProfRegistrado, nombreProfesor, nuevoCodigo, nuevoNombre);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    if (!found) {
        printf("No se encontró la asignación especificada para el profesor con ID %d.\n", idProfesor);
    }

    fclose(Professor);
    fclose(Asignaciones);
    fclose(temp);

    remove("Asignaciones.txt");
    rename("temp.txt", "Asignaciones.txt");

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.3.2

void deleteAsign() {

    FILE *Asignaciones = fopen("Asignaciones.txt", "r");
    if (Asignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        return;
    }

    int idProfesor;
    char codigoAsignatura[20];
    printf("Ingrese el ID del profesor para eliminar la asignación: ");
    scanf("%d", &idProfesor);
    printf("Ingrese el código de la asignatura a eliminar: ");
    scanf("%s", codigoAsignatura);

    char line[256];
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(Asignaciones);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), Asignaciones)) {
        int idProfRegistrado;
        char idAsignatura[20], nombreProfesor[50], nombreAsignatura[50];
        sscanf(line, "%d;%49[^;];%19[^;];%49[^\n]", &idProfRegistrado, nombreProfesor, idAsignatura, nombreAsignatura);

        if (idProfRegistrado == idProfesor && strcmp(idAsignatura, codigoAsignatura) == 0) {
            found = 1;
            printf("Asignación eliminada: %s -> %s\n", nombreProfesor, nombreAsignatura);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    if (!found) {
        printf("No se encontró la asignación especificada.\n");
    }

    fclose(Asignaciones);
    fclose(temp);
    remove("Asignaciones.txt");
    rename("temp.txt", "Asignaciones.txt");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.3.3
void showAsigns(){
    FILE *fpAsignaciones = fopen("Asignaciones.txt", "r");
    if (fpAsignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        return;
    }

    char line[256];
    int idProfesor;
    char nombreProfesor[50], idAsignatura[20], nombreAsignatura[50];

    printf("\n+------------------------------------------------------------------------------------+\n");
    printf("|                                    Asignaciones                                     |\n");
    printf("+------------+------------------------------+--------------+-------------------------+\n");
    printf("| %-10s | %-28s | %-12s | %-23s |\n", "IdProfesor", "Nombre Profesor", "IdAsignatura", "Nombre Asignatura");
    printf("+------------+------------------------------+--------------+-------------------------+\n");

    // Leer y mostrar cada asignación
    while (fgets(line, sizeof(line), fpAsignaciones)) {
        sscanf(line, "%d;%49[^;];%[^;];%49[^\n]", &idProfesor, nombreProfesor, idAsignatura, nombreAsignatura);
        printf("| %-10d | %-28s | %-12s | %-23s |\n", idProfesor, nombreProfesor, idAsignatura, nombreAsignatura);
    }

    printf("+------------+------------------------------+--------------+-------------------------+\n");

    fclose(fpAsignaciones);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Students
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.4

void makeStudent(){
    int n; 

    printf("\n¿Cuántos estudiantes desea ingresar? ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++) {

        Estudiante student;

        printf("\nIngrese el ID del estudiante: ");
        scanf("%i", &student.idEstudiante);

        FILE *Estudiantees = fopen("Estudiantes.txt", "a+");
        if (Estudiantees == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }

        char line[256];
        int found = 0;

        rewind(Estudiantees); // Empezar desde el inicio 
        while (fgets(line, sizeof(line), Estudiantees)) {
            int idRegistrado;
            sscanf(line, "%d", &idRegistrado);
            if (idRegistrado == student.idEstudiante) {
                printf("El estudiante con ID %d ya se encuentra registrado.\n", student.idEstudiante);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Ingrese el nombre del estudiante: ");
            getchar(); 
            fgets(student.nombre, sizeof(student.nombre), stdin);
            student.nombre[strcspn(student.nombre, "\n")] = '\0'; 

            printf("Ingrese el semestre que cursa: ");
            scanf("%i", &student.semestre);

            fprintf(Estudiantees, "%i;%s;%i\n", student.idEstudiante, student.nombre, student.semestre);
            printf("Registrado correctamente.\n\n");

        }

        fclose(Estudiantees);

    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.4.1

void editEstudent() {

    int NumAsig;
    Estudiante student;

    printf("\nIngrese el ID del estudiante que desea editar: ");
    scanf("%i", &student.idEstudiante);

    FILE *Estudiantes = fopen("Estudiantes.txt", "r");
    if (Estudiantes == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Estudiantes);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), Estudiantes)) {

        int idRegistrado;
        sscanf(line, "%d", &idRegistrado);

        if (idRegistrado == student.idEstudiante) {

            found = 1;

            printf("Ingrese el nombre del estudiante: ");
            getchar(); 
            fgets(student.nombre, sizeof(student.nombre), stdin);
            student.nombre[strcspn(student.nombre, "\n")] = '\0';

            printf("Semestre que se encuentra cursando: ");
            scanf("%i", &student.semestre);

            
            fprintf(TempFile, "%i;%s;%i\n", student.idEstudiante, student.nombre, student.semestre);
            
        } else {
            fputs(line, TempFile);
        }
    }

    fclose(Estudiantes);
    fclose(TempFile);

    remove("Estudiantes.txt");
    rename("Temp.txt", "Estudiantes.txt");

    if (found) {
        printf("Los datos del profesor con ID %d han sido actualizados.\n", student.idEstudiante);
    } else {
        printf("No se encontró un profesor con el ID %d.\n", student.idEstudiante);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.4.2

void deleteStudent(){

    int ID;
    int found = 0;

    printf("\nIngrese el ID del profesor que desea eliminar: ");
    scanf("%d", &ID);

    FILE *Estudiantes = fopen("Estudiantes.txt", "r");
    if (Estudiantes == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *TempFile = fopen("Temp.txt", "w");
    if (TempFile == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(Estudiantes);
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), Estudiantes)) {
        
        int idRegistrado;
        sscanf(line, "%d", &idRegistrado); 

        if (idRegistrado == ID) {
            found = 1; 
            printf("Eliminando al estudiante con ID %d.\n", ID);
            continue; 
        }

        fputs(line, TempFile);
    }

    fclose(Estudiantes);
    fclose(TempFile);

    remove("Estudiantes.txt");
    rename("Temp.txt", "Estudiantes.txt");

    if (found) {
        printf("El Estudiante con ID %d ha sido eliminado exitosamente.\n", ID);
    } else {
        printf("No se encontró un Estudiantes con el ID %d.\n", ID);
    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.4.3

void showEstudents() {
    FILE *fpTemporal = fopen("Estudiantes.txt", "r");
    if (fpTemporal == NULL) {
        printf("Error al abrir el archivo para la lectura.\n");
        return;
    }

    char line[256];
    Estudiante student;

    // Imprimir encabezado de la tabla
    printf("\n+-------------------------------------------------------------------+\n");
    printf("|%-60s|\n", "                            Estudiantes                            ");
    printf("+------------+-------------------------------------------+----------+\n");
    printf("| %-10s | %-41s | %-8s |\n", "ID", "Nombre", "Semestre");
    printf("+------------+-------------------------------------------+----------+\n");

    while (fgets(line, sizeof(line), fpTemporal)) {
        if (!esLineaVacia(line)) {
            char *campo;

            // Extraer el campo ID
            campo = strtok(line, ";");
            if (campo != NULL) {
                student.idEstudiante = atoi(campo);
            }

            // Extraer el nombre
            campo = strtok(NULL, ";"); 
            if (campo != NULL) {
                strncpy(student.nombre, campo, sizeof(student.nombre) - 1);
                student.nombre[sizeof(student.nombre) - 1] = '\0'; // Asegurarse de que sea una cadena válida
            }

            // Extraer el semestre
            campo = strtok(NULL, ";");
            if (campo != NULL) {
                student.semestre = atoi(campo);
            }

            // Imprimir los datos del estudiante con formato
            printf("| %-10d | %-41s | %-8d |\n", student.idEstudiante, student.nombre, student.semestre);
        }
    }

    // Cierre de la tabla
    printf("+------------+-------------------------------------------+----------+\n");

    fclose(fpTemporal);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Subject
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.5

void asignStudent() {

    int n;

    printf("\nIngrese cuántas asignaturas desea asignar: ");
    scanf("%i", &n);

    for (int i = 0; i < n; i++) {
        Estudiante student;
        Asignatura asign;
        int NumAsig;

        printf("\nIngrese el ID del estudiante al que quiere asignar la asignatura: ");
        scanf("%i", &student.idEstudiante);

        FILE *Estudiantes = fopen("Estudiantes.txt", "r");
        if (Estudiantes == NULL) {
            printf("Error al abrir el archivo Profesores.txt.\n");
            return;
        }

        FILE *Asignaturas = fopen("Asignaturas.txt", "r");
        if (Asignaturas == NULL) {
            printf("Error al abrir el archivo Asignaturas.txt.\n");
            fclose(Estudiantes);
            return;
        }

        FILE *Asignaciones = fopen("AsignacionesEstudiantes.txt", "a+");
        if (Asignaciones == NULL) {
            printf("Error al abrir el archivo Asignaciones.txt.\n");
            fclose(Estudiantes);
            fclose(Asignaturas);
            return;
        }

        char line[256];
        int found = 0;

        rewind(Estudiantes);
        while (fgets(line, sizeof(line), Estudiantes)) {
            int idRegistrado;
            char nombreEstudiante[50], asignaturaEstudiante[50];
            sscanf(line, "%d;%49[^;];%49[^\n]", &idRegistrado, nombreEstudiante, asignaturaEstudiante);

            if (idRegistrado == student.idEstudiante) {
                found = 1;
                strcpy(student.nombre, nombreEstudiante);

                printf("Ingrese el número de asignaturas que desea asignarle al estudiante: ");
                scanf("%i", &NumAsig);

                for (int j = 1; j <= NumAsig; j++) {
                    printf("Ingrese el código de la asignatura %i: ", j);
                    scanf("%s", asign.idAsignatura);

                    // Verificar si la asignatura ya está asignada al profesor
                    rewind(Asignaciones);
                    int yaAsignada = 0;
                    while (fgets(line, sizeof(line), Asignaciones)) {
                        int idProfAsignado;
                        char asignaturaAsignada[20];
                        sscanf(line, "%d;%*[^;];%[^;]", &idProfAsignado, asignaturaAsignada);

                        if (idProfAsignado == student.idEstudiante &&
                            strcmp(asignaturaAsignada, asign.idAsignatura) == 0) {
                            yaAsignada = 1;
                            printf("La asignatura '%s' ya está asignada al estudiante '%s' (ID: %d).\n",
                                   asign.idAsignatura, student.nombre, student.idEstudiante);
                            break;
                        }
                    }

                    if (yaAsignada) {
                        continue;
                    }

                    // Buscar la asignatura en el archivo Asignaturas.txt
                    rewind(Asignaturas);
                    int found2 = 0;
                    while (fgets(line, sizeof(line), Asignaturas)) {
                        char idRegistradoA[20], nombreAsignatura[50];
                        int creditos;
                        sscanf(line, "%[^;];%49[^;];%d", idRegistradoA, nombreAsignatura, &creditos);

                        if (strcmp(idRegistradoA, asign.idAsignatura) == 0) {
                            found2 = 1;
                            strcpy(asign.nombre, nombreAsignatura);

                            // Escribir la asignación en el archivo Asignaciones.txt
                            fprintf(Asignaciones, "%d;%s;%s;%s\n",
                                    student.idEstudiante, student.nombre,
                                    asign.idAsignatura, asign.nombre);

                            printf("Asignatura '%s' (código: %s) asignada al estudiante '%s' (ID: %d).\n",
                                   asign.nombre, asign.idAsignatura,
                                   student.nombre, student.idEstudiante);
                            break;
                        }
                    }

                    if (!found2) {
                        printf("La asignatura con código '%s' no está registrada.\n", asign.idAsignatura);
                    }
                }
                break;
            }
        }

        if (!found) {
            printf("El estudiante identificado con ID %d no se encuentra registrado.\n", student.idEstudiante);
        }

        fclose(Estudiantes);
        fclose(Asignaturas);
        fclose(Asignaciones);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.5.1

void editAsignStudent() {

    FILE *Estudiantes = fopen("Estudiantes.txt", "r");
    if (Estudiantes == NULL) {
        printf("Error al abrir el archivo Profesores.txt.\n");
        return;
    }

    FILE *Asignaciones = fopen("AsignacionesEstudiantes.txt", "r+");
    if (Asignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        fclose(Estudiantes);
        return;
    }

    int idStudent;
    char codigoAsignatura[20];
    printf("Ingrese el ID del estudiante para editar la asignación: ");
    scanf("%d", &idStudent);

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), Estudiantes)) {
        int idRegistrado;
        char nameStudent[50];
        sscanf(line, "%d;%49[^\n]", &idRegistrado, nameStudent);

        if (idRegistrado == idStudent) {
            found = 1;
            printf("Estudiante encontrado: %s (ID: %d).\n", nameStudent, idRegistrado);
            break;
        }
    }

    if (!found) {
        printf("El estudiante con ID %d no se encuentra registrado.\n", idStudent);
        fclose(Estudiantes);
        fclose(Asignaciones);
        return;
    }

    printf("Ingrese el código de la asignatura a asignar: ");
    scanf("%s", codigoAsignatura);

    // Crear archivo temporal para reescribir Asignaciones.txt
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(Estudiantes);
        fclose(Asignaciones);
        return;
    }

    found = 0;
    while (fgets(line, sizeof(line), Asignaciones)) {
        int idStdRegistrado;
        char idAsignatura[20], nombreProfesor[50], nombreAsignatura[50];
        sscanf(line, "%d;%49[^;];%19[^;];%49[^\n]", &idStdRegistrado, nombreProfesor, idAsignatura, nombreAsignatura);

        if (idStdRegistrado == idStudent && strcmp(idAsignatura, codigoAsignatura) == 0) {
            found = 1;
            printf("Asignación encontrada: %s -> %s\n", nombreProfesor, nombreAsignatura);
            printf("Ingrese el nuevo código de la asignatura: ");
            char nuevoCodigo[20];
            scanf("%s", nuevoCodigo);

            printf("Ingrese el nuevo nombre de la asignatura: ");
            char nuevoNombre[50];
            scanf(" %[^\n]s", nuevoNombre);

            fprintf(temp, "%d;%s;%s;%s\n", idStdRegistrado, nombreProfesor, nuevoCodigo, nuevoNombre);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    if (!found) {
        printf("No se encontró la asignación especificada para el estudiante con ID %d.\n", idStudent);
    }

    fclose(Estudiantes);
    fclose(Asignaciones);
    fclose(temp);

    remove("AsignacionesEstudiantes.txt");
    rename("temp.txt", "AsignacionesEstudiantes.txt");

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.5.2

void deleteAsignStudent() {

    FILE *Asignaciones = fopen("AsignacionesEstudiantes.txt", "r");
    if (Asignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        return;
    }

    int idStudent;
    char codigoAsignatura[20];
    printf("Ingrese el ID del estudiante para eliminar la asignación: ");
    scanf("%d", &idStudent);
    printf("Ingrese el código de la asignatura a eliminar: ");
    scanf("%s", codigoAsignatura);

    char line[256];
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(Asignaciones);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), Asignaciones)) {
        int idStdRegistrado;
        char idAsignatura[20], nombreEStudent[50], nombreAsignatura[50];
        sscanf(line, "%d;%49[^;];%19[^;];%49[^\n]", &idStdRegistrado, nombreEStudent, idAsignatura, nombreAsignatura);

        if (idStdRegistrado == idStudent && strcmp(idAsignatura, codigoAsignatura) == 0) {
            found = 1;
            printf("Asignación eliminada: %s -> %s\n", nombreEStudent, nombreAsignatura);
        } else {
            fprintf(temp, "%s", line);
        }
    }

    if (!found) {
        printf("No se encontró la asignación especificada.\n");
    }

    fclose(Asignaciones);
    fclose(temp);
    remove("AsignacionesEstudiantes.txt");
    rename("temp.txt", "AsignacionesEstudiantes.txt");

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//1.5.3
void showAsignStudents(){

    FILE *fpAsignaciones = fopen("AsignacionesEstudiantes.txt", "r");
    if (fpAsignaciones == NULL) {
        printf("Error al abrir el archivo Asignaciones.txt.\n");
        return;
    }

    char line[256];
    int idStudents;
    char nombrEstudiante[50], idAsignatura[20], nombreAsignatura[50];

    printf("\n+------------------------------------------------------------------------------------+\n");
    printf("|                                    Asignaciones                                     |\n");
    printf("+------------+------------------------------+--------------+-------------------------+\n");
    printf("| %-10s | %-28s | %-12s | %-23s |\n", "IdStudent", "Nombre Estudiante", "IdAsignatura", "Nombre Asignatura");
    printf("+------------+------------------------------+--------------+-------------------------+\n");

    // Leer y mostrar cada asignación
    while (fgets(line, sizeof(line), fpAsignaciones)) {
        sscanf(line, "%d;%49[^;];%[^;];%49[^\n]", &idStudents, nombrEstudiante, idAsignatura, nombreAsignatura);
        printf("| %-10d | %-28s | %-12s | %-23s |\n", idStudents, nombrEstudiante, idAsignatura, nombreAsignatura);
    }

    printf("+------------+------------------------------+--------------+-------------------------+\n");

    fclose(fpAsignaciones);

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------