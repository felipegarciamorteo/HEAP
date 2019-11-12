#include <stdio.h>
#include "heap.h"
//#include "cola.h"

#define TAM 31
#define AGRANDAR 2
#define ACHICAR 1/4


struct heap{
    void ** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
} heap_t;


/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){


}

/******************************************************************
 *                 FUNCIONES AUXILIARES DEL HEAP                  *     
 ******************************************************************/

void swap (void *x, void *y) {
	void aux = *x ;
	*x = *y ;
	*y = aux ;
}

bool es_heap(heap_t *heap, size_t padre){
	if(heap->cmp(heap->datos[padre],heap->datos[2*padre+2]) < 0 || heap->cmp(heap->datos[padre],heap->datos[2*padre+1]) < 0){
		return false;
	}
	return true;
}

void upheap(heap_t *heap, size_t pos){
	int padre = (pos-1)/2;
	if(es_heap(heap,padre)return;
	swap(pos,padre);
	upheap(heap,padre);
}

void downheap(heap_t *heap, size_t pos){
	if(es_heap(heap,pos))return;
	size_t padre;
	if(heap->cmp(heap->datos[2*pos+1],heap->datos[2*pos+2]) > 0){
		padre = 2*pos+1;
		swap(heap->datos[pos],heap->datos[padre]);
	}else{
		padre = 2*pos+2;
		swap(heap->datos[pos],heap->datos[padre]);
	}
	downheap(heap,padre);
}

void heapify(){
	
}


/*
 * Implementación de un TAD cola de prioridad, usando un max-heap.
 *
 * Notar que al ser un max-heap el elemento mas grande será el de mejor
 * prioridad. Si se desea un min-heap, alcanza con invertir la función de
 * comparación.
 */

/******************************************************************
 *                    PRIMITIVAS DEL HEAP                         *     
 ******************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	if(!heap)return NULL;
	
	heap->datos = malloc(TAM*sizeof(void*));
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	
	heap->tam = TAM;
	heap->cmp = cmp;
	heap->cant = 0;
	return heap;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
	heap_t *heap = malloc(sizeof(heap_t));
	if(!heap)return NULL;
	
	heap->datos = malloc(TAM*sizeof(void*));
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	
	//heapify
	
	heap->tam = TAM;
	heap->cmp = cmp;
	heap->cant = n;	
	return heap;
}


void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento){
		for(size_t i = 0; i < heap->cant; i++){
			destruir_elemento(heap->datos[i]);
		}
	}	
	free(heap->datos);
	free(heap);	
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}
	
bool heap_encolar(heap_t *heap, void *elem){
	if(!elem)return false;
	if(heap->cant == TAM){
		if(!heap_redimension(heap,AGRANDAR*heap->tam)return false;
	}
	heap->datos[heap->cant] = elem;
	upheap(heap,heap->cant);
	heap->cant++;
	return true;
}

void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap))return NULL;
	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap))return NULL;
	if(heap->cant <= heap->tam/2){
		if(!heap_redimension(heap,heap->tam*ACHICAR)return NULL;
	}
	heap->cant--;
	swap(heap->datos[0],heap->datos[heap->cant]);
	void *dato = heap->datos[heap->cant];
	downheap(heap,0);
	return dato;
}


