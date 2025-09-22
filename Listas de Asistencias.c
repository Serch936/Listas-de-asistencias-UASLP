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
    TAlumno *alumnos;
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

    inicializa_alumno(&a);
    inicializa_lista(&l);
    inicializa_dia(&d);
    
    return 0;
}