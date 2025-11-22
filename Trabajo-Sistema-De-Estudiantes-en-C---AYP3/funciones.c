#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// NODO ESTUDIANTE
NodoEstudiante* crearNodoEstudiante(Estudiante est){
    NodoEstudiante* nuevoEstudiante = (NodoEstudiante*)malloc(sizeof(NodoEstudiante));
    if (nuevoEstudiante == NULL)
    {
        printf("Error: No se pudo asignar memoria");
        return;
    }
    nuevoEstudiante->datos = est;
    nuevoEstudiante->siguiente = NULL;
    return nuevoEstudiante;
}

// ID UNICO PARA ESTUDIANTE
int idUnicoEstudiante(NodoEstudiante* lista){
    int maximo_id = 0;
    NodoEstudiante* actual = lista;
    while (actual != NULL)
    {
        if (actual->datos.id > maximo_id)
        {
            maximo_id = actual->datos.id;
        }
        actual = actual->siguiente;
    }
    return maximo_id + 1;
}

// FUNCIONES ESTUDIANTES
// ALTA
void darDeAltaEstudiante(NodoEstudiante** lista){
    Estudiante nuevoEstudiante;
    
    // ID
    nuevoEstudiante.id = generarIdEstudiante(*lista);
    nuevoEstudiante.cantidad_materias = 0;
    
    // DATOS AL USUARIO
    printf("\n========== DAR DE ALTA ESTUDIANTE ==========\n");
    printf("Nombre completo: ");
    fgets(nuevoEstudiante.nombre, MAXIMO_NOMBRE, stdin);
    
    printf("Edad: ");
    scanf("%d", &nuevoEstudiante.edad);
    
    // NUEVO NODO
    NodoEstudiante* nodo_nuevo = crearNodoEstudiante(nuevoEstudiante);
    if (nodo_nuevo == NULL) return;
    
    // INSERTAR AL PRINCIPIO DE LA LISTA
    nodo_nuevo->siguiente = *lista;
    *lista = nodo_nuevo;
    
    printf("\n✓ Estudiante '%s' agregado exitosamente con ID: %d\n", nuevoEstudiante.nombre, nuevoEstudiante.id);
    printf("============================================\n");
}

// LISTAR //
void listarEstudiantes(NodoEstudiante* lista) {
    if (lista == NULL) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    printf("\n==================== LISTA DE ESTUDIANTES ====================\n");
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        printf("ID: %d | Nombre: %s | Edad: %d | Materias cursando: %d\n",
               actual->datos.id,
               actual->datos.nombre,
               actual->datos.edad,
               actual->datos.cantidad_materias);
        actual = actual->siguiente;
    }
    printf("==============================================================\n");
}

// MODIFICAR //
void modificarEstudiante(NodoEstudiante* lista, int id) {
    NodoEstudiante* estudiante = buscarEstudiantePorId(lista, id);
    
    if (estudiante == NULL) {
        printf("Error: No se encontró estudiante con ID %d\n", id);
        return;
    }
    
    printf("\n--- Modificar estudiante ID %d ---\n", id);
    printf("Nombre actual: %s\n", estudiante->datos.nombre);
    printf("Nuevo nombre (Enter para mantener): ");
    char buffer[MAXIMO_NOMBRE];
    fgets(buffer, MAXIMO_NOMBRE, stdin);
    if (buffer[0] != '\n') {
        strcpy(estudiante->datos.nombre, buffer);
    }
    
    printf("Edad actual: %d\n", estudiante->datos.edad);
    printf("Nueva edad: ");
    int nueva_edad;
    scanf("%d", &nueva_edad);
    getchar();  
    if (nueva_edad > 0) {
        estudiante->datos.edad = nueva_edad;
    }
    
    printf("Estudiante modificado exitosamente.\n");
}

