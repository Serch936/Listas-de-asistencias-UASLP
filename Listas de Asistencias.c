#include<stdio.h>
#include<stdbool.h>


typedef struct alumno{
    char *nombre;
    bool asistencia;
    TAlumno *siguiente;
    TAlumno *anterior;
}TAlumno;

typedef struct lista{
    TDia *siguiente;
    TDia *anterior;
    TAlumno *alumnos; //Arreglo dinamico de alumnos
    int cantidad;
}TLista;

typedef struct dia{
    TDia *arriba;
    TDia *abajo;
    TLista *alumnosDelDía;
    int día
}TDia;

void inicializa_dia(TDia *d){
    d->arriba = NULL;
    d->abajo = NULL;
    d->alumnosDelDía = NULL;
    d->día = 0;
}

void inicializa_lista(TLista *l){
    l->siguiente = NULL;
    l->anterior = NULL;
    l->alumnos = NULL;
    l->cantidad = 0;
}

void inicializa_alumno(TAlumno *a){
    a->nombre = NULL;
    a->asistencia = false;
    a->siguiente = NULL;
    a->anterior = NULL;
}

int main(){
    TAlumno a;
    TLista l;
    TDia d;
    int opcion;

    inicializa_alumno(&a);
    inicializa_lista(&l);
    inicializa_dia(&d);

    do{
        printf("---MENU---\n");
        printf("1. Agregar alumno\n");
        printf("2. Eliminar alumno\n");
        printf("3. Marcar asistencias\n");
        printf("4. Mostrar lista de asistencias de un dia\n");
        printf("5. Mostrar lista de asistencias de un alumno\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                // Agregar alumno
                break;
            case 2:{
                if(l.cantidad == 0){
                    printf("No hay alumnos en la lista.\n");
                    break;
                }

                break;
            }
            case 3:
                // Marcar asistencias
                break;
            case 4:
                // Mostrar lista de asistencias de un dia
                break;
            case 5:
                // Mostrar lista de asistencias de un alumno
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("\nOpcion invalida \nIntentelo nuevamente\n");
        }
    }while(opcion != 6);
    
    return 0;
}