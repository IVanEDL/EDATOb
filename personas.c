// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// personas.h
// Modulo de Implementacion de Personas

using namespace std;
#include "definiciones.h"
#include "personas.h"

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
    Cadena cargo;
    Empresa son;
    Empresa bro;
    nodoPer integrantes;
};

nodoPer BuscarPersonaArbol(Empresa e, Cadena ci){
	if (e == NULL){
		return NULL;
	}else if(e->integrantes != NULL){
		if (BuscarPersonaNodo(e->integrantes, ci) != NULL){
			return BuscarPersonaNodo(e->integrantes, ci);
		}
	}else{
	    nodoPer aux = BuscarPersonaArbol(e->bro, ci);
		if(aux != NULL){
			return aux;
		}else{
			return BuscarPersonaArbol(e->son, ci);
		}
	}
}

nodoPer BuscarPersonaNodo(nodoPer per, Cadena ci){
	if (per->persona->ci == ci)
		return per;
	else if (per->next != NULL)
		return BuscarPersonaNodo(per->next, ci);
	else
		return NULL;
}

TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci){
// Asignar una persona a un cargo, si este existe.
// Asigna una persona de nombre nom  y cédula de identidad ci al cargo cargo
// siempre que el cargo exista en la empresa y esa persona no este asignada a
// ese u otro cargo, en caso contrario la operación quedará sin efecto.
// Adicional: Que hijo de mil puta esto de tener que buscar la persona en todo el árbol.
	if (BuscarPersonaArbol(e, ci) != NULL)
		return ERROR;
	else{
		nodoPer aux1 = BuscarCargo(e, cargo)->integrantes;
		nodoPer aux2 = NULL;
		if (aux1 == NULL){
			aux2 = new(nodo_persona);
			aux2->next = NULL;
			aux2->persona = new(tipo_persona);
			aux2->persona->ci = ci;
			aux2->persona->nom = nom;
			BuscarCargo(e, cargo)->integrantes = aux2;
			return OK;
		}else if (aux1->next != NULL){
			while (aux1 != NULL){
				aux2 = aux1;
				aux1 = aux1->next;
			}
			aux1->prev = aux2;
			aux2->next = aux1;
			aux1->next = NULL;
			aux1->persona = new(tipo_persona);
			aux1->persona->ci = ci;
			aux1->persona->nom = nom;
			return OK;
		}else{
			aux2 = new(nodo_persona);
			aux2->prev = aux1;
			aux1->next = aux2;
			aux2->next = NULL;
			aux2->persona = new(tipo_persona);
			aux2->persona->ci = ci;
			aux2->persona->nom = nom;
			return OK;
		}
	}
}

TipoRet EliminarPersona(Empresa &e, Cadena ci){
// Eliminar una persona de un cargo.
// Elimina una persona de cédula ci de la empresa siempre y cuando la misma exista,
// en caso contrario la operación quedará sin efecto.
	nodoPer aux = BuscarPersonaArbol(e, ci);
	if (aux == NULL)
		return ERROR;
	else{
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete(aux->persona);
		return OK;
	}
}

TipoRet ReasignarPersona(Empresa &e, Cadena cargo, Cadena ci){
// Reasignar una persona a un nuevo cargo.
// Reasigna una persona de la empresa de cédula ci al nuevo cargo de nombre cargo
// siempre que el cargo exista en la empresa y esa persona no este ya asignada a
// dicho cargo. En caso contrario la operación quedará sin efecto.
	return NO_IMPLEMENTADA;
}

TipoRet ListarPersonas(Empresa e, Cadena cargo){
// Dado un cargo listar las personas asignadas al mismo ordenadas por fecha de alta a la empresa.
// Lista todas las personas asignadas al cargo de nombre cargo.
	if (e == 00)
    	return ERROR;
	Empresa x = BuscarCargo(e, cargo);
	printf("Cargo %c: \n", x->cargo);
	if(x == NULL || x->integrantes == NULL || x->integrantes->persona == NULL){ //
		return ERROR;
	}else{ //
		nodoPer a = x -> integrantes;
		while (a){
			printf("CI = %s, Nombre = %s\n", a->persona->ci, a->persona->nom);
			a = a->next;
		}	
	}
	return OK;
}