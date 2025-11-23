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
        return NULL;
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

// BUSCAR ESTUDIANTE POR ID
NodoEstudiante* buscarEstudiantePorId(NodoEstudiante* lista, int id) {
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        if (actual->datos.id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// FUNCIONES ESTUDIANTES
// ALTA
void darDeAltaEstudiante(NodoEstudiante** lista){
    Estudiante nuevoEstudiante;
    
    // ID
    nuevoEstudiante.id = idUnicoEstudiante(*lista);
    nuevoEstudiante.cantidad_materias = 0;
    
    // DATOS AL USUARIO
    printf("\n========== DAR DE ALTA ESTUDIANTE ==========\n");
    printf("Nombre: ");
    fgets(nuevoEstudiante.nombre, MAXIMO_NOMBRE, stdin);
    
    printf("Edad: ");
    scanf("%d", &nuevoEstudiante.edad);
    getchar();
    
    // NUEVO NODO
    NodoEstudiante* nodo_nuevo = crearNodoEstudiante(nuevoEstudiante);
    if (nodo_nuevo == NULL) 
        return;
    
    // INSERTAR AL PRINCIPIO DE LA LISTA
    nodo_nuevo->siguiente = *lista;
    *lista = nodo_nuevo;
    
    printf("\nEstudiante '%s' agregado exitosamente con ID: %d\n", nuevoEstudiante.nombre, nuevoEstudiante.id);
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
        printf("Error: No se encontro estudiante con ID %d\n", id);
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
        printf("Error: La lista esta vacia\n");
        return;
    }
    
    NodoEstudiante* actual = *lista;
    NodoEstudiante* anterior = NULL;
    
    while (actual != NULL && actual->datos.id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        printf("Error: No se encontro estudiante con ID %d\n", id);
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
    printf("\n--- Resultados de busqueda para: '%s' ---\n", nombre);
    
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
    printf("\n--- Estudiantes con edad entre %d y %d anos ---\n", min, max);
    
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

// PROMEDIO //
void calcularPromedioEstudiante(NodoEstudiante* lista){
    char nombre[MAXIMO_NOMBRE];
    printf("\n========== CALCULAR PROMEDIO DE ESTUDIANTE ==========\n");
    printf("Ingrese el nombre del estudiante: ");
    fgets(nombre, MAXIMO_NOMBRE, stdin);
    
    float promedio = 0;
    int suma = 0;
    int encontrado = 0;
    
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        if (strstr(actual->datos.nombre, nombre) != NULL) {
            encontrado = 1;
            
            if (actual->datos.cantidad_materias == 0) {
                printf("El estudiante '%s' no esta cursando ninguna materia.\n", actual->datos.nombre);
                return;
            }
            
            // promedio de solo materias aprobadas
            int materias_aprobadas = 0;
            for (int i = 0; i < actual->datos.cantidad_materias; i++) {
                if (actual->datos.materias[i].aprobada == 1) {
                    suma += actual->datos.materias[i].nota;
                    materias_aprobadas++;
                }
            }
            
            if (materias_aprobadas == 0) {
                printf("El estudiante '%s' no tiene materias aprobadas aun.\n", actual->datos.nombre);
                return;
            }
            
            promedio = suma / (float)materias_aprobadas;
            printf("\nEstudiante: %s", actual->datos.nombre);
            printf("Materias aprobadas: %d/%d\n", materias_aprobadas, actual->datos.cantidad_materias);
            printf("Promedio: %.2f\n", promedio);
            printf("=====================================================\n");
            return;
        }
        actual = actual->siguiente;
    }
    
    if (!encontrado) {
        printf("No se encontro un estudiante con ese nombre.\n");
    }
}

//NODO MATERIAS //
NodoMateria* crearNodoMateria(Materia mat){
    NodoMateria* nuevo = malloc(sizeof(NodoMateria));
    if (!nuevo) {
        printf("Error al reservar memoria.\n");
        return NULL;
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
    getchar();

    printf("Ingrese nombre: ");
    fgets(nuevaMateria.nombre, MAXIMO_NOMBRE, stdin);
    nuevaMateria.nombre[strcspn(nuevaMateria.nombre, "\n")] = 0;

    printf("Ingrese cupo actual: ");
    scanf("%d", &nuevaMateria.cupo_actual);
    getchar();

    NodoMateria* nuevo = crearNodoMateria(nuevaMateria);
    if (nuevo == NULL) return;

    nuevo->siguiente = *lista;
    *lista = nuevo;

    printf("\nMateria '%s' creada exitosamente con ID: %d\n", nuevaMateria.nombre, nuevaMateria.id);
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
        printf("ID: %d | Nombre: %s | Cupo disponible: %d\n",
               actual->datos.id,
               actual->datos.nombre,
               actual->datos.cupo_actual);
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
        printf("Error: La lista esta vacia\n");
        return;
    }

    NodoMateria* actual = *lista;
    NodoMateria* anterior = NULL;

    while (actual != NULL && actual->datos.id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Error: No se encontro la materia con ID %d\n", id);
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

// INSCRIBIRSE A MATERIA //
int inscribirseAMateria(NodoEstudiante* lista1, NodoMateria* lista2, int id1, int id2) {
    NodoEstudiante* nodoE = lista1;
    while (nodoE != NULL && nodoE->datos.id != id1)
        nodoE = nodoE->siguiente;
    if (nodoE == NULL) 
        return 0;

    NodoMateria* nodoM = lista2;
    while (nodoM != NULL && nodoM->datos.id != id2)
        nodoM = nodoM->siguiente;
    if (nodoM == NULL) 
        return 0;

    Estudiante* e = &nodoE->datos;
    Materia* m = &nodoM->datos;

    if (m->cupo_actual <= 0) 
        return 0;

    for (int i = 0; i < e->cantidad_materias; i++) {
        if (e->materias[i].id_materia == id2) {
            return 0;
        }
    }

    if (e->cantidad_materias >= MAXIMO_MATERIAS)
        return 0;

    MateriaCursada nueva;
    nueva.id_materia = m->id;
    strcpy(nueva.nombre, m->nombre);
    nueva.aprobada = 0;
    nueva.nota = 0;

    e->materias[e->cantidad_materias] = nueva;
    e->cantidad_materias++;

    // Reducir cupo
    m->cupo_actual--;

    return 1;
}

// RENDIR MATERIA //
int rendirExamen(NodoEstudiante* lista, int id1, int id2, int nota) {
    NodoEstudiante* nodo = lista;
    while (nodo != NULL && nodo->datos.id != id1)
        nodo = nodo->siguiente;
    if (nodo == NULL)
        return 0;

    Estudiante* e = &nodo->datos;

    for (int i = 0; i < e->cantidad_materias; i++) {
        if (e->materias[i].id_materia == id2) {
            if (e->materias[i].aprobada == 1)
                return 0;

            e->materias[i].nota = nota;
            e->materias[i].aprobada = 1;
            return 1;
        }
    }

    return 0; // el estudiante no cursa esa materia
}

// ESTADISTICAS //
void calcularEstadisticasMateria(NodoEstudiante* lista){
    int id_materia;
    printf("\n========== ESTADISTICAS DE MATERIA ==========\n");
    printf("Ingrese el ID de la materia: ");
    scanf("%d", &id_materia);
    getchar();
    
    int suma = 0;
    int cantEstudiantes = 0;
    int estudiantesAprobados = 0;
    int encontrado = 0;
    
    printf("\n--- Estudiantes cursando la materia ID %d ---\n", id_materia);
    
    NodoEstudiante* actual = lista;
    while (actual != NULL) {
        for (int i = 0; i < actual->datos.cantidad_materias; i++) {
            if (actual->datos.materias[i].id_materia == id_materia) {
                encontrado = 1;
                
                printf("Nombre: %s | Edad: %d | Aprobado: %s",
                       actual->datos.nombre,
                       actual->datos.edad,
                       actual->datos.materias[i].aprobada ? "Si" : "No");
                
                if (actual->datos.materias[i].aprobada) {
                    printf(" | Nota: %d", actual->datos.materias[i].nota);
                    suma += actual->datos.materias[i].nota;
                    estudiantesAprobados++;
                }
                printf("\n");
                
                cantEstudiantes++;
            }
        }
        actual = actual->siguiente;
    }
    
    if (!encontrado) {
        printf("No se encontro ningun estudiante cursando esa materia.\n");
        return;
    }
    
    printf("\n--- Estadisticas ---\n");
    printf("Total de estudiantes cursando: %d\n", cantEstudiantes);
    printf("Estudiantes que aprobaron: %d\n", estudiantesAprobados);
    
    if (estudiantesAprobados > 0) {
        printf("Promedio general de aprobados: %.2f\n", (float)suma / estudiantesAprobados);
    } else {
        printf("Aun no hay estudiantes que hayan aprobado esta materia.\n");
    }
    printf("=============================================\n");
}

// LIBERAR LISTAS
void liberarListaEstudiantes(NodoEstudiante* lista) {
    while (lista != NULL) {
        NodoEstudiante* temp = lista;
        lista = lista->siguiente;
        free(temp);
    }
}

void liberarListaMaterias(NodoMateria* lista) {
    while (lista != NULL) {
        NodoMateria* temp = lista;
        lista = lista->siguiente;
        free(temp);
    }
}