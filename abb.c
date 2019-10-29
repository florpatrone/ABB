#define _POSIX_C_SOURCE 200809L 
#define OBTENER_PADRE true
#define PERTENECE true
#define GUARDAR true
#include "abb.h"
#include <stdlib.h>
#include <string.h>

enum posicion{IZQUIERDA,RAIZ,DERECHA};
typedef enum posicion posicion_t;

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
* Primitivas del nodo
****************************/

nodo_t* crear_nodo(const char *clave,void *dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (!nodo) return NULL;
	nodo->izq = NULL;
	nodo->der = NULL;
	nodo->clave = clave;
	nodo->dato = dato;
	return nodo;
}

/***************************
* Funciones Auxiliares
****************************/

bool abb_buscar_y(bool pertenencia, bool guardado, abb_t *abb, nodo_t* raiz, const char *clave, void *dato){
	if (!abb) return false;

	nodo_t* act = raiz;
	if (abb->cmp(clave, act->clave) == 0){
		if (guardado){
			act->dato = dato;
		}
		return true;
	}

	bool clave_mayor = abb->camp(clave,act->clave) > 0;
	
	if (pertenencia){
		nodo_t* prox = clave_mayor ?  act->der : act->izq ;
		return abb_buscar_y(pertenencia, guardado, abb, prox, clave, dato);
	}

	if (guardado){
		if (clave_mayor && !act->der){
			nodo_t* nodo = crear_nodo(clave,dato);
			if (!nodo) return false;
			act->der = nodo;
			return true;
		}
		if (!clave_mayor && !act->izq){
			nodo_t nodo = crear_nodo(clave,dato);
			if (!nodo) return false;
			act->izq = nodo;
			return true;
		}
	}
	nodo_t* prox = clave_mayor ? act->der : act->izq;
	return abb_buscar_y(pertenencia, guardado, abb, prox, clave, dato);
}

void _destruir_nodos(nodo_t* raiz, abb_destruir_dato_t destruir_dato){
	if (!raiz) return;
	_destruir_nodos(raiz->izq,destruir_dato);
	_destruir_nodos(raiz->der,destruir_dato);
	
	if (destruir_dato) destruir_dato(raiz->dato);
	free(raiz);
}

/***************************
* Primitivas del ABB
****************************/

nodo_t* proximo_inorder(nodo_t* nodo, int direccion){
	if (direccion == DERECHA){
		if (!nodo->der) return nodo;
		return proximo_inorder(nodo->der,direccion);
	}
	
	else if (direccion == IZQUIERDA){
		if (!nodo->izq) return nodo;
		return proximo_inorder(nodo->izq,direccion);
	}
}

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

void* _abb_borrar(abb_t* arbol, nodo_t* nodo, const char* clave, abb_comparar_clave_t cmp){
	if (!nodo) return NULL;

	nodo_t* padre = _abb_obtener(nodo,clave,cmp,OBTENER_PADRE);

	if (!padre) return NULL;

	void* dato = nodo->dato;
	
	//caso 3
	if (nodo->der && nodo->izq){
		nodo_t* reemplazo = proximo_inorder(nodo->der, IZQUIERDA);
		char* clave_reemplazo = strdup(reemplazo->clave);
		void* dato_reemplazo = _abb_borrar(arbol,reemplazo,reemplazo->clave,cmp);
		nodo->clave = clave_reemplazo;
		nodo->dato = dato_reemplazo;
		arbol->cantidad--;
		return dato;
	}

	//caso 1 y 2
	nodo_t* nuevo_hijo = (nodo->der) ? nodo->der : nodo->izq;

	if (padre->izq == nodo){
		padre->izq = nuevo_hijo;
	}

	else if (padre->der == nodo){
		padre->der = nuevo_hijo;
	}
	
	else{
		arbol->raiz = nuevo_hijo;
	}

	nodo_destruir(nodo);
	arbol->cantidad--;
	return dato;
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


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_t* actual = arbol->raiz;
	bool guardado = abb_buscar_y(!PERTENECE, GUARDAR, arbol, actual, clave, dato);
	bool pertenece = abb_buscar_y(PERTENECE, !GUARDAR, arbol, actual, clave, dato);
	if (guardado && !pertenece) arbol->cantidad++;
	return guardado;
}


void *abb_borrar(abb_t *arbol, const char *clave){
	return _abb_borrar(arbol,arbol->raiz,clave,arbol->cmp);
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	nodo_t* nodo = _abb_obtener(arbol->raiz,clave,arbol->cmp,!OBTENER_PADRE);

	if (!nodo) return NULL;

	return nodo->dato;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_t* primero = arbol->raiz;
	return abb_buscar_y(PERTENECE, !GUARDAR, arbol, primero, clave, NULL);
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}


void abb_destruir(abb_t *arbol){
	abb_destruir_dato_t destruir_dato = arbol->destruir_dato;
	nodo_t* raiz = arbol->raiz;
	_destruir_nodos(raiz, destruir_dato);
	free(arbol);
}

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
