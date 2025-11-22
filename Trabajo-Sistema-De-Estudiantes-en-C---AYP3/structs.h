#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMO_NOMBRE 50
#define MAXIMO_MATERIAS 20

// STRUCT MATERIA 
typedef struct {
    int id_materia;
    char nombre[MAXIMO_NOMBRE];
    int aprobada;  // 0 = cursando, 1 = aprobada
    int nota;
} MateriaCursada; 

// STRUCT ESTUDIANTE
typedef struct {
    int id;
    char nombre[MAXIMO_NOMBRE];
    int edad;
    MateriaCursada materias[MAXIMO_MATERIAS];
    int cantidad_materias;
} Estudiante;

// STRUCT MATERIA 
typedef struct {
    int id;
    char nombre[MAXIMO_NOMBRE];
    int cupo_actual;
} Materia;


// NODOS DE LA LISTA ENLAZADA PARA ESTUDIANTES O MATERIAS
typedef struct{
    Estudiante datos;
    struct NodoEstudiante* siguiente;
} NodoEstudiante;

typedef struct{
    Materia datos;
    struct NodoMateria* siguiente;
} NodoMateria;


// FUNCIONES ESTUDIANTES
void darDeAltaEstudiante(NodoEstudiante** lista);
void listarEstudiantes(NodoEstudiante* lista);
void modificarEstudiante(NodoEstudiante* lista, int id);
void darDeBajaEstudiante(NodoEstudiante** lista, int id);
void buscarEstudiantePorNombre(NodoEstudiante* lista, char* nombre);
void buscarEstudiantePorEdad(NodoEstudiante* lista, int min, int max);

// FUNCIONES MATERIAS
void darDeAltaMateria(NodoMateria** lista);
void listarMaterias(NodoMateria* lista);
void modificarMateria(NodoMateria* lista, int id);
void eliminarMateria(NodoMateria** lista, int id);

// FUNCION INSCRIBIR Y RENDIR MATERIA 
void inscribir(Estudiante* estudiante, NodoMateria* lista);
void RendirMateria(Estudiante* estudiante, int nota);

// LIMPIAR LISTAS
void liberarListaEstudiantes(NodoEstudiante* lista);
void liberarListaMaterias(NodoMateria* lista);
