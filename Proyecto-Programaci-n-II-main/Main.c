#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estructuras.c"
#include "Opcion1.c"
#include "Opcion2.c"
#include "Opcion3.c"

void MakeMenu(){

    int opc = 0; 
    char opc2[10]; 

    do {

        printf("\n-----------------------------------------------------Menú del Proyecto-----------------------------------------------------\n");
        printf("\n1. Administrador\n");
        printf("   1.1 Crear perfil del profesor\n");
        printf("       1.1.1 Editar datos\n");
        printf("       1.1.2 Eliminar\n");
        printf("       1.1.3 Listar Profesores\n");
        printf("   1.2 Crear perfil de la asignatura\n");
        printf("       1.2.1 Editar datos\n");
        printf("       1.2.2 Eliminar\n");
        printf("       1.2.3 Listar Asignatura\n");
        printf("   1.3 Asignar materia al profesor\n");
        printf("       1.3.1 Editar datos\n");
        printf("       1.3.2 Eliminar asignación\n");
        printf("       1.3.3 Listar Asignatura y su profesor\n");
        printf("   1.4 Crear perfil estudiante\n");
        printf("       1.4.1 Editar datos\n");
        printf("       1.4.2 Eliminar\n");
        printf("       1.4.3 Listar estudiantes\n");
        printf("   1.5 Asignar materia al estudiante\n");
        printf("       1.5.1 Editar datos\n");
        printf("       1.5.2 Eliminar asignación\n");
        printf("       1.5.3 Listar Asignatura y sus estudiantes\n");
        printf("2. Docente\n");
        printf("   2.1 Crear actividades y sus porcentajes de la materia\n");
        printf("       2.1.1 Editar actividades\n");
        printf("       2.1.2 Eliminar actividad\n");
        printf("       2.1.3 Listar actividades\n");
        printf("   2.2 Crear notas para la actividad\n");
        printf("       2.2.1 Modificar notas\n");
        printf("       2.2.2 Eliminar notas\n");
        printf("   2.3 Mostrar notas de todos los estudiantes\n");
        printf("3. Estudiante\n");
        printf("   3.1 Mostrar todas las notas\n");
        printf("   3.2 Mostrar n  otas de una materia específica\n");
        printf("\n\nTener en cuenta:\n");
        printf("- Que las notas van de 0.0 a 5.0.\n");
        printf("- Las cédulas no se repiten.\n");
        printf("- El código de la materia no se repite.\n");
        printf("\nSeleccione una opcion: ");
        scanf("%i", &opc); 
        
        if (opc == 0) {
            printf("Saliendo del programa...\n");
            system("cls"); 
        } else if (opc == 1) {
            printf("\n1. Administrador\n");
            printf("  1.1 Crear perfil del profesor\n");
            printf("  1.2 Crear perfil de la asignatura\n");
            printf("  1.3 Asignar materia al profesor\n");
            printf("  1.4 Crear perfil estudiante\n");
            printf("  1.5 Asignar materia al estudiante\n");
            printf("Selecciona una subopción: ");
            scanf("%s", opc2);

            if (strcmp(opc2, "1.1") == 0) {
                printf("1.1 Crear perfil del profesor.\n");
                makeTeacher(); 
                printf("\n0. Volver al menu principal.\n");
                printf("  1.1.1 Editar datos\n");
                printf("  1.1.2 Eliminar\n");
                printf("  1.1.3 Listar profesores\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "1.1.1") == 0) {
                    printf("1.1.1 Editar datos.\n");
                    editData();
                } else if (strcmp(opc2, "1.1.2") == 0) {
                    printf("1.1.2 Eliminar.\n");
                    deleteTeacher();
                } else if (strcmp(opc2, "1.1.3") == 0) {
                    printf("1.1.3 Listar Profesores\n");
                    showTeachers();
                } else if (strcmp (opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }

            } else if (strcmp(opc2, "1.2") == 0) {
                printf("1.2 Crear perfil de la asignatura.\n");
                makeSubject();
                printf("\n0. Volver al menu principal\n");
                printf("  1.2.1 Editar datos\n");
                printf("  1.2.2 Eliminar\n");
                printf("  1.2.3 Lista1r asignatura\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "1.2.1") == 0) {
                    printf("1.2.1 Editar datos.\n");
                    editSubject();
                } else if (strcmp(opc2, "1.2.2") == 0) {
                    printf("1.2.2 Eliminar.\n");
                    deleteSubject();
                } else if (strcmp(opc2, "1.2.3") == 0) {
                    printf("1.2.3 Listar asignatura");
                    showSubjects();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }
                
            } else if (strcmp(opc2, "1.3") == 0) {
                printf("1.3 Asignar materia al profesor.\n");
                asignSubject();
                printf("\n0. Volver al menu principal.\n");
                printf("  1.3.1 Editar datos\n");
                printf("  1.3.2 Eliminar\n");
                printf("  1.3.3 Listar asignatura y su profesor\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "1.3.1") == 0) {
                    printf("1.3.1 Editar datos.\n");
                    editAsign();
                } else if (strcmp(opc2, "1.3.2") == 0) {
                    printf("1.3.2 Eliminar.\n");
                    deleteAsign();
                } else if (strcmp(opc2, "1.3.3") == 0) {
                    printf("1.3.3 Listar asignatura y su profesor");
                    showAsigns();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }

            } else if (strcmp(opc2, "1.4") == 0) {
                printf("1.4 Crear perfil estudiante.\n");
                makeStudent();
                printf("\n0. Volver al menu principal\n");
                printf("  1.4.1 Editar datos\n");
                printf("  1.4.2 Eliminar\n");
                printf("  1.4.3 Listar estudiantes\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "1.4.1") == 0) {
                    printf("1.4.1 Editar datos.\n");
                    editEstudent();
                } else if (strcmp(opc2, "1.4.2") == 0) {
                    printf("1.4.2 Eliminar.\n");
                    deleteStudent();
                } else if (strcmp(opc2, "1.4.3") == 0) {
                    printf("1.4.3 Listar estudiantes");
                    showEstudents();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }

            } else if (strcmp(opc2, "1.5") == 0) {
                printf("1.5 Asignar materia al estudiante.\n");
                asignStudent();
                printf("\n 0. Volver al menu principal\n");
                printf("  1.5.1 Editar datos\n");
                printf("  1.5.2 Eliminar\n");
                printf("  1.5.3 Listar asignatura y sus estudiantes\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "1.5.1") == 0) {
                    printf("1.5.1 Editar datos.\n");
                    editAsignStudent();
                } else if (strcmp(opc2, "1.5.2") == 0) {
                    printf("1.5.2 Eliminar.\n");
                    deleteAsignStudent();
                } else if (strcmp(opc2, "1.5.3") == 0) {
                    printf("1.5.3 Listar asignatura y sus estudiantes");
                    showAsignStudents();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }

            } else {
                printf("Subopción inválida.\n");
            }
            
        } else if (opc == 2) {
            printf("\n2. Docente\n");
            printf("  2.1 Crear actividades y sus porcentajes de la materia\n");
            printf("  2.2 Crear notas para la actividad\n");
            printf("  2.3 Mostrar notas de todos los estudiantes\n");
            printf("Selecciona una subopción: ");
            scanf("%s", opc2);

            if (strcmp(opc2, "2.1") == 0) {
                printf("2.1 Crear actividades.\n");
                createActivities();
                printf("\n0. Volver al menu principal.\n");
                printf("  2.1.1 Editar datos\n");
                printf("  2.1.2 Eliminar\n");
                printf("  2.1.3 Listar asignatura y su profesor\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "2.1.1") == 0) {
                    printf("2.1.1 Editar actividad.\n");
                    editActivities();
                } else if (strcmp(opc2, "2.1.2") == 0) {
                    printf("2.1.2 Eliminar actividad\n");
                    deleteActivity();
                } else if (strcmp(opc2, "2.1.3") == 0) {
                    printf("2.1.3 Listar actividades");
                    showActivities();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }
            } else if (strcmp(opc2, "2.2") == 0) {
                printf("2.2 Crear notas para la actividad.\n");
                asignarNotas();
                printf("\n0. Volver al menu principal.\n");
                printf("  2.2.1 Editar Notas\n");
                printf("  2.2.2 Eliminar Notas\n");
                printf("Selecciona una subopción: ");
                scanf("%s", opc2);
                if (strcmp(opc2, "2.2.1") == 0) {
                    printf("2.2.1 Editar Notas.\n");
                    editNotes();
                } else if (strcmp(opc2, "2.2.2") == 0) {
                    printf("2.2.2 Eliminar Notas\n");
                    deleteNote();
                } else if (strcmp(opc2, "0") == 0) {
                    printf("Volver al menu principal.\n");
                    system("pause");
                    system("cls");
                    MakeMenu();
                }
            } else if (strcmp(opc2, "2.3") == 0) {
                printf("2.3 Mostrar notas de todos los estudiantes.\n");
                imprimirNotas();
            } else {
                printf("Subopción inválida.\n");
            }
        } else if (opc == 3) {
            printf("\n3. Estudiante\n");
            printf("  3.1 Mostrar todas las notas\n");
            printf("  3.2 Mostrar notas de una materia específica\n");
            printf("Selecciona una subopción: ");
            scanf("%s", opc2);

            if (strcmp(opc2, "3.1") == 0) {
                printf("3.1 Mostrar todas las notas.\n");
                showNotes();
            } else if (strcmp(opc2, "3.2") == 0) {
                printf("3.2 Mostrar notas de una materia específica.\n");
                showNotesAsign();
            } else {
                printf("Subopción inválida.\n");
            }
        } else {
            printf("¡Opción incorrecta!\n");
        }
    } while (opc != 0);

}

int main(){

    MakeMenu();
    
}