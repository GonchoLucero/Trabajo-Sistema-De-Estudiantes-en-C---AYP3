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
typedef struct NodoEstudiante {
    Estudiante datos;
    struct NodoEstudiante* siguiente;
} NodoEstudiante;

typedef struct NodoMateria {
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
int inscribirseAMateria(NodoEstudiante* lista1, NodoMateria* lista2, int id1, int id2);
int rendirExamen(NodoEstudiante* lista, int id1, int id2, int nota);

// FUNCIONES AUXILIARES
NodoEstudiante* buscarEstudiantePorId(NodoEstudiante* lista, int id);
int idUnicoEstudiante(NodoEstudiante* lista);
NodoMateria* buscarMateria(NodoMateria* lista, int id);

// FUNCIONES PUNTOS EXTRAS
void calcularPromedioEstudiante(NodoEstudiante* lista);
void calcularEstadisticasMateria(NodoEstudiante* lista);


// LIMPIAR LISTAS
void liberarListaEstudiantes(NodoEstudiante* lista);
void liberarListaMaterias(NodoMateria* lista);