#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funciones.c"

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPresione Enter para continuar...");
    getchar();
}

void mostrarMenuPrincipal() {
    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║   SISTEMA DE GESTIÓN DE ESTUDIANTES       ║\n");
    printf("╔════════════════════════════════════════════╝\n");
    printf("║\n");
    printf("║  [1] Gestión de Estudiantes\n");
    printf("║  [2] Gestión de Materias\n");
    printf("║  [3] Inscripciones y Exámenes\n");
    printf("║  [0] Salir\n");
    printf("║\n");
    printf("╚════════════════════════════════════════════\n");
    printf("Opción: ");
}

void menuEstudiantes(NodoEstudiante** lista) {
    int opcion;
    do {
        limpiarPantalla();
        printf("\n");
        printf("╔════════════════════════════════════════════╗\n");
        printf("║      GESTIÓN DE ESTUDIANTES                ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("  [1] Dar de alta estudiante\n");
        printf("  [2] Listar estudiantes\n");
        printf("  [3] Modificar estudiante\n");
        printf("  [4] Dar de baja estudiante\n");
        printf("  [5] Buscar por nombre\n");
        printf("  [6] Buscar por rango de edad\n");
        printf("  [0] Volver al menú principal\n");
        printf("\nOpción: ");
        scanf("%d", &opcion);
        getchar();
        
        switch(opcion) {
            case 1:
                darDeAltaEstudiante(lista);
                pausar();
                break;
            case 2:
                listarEstudiantes(*lista);
                pausar();
                break;
            case 3: {
                int id;
                printf("Ingrese ID del estudiante a modificar: ");
                scanf("%d", &id);
                getchar();
                modificarEstudiante(*lista, id);
                pausar();
                break;
            }
            case 4: {
                int id;
                listarEstudiantes(*lista);
                printf("\nIngrese ID del estudiante a dar de baja: ");
                scanf("%d", &id);
                getchar();
                darDeBajaEstudiante(lista, id);
                pausar();
                break;
            }
            case 5: {
                char nombre[MAXIMO_NOMBRE];
                printf("Ingrese nombre a buscar: ");
                fgets(nombre, MAXIMO_NOMBRE, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                buscarEstudiantePorNombre(*lista, nombre);
                pausar();
                break;
            }
            case 6: {
                int min, max;
                printf("Edad mínima: ");
                scanf("%d", &min);
                printf("Edad máxima: ");
                scanf("%d", &max);
                getchar();
                buscarEstudiantePorEdad(*lista, min, max);
                pausar();
                break;
            }
            case 0:
                break;
            default:
                printf("Opción inválida\n");
                pausar();
        }
    } while(opcion != 0);
}


int main() {
    NodoEstudiante* lista_estudiantes = NULL;
    NodoMateria* lista_materias = NULL;
    
    int opcion;
    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        scanf("%d", &opcion);
        getchar();
        
        switch(opcion) {
            case 1:
                menuEstudiantes(&lista_estudiantes);
                break;
            case 2:
                menuMaterias(&lista_materias);
                break;
            case 3:
                menuInscripciones(&lista_estudiantes, &lista_materias);
                break;
            case 0:
                printf("\n¡SALIR!\n");
                break;
            default:
                printf("Ingrese una opcion correcta\n");
                pausar();
        }
    } while(opcion != 0);
    
    liberarListaEstudiantes(lista_estudiantes);
    liberarListaMaterias(lista_materias);
    
    return 0;
}