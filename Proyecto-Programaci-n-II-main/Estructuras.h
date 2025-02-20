#ifndef Estructuras_h
#define Estructuras_h

#include <stdio.h>
//#include "Estructuras.c"


// Estructura para las notas
typedef struct {
    char idMateria[6];         
    float calificacion;   
    int porcentaje;  
} Nota;

// Estructura para las materias
typedef struct {
    char idAsignatura[6];         
    char nombre[40];       
    int creditos;   
} Asignatura;

// Estructura para los estudiantes
typedef struct {
    int idEstudiante;      
    char nombre[40];
    int semestre;       
    float notaTotal;          
} Estudiante;

// Estructura para los profesores
typedef struct {
    int idProfesor;        
    char nombre[30];    
    char nombre_asignatura[30];     
} Profesor;

typedef struct {
    int PorcentajeActividad;
    char nombre[30];
    char IdActividad[3];
    float notaActividad;
} Actividad;

typedef struct {
        int idEstudiante;
        char nombre[40];
        float sumaPonderada;
        int evaluaciones;
    } EstudianteData;

// Funciones declaradas
int esLineaVacia (const char *linea);

#endif
