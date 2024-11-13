// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.c
// Modulo de Implementacion de la Empresa

using namespace std;
#include "definiciones.h"
#include "empresa.h"
#include "listaOrdenes.c"

struct tipo_persona{
    Cadena ci;
    Cadena nom;
};

struct nodo_persona{
    nodoPer next;
    nodoPer prev;
    Persona persona;
}; //Nodo_Persona; Es un nodo de lista doble con una estructura Persona dentro.

struct tipo_empresa{
	ListaOrden lorden;
	TipoCargo cargoPrin;
};

struct tipo_cargo{
    Cadena cargo;
    Empresa son;
    Empresa bro;
    nodoPer integrantes;
};



TipoCargo BuscarCargo(Empresa e, Cadena cargo){
	if(e == NULL){
		return NULL;
	}
	TipoCargo aux = e->cargoPrin;

	if(strcasecmp(aux->cargo, cargo) == 0){
		return aux;
	}
	TipoCargo aux2 = BuscarCargo(aux->bro, cargo);
	if(aux2 != NULL){
		return aux2;
	}
	return BuscarCargo(aux2->son, cargo);
}


TipoRet CrearOrg(Empresa &e, Cadena cargo){
// Inicializa la empresa y crea el primer cargo de la empresa.
// Originalmente la misma debería  estar vacía, en otro caso la operación quedará sin efecto.
	if (e != NULL){
		return ERROR;
	} else {
		e = new(tipo_empresa);
		TipoCargo man = new(tipo_cargo);
		e->cargoPrin = man;
		man->bro = NULL;
		man->cargo = cargo;
		man->son = NULL;
		man->integrantes = NULL;
		e->lorden = crearListaOrden(man, cargo);
		return OK;
	}
}

TipoRet EliminarOrg(Empresa &e){
// Eliminar el organigrama, elimina toda la estructura del organigrama, liberando la memoria asignada.
// Pendiente: esta función requiere modificaciones. Es un poco estúpido borrar la estructura nodo por-
//-nodo sin una función adyacente que borre las personas de cada cargo. Pero hace lo que tiene que hacer.
	if (e != NULL){
		if (e->son != NULL) {
			EliminarOrg(e->son);
		}
		if (e->bro != NULL) {
			EliminarOrg(e->bro);
		}
		e->cargo = NULL;
		e->integrantes = NULL;
		//En cuanto esté eliminar persona, aquí va una llamada a otra función que sea "limpiar toda persona" o así
	}
	e = NULL;
	return OK;
} //Pending redo

TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo){
// Insertar un nuevo cargo como dependiente de otro ya existente.
// El nuevo cargo no debe existir en el sistema.
	Empresa aux = NULL;
	Empresa aux2 = BuscarCargo(e, cargoPadre);
	if (BuscarCargo(e, nuevoCargo) != NULL){
		return ERROR;
	}else if (aux2->son != NULL){
		return NuevoCargoBro(e, aux2->son, nuevoCargo);
	}else{
		aux = new(tipo_empresa);
		aux->son = NULL;
		aux->bro = NULL;
		aux->cargo = nuevoCargo;
		aux->integrantes = NULL;
		aux2->son = aux;
		return OK;
	}
} //Pending redo

TipoRet NuevoCargoBro(Empresa &e, Empresa &cargoHermano, Cadena nuevoCargo){
	if (BuscarCargo(e, nuevoCargo)->son != NULL){
		return ERROR;
	}
	else{
		if (cargoHermano->bro != NULL){
			return NuevoCargoBro(e, cargoHermano->bro, nuevoCargo);
		} else {
			Empresa cargoNuevo = new(tipo_empresa);
			cargoHermano->bro = cargoNuevo;
			cargoNuevo->son = NULL;
			cargoNuevo->cargo = nuevoCargo;
			cargoNuevo->integrantes = NULL;
			return OK;
		}
	}
}

TipoRet EliminarCargo(Empresa &e, Cadena cargo){
// Eliminar un cargo, junto con sus subcargos y personas asociadas.
// Elimina un cargo en la empresa si cargo ya existe en la misma.
// En otro caso la operación quedará sin efecto.
// Si el cargo a eliminar posee subcargos, éstos deberán ser eliminados también, así como
// las personas asociadas a cada uno de los cargos suprimidos.
	return NO_IMPLEMENTADA;
}



