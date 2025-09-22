#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct nombre {
    char nombres[60];
    char apellido_paterno[35];
    char apellido_materno[35];
} TNombre;

typedef struct alumno {
    TNombre nombre;
    bool asistencia;
    struct alumno *siguiente;
    struct alumno *anterior;
} TAlumno;

typedef struct lista {
    TAlumno *alumnos;
    int cantidad;
} TLista;

typedef struct dia {
    int dia; // <-- Cambié 'día' por 'dia'
    TLista lista_alumnos;
    struct dia *siguiente;
} TDia;

void inicializa_lista(TLista *l) {
    l->alumnos = NULL;
    l->cantidad = 0;
}

TDia *inicializa_dia(int dia) {
    TDia *nuevo = (TDia *)malloc(sizeof(TDia));
    nuevo->dia = dia;
    inicializa_lista(&(nuevo->lista_alumnos));
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregar_alumno(TLista *lista, TNombre nombre) {
    TAlumno *nuevo = (TAlumno *)malloc(sizeof(TAlumno));
    nuevo->nombre = nombre;
    nuevo->asistencia = false;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    if (lista->alumnos == NULL) {
        lista->alumnos = nuevo;
    } else {
        TAlumno *actual = lista->alumnos;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->anterior = actual;
    }
    lista->cantidad++;
}

void eliminar_alumno(TLista *lista, const char *nombre_completo) {
    TAlumno *actual = lista->alumnos;
    while (actual != NULL) {
        char buffer[130];
        snprintf(buffer, sizeof(buffer), "%s %s %s",
                 actual->nombre.nombres,
                 actual->nombre.apellido_paterno,
                 actual->nombre.apellido_materno);
        if (strcmp(buffer, nombre_completo) == 0) {
            if (actual->anterior)
                actual->anterior->siguiente = actual->siguiente;
            if (actual->siguiente)
                actual->siguiente->anterior = actual->anterior;
            if (actual == lista->alumnos)
                lista->alumnos = actual->siguiente;
            free(actual);
            lista->cantidad--;
            printf("Alumno eliminado exitosamente.\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("Alumno no encontrado.\n");
}

void marcar_asistencia(TLista *lista, const char *nombre_completo, bool asistencia) {
    TAlumno *actual = lista->alumnos;
    while (actual != NULL) {
        char buffer[130];
        snprintf(buffer, sizeof(buffer), "%s %s %s",
                 actual->nombre.nombres,
                 actual->nombre.apellido_paterno,
                 actual->nombre.apellido_materno);
        if (strcmp(buffer, nombre_completo) == 0) {
            actual->asistencia = asistencia;
            printf("Asistencia marcada exitosamente.\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("Alumno no encontrado.\n");
}

void mostrar_lista_asistencias_dia(TDia *dia) {
    printf("\nLista de asistencias del dia %d:\n", dia->dia);
    TAlumno *actual = dia->lista_alumnos.alumnos;
    if (actual == NULL) {
        printf("No hay alumnos registrados.\n");
        return;
    }
    while (actual != NULL) {
        printf("%s %s %s - %s\n",
               actual->nombre.nombres,
               actual->nombre.apellido_paterno,
               actual->nombre.apellido_materno,
               actual->asistencia ? "Presente" : "Ausente");
        actual = actual->siguiente;
    }
}

// Faltaba esta función
void mostrar_lista_asistencias_alumno(TDia *dias, const char *nombre_completo) {
    TDia *dia = dias;
    bool encontrado = false;
    while (dia != NULL) {
        TAlumno *actual = dia->lista_alumnos.alumnos;
        while (actual != NULL) {
            char buffer[130];
            snprintf(buffer, sizeof(buffer), "%s %s %s",
                     actual->nombre.nombres,
                     actual->nombre.apellido_paterno,
                     actual->nombre.apellido_materno);
            if (strcmp(buffer, nombre_completo) == 0) {
                printf("Dia %d: %s\n", dia->dia, actual->asistencia ? "Presente" : "Ausente");
                encontrado = true;
            }
            actual = actual->siguiente;
        }
        dia = dia->siguiente;
    }
    if (!encontrado)
        printf("Alumno no encontrado en ningun dia.\n");
}

// Menú modularizado
void menu_agregar_alumnos(TDia *dia) {
    int cantidad;
    printf("¿Cuántos alumnos desea agregar? ");
    scanf("%d", &cantidad);
    getchar(); // Limpiar buffer

    for (int i = 0; i < cantidad; i++) {
        TNombre nombre;
        printf("Alumno %d:\n", i + 1);

        printf("  Nombres: ");
        fgets(nombre.nombres, sizeof(nombre.nombres), stdin);
        nombre.nombres[strcspn(nombre.nombres, "\n")] = 0;

        printf("  Apellido paterno: ");
        fgets(nombre.apellido_paterno, sizeof(nombre.apellido_paterno), stdin);
        nombre.apellido_paterno[strcspn(nombre.apellido_paterno, "\n")] = 0;

        printf("  Apellido materno: ");
        fgets(nombre.apellido_materno, sizeof(nombre.apellido_materno), stdin);
        nombre.apellido_materno[strcspn(nombre.apellido_materno, "\n")] = 0;

        agregar_alumno(&(dia->lista_alumnos), nombre);
    }
    printf("Alumnos agregados exitosamente.\n");
}

void menu_eliminar_alumno(TDia *dia) {
    char nombre_completo[130];
    printf("Ingrese el nombre completo del alumno a eliminar (Nombres ApellidoPaterno ApellidoMaterno):\n");
    fgets(nombre_completo, sizeof(nombre_completo), stdin);
    nombre_completo[strcspn(nombre_completo, "\n")] = 0;
    eliminar_alumno(&(dia->lista_alumnos), nombre_completo);
}

void menu_marcar_asistencia(TDia *dia) {
    TAlumno *actual = dia->lista_alumnos.alumnos;
    char respuesta[10];
    if (actual == NULL) {
        printf("No hay alumnos registrados.\n");
        return;
    }
    printf("Marcando asistencia para el día %d:\n", dia->dia);
    while (actual != NULL) {
        printf("%s %s %s ¿Presente? (s/n): ", 
            actual->nombre.nombres, 
            actual->nombre.apellido_paterno, 
            actual->nombre.apellido_materno);
        fgets(respuesta, sizeof(respuesta), stdin);
        respuesta[strcspn(respuesta, "\n")] = 0;
        actual->asistencia = (respuesta[0] == 's' || respuesta[0] == 'S');
        actual = actual->siguiente;
    }
    printf("Asistencias marcadas exitosamente.\n");
}

void menu_mostrar_lista_asistencias_dia(TDia *dia) {
    mostrar_lista_asistencias_dia(dia);
}

void menu_mostrar_lista_asistencias_alumno(TDia *dias) {
    char nombre_completo[130];
    printf("Ingrese el nombre completo del alumno para consultar asistencias (Nombres ApellidoPaterno ApellidoMaterno):\n");
    fgets(nombre_completo, sizeof(nombre_completo), stdin);
    nombre_completo[strcspn(nombre_completo, "\n")] = 0;
    mostrar_lista_asistencias_alumno(dias, nombre_completo);
}

int main() {
    TDia *dias = NULL;
    int opcion;

    dias = inicializa_dia(1); // Inicializa el primer día

    do {
        printf("\n---MENU---\n");
        printf("1. Agregar alumno\n");
        printf("2. Eliminar alumno\n");
        printf("3. Marcar asistencias\n");
        printf("4. Mostrar lista de asistencias de un dia\n");
        printf("5. Mostrar lista de asistencias de un alumno\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer antes de usar fgets

        switch (opcion) {
            case 1:
                menu_agregar_alumnos(dias);
                break;
            case 2:
                menu_eliminar_alumno(dias);
                break;
            case 3:
                menu_marcar_asistencia(dias);
                break;
            case 4:
                menu_mostrar_lista_asistencias_dia(dias);
                break;
            case 5:
                menu_mostrar_lista_asistencias_alumno(dias);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("\nOpcion invalida. Intentelo nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}