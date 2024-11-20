#ifndef EMPRESA_H
#define EMPRESA_H

// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.h
// Modulo de Definición de la Empresa


#include "definiciones.h"
#include "listaOrdenes.h"
#include "personas.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
typedef struct tipo_empresa* Empresa;
typedef struct tipo_persona* Persona;
typedef struct nodo_persona* nodoPer;
typedef struct tipo_cargo* TipoCargo;

TipoRet CrearOrg(Empresa &e, Cadena cargo);
// Inicializa la empresa y crea el primer cargo de la empresa.
// Originalmente la misma debería  estar vacía, en otro caso la operación quedará sin efecto. 

TipoRet EliminarOrg(Empresa &e);
// Eliminar el organigrama, elimina toda la estructura del organigrama, liberando la memoria asignada.

TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo);
// Insertar un nuevo cargo como dependiente de otro ya existente.
// El nuevo cargo no debe existir en el sistema.

TipoRet EliminarCargo(Empresa &e, Cadena cargo);
// Eliminar un cargo, junto con sus subcargos y personas asociadas.
// Elimina un cargo en la empresa si cargo ya existe en la misma.
// En otro caso la operación quedará sin efecto.
// Si el cargo a eliminar posee subcargos, éstos deberán ser eliminados también, así como
// las personas asociadas a cada uno de los cargos suprimidos.

TipoCargo NuevoCargoBro(TipoCargo &cargoHermano, Cadena nuevoCargo);
TipoCargo BuscarCargo(TipoCargo e, Cadena cargo);

#endif


