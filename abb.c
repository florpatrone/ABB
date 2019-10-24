#define _POSIX_C_SOURCE 200809L 
#define OBTENER_PADRE true
#include "abb.h"
#include <stdlib.h>
#include <string.h>

struct nodo{
    struct nodo* izq;
    struct nodo* der; 
    char* clave;
    void* dato;
};

typedef struct nodo nodo_t;

struct abb{
    nodo_t* raiz;
	size_t cantidad;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};

/***************************
* Primitivas del ABB
****************************/

nodo_t* _abb_obtener(nodo_t* nodo, const char* clave, abb_comparar_clave_t cmp, bool obtener_padre){
	if (!nodo) return NULL;

	int comparacion = cmp(nodo->clave,clave);

	if (comparacion == 0){
		return nodo;
	}

	if (comparacion > 0){
        if (obtener_padre){
			if (!nodo->izq) return NULL;

			if (cmp(nodo->izq->clave,clave) == 0){
				return nodo;
			}
		}
		return _abb_obtener(nodo->izq,clave,cmp,obtener_padre);
	}

    if (obtener_padre){ //comparacion < 0
		if (!nodo->der) return NULL;

		if (cmp(nodo->der->clave,clave) == 0){
			return nodo;
		}
	}
	return _abb_obtener(nodo->der,clave,cmp,obtener_padre);
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb));

    if (!abb) return NULL;

    abb->raiz = NULL;
	abb->cantidad = 0;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;

    return abb;

}


/*bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}
*/

/*void *abb_borrar(abb_t *arbol, const char *clave){

}
*/

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_t* nodo = _abb_obtener(arbol->raiz,clave,arbol->cmp,!OBTENER_PADRE);

	if (!nodo) return NULL;

	return nodo->dato;
}


/*bool abb_pertenece(const abb_t *arbol, const char *clave){

}
*/

/*size_t abb_cantidad(abb_t *arbol){

}
*/

/*void abb_destruir(abb_t *arbol){

}
*/

/*********************************
* Primitivas del iterador externo
**********************************/

/*abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

}
*/

/*bool abb_iter_in_avanzar(abb_iter_t *iter){

}
*/

/*const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

}
*/

/*bool abb_iter_in_al_final(const abb_iter_t *iter){

}
*/

/*void abb_iter_in_destruir(abb_iter_t* iter){

}
*/

/*********************************
* Primitivas del iterador interno
**********************************/

/*void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

}
*/