// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.c
// Modulo de Implementacion de la Empresa

using namespace std;
#include "definiciones.h"
#include "empresa.h"

struct tipo_persona{
    Cadena ci;
    Cadena nom;
};

struct nodo_persona{
    nodoPer next;
    nodoPer prev;
    Persona persona;
}; //Nodo_Persona; Es un nodo de lista doble con una estructura Persona dentro.

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

TipoCargo BuscarCargo(TipoCargo e, Cadena cargo){
	if(e == NULL){
		return NULL;
	}

	if(strcasecmp(e->cargo, cargo) == 0){
		return e;
	}
	TipoCargo aux = BuscarCargo(aux->bro, cargo);
	if(aux != NULL){
		return aux;
	}
	return BuscarCargo(aux->son, cargo);
}


TipoRet CrearOrg(Empresa &e, Cadena cargo){
// Inicializa la empresa y crea el primer cargo de la empresa.
// Originalmente la misma debería  estar vacía, en otro caso la operación quedará sin efecto.
	if (e != NULL){
		return ERROR;
	} else {
		e = new(tipo_empresa);
		TipoCargo nuevoCargo = new tipo_cargo;
        nuevoCargo->cargo = cargo;
        nuevoCargo->son = NULL;
        nuevoCargo->bro = NULL;
        nuevoCargo->integrantes = NULL;
        ListaOrden nuevaLista = crearListaOrden(e, nuevoCargo);
		e->lorden = nuevaLista;
		e->cargoPrin = nuevoCargo;
		return OK;
	}
}

TipoRet EliminarOrg(Empresa &e){
// Eliminar el organigrama, elimina toda la estructura del organigrama, liberando la memoria asignada.
// Pendiente: esta función requiere modificaciones. Es un poco estúpido borrar la estructura nodo por-
//-nodo sin una función adyacente que borre las personas de cada cargo. Pero hace lo que tiene que hacer.
	if (e != NULL){
	    if (e->lorden != NULL){
		    eliminarNodoLorden(e->lorden, e->cargoPrin);
		}
		if (e->cargoPrin != NULL) {
			EliminarCargo(e, e->cargoPrin->cargo);
		}
		//En cuanto esté eliminar persona, aquí va una llamada a otra función que sea "limpiar toda persona" o así
	}
	e = NULL;
	return OK;
}

TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo){
// Insertar un nuevo cargo como dependiente de otro ya existente.
// El nuevo cargo no debe existir en el sistema.
	TipoCargo aux = NULL;
	TipoCargo aux2 = BuscarCargo(e->cargoPrin, cargoPadre);
	if (BuscarCargo(e->cargoPrin, nuevoCargo) != NULL){
		return ERROR;
	}else if (aux2->son != NULL){
		aux = NuevoCargoBro(aux2->son, nuevoCargo);
		crearNodoLorden(aux, nuevoCargo, aux2, e->lorden);
		return OK;
	}else{
		aux = new(tipo_cargo);
		aux->son = NULL;
		aux->bro = NULL;
		aux->cargo = nuevoCargo;
		aux->integrantes = NULL;
		aux2->son = aux;
		crearNodoLorden(aux, nuevoCargo, aux2, e->lorden);
		return OK;
	}
}

TipoCargo NuevoCargoBro(TipoCargo &cargoHermano, Cadena nuevoCargo){
	if (cargoHermano->bro != NULL){
		return NuevoCargoBro(cargoHermano->bro, nuevoCargo);
	} else {
		TipoCargo cargoNuevo = new(tipo_cargo);
		cargoHermano->bro = cargoNuevo;
		cargoNuevo->son = NULL;
		cargoNuevo->cargo = nuevoCargo;
		cargoNuevo->integrantes = NULL;
		return cargoNuevo;
	}
}

void EliminarSubCargo(TipoCargo &subC) {
    if (subC == NULL)
        return;

    EliminarSubCargo(subC->son);

    EliminarSubCargo(subC->bro);

    LiberarPersonas(subC->integrantes);

    delete[] subC->cargo;
    delete subC;
    subC = NULL;
}

TipoRet EliminarCargoAux(TipoCargo &nodo, Cadena cargo) {
    if (nodo == NULL)
        return ERROR;

    if (strcmp(nodo->cargo, cargo) == 0) {
        EliminarSubCargo(nodo);
        return OK;
    }

    if (EliminarCargoAux(nodo->son, cargo) == OK) {
        nodo->son = NULL;
        return OK;
    }

    if (EliminarCargoAux(nodo->bro, cargo) == OK) {
        nodo->bro = NULL;
        return OK;
    }

    return ERROR;
}

TipoRet EliminarCargo(Empresa &e, Cadena cargo){
// Eliminar un cargo, junto con sus subcargos y personas asociadas.
// Elimina un cargo en la empresa si cargo ya existe en la misma.
// En otro caso la operación quedará sin efecto.
// Si el cargo a eliminar posee subcargos, éstos deberán ser eliminados también, así como
// las personas asociadas a cada uno de los cargos suprimidos.
	if (e == NULL || e->cargoPrin == NULL)
	    return ERROR;

    if (strcmp(e->cargoPrin->cargo, cargo) == 0) {
        EliminarSubCargo(e->cargoPrin);
        e->cargoPrin = NULL;
        return OK;
    }

    return EliminarCargoAux(e->cargoPrin->son, cargo);
}





