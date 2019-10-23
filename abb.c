#define _POSIX_C_SOURCE 200809L 
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

/*abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}
*/

/*bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}
*/

/*void *abb_borrar(abb_t *arbol, const char *clave){

}
*/

/*void *abb_obtener(const abb_t *arbol, const char *clave){

}
*/

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