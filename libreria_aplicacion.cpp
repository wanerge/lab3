#include "libreria_aplicacion.h"

string gestor_decodificar(string cadena1){
    string cadena2;
    cadena2 = convertir_binario_str(cadena1);
    cadena2 = decodificar_string(cadena2,5);
    cadena2 = convertir_string_str(cadena2);
    return cadena2;
}

string gestor_codificar(string cadena1){
    string cadena2;
    cadena2 = convertir_binario_str(cadena1);
    cadena2 = codificar_string(cadena2,5);
    cadena2 = convertir_string_str(cadena2);
    return cadena2;
}

Usuario::Usuario(){
    cedula = "";
    clave = "";
    saldo = 0;
}
Usuario::Usuario(const string &cedu, string &cla, unsigned long long int sal){
    cedula = cedu;
    clave = cla;
    saldo = sal;
}
Usuario::~Usuario(){

}

void creacion_usuario(string cadena_usu, Usuario *admin, unsigned int inicio, unsigned int fin)
{
    unsigned long long int numero=0;
    short caso=1;
    string cadena;
    for (unsigned int i = inicio; i < fin ; i++ ) {
        if((cadena_usu[i] != ',') && (cadena_usu[i] != '\n'))
            cadena.push_back(cadena_usu[i]);
        else if ((cadena_usu[i] == ',') || (i == fin-1)) {
            switch (caso) {
                case 1:
                    admin->cedula = cadena;
                    caso++;
                    cadena = "";
                break;

                case 2:
                    cadena = gestor_decodificar(cadena);
                    admin->clave = cadena;
                    caso++;
                    cadena="";
                break;

                default:
                    cadena = gestor_decodificar(cadena);
                    numero = string_a_entero(cadena);
                    admin->saldo = numero;
                break;
            }
        }
    }
}

unsigned long long int string_a_entero(string cadena){
    unsigned long long int num=0;
    for (unsigned int i = 0; i < cadena.length() ; i++ ) {
        num += (cadena[i]-48);
        num *= 10;
    }
    num /= 10;
    return num;
}

string entero_a_string(unsigned long long int num){
    string cadena;
    if (num == 0) cadena.push_back('0');
    for (;num > 0 ; num /=10 ) {
        cadena = (char((num%10)+48)+cadena);
    }
    return cadena;
}

void guardar_usu_new(Usuario *usu_new)
{
    string cadena, cadena2;
    usu_new->clave = gestor_codificar(usu_new->clave);
    cadena2 = entero_a_string(usu_new->saldo);
    cadena2 = gestor_codificar(cadena2);
    cadena += usu_new->cedula+',';
    cadena += usu_new->clave+',';
    cadena += cadena2+'\n';
    fstream archivo("sudo.txt", fstream::app);
    for (unsigned int i=0; i < cadena.length()  ; i++) {
        archivo.put(cadena[i]);
    }
    archivo.close();
}

string leer_txt_string(string nom_archivo)
{
    string archivo_string;
    fstream archivo(nom_archivo, fstream::in);
    if(archivo.is_open()){
        while (!archivo.eof()) {
            archivo_string.push_back(archivo.get());
        }
        archivo.close();
        archivo_string.pop_back();
    }
    else cout << "El nombre del archivo no existe" << endl;
    return archivo_string;
}

string leer_txt_string_admin(string nom_archivo)
{
    string archivo_string;
    fstream archivo(nom_archivo, fstream::in);
    if(archivo.is_open()){
        getline(archivo,archivo_string);
        archivo.close();
    }
    else cout << "El nombre del archivo no existe" << endl;
    return archivo_string;
}

string convertir_binario_str(string archivo_string)
{
    string archivo_binario;
    char a;
    int longitud_string = archivo_string.length();
    for ( int i = 0; i < longitud_string ; i++ ) {
        a = archivo_string[i];
        for (int j = 0; j < 8 ;j++ ) {
            if ((a & 128) == 128)archivo_binario.push_back('1');
            else archivo_binario.push_back('0');
            a = a<<1;
        }
    }
    return archivo_binario;
}

