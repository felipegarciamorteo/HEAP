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

int cmp_n(const void *a, const void *b){
	if(*(int*)a < *(int*)b)return -1;
	if(*(int*)a > *(int*)b)return 1;
	return 0;
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

    void *clave1 = "perro";
    void *clave2 = "gato";
    void *clave3 = "vaca";

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
    printf("El maximo es:%s\n", (char*)heap_ver_max(heap));
	
    print_test("Prueba heap ver maximo sigue siendo clave2", heap_ver_max(heap) == clave2);

    heap_destruir(heap,NULL);
}

/* Pruebas con algunos datos*/
static void pruebas_heap_algunos_datos()
{
    printf("\nINICIO DE PRUEBAS CON ALGUNOS DATOS\n");
    
    heap_t* heap = heap_crear(comparar);
    
    /*Pruebo que no se puede encolar el elemento NULL*/
    print_test("Pruebo que no se puede encolar el elemento NULL", !heap_encolar(heap,NULL));
    print_test("Prueba el heap sigue estando vacio", heap_esta_vacio(heap) );
    print_test("Pruebo que no se puede desencolar", !heap_desencolar(heap));
	
	void *valor[6] = {"perro","gorila","gato","vaca","foca","caballo"};
	
    /*Pruebo que puedo encolar y desencolar un mismo elemento*/
    print_test("Pruebo encolar un elemento", heap_encolar(heap,valor[0]));
    print_test("Prueba ver_max devuelve el mismo elemento", heap_ver_max(heap) == valor[0] );
    print_test("Prueba al desencolar tambien me devuelve el elemento", heap_desencolar(heap) == valor[0] );
    /*Pruebo que al desencolar hasta que este vacío, se comporta como recien creado*/
    print_test("Prueba desencolar el heap ya desencolado devuelve NULL", !heap_desencolar(heap));
	print_test("Prueba ver_max también devuelve NULL", !heap_ver_max(heap));
	print_test("Prueba el heap esta vacio", heap_esta_vacio(heap) );

	printf("Pruebas con 6 elementos\n");
	/*Creo un flag para saber si se pudieron encolar los valores*/
	bool result = true;
	
	/*Pruebo que se hayan encolado los 6 elementos*/	
	for(int i = 0 ; i < 6 ; i++ ){
		result = true;
		if(!heap_encolar(heap,valor[i])){
			result = false ;
		}
		print_test("Se pudo encolar el valor", result);	
		
	}
	printf("El maximo es:%s\n", (char*)heap_ver_max(heap));
	print_test("Prueba heap ver max es el correcto", heap_ver_max(heap) == valor[5]); 
	print_test("Prueba heap la cantidad de elementos es 6", heap_cantidad(heap) == 6);
	
	heap_destruir(heap,NULL);
}

static void prueba_heap_desencolar()
{
    heap_t* heap = heap_crear(comparar);

    char *clave1 = "River";
    char *clave2 = "Lanus";
    char *clave3 = "Independiente";

    /* Inserta 3 valores y luego los desencola */
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1));
    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    
printf("El maximo es:%s\n", (char*)heap_ver_max(heap));
	
    /* Al desencolar cada elemento comprueba que el maximo es distinto. */
	print_test("Prueba heap ver max es el correcto", heap_ver_max(heap) == clave3); 
	print_test("Prueba heap desencolar, es el maximo anterior", heap_desencolar(heap) == clave3);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
	
    print_test("Prueba heap ver max es el correcto", heap_ver_max(heap) == clave2); 
	print_test("Prueba heap desencolar, es el maximo anterior", heap_desencolar(heap) == clave2);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    
    print_test("Prueba heap ver max es el correcto", heap_ver_max(heap) == clave1); 
	print_test("Prueba heap desencolar, es el maximo anterior", heap_desencolar(heap) == clave1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap));
    
    /* Al estar vacio, no se puede seguir desencolando, pero al volver a encolar se comporta como recién creado*/
    print_test("Prueba heap desencolar, es NULL", !heap_desencolar(heap));
    print_test("Prueba se puede encolar de vuelta clave1", heap_encolar(heap,clave1));
    print_test("Prueba heap ver max es clave1", heap_ver_max(heap) == clave1);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
	print_test("Prueba se puede encolar de vuelta clave2", heap_encolar(heap,clave2));
	print_test("Prueba se puede encolar de vuelta clave3", heap_encolar(heap,clave3));
    print_test("Prueba heap ver max es clave3", heap_ver_max(heap) == clave3);
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    
    heap_destruir(heap,NULL);
}


static void prueba_crear_heap_arr()
{
	void *arreglo[6] = {"zorro","caballo","gato","vaca","leon","ballena"};
	
	heap_t *heap = heap_crear_arr(arreglo,6,comparar);
	
	
	
	printf("heap ver max es: %s\n", (char*)heap_ver_max(heap));
	print_test("Prueba heap ver max es ballena", heap_ver_max(heap) == arreglo[5]);//strcmp((char*)heap_ver_max(heap),"ballena") == 0);
	print_test("Prueba heap la cantidad de elementos es 6", heap_cantidad(heap) == 6);
	
	arreglo[5] = "raton";
	printf("Max es: %s\n", (char*)heap_ver_max(heap));
	print_test("Prueba no se guarda el mismo puntero",strcmp((char*)heap_ver_max(heap),"ballena") == 0);
    
	/*for(size_t y = 0; y < 6; y++){
		printf("el %ld es: %s\n",y,(char*)heap_desencolar(heap));
	}*/
	
	heap_destruir(heap,NULL);
}

static void prueba_heapsort()
{
	
	int n[7] = {4,7,9,2,3,7,0};
	void *p[7] = {n,n+1,n+2,n+3,n+4,n+5,n+6};
	/*
	void *p[7] = {"rusia","nigeria","tailandia","peru","brasil","canada","alemania"};*/
	heap_sort(p,7,comparar);
	
	
	for(int i = 0; i < 7; i++){
		printf("%d elemento: %d\n",i+1,*(int*)p[i]);
	}
	
}
/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_encolar();
	pruebas_heap_algunos_datos();
    prueba_heap_desencolar();
    prueba_crear_heap_arr();
    prueba_heapsort();
    /*pruebas_destruir_segun_funcion();
    prueba_heap_volumen(200, true);*/
}

