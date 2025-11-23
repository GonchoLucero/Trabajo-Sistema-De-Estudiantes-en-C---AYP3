#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausa()
{
    printf("\nPresione Enter para continuar...");
    getchar();
}

void mostrarMenuPrincipal()
{
    printf("\n");
    printf("============================================\n");
    printf("    SISTEMA DE ESTUDIANTES EN C       \n");
    printf("============================================\n");
    printf("\n");
    printf(" [1] Sistema de Estudiantes\n");
    printf(" [2] Sistema de Materias\n");
    printf(" [3] Inscripciones y Examenes\n");
    printf(" [0] Salir\n");
    printf("\n");
    printf("============================================\n");
    printf("Opcion: ");
}

void menuEstudiantes(NodoEstudiante **lista)
{
    int opcion;
    do
    {
        limpiarPantalla();
        printf("\n");
        printf("============================================\n");
        printf("      SISTEMA DE ESTUDIANTES                \n");
        printf("============================================\n");
        printf(" [1] Dar de alta estudiante\n");
        printf(" [2] Listar estudiantes\n");
        printf(" [3] Modificar estudiante\n");
        printf(" [4] Dar de baja estudiante\n");
        printf(" [5] Buscar por nombre\n");
        printf(" [6] Buscar por rango de edad\n");
        printf(" [7] Calcular promedio de estudiante\n");
        printf(" [0] Volver al menu principal\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            darDeAltaEstudiante(lista);
            pausa();
            break;
        case 2:
            listarEstudiantes(*lista);
            pausa();
            break;
        case 3:
        {
            int id;
            printf("Ingrese ID del estudiante a modificar: ");
            scanf("%d", &id);
            getchar();
            modificarEstudiante(*lista, id);
            pausa();
            break;
        }
        case 4:
        {
            int id;
            listarEstudiantes(*lista);
            printf("\nIngrese ID del estudiante a dar de baja: ");
            scanf("%d", &id);
            getchar();
            darDeBajaEstudiante(lista, id);
            pausa();
            break;
        }
        case 5:
        {
            char nombre[MAXIMO_NOMBRE];
            printf("Ingrese nombre a buscar: ");
            fgets(nombre, MAXIMO_NOMBRE, stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            buscarEstudiantePorNombre(*lista, nombre);
            pausa();
            break;
        }
        case 6:
        {
            int min, max;
            printf("Edad minima: ");
            scanf("%d", &min);
            printf("Edad maxima: ");
            scanf("%d", &max);
            getchar();
            buscarEstudiantePorEdad(*lista, min, max);
            pausa();
            break;
        }
        case 7:
        {
            calcularPromedioEstudiante(*lista);
            pausa();
            break;
        }
        case 0:
            break;
        default:
            printf("Opcion invalida\n");
            pausa();
        }
    } while (opcion != 0);
}

void menuMaterias(NodoMateria **lista, NodoEstudiante **listaEst)
{
    int opcion;
    do
    {
        limpiarPantalla();
        printf("\n");
        printf("============================================\n");
        printf("        SISTEMA DE MATERIAS                 \n");
        printf("============================================\n");
        printf(" [1] Dar de alta materia\n");
        printf(" [2] Listar materias\n");
        printf(" [3] Modificar materia\n");
        printf(" [4] Eliminar materia\n");
        printf(" [5] Buscar materia\n");
        printf(" [6] Estadisticas de materia\n");
        printf(" [0] Volver al menu principal\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            darDeAltaMateria(lista);
            pausa();
            break;
        case 2:
            listarMaterias(*lista);
            pausa();
            break;
        case 3:
        {
            int id;
            printf("Ingrese ID de la materia a modificar: ");
            scanf("%d", &id);
            getchar();
            modificarMateria(*lista, id);
            pausa();
            break;
        }
        case 4:
        {
            int id;
            listarMaterias(*lista);
            printf("\nIngrese ID de la materia a eliminar: ");
            scanf("%d", &id);
            getchar();
            eliminarMateria(lista, id);
            pausa();
            break;
        }
        case 5:
        {
            int id;
            printf("Ingrese ID a buscar: ");
            scanf("%d", &id);
            getchar();
            NodoMateria* resultado = buscarMateria(*lista, id);
            if (resultado != NULL) {
                printf("\nMateria encontrada:\n");
                printf("ID: %d | Nombre: %s\n", resultado->datos.id, resultado->datos.nombre);
            } else {
                printf("\nNo se encontro una materia con ese ID.\n");
            }
            pausa();
            break;
        }
        case 6:
        {
            calcularEstadisticasMateria(*listaEst);
            pausa();
            break;
        }
        case 0:
            break;
        default:
            printf("Opcion invalida\n");
            pausa();
        }
    } while (opcion != 0);
}

void menuInscripciones(NodoEstudiante **listaEst, NodoMateria **listaMat)
{
    int opcion;
    do
    {
        limpiarPantalla();
        printf("\n");
        printf("============================================\n");
        printf("        INSCRIPCION Y EXAMENES              \n");
        printf("============================================\n");
        printf("  [1] Inscribirse a materia\n");
        printf("  [2] Rendir una materia\n");
        printf("  [0] Volver al menu principal\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
        {
            int id1, id2;
            listarEstudiantes(*listaEst);
            printf("\nIngrese el ID del estudiante a inscribir: ");
            scanf("%d", &id1);
            getchar();
            listarMaterias(*listaMat);
            printf("\nIngrese el ID de la materia buscada: ");
            scanf("%d", &id2);
            getchar();
            if (inscribirseAMateria(*listaEst, *listaMat, id1, id2))
            {
                printf("\nInscripcion exitosa!\n");
            }
            else
            {
                printf("\nError en la inscripcion. Verifique:\n");
                printf("- Que el estudiante y la materia existan\n");
                printf("- Que haya cupo disponible\n");
                printf("- Que el estudiante no este ya inscrito\n");
            }
            pausa();
            break;
        }
        case 2:
        {
            int id1, id2, nota;
            listarEstudiantes(*listaEst);
            printf("\nIngrese el ID del estudiante a rendir: ");
            scanf("%d", &id1);
            getchar();
            printf("Ingrese el ID de la materia: ");
            scanf("%d", &id2);
            getchar();
            printf("Ingrese la nota del estudiante en el examen (0-10): ");
            scanf("%d", &nota);
            getchar();
            if (rendirExamen(*listaEst, id1, id2, nota))
            {
                printf("\nExamen registrado exitosamente!\n");
            }
            else
            {
                printf("\nError al registrar el examen. Verifique:\n");
                printf("- Que el estudiante este inscrito en la materia\n");
                printf("- Que la materia no este ya aprobada\n");
            }
            pausa();
            break;
        }
        case 0:
            break;
        default:
            printf("Opcion invalida\n");
            pausa();
        }
    } while (opcion != 0);
}

int main()
{
    NodoEstudiante *lista_estudiantes = NULL;
    NodoMateria *lista_materias = NULL;

    int opcion;
    do
    {
        limpiarPantalla();
        mostrarMenuPrincipal();
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            menuEstudiantes(&lista_estudiantes);
            break;
        case 2:
            menuMaterias(&lista_materias, &lista_estudiantes);
            break;
        case 3:
            menuInscripciones(&lista_estudiantes, &lista_materias);
            break;
        case 0:
            printf("\nSaliendo del sistema...\n");
            printf("Hasta pronto!\n");
            break;
        default:
            printf("Ingrese una opcion correcta\n");
            pausa();
        }
    } while (opcion != 0);

    liberarListaEstudiantes(lista_estudiantes);
    liberarListaMaterias(lista_materias);

    return 0;
}