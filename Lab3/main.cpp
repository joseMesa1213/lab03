#include <iostream>
#include <Funciones.h>
//#include <funciones_string.h>

using namespace std;

int main() {
    int n, opcion = 0;
    while (opcion != 4) {
        cout << "Menu de opciones:" << endl;
        cout << "1. Codificar archivo con char" << endl;
        cout << "2. Decodificar archivo" << endl;
        cout << "3. Ejecutar cajero automatico" << endl;
        cout << "4. Para salir del programa" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        system("cls");
        switch (opcion) {
            case 1:
                int metodo;
                cout << "Opcion 1. Codificar archivo" << endl;
                cout << "Ingrese el nombre del archivo que desea codificar, no olvides ponerle .txt al final: ";
                char archivo[15];
                cin >> archivo;

                cout << "Escoja el metodo para codificar el archivo (1 o 2): ";
                cin >> metodo;
                while (metodo != 1 && metodo != 2) {
                    cout << "Opcion no valida, intente nuevamente." << endl;
                    cout << "Escoja el metodo para codificar el archivo (1 o 2): ";
                    cin >> metodo;
                }

                cout << "Ingrese el numero de semilla para la codificacion: ";
                cin >> n;
                procesar_Archivo(archivo, n, opcion, metodo, NULL);
                cout << "El texto se codifico correctamente con una semilla de: " << n << endl;
                system("PAUSE");
                system("cls");
                break;
            case 2:
                int metodod;
                cout << "Opcion 2. Decodificar un archivo" << endl;
                cout << "Ingrese el nombre del archivo que desea decodificar, no olvides poner el formato .dat al final: ";
                char archivod[15];
                cin >> archivod;
                cout << "Escoja el metodo para decodificar el archivo (1 o 2) debe ser el mismo con el que se codifico: ";
                cin >> metodod;
                while (metodod != 1 && metodod != 2) {
                    cout << "Opción no valida, intente nuevamente." << endl;
                    cout << "Escoja el metodo para decodificar el archivo (1 o 2): ";
                    cin >> metodod;
                }
                cout << "Ingrese el numero de semilla con el cual se codifico el texto: ";
                cin >> n;
                procesar_Archivo(archivod, n, opcion, metodod, NULL);
                cout << "El texto se decodifico correctamente con una semilla de: " << n << endl;
                system("PAUSE");
                system("cls");
                break;
            case 3:
                short eleccion;
                do {
                cout << "\t BIENVENIDO A SU CAJERO FAVORITO DONDE PODRAS: \t" << endl;
                cout << "1. Ingresar como administrador del sistema" << endl;
                cout << "2. Ingresar como usuario" << endl;
                cout << "3. Salir del programa" << endl;
                cout << "Ingrese una opcion a continuacion: ";
                cin >> eleccion;
                system("cls");
                switch (eleccion) {
                case 1:
                    cout << "Primero debes encriptar tu clave con un metodo de codificacion y una semilla, luego volver aqui" << endl;
                    system("PAUSE");
                    system("cls");
                    short metodo, semilla;
                    cout << "Ingresa el metodo de codificacion usado (1 o 2): ";
                    cin >> metodo;
                    cout << "Ingresa la semilla que usaste: ";
                    cin >> semilla;
                    administrador(metodo,opcion,semilla);
                    break;
                case 2:
                    char C_ingresada[11],Cl_ingresada[5],Saldo_actual[15];
                    short usuario;
                    cout << "Ingrese su numero de cedula para validar si estas registrado: ";
                    cin >> C_ingresada;
                    cout << "Ingrese su clave de 4 digitos: ";
                    cin >> Cl_ingresada;
                    system("cls");
                    if (inicio_sesion(C_ingresada,Cl_ingresada,Saldo_actual)){
                        cout << "\t BIENVENIDO USUARIO A SU CAJERO FAVORITO DONDE PODRAS: \t" << endl;
                        do {
                            cout << "1. consultar saldo" << endl;
                            cout << "2. Retirar dinero" << endl;
                            cout << "3. Salir del programa" << endl;
                            cout << "Recuerde que cada transaccion tiene un costo de 1000$" << endl;
                            cout << "Ingrese una opcion a continuacion: ";
                            cin >> usuario;
                            system("cls");
                            int saldo_desc = 0;
                            saldo_desc = atoi(Saldo_actual);
                            saldo_desc -= 1000;
                            int retiro = 0;
                            switch(usuario){
                                case 1:
                                    // Consultar saldo
                                    cout << "El saldo disponible que tienes en tu cuenta es de: " << Saldo_actual << "$." << endl;
                                    if (saldo_desc<0){
                                        cout << "No tienes mas dinero, pidele al administrador que te pague el saldo!!" << endl;
                                        break;
                                    }
                                    else {
                                        sprintf(Saldo_actual, "%d", saldo_desc);
                                        cout << "Se ha descontado el costo de la transaccion. El saldo actualizado es de " << saldo_desc << "$." << endl;
                                        actualizar_saldo(C_ingresada,Cl_ingresada,Saldo_actual);
                                        break;
                                    }
                                case 2:
                                    cout << "El saldo dispoble que tienes en tu cuenta es de: " << Saldo_actual << "$." << endl;
                                    cout << "Ingrese la cantidad que desea retirar: ";
                                    cin >> retiro;
                                    if (retiro > saldo_desc) {
                                        cout << "No tienes suficientes fondos para realizar esta transaccion." << endl;
                                    }
                                    else {
                                        saldo_desc -= retiro;
                                        sprintf(Saldo_actual, "%d", saldo_desc);
                                        cout << "La transaccion se ha realizado exitosamente. El saldo actualizado es de " << saldo_desc << "$." << endl;
                                        actualizar_saldo(C_ingresada,Cl_ingresada,Saldo_actual);
                                    }
                                    break;
                                case 3:
                                    // Salir del programa
                                    cout << "Gracias por utilizar nuestro servicio de cajero automatico." << endl;
                                    break;
                                default:
                                    cout << "La opcion ingresada no es valida." << endl;
                                    break;
                            }
                            system("PAUSE");
                            system("cls");
                        } while (usuario != 3);
                    }
                    else
                        cout << "Cedula o clave incorrectos. " << endl;;
                    break;
                case 3:
                    break;
                default:
                    cout << "La opcion ingresada no es valida." << endl;
                    break;
                }
                } while (eleccion != 3);
            break;
        case 4:
            cout << "Gracias por usar este programa. Hasta luego." << endl;
            break;
        default:
            cout << "Opcion no valida, intente nuevamente." << endl;
            break;
        }
    }
    return 0;
}
