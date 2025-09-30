#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct nombre {
    char nombres[60];
    char apellido_paterno[35];
    char apellido_materno[35];
} TNombre;

typedef struct asistencia{
    char fecha[11];
    bool presente;
    struct asistencia *siguiente;
}TAsistencia

typedef struct alumno {
    TNombre nombre;
    int clave;
    TAsistencia *asistencias;
    struct alumno *siguiente;
    struct alumno *anterior;
} TAlumno;

typedef struct lista {
    TAlumno *alumnos;
    int cantidad;
} TLista;

typedef struct dia {
    int dia; 
    TLista lista_alumnos;
    struct dia *siguiente;
} TDia;

void inicializa_lista(TLista *l) {
    l->alumnos = NULL;
    l->cantidad = 0;
}

void agregar_alumno(TLista *lista, TNombre nombre, int clave) {
    TAlumno *nuevo = (TAlumno *)malloc(sizeof(TAlumno));
    nuevo->nombre = nombre;
    nuevo->clave = clave;
    nuevo->asistencia = NULL;
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

void eliminar_alumno(TLista *lista, int clave) {
    TAlumno *actual = lista->alumnos;
    while (actual != NULL) {
        if(actual->clave == clave){
            if (actual->anterior)
                actual->anterior->siguiente = actual->siguiente;
            if (actual->siguiente)
                actual->siguiente->anterior = actual->anterior;
            if (actual == lista->alumnos)
                lista->alumnos = actual->siguiente;
            TAsistencia *as = actual->asistencia;
            while(as != NULL){
                TAsistencia *tmp = as;
                as = as->siguiente;
                free(tmp);
            }
            free(actual);
            lista->cantidad--;
            printf("Alumno eliminado exitosamente.\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("Alumno no encontrado.\n");
}

void ordenar alumnos(TLista *lista){
    if(lista->cantidad < 2) return;
    for (TAlumno *i = lista->alumnos; i != NULL; i = i->siguiente) {
	for (TAlumno *j = i->siguiente; j != NULL; j = j->siguiente) {
		if (strcmp(i->nombre.apellido_paterno, j->nombre.apellido_paterno) > 0 ||
			(strcmp(i->nombre.apellido_paterno, j->nombre.apellido_paterno) == 0 &&
				strcmp(i->nombre.apellido_materno, j->nombre.apellido_materno) > 0) ||
			(strcmp(i->nombre.apellido_paterno, j->nombre.apellido_paterno) == 0 &&
				strcmp(i->nombre.apellido_materno, j->nombre.apellido_materno) == 0 &&
				strcmp(i->nombre.nombres, j->nombre.nombres) > 0)) {
			TAlumno temp = *i;
			*i = *j;
			*j = temp;
            TAlumno *tmp_s = i->siguiente;
			i->siguiente = j->siguiente;
			j->siguiente = tmp_s;
			TAlumno *tmp_a = i->anterior;
			i->anterior = j->anterior;
			j->anterior = tmp_a;
            }
        }
    }
}


void marcar_asistencia(TLista *lista) {
    if(lista->alumnos == NULL){
        printf("No hay alumnos registrados\n");
        return;
    }
    char fecha[11];
    char respuesta[10];
    printf("Ingrese la fecha (dd/mm/aaaa): ");
    scanf("%s", fecha);
    TAlumno *actual = lista->alumnos;
    while (actual != NULL) {
        printf("| Nombre: %s %s %s | Clave: %d |\n",
                 actual->nombre.nombres,
                 actual->nombre.apellido_paterno,
                 actual->nombre.apellido_materno,
                 actual->clave);
        printf("| Asistencia (s/n): ");
        scanf("%s", respuesta);
        TAsistencia *nueva = (TAsistencia *)malloc(sizeof(TAsistencia));
		strcpy(nueva->fecha, fecha);
		nueva->presente = (respuesta[0] == 's' || respuesta[0] == 'S');
		nueva->siguiente = actual->asistencias;
		actual->asistencias = nueva;
        }
        actual = actual->siguiente;
    }
    printf("Alumno no encontrado.\n");
}

void mostrar_lista_asistencias_dia(TLista *lista) {
   if (lista->alumnos == NULL) {
		printf("No hay alumnos registrados.\n");
		return;
	}
	
	char fecha[11];
	printf("Ingrese la fecha (dd/mm/aaaa) para mostrar asistencias: ");
	scanf("%s", fecha);
	
	ordenar_alumnos(lista);
	
	printf("\n------LISTA DE ASISTENCIA %s------\n", fecha);
	TAlumno *actual = lista->alumnos;
	bool encontrado = false;
    while (actual != NULL) {
		TAsistencia *as = actual->asistencias;
		while (as != NULL) {
			if (strcmp(as->fecha, fecha) == 0) {
				printf("| Nombre: %s %s %s | Clave: %d | Asistencia: %c |\n",
					   actual->nombre.nombres,
					   actual->nombre.apellido_paterno,
					   actual->nombre.apellido_materno,
					   actual->clave,
					   as->presente ? 's' : 'n');
				encontrado = true;
				break;
			}
			as = as->siguiente;
		}
		actual = actual->siguiente;
	}
	
	if (!encontrado) {
		printf("No hay asistencias registradas para esta fecha.\n");
	}
}

void mostrar_lista_asistencias_alumno(TLista *lista, int clave) {
    TAlumno *actual = lista->alumnos;
    bool encontrado = false;
    while (actual != NULL) {
        if (actual->clave == clave) {
			TAsistencia *as = actual->asistencias;
			printf("Asistencias de %s %s %s (Clave: %d):\n",
                     actual->nombre.nombres,
                     actual->nombre.apellido_paterno,
                     actual->nombre.apellido_materno,
                     actual->clave);
            while (as != NULL) {
				printf("| Fecha: %s | Asistencia: %c |\n",
					   as->fecha,
					   as->presente ? 's' : 'n');
				as = as->siguiente;
			}
			encontrado = true;
			break;
		}
		actual = actual->siguiente;
	}
	
	if (!encontrado) {
		printf("Alumno no encontrado.\n");
	}
}

// Menú modularizado
void menu_agregar_alumnos(TLista *lista) {
    int cantidad;
    printf("¿Cuántos alumnos desea agregar? ");
    scanf("%d", &cantidad);
    getchar(); // Limpiar buffer

    for (int i = 0; i < cantidad; i++) {
        TNombre nombre;
        int clave;
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

        printf("\tClave: ");
		scanf("%d", &clave);
		getchar();

        agregar_alumno(lista, nombre, clave);
    }
    printf("Alumnos agregados exitosamente.\n");
}

void menu_eliminar_alumno(TDia *dia) {
    int clave;
	printf("Clave del alumno a eliminar: ");
	scanf("%d", &clave);
	getchar();
	eliminar_alumno(lista, clave);
}

void menu_mostrar_lista_asistencias_alumno(TLista *lista) {
   int clave;
	printf("Clave del alumno: ");
	scanf("%d", &clave);
	getchar();
	mostrar_lista_asistencias_alumno(lista, clave);
}

int main() {
   TLista lista;
	inicializa_lista(&lista);
	int opcion;

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
                menu_agregar_alumnos(&lisa);
                break;
            case 2:
                menu_eliminar_alumno(&lista);
                break;
            case 3:
                marcar_asistencia(&lista);
                break;
            case 4:
                mostrar_lista_asistencias_dia(&lista);
                break;
            case 5:
                menu_mostrar_lista_asistencias_alumno(&lista);
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