// BAJA //
void darDeBajaEstudiante(NodoEstudiante** lista, int id) {
    if (*lista == NULL) {
        printf("Error: La lista está vacía\n");
        return;
    }
    
    NodoEstudiante* actual = *lista;
    NodoEstudiante* anterior = NULL;
    
    while (actual != NULL && actual->datos.id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        printf("Error: No se encontró estudiante con ID %d\n", id);
        return;
    }
    
    if (anterior == NULL) {
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    
    printf("Estudiante '%s' (ID: %d) dado de baja exitosamente.\n", 
           actual->datos.nombre, actual->datos.id);
    free(actual);
}

// FILTRAR ESTUDIANTE POR NOMBRE //
void buscarEstudiantePorNombre(NodoEstudiante* lista, char* nombre) {
    if (lista == NULL) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    int encontrados = 0;
    printf("\n--- Resultados de búsqueda para: '%s' ---\n", nombre);
    
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        if (strstr(actual->datos.nombre, nombre) != NULL) {
            printf("ID: %d | Nombre: %s | Edad: %d\n",
                   actual->datos.id,
                   actual->datos.nombre,
                   actual->datos.edad);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    
    if (encontrados == 0) {
        printf("No se encontraron estudiantes con ese nombre.\n");
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

// FILTRAR ESTUDIANTE POR EDAD //
void buscarEstudiantePorEdad(NodoEstudiante* lista, int min, int max) {
    if (lista == NULL) {
        printf("No hay estudiantes registrados.\n");
        return;
    }
    
    int encontrados = 0;
    printf("\n--- Estudiantes con edad entre %d y %d años ---\n", min, max);
    
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        if (actual->datos.edad >= min && actual->datos.edad <= max) {
            printf("ID: %d | Nombre: %s | Edad: %d\n",
                   actual->datos.id,
                   actual->datos.nombre,
                   actual->datos.edad);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    
    if (encontrados == 0) {
        printf("No se encontraron estudiantes en ese rango de edad.\n");
    } else {
        printf("Total encontrados: %d\n", encontrados);
    }
}

//NODO MATERIAS //
NodoMateria* crearNodoMateria(Materia mat){
    NodoMateria* nuevo = malloc(sizeof(NodoMateria));
    if (!nuevo) {
        printf("Error al reservar memoria.\n");
        return;
    }
    nuevo->datos = mat;
    nuevo->siguiente = NULL;
    return nuevo;
}
// FUNCIONES MATERIAS //

// ALTA //
void darDeAltaMateria(NodoMateria** lista){
    Materia nuevaMateria;
    printf("\n========== CREAR NUEVA MATERIA ==========\n");
    printf("Ingrese ID: ");
    scanf("%d", &nuevaMateria.id);

    printf("Ingrese nombre: ");
    scanf("%s", nuevaMateria.nombre);

    printf("Ingrese cupo actual: ");
    scanf("%d", &nuevaMateria.cupo_actual);

    NodoMateria* nuevo = crearNodoMateria(nuevaMateria);
    if (nuevo == NULL) return;

    nuevo->siguiente = *lista;
    *lista = nuevo;

    printf("\n✓ Materia '%s' creada exitosamente con ID: %d\n", nuevaMateria.nombre, nuevaMateria.id);
    printf("============================================\n");
}

// LISTAR //
void listarMaterias(NodoMateria* lista){
    if (lista == NULL) {
        printf("No hay Materias.\n");
        return;
    }
    printf("\n==================== LISTA DE MATERIAS ====================\n");
    NodoMateria* actual = lista;
    while(actual!=NULL){
        printf("ID: %d | Nombre: %s\n",
               actual->datos.id,
               actual->datos.nombre);
        actual = actual->siguiente;
    }
    printf("==============================================================\n");
}

// MODIFICAR //
void modificarMateria(NodoMateria* lista, int id){
    NodoMateria* materia = buscarMateria(lista,id);
    if (materia==NULL){
        printf("No se ha encontrado una materia con el id %d.\n",id);
        return;
    }
    printf("\n--- Modificar Materia ID %d ---\n", id);
    printf("Nombre actual: %s\n", materia->datos.nombre);
    printf("Nuevo nombre (Enter para mantener): ");
    char buffer[MAXIMO_NOMBRE];
    fgets(buffer, MAXIMO_NOMBRE, stdin);
    if (buffer[0] != '\n') {
        strcpy(materia->datos.nombre, buffer);
    }
    printf("Materia modificado exitosamente.\n");
    printf("==============================================================\n");
}

// ELIMINAR //
void eliminarMateria(NodoMateria** lista, int id){
     if (*lista == NULL) {
        printf("Error: La lista está vacía\n");
        return;
    }

    NodoMateria* actual = *lista;
    NodoMateria* anterior = NULL;

    while (actual != NULL && actual->datos.id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Error: No se encontró la materia con ID %d\n", id);
        return;
    }

    if (anterior == NULL) {
        *lista = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    printf("La Materia '%s' (ID: %d) se ha eliminado.\n", 
           actual->datos.nombre, actual->datos.id);
    free(actual);
}

// BUSCAR //
NodoMateria* buscarMateria(NodoMateria* lista,int id){
     if (lista == NULL) {
        printf("No hay Materias.\n");
        return NULL;
    }
    NodoMateria* actual =lista;
    while(actual!=NULL){
        if (actual->datos.id==id){
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}