#include "libreria_aplicacion.h"

int main()
{
    unsigned int inicio=0,fin=0;
    char eleccion, eleccion2;
    string cadena1,cadena2,cadena3;
    unsigned long long int numero=0;
    do {
        cout << "Para salir ingrese cualquier valor" << endl;
        cout << "(1) Administrador" << endl;
        cout << "(2) Usuario comun" << endl;
        cout << "\nQue desea hacer?: ";
        cin >> eleccion;
        if (eleccion == '1') {
            cadena1 = leer_txt_string_admin("sudo.txt");
            cadena1.push_back('\n');
            Usuario *admin;
            admin = new Usuario;
            creacion_usuario(cadena1, admin, 0, cadena1.length());
            cout << "\ncedula: ";
            cin >> cadena1;
            cout << "clave: ";
            cin >> cadena2;
            if ((cadena1 == admin->cedula) && (cadena2 == admin->clave)) {
                delete admin;
                Usuario *usu_new;
                usu_new = new Usuario;
                cout << "\nCreacion de usuario nuevo\n\n";
                cout << "Cedula: ";
                cin >> cadena1;
                usu_new->cedula = cadena1;
                cout << "Clave: ";
                cin >> cadena1;
                usu_new->clave = cadena1;
                cout << "Saldo: ";
                cin >> numero;
                usu_new->saldo = numero;
                guardar_usu_new(usu_new);
                cout << endl;
                delete usu_new;
            }
            else cout << "\nCedula o clave incorrectas\n\n";
        }
        else if (eleccion == '2') {
            cadena3 = leer_txt_string("sudo.txt");
            cout << "\ncedula: ";
            cin >> cadena1;
            cout << "clave: ";
            cin >> cadena2;
            if (cadena3.find(cadena1) == string::npos)
                cout << "\nCedula o clave incorrectas\n\n";
            else {
                inicio = cadena3.find(cadena1);
                fin = cadena3.find('\n',inicio);
                Usuario *usu_comun;
                usu_comun = new Usuario;
                creacion_usuario(cadena3, usu_comun, inicio, (fin+1));
                if (cadena2 == usu_comun->clave) {
                    cout << "\n(1) Consultar saldo" << endl;
                    cout << "(2) Retirar dinero" << endl;
                    cout << "(3) Salir" << endl;
                    cout << "\nQue desea hacer?: ";
                    cin >> eleccion2;
                    if (eleccion2 == '1') {
                        usu_comun->saldo -= 1000;
                        cout << "El saldo es el siguiente: " << usu_comun->saldo << endl;
                        guardar_actualizacion(cadena3, usu_comun, inicio, fin);
                    }
                    else if (eleccion2 == '2') {
                        cout << "\nCuanto desea retirar: ";
                        cin >> numero;
                        if(numero > (usu_comun->saldo-1000)) cout << "\nSaldo Insuficiente" << endl;
                        else{
                            usu_comun->saldo -= 1000;
                            cout << "\nAcaba de retirar: " << numero << endl;
                            usu_comun->saldo -= numero;
                            cout << "El saldo actualizado es el siguiente: " << usu_comun->saldo << endl;
                            guardar_actualizacion(cadena3, usu_comun, inicio, fin);
                        }
                    }
                    else cout << "\nSaliendo..."<< endl;
                    cout << endl;
                }
                else cout << "\nCedula o clave incorrectas\n\n";
                delete usu_comun;
            }
        }
    } while ((eleccion == '1') || (eleccion == '2'));

    return 0;
}
