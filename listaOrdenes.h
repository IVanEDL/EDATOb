#ifndef LISTAORDENES_H
#define LISTAORDENES_H

// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// listaOrdenes.h
// Modulo de Definición del módulo de órdenes de cargos

#include "definiciones.h"
#include "personas.h"
#include "empresa.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
typedef struct tipo_empresa* Empresa;
typedef struct tipo_lista_orden* ListaOrden;
typedef struct tipo_cargo* TipoCargo;

TipoRet ListarCargosAlf(Empresa e);
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo. 

TipoRet ListarJerarquia(Empresa e);
// Listar todos los cargos de la empresa en orden jerárquico. 
// Lista todos los cargos de la empresa ordenados por nivel jerárquico e indentados
// según se muestra el ejemplo de la letra. 

TipoRet ListarSuperCargos (Empresa e, Cadena cargo);
// Dado un cargo listar los cargos que lo anteceden.
// Lista todas los cargos que anteceden, en la jerarquía, al cargo de nombre cargo. 

ListaOrden crearListaOrden(Empresa &e, TipoCargo car);
ListaOrden crearNodoLorden(TipoCargo e, Cadena car, TipoCargo supercar, ListaOrden lorden);
void eliminarNodoLorden(ListaOrden lorden, TipoCargo e);
#endif