#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct fecha{
    int dia;
    int mes;
    int año;
}TFECHA;

typedef struct nombre{
    char nombres[65];
    char apell_p[35];
    char apell_m[35];
}TNOMBRE;

typedef struct alumno{
    TNOMBRE nombre;
    bool asistencias;
    int ID;
    struct alumno *siguiente;
}TALUMNO;

typedef struct dia{
    TFECHA fecha;
    bool asistencia_del_dia;
    struct dia *siguiente;
    TALUMNO *lista_alumnos;
}TDIA;

void mostrar_listas(TDIA *cab);
void crea_dia(TDIA **cab_dia, TALUMNO *lista_original, TFECHA fecha);
void agrega_alumnos(TALUMNO *cab, TALUMNO *inicio, int cantidad_alumnos);
TALUMNO *copiar_lista_alumnos(TALUMNO *original);
void tomar_asistencia(TALUMNO *cab);

/*
Nodo* crearnodo(char nombre[]);
Nodo* insertarinicio(Nodo* cabeza, char nombre[]);
void tomarAsistencia(Nodo* cabeza, int dia);
void mostrarlista(Nodo* cabeza);
*/

int main(){
    int opcion, cont = 1, cantidad_alumnos = 0;
    char nombre[50];
    TALUMNO *cab, *inicio;
    TDIA *cab_dia, *lista_original;

    cab = cab_dia = inicio = lista_original = NULL;
    
    printf("Primero, ingrese la cantidad de alumnos: ");
    scanf("%i", &cantidad_alumnos);
    getchar();

    agrega_alumnos(cab, inicio, cantidad_alumnos);
    
    do{
        printf("\n---MENU---\n");
        printf("1. Mostrar listas\n");
        printf("2. Tomar asistencia\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%i", &opcion);
        getchar();

        switch(opcion){
            case 1:{
                int opc;

                if(cab == NULL) {
                    printf("La lista está vacía\n");
                    printf("Regresando al menú principal...\n");
                }else{
                    printf("\n---MENU MOSTRAR---\n");
                    printf("1. Mostrar listas completas\n");
                    printf("2. Mostrar un alumno en particular\n");
                    printf("3. Mostrar un dia en particular\n");
                    printf("Elige una opcion: ");
                    scanf("%i", &opc);

                    switch(opc){
                        case 1:
                            mostrar_listas(&cab);
                            break;
                        case 2:
                            printf("Ingresa el nombre del alumno a buscar: ");
                            gets(nombre);
                            //buscar_alumno(cab, nombre);
                            break;
                        case 3:
                            printf("Ingresa el numero del dia a buscar: ");
                            int dia;
                            scanf("%i", &dia);
                            //buscar_dia(cab_dia, dia);
                            break;
                        default:
                            printf("Opcion no valida\n");
                    }
                }
                break;
            }
            case 2:{
                TDIA *aux;
                TFECHA fecha;
                
                if(aux == NULL) {
                    printf("La lista está vacía\n");
                    printf("Regresando al menú principal...\n");
                }else{
                    crea_dia(&aux, cab, fecha);
                    
                    tomar_asistencia(aux);
                }
                break;
            }
            case 3:
                dia++;
                tomarAsistencia(cabeza, dia);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    }while(opcion != 4);

    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp->asistencias);
        free(temp);
    }

    return 0;
}

/*--- Definiciones de Funciones ---*/

void mostrar_listas(TDIA *cab){
    TDIA *dia_aux;
    TALUMNO *alumno_aux;
    
}

void crea_dia(TDIA **cab_dia, TALUMNO *lista_original, TFECHA fecha){
    TDIA *nuevo;
    TFECHA fecha_aux;

    nuevo = (TDIA*) malloc(sizeof(TDIA));

    if(nuevo == NULL){
        printf("Error de memoria\n");
        exit(1);
    }

    printf("\nIngresa el numero del dia: ");
    scanf("%i", &fecha.dia);
    printf("\nIngresa el numero del mes: ");
    scanf("%i", &fecha.mes);
    printf("\nIngresa el numero del año: ");
    scanf("%i", &fecha.año);

    nuevo->fecha.dia = fecha.dia;
    nuevo->fecha.mes = fecha.mes;
    nuevo->fecha.año = fecha.año;
    nuevo->asistencia_del_dia = false;
    nuevo->siguiente = NULL;
    nuevo->lista_alumnos = copiar_lista_alumnos(lista_original);

    if(*cab_dia == NULL){
        *cab_dia = nuevo;
    }else{
        TDIA *aux = *cab_dia;

        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
    }
}

