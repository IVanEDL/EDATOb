#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// definiciones.h
// Definiciones generales del proyecto (constantes, etc).

#define MAX_COMANDO 50

typedef char * Cadena;

struct tipo_persona{
    Cadena ci;
    Cadena nom;
};
typedef tipo_persona* Persona;

struct nodo_persona{
    nodo_persona next;
    nodo_persona prev;
    Persona persona;
}
typedef nodo_persona* nodoPer;

struct tipo_empresa{
    Cadena cargo;
    tipo_empresa son;
    tipo_empresa bro;
    nodo_persona integrantes;
};
typedef tipo_empresa* Empresa;

enum tipo_retorno{OK, ERROR, NO_IMPLEMENTADA};
typedef enum tipo_retorno TipoRet;



#endif
