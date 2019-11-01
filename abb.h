#include <stdbool.h>
#include <stddef.h>

typedef struct abb abb_t;
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

/* Primitivas del abb */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Si la clave ya existe, se reemplaza su dato. De lo contrario,
se guarda en una nueva hoja del arbol la clave y el dato.
Para ambos casos, devuelve true.
En caso de error, devuelve false.
Pre: el arbol debe haber sido creado. */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

/* Devuelve true si la clave buscada se encuentra en el arbol.
De lo contrario, devuelve false.
Pre: el arbol debe haber sido creado. */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de nodos que tiene el arbol.*/
size_t abb_cantidad(abb_t *arbol);

/* Destruye el arbol y todos sus nodos */
void abb_destruir(abb_t *arbol);

/* Iterador externo del abb */

typedef struct abb_iter abb_iter_t;

/* Primitivas del iterador externo del abb */

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Avanza una posición del iterador de manera INORDER y
devuelve true. Si no puede avanzar o el árbol está vacío
devuelve false. */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Muestra la clave del nodo señalado por el iterador*/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Devuelve true si el iterador llegó al final del arbol
o, de lo contrario, false. */
bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t* iter);

/* Primitivas del iterador interno del abb */

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);