string convertir_string_str(string archivo_binario)
{
    string archivo_string;
    int cont=0, caso=0, num=0;
    unsigned long long longitud_string = archivo_binario.length();
    for (unsigned long long i = 0; i < longitud_string ;i++ ) {
        cont++;
        if(archivo_binario[i] == '1')caso = cont;
        else caso = 0;
        switch (caso) {
            case 1:
                num += 128;
            break;
            case 2:
                num += 64;
            break;
            case 3:
                num += 32;
            break;
            case 4:
                num += 16;
            break;
            case 5:
                num += 8;
            break;
            case 6:
                num += 4;
            break;
            case 7:
                num += 2;
            break;
            case 8:
                num += 1;
            break;
        }
        if((i+1)%8==0){
            cont=0;
            archivo_string.push_back(num);
            num=0;
        }
    }
    return archivo_string;
}

string codificar_string(string archivo_binario, short semilla)
{
    string archivo_codificado;
    int cont=1, cont_unos=0, caso=1;
    unsigned long long longitud_string = archivo_binario.length();
    for (unsigned long long i = 0; i < longitud_string ;i++ ) {
        if(archivo_binario[i] == '1')cont_unos++;
        switch (caso) {
            case 1:
                if(archivo_binario[i] == '1')archivo_codificado.push_back('0');
                else archivo_codificado.push_back('1');
            break;

            case 2:
                if (cont%2==0) {
                    if(archivo_binario[i] == '1')archivo_codificado.push_back('0');
                    else archivo_codificado.push_back('1');
                }
                else archivo_codificado.push_back(archivo_binario[i]);
            break;

            default:
                if (cont%3==0) {
                    if(archivo_binario[i] == '1')archivo_codificado.push_back('0');
                    else archivo_codificado.push_back('1');
                }
                else archivo_codificado.push_back(archivo_binario[i]);
            break;
        }
        if (cont == semilla) {
            if(semilla-cont_unos == cont_unos) caso = 1;
            else if (semilla-cont_unos > cont_unos) caso = 2;
            else caso = 3;
            cont = 0;
            cont_unos=0;
        }
        cont++;
    }
    return archivo_codificado;
}

string decodificar_string(string archivo_binario, short semilla)
{
    string archivo_decodificado;
    int cont=1, cont_unos=0, caso=1;
    unsigned long long longitud_string = archivo_binario.length();
    for (unsigned long long i = 0; i < longitud_string ;i++ ) {
        switch (caso) {
            case 1:
                if(archivo_binario[i] == '1')archivo_decodificado.push_back('0');
                else archivo_decodificado.push_back('1');
            break;

            case 2:
                if (cont%2==0) {
                    if(archivo_binario[i] == '1')archivo_decodificado.push_back('0');
                    else archivo_decodificado.push_back('1');
                }
                else archivo_decodificado.push_back(archivo_binario[i]);
            break;

            default:
                if (cont%3==0) {
                    if(archivo_binario[i] == '1')archivo_decodificado.push_back('0');
                    else archivo_decodificado.push_back('1');
                }
                else archivo_decodificado.push_back(archivo_binario[i]);
            break;
        }
        if(archivo_decodificado[i] == '1')cont_unos++;
        if (cont == semilla) {
            if(semilla-cont_unos == cont_unos) caso = 1;
            else if (semilla-cont_unos > cont_unos) caso = 2;
            else caso = 3;
            cont = 0;
            cont_unos=0;
        }
        cont++;
    }
    return archivo_decodificado;
}

void guardar_actualizacion(string archi_string, Usuario *usu, unsigned int inicio, unsigned int fin)
{
    string cadena, cadena2;
    usu->clave = gestor_codificar(usu->clave);
    cadena = entero_a_string(usu->saldo);
    cadena = gestor_codificar(cadena);
    fstream archivo("sudo.txt", fstream::out);
    for ( unsigned i = 0; i < inicio ; i++ ) {
        archivo.put(archi_string[i]);
    }
    cadena2 += usu->cedula+',';
    cadena2 += usu->clave+',';
    cadena2 += cadena;
    archivo.write(cadena2.c_str(), cadena2.length());
    for ( unsigned i = fin; i < archi_string.length() ; i++ ) {
        cout << archi_string[i];
        archivo.put(archi_string[i]);
    }
    archivo.close();
}
