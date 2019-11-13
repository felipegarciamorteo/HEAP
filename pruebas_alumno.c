#include "heap.h"
#include "testing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

int comparar (const void *s, const void *r){
	return strcmp(s,r);
}
	
/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener max, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap desencolar, es NULL, no se puede", !heap_desencolar(heap));
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap));

    heap_destruir(heap,NULL);
}
static void prueba_heap_encolar()
{
    heap_t* heap = heap_crear(comparar);

    char *clave1 = "perro";
    char *clave2 = "gato";
    char *clave3 = "vaca";

    /* Inserta 1 valor y luego lo desencola */
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver maximo es clave1", heap_ver_max(heap) == clave1);
    print_test("Prueba heap desencolar es clave1", heap_desencolar(heap) == clave1);
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap));

    /* Inserta otros 2 valores y no los borra (se destruyen con el heap) */
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver maximo es clave2", heap_ver_max(heap) == clave2);
    
	print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver maximo sigue siendo clave2", heap_ver_max(heap) == clave2);

    heap_destruir(heap,NULL);
}


static void prueba_heap_desencolar()
{
    heap_t* heap = heap_crear(comparar);

    char *clave1 = "perro";
    char *clave2 = "gato";
    char *clave3 = "vaca";

    /* Inserta 3 valores y luego los desencola */
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));

    /* Al desencolar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    heap_destruir(heap,NULL);
}

static void prueba_crear_heap_arr()
{
	char *arr[6] = {"perro","caballo","gato","vaca","leon","tigre"};
	void *arreglo[6] = {arr,arr+1,arr+2,arr+3,arr+4,arr+5};
	
	heap_t *heap = heap_crear_arr(arreglo,6,comparar);
	
	printf("heap ver max es: %s\n", (char*)heap_ver_max(heap));
	print_test("Prueba heap ver max es caballo", heap_ver_max(heap) == arreglo[1]);
	
	
	heap_destruir(heap,NULL);
}

static void prueba_heap_clave_vacia()
{
    abb_t* abb = abb_crear(comparar,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_heap_valor_null()
{
    abb_t* abb = abb_crear(comparar,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_heap_clave_null()
{
    abb_t* abb = abb_crear(comparar,NULL);

    char *clave = NULL, *valor = "NADA";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave NULL es false", !abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave NULL es NULL", abb_obtener(abb, clave) == NULL);
    print_test("Prueba abb pertenece clave NULL, es false", !abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave NULL es NULL", abb_borrar(abb, clave) == NULL);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


static void prueba_heap_volumen(size_t largo, bool debug)
{
    abb_t* abb = abb_crear(comparar,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(comparar,free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_crear_heap_arr();
    /*prueba_heap_clave_vacia();
    prueba_heap_valor_null();
    prueba_heap_clave_null();
    prueba_heap_volumen(200, true);*/
}

