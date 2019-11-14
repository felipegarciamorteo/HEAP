#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "heap.h"
//#include "cola.h"

#define TAM 31
#define RED 2
#define MIN 1/4


struct heap{
    void ** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};


/******************************************************************
 *                 FUNCIONES AUXILIARES DEL HEAP                  *     
 ******************************************************************/

/*void swap(void **a, void **b){
    void *aux = *a;
    *a = *b;
    *b = aux;
}*/
void swap (void *a[],size_t x, size_t y) {
	void **aux = a[x];
	a[x] = a[y];
	a[y] = aux;
}
/*
size_t max(heap_t *heap, size_t izq, size_t der){
	if(heap->cmp(heap->datos[izq],heap->datos[der]) < 0){
		return der;
	}else{
		return izq;
	}
}

bool es_heap(heap_t *heap, size_t padre){
	if(!heap->datos+(2*padre+1)){
		return true;
	}else if(!heap->datos+(2*padre+2) && heap->cmp(heap->datos[padre],heap->datos[2*padre+1]) < 0){
		//printf("ENTRO\n");
		return false;
	}else if(heap->cmp(heap->datos[padre],heap->datos[2*padre+1]) < 0 || heap->cmp(heap->datos[padre],heap->datos[2*padre+2]) < 0){
		return false;
	}
	return true;
}*/

void upheap(heap_t *heap, size_t pos){
	if(pos==0)return;
	size_t padre = (pos-1)/2;
	/*if(es_heap(heap,padre))return;
	swap(heap->datos,pos,padre);
	upheap(heap,padre);*/
	//printf("padre es:%s   pos(hijo)es:%s \n",(char*)heap->datos[padre],(char*)heap->datos[pos]);
	if(heap->cmp(heap->datos[padre],heap->datos[pos]) > 0){
		//printf("entro\n");
		//printf("padre es:%s   pos(hijo)es:%s \n",(char*)heap->datos[padre],(char*)heap->datos[pos]);
		swap(heap->datos,pos,padre);
		//printf("padre es:%s   pos(hijo)es:%s \n",(char*)heap->datos[padre],(char*)heap->datos[pos]);
		upheap(heap,padre);
	}
}

void downheap(cmp_func_t cmp, size_t cant, void *datos[],size_t pos){
	//printf("%ld\n",heap->cant);
	if( pos >= cant)return;
	//if(heap->cant <= 2*pos+1)return;
	//if(es_heap(heap,pos))return;
	//printf("ENTRO CHINWA\n");	
	size_t izq = 2*pos+1, der = 2*pos+2, hijo = pos;
	//printf("pos es: %ld, izq es: %ld y der es: %ld\n",pos,izq,der);
	if(izq < cant && cmp(datos[pos],datos[izq]) > 0){
	//size_t padre = max(heap,2*pos+1,2*pos+2);
			
			hijo = izq;
			//swap(heap->datos,pos,izq);
			//downheap(heap,izq);
	}
	if(der < cant && cmp(datos[hijo],datos[der]) > 0 ){
			hijo = der;
			//swap(heap->datos,pos,2*pos+2);
			//downheap(heap,2*pos+2);
	}
	if(hijo != pos){
		swap(datos,pos,hijo);
		downheap(cmp,cant,datos,hijo);
	}	
}

/*
void downheap(heap_t *heap, void *datos[],size_t pos){
	if( pos > (heap->cant/2)-1)return;
	//if(es_heap(heap,pos))return;
	//printf("entro\n");
	size_t izq = 2*pos+1, der = 2*pos+2, hijo = pos;
	if(izq < heap->cant && heap->cmp(datos[pos],datos[izq]) < 0){
	//size_t padre = max(heap,2*pos+1,2*pos+2);
			hijo = izq;
			//swap(heap->datos,pos,izq);
			//downheap(heap,izq);
	}
	if(der < heap->cant && heap->cmp(datos[hijo],datos[der]) < 0 ){
			//printf("entro\n");
			hijo = der;
			//swap(heap->datos,pos,2*pos+2);
			//downheap(heap,2*pos+2);
	}
	if(hijo != pos){
		printf("hijo es:%ld\n",hijo);
		swap(datos,pos,hijo);
		printf("despues hijo es:%ld\n",hijo);
		downheap(heap,datos,hijo);
	}	
}*/

void heapify(cmp_func_t cmp, void *arreglo[], size_t n){
	
	
	for(int h = (int)((n)/2)-1; h > -1 ; h--){
		//printf("entro,por:%s \n",(char*)heap->datos[h]);
		//printf("h: %d\n",h);
		downheap(cmp,n,arreglo,h);
		//printf("que ahora es: %s\n",(char*)heap->datos[h]);
	}
	/*for(size_t y = 0; y < 6; y++){
		printf("el %ld es: %s\n",y+1,(char*)heap->datos[y]);
	}*/
}

bool heap_redimension(heap_t *heap, size_t TAM_NUEVO){
					
	void** datos_nuevo = realloc(heap->datos,TAM_NUEVO*sizeof(void*));
	if (!datos_nuevo) return false;
	
	heap->datos	= datos_nuevo;
	heap->tam = TAM_NUEVO;
	return true;
}

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(cmp,elementos,cant);
	/*for(size_t i = 0; i < cant; i++){
		printf("%ld es: %s\n",i,(char*)elementos[i]);
	}*/
	
	for(size_t i = 0; i < cant; i++){
		//printf("se rompio en %ld(+1)",i);
		swap(elementos,i,cant-i-1);
		downheap(cmp,cant-i-1,elementos,i);
	}
}

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


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	
	heap_t *heap = heap_crear(cmp);
	if(!heap)return NULL;
	
	if(n > heap->tam){
		if(!heap_redimension(heap,RED*n))return NULL;
	}
	heap->cant = n;
	for(size_t i = 0; i < n; i++){
		heap->datos[i] = arreglo[i];
	}
	heapify(heap->cmp,heap->datos,n);
	
	
	
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
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}
	
bool heap_encolar(heap_t *heap, void *elem){
	if(!elem)return false;
	if(heap->cant == heap->tam){
		if(!heap_redimension(heap,RED*heap->tam))return false;
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
	if(heap->cant <= heap->tam*MIN && heap->cant > TAM){
		if(!heap_redimension(heap,heap->tam/RED))return NULL;
	}
	heap->cant--;
	swap(heap->datos,0,heap->cant);
	void *dato = heap->datos[heap->cant];
	if(heap->cant != 0)downheap(heap->cmp,heap->cant,heap->datos,0);
	return dato;
}


