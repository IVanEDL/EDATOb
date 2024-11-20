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
    TipoCargo son;
    TipoCargo bro;
    nodoPer integrantes;
};

struct tipo_empresa{
	ListaOrden lorden;
	TipoCargo cargoPrin;
};

struct tipo_lista_orden{
    Cadena cargo;
    TipoCargo correspon;
    TipoCargo supercargo;
    ListaOrden next;
    ListaOrden prev;
};

ListaOrden crearListaOrden(Empresa &e, TipoCargo car){
    //Crea una nueva lista orden. Pre: Deben existir car y e.
    ListaOrden aux = new(tipo_lista_orden);
    e->lorden = aux;
    aux->cargo = car->cargo;
    aux->correspon = e->cargoPrin;
    aux->prev = NULL;
    aux->next = NULL;
    return aux;
}

ListaOrden crearNodoLorden(TipoCargo e, Cadena car, TipoCargo supercar, ListaOrden lorden){
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

void eliminarNodoLorden(ListaOrden lorden, TipoCargo e){
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

void cambioNodoLorden(ListaOrden &a, ListaOrden &b) {
    // Intercambia los valores de "cargo" y "correspon" (sin mover los nodos físicamente)
    Cadena aux = a->cargo;
    TipoCargo aux2 = a->correspon;

    a->cargo = b->cargo;
    a->correspon = b->correspon;

    b->cargo = aux;
    b->correspon = aux2;
}

void ordenarListaOrden(ListaOrden &inicio) {
    if (inicio == NULL)
        return;

    bool Check;
    do {
        Check = false;
        ListaOrden actual = inicio;

        while (actual->next != NULL) {
            if (strcmp(actual->cargo, actual->next->cargo) > 0) {
                cambioNodoLorden(actual, actual->next);
                Check = true;
            }
            actual = actual->next;
        }
    } while (Check);
}


TipoRet ListarCargosAlf(Empresa e){
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo.
	if (e == NULL || e->lorden == NULL) {
        std::cout << "La idea de listar los cargos alfabeticamente es que hayan cargos, capo.\n";
        return ERROR;
    }
    
    ordenarListaOrden(e->lorden);
    
    ListaOrden actual = e->lorden;
    while (actual != NULL) {
        std::cout << actual->cargo << "\n";
        actual = actual->next;
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