void agrega_alumnos(TALUMNO *cab, TALUMNO *inicio, int cantidad_alumnos){
    TALUMNO *nuevo, *aux;
    TNOMBRE nombre;

    for(int i=0; i<cantidad_alumnos; i++){
        nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));
        
        if(nuevo == NULL){
            printf("Error de memoria\n");
            exit(1);
        }

        printf("Ingresa el nombre del alumno %d: \n", i+1);
        gets(nombre.nombres);
        printf("Ingresa el apellido paterno del alumno %d: \n", i+1);
        gets(nombre.apell_p);
        printf("Ingresa el apellido materno del alumno %d: \n", i+1);
        gets(nombre.apell_m);

        strcpy(nuevo->nombre.nombres, nombre.nombres);
        strcpy(nuevo->nombre.apell_p, nombre.apell_p);
        strcpy(nuevo->nombre.apell_m, nombre.apell_m);
        nuevo->asistencias = false;
        nuevo->siguiente = NULL;
        nuevo->ID = i;

        if(cab == NULL){
            cab = nuevo;
            inicio = cab;
        }else{
            aux = cab;
            while(aux->siguiente != NULL){
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }
}

TALUMNO *copiar_lista_alumnos(TALUMNO *original){
    if(original == NULL){
        return NULL;
    }

    TALUMNO *nuevo_cab = NULL;
    TALUMNO *nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));
    TALUMNO *actual_original = original->siguiente;
    TALUMNO *actual_nuevo = nuevo_cab;

    if(nuevo == NULL){
        printf("Error de memoria\n");
        exit(1);
    }

    //copiar los datos del nodo original al nuevo nodo
    strcpy(nuevo->nombre.nombres, original->nombre.nombres);
    strcpy(nuevo->nombre.apell_p, original->nombre.apell_p);
    strcpy(nuevo->nombre.apell_m, original->nombre.apell_m);
    
    nuevo->asistencias = original->asistencias;
    nuevo->ID = original->ID;
    nuevo->siguiente = NULL;
    nuevo_cab = nuevo;

    //copiar los nodos restantes
    while(actual_original != NULL){
        nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));

        if(nuevo == NULL){
            printf("Error de memoria\n");
            exit(1);
        }

        strcpy(nuevo->nombre.nombres, actual_original->nombre.nombres);
        strcpy(nuevo->nombre.apell_p, actual_original->nombre.apell_p);
        strcpy(nuevo->nombre.apell_m, actual_original->nombre.apell_m);

        nuevo->asistencias = actual_original->asistencias;
        nuevo->ID = actual_original->ID;
        nuevo->siguiente = NULL;

        actual_nuevo->siguiente = nuevo;
        actual_nuevo = nuevo;
        actual_original = actual_original->siguiente;
    }

    return nuevo_cab;
}

void tomar_lista(TDIA *cab){
    TDIA *aux;
    TALUMNO *lista_aux;

    aux = cab;

    while(aux->siguiente !=  NULL){
        aux = aux->siguiente;
    }

    lista_aux = aux->lista_alumnos;
    aux->asistencia_del_dia = true;

    while(lista_aux != NULL){
        bool respuesta;

        printf("El alumno %s %s %s asistio el dia de hoy (%i/%i/%i)? (1 para si, 0 para no): ", lista_aux->nombre.nombres, lista_aux->nombre.apell_p, lista_aux->nombre.apell_m, aux->fecha.dia, aux->fecha.mes, aux->fecha.año);
        scanf("%i", &respuesta);

        lista_aux->asistencias = respuesta;
        lista_aux = lista_aux->siguiente;
    }
}

/*
Nodo* crearnodo(char nombre[]) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo != NULL) {
        strcpy(nuevo->nombre, nombre);
        nuevo->asistencias = NULL;
        nuevo->numDias = 0;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

Nodo* insertarinicio(Nodo* cabeza, char nombre[]) {
    Nodo* nuevo = crearnodo(nombre);
    nuevo->siguiente = cabeza;
    return nuevo;
}

void tomarAsistencia(Nodo* cabeza, int dia) {
    Nodo* actual = cabeza;
    char respuesta;

    if (cabeza == NULL) {
        printf("No hay alumnos en la lista.\n");
        return;
    }
    
    printf("\nTomando asistencia para el Dia %d:\n", dia);
    while (actual != NULL) {
        actual->asistencias = (int*) realloc(actual->asistencias, (actual->numDias + 1) * sizeof(int));
        if (actual->asistencias == NULL) {
            printf("Error de memoria.\n");
            exit(1);
        }

        printf("%s (p/a): ", actual->nombre);
        scanf(" %c", &respuesta);
        if (respuesta == 'p' || respuesta == 'P')
            actual->asistencias[actual->numDias] = 1;
        else
            actual->asistencias[actual->numDias] = 0;

        actual->numDias++;
        actual = actual->siguiente;
    }
}

void mostrarlista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    int presentes;
    int ausentes;

    if (cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    printf("\nRegistro de alumnos:\n");

    while (actual != NULL) {
        presentes = 0;
        ausentes = 0;
        printf("%s: ", actual->nombre);
        
        for (int i = 0; i < actual->numDias; i++) {
            if (actual->asistencias[i] == 1) {
                printf("P ");
                presentes++;
            } else {
                printf("A ");
                ausentes++;
            }
        }
        printf("| P: %d, A: %d\n", presentes, ausentes);
        actual = actual->siguiente;
    }
}
*/