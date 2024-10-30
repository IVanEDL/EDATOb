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

struct tipo_empresa{
    Cadena cargo;
    Empresa son;
    Empresa bro;
    nodoPer integrantes;
};



Empresa BuscarCargo(Empresa e, Cadena cargo){
	if(e == NULL){
		return NULL;
	}else if(strcasecmp(e->cargo, cargo)){
		return e;
	}else{
	    Empresa aux = BuscarCargo(e->bro, cargo);
		if(aux != NULL){
			return aux;
		}else{
			return BuscarCargo(e->son, cargo);
		}
	}
}

TipoRet CrearOrg(Empresa &e, Cadena cargo){
// Inicializa la empresa y crea el primer cargo de la empresa.
// Originalmente la misma debería  estar vacía, en otro caso la operación quedará sin efecto.
	if (e != NULL){
		return ERROR;
	} else {
		e = new(tipo_empresa);
		e->cargo = cargo, e->son = NULL, e->bro = NULL, e->integrantes = NULL;
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
}

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
}

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

/*Cadena[]BuscaryListar(Cadena[] &ret, Empresa e){
	
}*/

TipoRet ListarCargosAlf(Empresa e){
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo.
/*	if(e == NULL){
		return NULL;
	}else if(e -> bro == NULL){
		printf("cargo %s", e -> cargo);
		return ListarCargosAlf(e -> son);
	}else{
		printf("cargo %s", e -> cargo);
		return ListarCargosAlf(e -> bro);
	}*/
	return NO_IMPLEMENTADA;
}

TipoRet ListarJerarquia(Empresa e){
// Listar todos los cargos de la empresa en orden jerárquico.
// Lista todos los cargos de la empresa ordenados por nivel jerárquico e indentados
// según se muestra el ejemplo de la letra.
	return NO_IMPLEMENTADA;
}

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
			aux2->prev = NULL;
			aux2->next = NULL;
			aux2->persona = new(tipo_persona);
			aux2->persona->ci = ci;
			aux2->persona->nom = nom;
			BuscarCargo(e, cargo)->integrantes = aux2;
			return OK;
		}
		else if (aux1->next != NULL){
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
		}
		else{
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


TipoRet ListarSuperCargos (Empresa e, Cadena cargo){
// Dado un cargo listar los cargos que lo anteceden.
// Lista todas los cargos que anteceden, en la jerarquía, al cargo de nombre cargo.
	return NO_IMPLEMENTADA;
}

