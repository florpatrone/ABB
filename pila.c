#include "pila.h"
#include <stdlib.h>
#define CAPACIDAD_INICIAL 8
#define FACTOR_REDIMENSION 2
#define FACTOR_RELACION_CAPACIDAD_CANTIDAD 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){

    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = 0;
    pila->datos = malloc(pila->capacidad * sizeof(void*));

    return pila;
}

void pila_destruir(pila_t *pila){

    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){

    return pila->cantidad == 0;
}

bool pila_redimensionar_capacidad(pila_t* pila, size_t (*operacion)(pila_t*)); //definida al final
size_t aumentar_capacidad(pila_t* pila); //definida al final
size_t disminuir_capacidad(pila_t* pila); //definida al final

bool pila_apilar(pila_t *pila, void* valor){

    if (pila->cantidad == pila->capacidad){
        if(!pila_redimensionar_capacidad(pila, aumentar_capacidad)){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad +=1;
    return true;
}

void* pila_ver_tope(const pila_t *pila){

    void* valor = pila_esta_vacia(pila) ? NULL : pila->datos[pila->cantidad -1];
    return valor;
}

void* pila_desapilar(pila_t *pila){

    if (pila_esta_vacia(pila)){
        return NULL;
    }
    void* valor =  pila->datos[pila->cantidad -1]; // valor es un puntero = al puntero que sale de dato[cantidad-1]
    pila->cantidad -= 1;

    if (pila->cantidad <= (pila->capacidad / FACTOR_RELACION_CAPACIDAD_CANTIDAD) && pila->cantidad != 0){
        
        pila_redimensionar_capacidad(pila, disminuir_capacidad);
    }
    return valor;
}

// Redimensiona la capacidad de la pila, cambiándola por la nueva_capacidad pasada por parámetro.
// En caso de no encontrar memoria para ubicar la nueva pila, no modifica la pila original.
bool pila_redimensionar_capacidad(pila_t* pila, size_t (*operacion)(pila_t*)){

        size_t nueva_capacidad = (*operacion)(pila);
        void* pila_auxiliar = realloc(pila->datos, nueva_capacidad * sizeof(void*));
        
        if (pila_auxiliar == NULL){
            return false;
        }

        pila->capacidad = nueva_capacidad;
        pila->datos = pila_auxiliar;
        return true;
}

size_t aumentar_capacidad(pila_t* pila){

    return pila->capacidad * (size_t) FACTOR_REDIMENSION;
}

size_t disminuir_capacidad(pila_t* pila){

    return pila->capacidad / (size_t) FACTOR_REDIMENSION;
}
