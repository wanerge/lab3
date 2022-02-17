#ifndef LIBRERIA_APLICACION_H
#define LIBRERIA_APLICACION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unsigned long long int string_a_entero(string);
string entero_a_string(unsigned long long int);
string gestor_codificar(string);
string gestor_decodificar(string);
string leer_txt_string(string);
string leer_txt_string_admin(string);
string convertir_binario_str(string);
string convertir_string_str(string);
string codificar_string(string, short);
string decodificar_string(string, short);
void creacion_usuario(string, struct Usuario *, unsigned int, unsigned int);
void guardar_usu_new(struct Usuario *);
void guardar_actualizacion(string, struct Usuario *, unsigned int, unsigned int);

struct Usuario
{
    string cedula;
    string clave;
    unsigned long long int saldo;

    Usuario();
    Usuario(const string &cedu, string &cla, unsigned long long int sal );
    ~Usuario();
};

#endif // LIBRERIA_APLICACION_H
