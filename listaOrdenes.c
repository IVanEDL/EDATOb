// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// listaOrdenes.c
// Modulo de Ordenamiento de Cargos

using namespace std;
#include "definiciones.h"
#include "listaOrdenes.h"

struct tipo_cargo{
    Cadena cargo;
    Empresa son;
    Empresa bro;
    nodoPer integrantes;
};

struct tipo_empresa{
    Cadena cargo;
    Empresa son;
    Empresa bro;
    nodoPer integrantes;
};

struct tipo_lista_orden{
    Cadena cargo;
    Empresa correspon;
    Empresa supercargo;
    ListaOrden next;
    ListaOrden prev;
};

ListaOrden crearListaOrden(Empresa &e, cargo car){
    //Crea una nueva lista orden. Pre: Deben existir car y e.
    ListaOrden aux = new(tipo_lista_orden);
    e->lorden = aux;
    aux->cargo = car;
    aux->correspon = e->cargoPrin;
    aux->prev = NULL;
    aux->next = NULL;
    return aux;
}

ListaOrden crearNodoLorden(TipoCargo e, cargo car, Empresa supercar, ListaOrden lorden){
    //PRE; Car, e, y Lorden deben existir.
    //Crea un nodo adicional a la lista de órdenes. 
    ListaOrden aux = new(tipo_lista_orden);
    while (lorden->next != NULL){
        lorden = lorden->next;
    }
    aux->cargo = car;
    aux->correspon = e;
    aux->supercargo = supercar;
    lorden->next = aux;
    aux->prev = lorden;
    aux->next = NULL;
    return aux;
}

void eliminarNodoLorden(ListaOrden lorden, Empresa e){
    //Elimina un nodo de Lista Orden, usar cuando se elimine un cargo. PRE; Debe existir una lista orden y el cargo que se quiere borrar.
    if (lorden->correspon == e){
        lorden->next->prev = NULL;
        delete(lorden);
    } else {
        while (lorden->next != NULL){
            if (lorden->correspon == e){
                lorden->prev->next = lorden->next;
                lorden->next->prev = lorden->prev;
                delete(lorden);
            }
        }
    }
}

TipoRet ListarCargosAlf(Empresa e){
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo.
	if (e == NULL){
		return ERROR;
	} else {
		
	}
}

TipoRet ListarJerarquia(Empresa e){
// Listar todos los cargos de la empresa en orden jerárquico.
// Lista todos los cargos de la empresa ordenados por nivel jerárquico e indentados
// según se muestra el ejemplo de la letra.
	return NO_IMPLEMENTADA;
}


TipoRet ListarSuperCargos (Empresa e, Cadena cargo){
// Dado un cargo listar los cargos que lo anteceden.
// Lista todas los cargos que anteceden, en la jerarquía, al cargo de nombre cargo.
	return NO_IMPLEMENTADA;
}