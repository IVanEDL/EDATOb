// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// personas.h
// Modulo de Implementacion de Personas

using namespace std;
#include "definiciones.h"
#include "personas.h"
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

struct tipo_empresa{
	ListaOrden lorden;
	TipoCargo cargoPrin;
};

struct tipo_cargo{
    Cadena cargo;
    TipoCargo son;
    TipoCargo bro;
    nodoPer integrantes;
};

bool BuscarPersonaArbol(TipoCargo e, Cadena ci){
	//True si no existe. False si sí.
	if (e == NULL){
		return true;
	}

	nodoPer temp = e->integrantes;
	while (temp != NULL){
		if (strcasecmp(temp->persona->ci, ci) == 1){
			return false;
		}
		temp = temp->next;
	}

	if (!BuscarPersonaArbol(e->son, ci)){
		return false;
	}

	return BuscarPersonaArbol(e->bro, ci);
}

nodoPer BuscarPersonaArbolAux(TipoCargo e, Cadena ci){
	//Lo de arriba, pero auxiliarmente para devolver una persona buscada.
	if (e == NULL){
		return NULL;
	}

	nodoPer temp = e->integrantes;
	while (temp != NULL){
		if (strcasecmp(temp->persona->ci, ci) == 1){
			return temp;
		}
		temp = temp->next;
	}

	if (BuscarPersonaArbolAux(e->son, ci) != NULL){
		return BuscarPersonaArbolAux(e->son, ci);
	}

	return BuscarPersonaArbolAux(e->bro, ci);
}

TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci){
// Asignar una persona a un cargo, si este existe.
// Asigna una persona de nombre nom  y cédula de identidad ci al cargo cargo
// siempre que el cargo exista en la empresa y esa persona no este asignada a
// ese u otro cargo, en caso contrario la operación quedará sin efecto.
// Adicional: Que hijo de mil puta esto de tener que buscar la persona en todo el árbol.
	tipo_persona Per;
	Per.ci = ci;
	Per.nom = nom;

	TipoCargo Nuevocargo = BuscarCargo(e->cargoPrin, cargo);

	if (cargo == NULL){
		printf("Cargo no encontrado.");
		return ERROR;
	}

	if (!BuscarPersonaArbol(e->cargoPrin, ci)){
		printf("Persona ya existente.");
		return ERROR;
	}

	nodoPer NuevoEmp = new(nodo_persona);
	NuevoEmp->next = NULL;
	NuevoEmp->prev = NULL;

	if (Nuevocargo->integrantes == NULL){
		Nuevocargo->integrantes = NuevoEmp;
		return OK;
	}else{
		nodoPer temp = Nuevocargo->integrantes;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = NuevoEmp;
		NuevoEmp->prev = NuevoEmp;
		return OK;
	}
}

TipoRet EliminarPersona(Empresa &e, Cadena ci){
// Eliminar una persona de un cargo.
// Elimina una persona de cédula ci de la empresa siempre y cuando la misma exista,
// en caso contrario la operación quedará sin efecto.
	nodoPer aux = BuscarPersonaArbolAux(e->cargoPrin, ci);
	if (aux == NULL){
		return ERROR;
	}else{
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete(aux->persona);
		return OK;
	}
}

void LiberarPersonas(nodoPer &nodP){
    while (nodP != NULL) {
        nodoPer temp = nodP;
        nodP = nodP->next;
        
        // Liberar la memoria de la persona
        delete[] temp->persona->ci;
        delete[] temp->persona->nom;
        delete temp->persona;

        // Liberar el nodo
        delete temp;
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
	TipoCargo x = BuscarCargo(e->cargoPrin, cargo);
	printf("Cargo %s: \n", x->cargo);
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