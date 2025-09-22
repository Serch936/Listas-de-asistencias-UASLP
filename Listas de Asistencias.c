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

int main(){
    return 0;
}