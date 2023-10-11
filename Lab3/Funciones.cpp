#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;


void leer_archivo(char* rutaArchivo, char* contenido, unsigned long long longitud)
{
    fstream archivo(rutaArchivo, ios_base::in | ios_base::binary); // Abrimos el archivo en modo lectura
    archivo.read(contenido, longitud);
    archivo.close(); // Cerramos el archivo
}

void escribirEnArchivo(char* texto, char* nombreArchivo, unsigned long long longitud) {
    ofstream archivo(nombreArchivo, ios_base::out | ios_base::binary); // Abrir archivo en modo de escritura al final del archivo
    if (archivo.is_open()) {
        archivo.write(texto,longitud); // Escribir el texto en el archivo
        archivo.flush();
        archivo.close(); // Cerrar el archivo
    } else {
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
    }
}

bool comparar(char *cadena1, char *cadena2)
{
    bool iguales=true;
    if (strlen(cadena1)!=strlen(cadena2)){
        iguales = false;
    }
    for (int i=0; i < short(strlen(cadena1));i++){
        if (cadena1[i]!=cadena2[i]){
            iguales = false;
            break;
        }
    }
    return iguales;
}

void decimal_binario(char *texto, unsigned long long longitud, char *c_binario)
{
    // Convertir cada carácter en su representación binaria y concatenar
    unsigned long long k = 0;
    for (unsigned long long i=0; i < longitud; ++i) {
        for (short int j = 7; j >= 0; --j) {
            char bit = ((texto[i] >> j) & 1) + '0'; // Convertir el bit en un caracter '0' o '1'
            c_binario[k++] = bit;
        }
    }
}

char binario_texto(char *numero_binario)
{
    int valor_decimal = 0;
    int potencia_dos = 1;
    for (int i = 7; i >= 0; i--) {
        if (numero_binario[i] == '1') {
            valor_decimal += potencia_dos;
        }
        potencia_dos *= 2;
    }
    return char(valor_decimal);
}


int contar0(char *binario, int semilla)
{
    char cero = '0';
    int ceros = 0;
    for (int i=0;i<semilla;i++){
        if (cero==binario[i])
            ceros++;
    }
    return ceros;
}

void invertir(char *binario, int semilla) {
    for(int i=0; i<semilla; i++) {
        if (binario[i]=='0')
            binario[i]='1';
        else
            binario[i]='0';
    }
}

void invertir_cada_2_bits(char *binario, int semilla)
{
    for (int i=0;i<semilla;i++){
        if ((i+1)%2==0){
            if (binario[i] == '0')
                binario[i] = '1';
            else
                binario[i] = '0';
        }
    }
}

// Funcion para invertir cada 3 bits

void invertir_cada_3_bits(char *binario, int semilla)
{
    for (int i=0;i<semilla;i++){
        if (strlen(binario)<3)
            break;
        if ((i+1)%3==0){
            if (binario[i] == '0')
                binario[i] = '1';
            else
                binario[i] = '0';
        }
    }
}

void procesar_grupo(int n, int ceros, int unos, char* codificacion, char* grupos, unsigned long long cont) {
    if (ceros == unos) {
        invertir(codificacion, n);
        memcpy(grupos + cont, codificacion, n);
    }
    else if (ceros > unos) {
        invertir_cada_2_bits(codificacion, n);
        memcpy(grupos + cont, codificacion, n);
    }
    else if (ceros < unos) {
        invertir_cada_3_bits(codificacion, n);
        memcpy(grupos + cont, codificacion, n);
    }
}

void primer_metodo(int n, unsigned long long longitud, char* binario, short opcion) {
    int ceros = 0, unos = 0;
    char codificacion[n], codant[n], bin_text[8],codif[longitud];
    unsigned long long num_grupos = longitud * 8 / n;
    int residuo = longitud * 8 % n;
    char* grupos = new char[(num_grupos + 1) * n];
    unsigned long long cont_ant = 0, cont = n;
    memcpy(codant, binario, n);
    invertir(codant, n);
    memcpy(grupos, codant, n);
    for (unsigned long long i = 1; i < num_grupos; i++) {
        copy_n(binario + cont_ant, n, codant);
        memcpy(codificacion, binario + cont, n);
        ceros = contar0(codant, n);
        unos = n - ceros;
        procesar_grupo(n, ceros, unos, codificacion, grupos, cont);
        cont_ant += n;
        cont += n;
    }
    if (residuo != 0) {
        copy_n(binario + cont_ant, n, codant);
        memcpy(codificacion, binario + cont, n);
        ceros = contar0(codant, n);
        unos = n - ceros;
        procesar_grupo(residuo, ceros, unos, codificacion, grupos, cont);
    }
    for (unsigned long long i=0; i<longitud*8; i+=8){
        memcpy(bin_text, grupos+i, 8);
        codif[i/8]=binario_texto(bin_text);
    }
    if (opcion !=4){
        char nombre[15];
        cout << "Elige el nombre del archivo donde estara codificado con el primer metodo el texto, no olvides agregarle el formato .dat al final: ";
        cin >> nombre;
        escribirEnArchivo(codif, nombre, longitud);
        }
    else {
        char nombre[]="Registros.dat";
        escribirEnArchivo(codif, nombre, longitud);
    }
    delete[] grupos;
}

void desplazar_der(char* binario, int n) {
    char* copia = new char[n];
    memcpy(copia, binario, n);
    binario[0] = copia[n - 1];
    for (int i = 0; i <= n - 2; i++) {
        binario[i + 1] = copia[i];
    }
    delete[] copia;
}

void desplazar_izq(char* binario, int n) {
    char* copia = new char[n];
    memcpy(copia, binario, n);
    for (int i = 0; i <= n - 2; i++) {
        binario[i] = copia[i + 1];
    }
    binario[n - 1] = copia[0];
    delete[] copia;
}

void segundo_metodo(int n, unsigned long long longitud, char *binario, short opcion)
{
    unsigned long long cont=0;
    char codificacion[n],bin_text[8],codif[longitud];
    int num_grupos = longitud * 8 / n;
    int residuo = longitud * 8 % n;
    char* grupos = new char[(num_grupos + 1) * n];
    memcpy(codificacion,binario,n);
    for (int i = 1; i <= num_grupos; i++) {
            desplazar_der(codificacion,n);
            memcpy(grupos+cont,codificacion,n);
            cont+=n;
            memcpy(codificacion,binario+cont,n);
        }
    if (residuo!=0){
        desplazar_der(codificacion, residuo);
        memcpy(grupos+cont,codificacion,residuo);
    }
    for (unsigned long long i=0; i<longitud*8; i+=8){
        memcpy(bin_text, grupos+i, 8);
        codif[i/8]=binario_texto(bin_text);
    }
    if (opcion !=3){
        char nombre[15];
        cout << "Elige el nombre del archivo donde estara codificado con el segundo metodo el texto, no olvides agregarle el formato .dat al final: ";
        cin >> nombre;
        escribirEnArchivo(codif, nombre, longitud);
    }
    else {
        char nombre[]="Registros.dat";
        escribirEnArchivo(codif, nombre, longitud);
    }
    delete[] grupos;
}

void decod_primer_metodo(int n, unsigned long long longitud, char *binario, char* codif, short opcion)
{
    int ceros = 0, unos = 0;
    char codificacion[n], codant[n], bin_text[8];
    unsigned long long num_grupos = longitud * 8 / n;
    int residuo = longitud * 8 % n;
    char* grupos = new char[(num_grupos + 1) * n];
    unsigned long long cont_ant = 0, cont = n;
    memcpy(codant, binario, n);
    invertir(codant, n);
    memcpy(grupos, codant, n);
    for (unsigned long long i = 1; i < num_grupos; i++) {
        copy_n(grupos + cont_ant, n, codant);
        memcpy(codificacion, binario + cont, n);
        ceros = contar0(codant, n);
        unos = n - ceros;
        procesar_grupo(n, ceros, unos, codificacion, grupos, cont);
        cont_ant += n;
        cont += n;
    }
    if (residuo != 0) {
        copy_n(grupos + cont_ant, n, codant);
        memcpy(codificacion, binario + cont, n);
        ceros = contar0(codant, n);
        unos = n - ceros;
        procesar_grupo(residuo, ceros, unos, codificacion, grupos, cont);
    }
    for (unsigned long long i=0; i<longitud*8; i+=8){
        memcpy(bin_text, grupos+i, 8);
        codif[i/8]=binario_texto(bin_text);
    }
    delete[] grupos;
    if (opcion !=3){
        char nombre[15];
        cout << "Elige el nombre del archivo donde estara decodificado con el primer metodo el texto, no olvides agregarle el formato .txt al final: ";
        cin >> nombre;
        escribirEnArchivo(codif, nombre, longitud);
    }
}

void decod_segundo_metodo(int n, unsigned long long longitud, char *binario, char* codif, short opcion)
{
    unsigned long long cont=0;
    char codificacion[n],bin_text[8];
    int num_grupos = longitud * 8 / n;
    int residuo = longitud * 8 % n;
    char* grupos = new char[(num_grupos + 1) * n];
    memcpy(codificacion,binario,n);
    for (int i = 1; i <= num_grupos; i++) {
            desplazar_izq(codificacion,n);
            memcpy(grupos+cont,codificacion,n);
            cont+=n;
            memcpy(codificacion,binario+cont,n);
        }
    if (residuo!=0){
        desplazar_izq(codificacion, residuo);
        memcpy(grupos+cont,codificacion,residuo);
    }
    for (unsigned long long i=0; i<longitud*8; i+=8){
        memcpy(bin_text, grupos+i, 8);
        codif[i/8]=binario_texto(bin_text);
    }
    delete[] grupos;
    if (opcion !=3){
        char nombre[15];
        cout << "Elige el nombre del archivo donde estara decodificado con el primer metodo el texto, no olvides agregarle el formato .txt al final: ";
        cin >> nombre;
        escribirEnArchivo(codif, nombre, longitud);
    }
}

unsigned long long hallar_len(char *texto)
{
    unsigned long long longitud = 0;
    fstream archivo(texto, ios_base::in | ios_base::binary | ios_base::ate); // Abrimos el archivo en modo lectur
    if (!archivo.is_open()) {
        return 0;
    }
    else{
        longitud = archivo.tellg();
    }
    return longitud;
}

void procesar_Archivo(char *nombreArchivo, int n, short opcion, short metodo, char *codif)
{
    unsigned long long longitud;
    do {
        longitud = hallar_len(nombreArchivo); //Contar la cantidad de caracteres
        if (longitud == 0) {
            cout << "Nombre del archivo incorrecto, por favor intente de nuevo, no olvides agregar el formato .txt o .dat segun sea el caso." << endl;
            system("PAUSE");
            system("cls");
            cout << "Ingrese el nombre del archivo para codificar, el archivo ya debe estar creado: ";
            cin >> nombreArchivo;
        }
    } while (longitud == 0);    char* texto = new char[longitud];
    // convertir texto a binario
    leer_archivo(nombreArchivo,texto,longitud);
    char* binario = new char[longitud*8]; // reservar suficiente memoria
    decimal_binario(texto, longitud, binario);        
    delete[] texto;
    if (metodo==1 && opcion==1)
        primer_metodo(n, longitud, binario, opcion);
    else if (metodo==2 && opcion==1)
        segundo_metodo(n, longitud, binario, opcion);
    else if (metodo==1 && opcion==2){
        codif=new char[longitud];
        decod_primer_metodo(n,longitud,binario, codif, opcion);
        delete[] codif;
    }
    else if (metodo==2 && opcion==2){
        codif=new char[longitud];
        decod_segundo_metodo(n,longitud,binario, codif, opcion);
        delete[] codif;
    }
    else if (metodo==1 && opcion==3){
        decod_primer_metodo(n,longitud,binario, codif, opcion);
    }
    else if (metodo==2 && opcion==3)
        decod_segundo_metodo(n,longitud,binario, codif, opcion);
    else if (metodo==1 && opcion==4)
        primer_metodo(n, longitud, binario, opcion);
    else if (metodo==2 && opcion==4)
        segundo_metodo(n, longitud, binario, opcion);
    delete[] binario;
}

void crear_usuarios(char *cedula, char *claveU, char *saldo)
{
    char registro[]="Registros.dat";
    short L_cedula=strlen(cedula), L_claveU=strlen(claveU), L_saldo=strlen(saldo);

    // Asegurarse de que las cadenas tengan suficiente espacio para los caracteres adicionales
    if (L_cedula < 1 || L_claveU < 1 || L_saldo < 1) {
        cout << "Los valos ingresados para registrar al usuario son incorrectos" << endl;
        return; // O lanzar una excepción
    }
    char* datos=new char[L_cedula+L_saldo+L_claveU+3];
    strncpy(datos, cedula, L_cedula);
    datos[L_cedula] = ';';
    strncpy(datos + L_cedula + 1, claveU, L_claveU);
    datos[L_cedula + L_claveU + 1] = ';';
    strncpy(datos + L_cedula + L_claveU + 2, saldo, L_saldo);
    datos[L_cedula + L_claveU + L_saldo + 2] = '.';
    datos[L_cedula + L_claveU + L_saldo + 3] = '\0';

    int L_datos=strlen(datos);
    unsigned long long longitud = hallar_len(registro);
    char*texto=new char[longitud + L_datos];

    if (longitud==0){
        escribirEnArchivo(datos,registro,L_datos);
        procesar_Archivo(registro,5,4,1,NULL);
    }
    else{
        procesar_Archivo(registro,5,3,1,texto);
        // Usar memcpy para copiar los datos a la memoria inicializada con ceros
        memcpy(texto+longitud,datos,L_datos);
        escribirEnArchivo(texto,registro,L_datos+longitud);
        procesar_Archivo(registro,5,4,1,NULL);
    }
    delete[] datos;
    delete[] texto;
}


void administrador(short metodo, short opcion, short semilla)
{
    char clave_enc[]="sudo.dat";
    char clave[15], clave2[15], cedula[10], saldo[15], claveU[6];
    claveU[5]='\0';
    cout << "Ingrese la constrasena del administrador: ";
    cin >> clave;
    procesar_Archivo(clave_enc,semilla,opcion,metodo,clave2);
    system("cls");
    bool admin = comparar(clave, clave2);
    short op_admin=0;
    while (admin==true && op_admin != 2){
       cout << "\t Has ingresado como administrador, ahora podras: \t" << endl;
       cout << "1. Crear usuarios" << endl;
       cout << "2. Salir del sistema" << endl;
       cout << "Ingresa que quieres hacer: ";
       cin >> op_admin;
       system("cls");
       switch (op_admin) {
       case 1:
           cout << "Ingrese la cedula del usuario a registrar: ";
           cin >> cedula;
           cout << "Ingrese la clave del usuario a registrar, debe ser de solo 4 digitos: ";
           cin >> claveU;
           cout << "Ingrese el saldo inicial del usuario a registrar: ";
           cin >> saldo;
           crear_usuarios(cedula,claveU,saldo);
           cout << "Usuario creado con exito" << endl;
           system("PAUSE");
           system("cls");
           break;
       case 2:
           cout << "Saliendo del sistema..." << endl;
           system("cls");
           break;
       default:
           cout << "Opcion invalida, intente nuevamente" << endl;
           break;
       }
   }
   if (admin==false)
       cout << "La contrasena ingresada es incorrecta, intente nuevamente" << endl;
}


bool inicio_sesion(char *cedula, char *clave, char *Susaldo)
{
    char datos_cod[]="Registros.dat";
    unsigned long long len=hallar_len(datos_cod);
    char datos[len];
    procesar_Archivo(datos_cod,5,3,1,datos);
    char* validacion = strtok(datos, ";");
    while (validacion != NULL) {
        if (comparar(validacion, cedula) == true) {
            validacion = strtok(NULL, ";");
            if (comparar(validacion, clave) == true) {
                validacion = strtok(NULL, ".");
                memcpy(Susaldo,validacion,strlen(validacion)+1);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            validacion = strtok(NULL, ";");
            validacion = strtok(NULL, ".");
            validacion = strtok(NULL, ";");
        }
    }
    return false;
}


void actualizar_saldo(char *cedula, char *clave, char *nuevo_saldo) {
    char datos_cod[] = "Registros.dat";
    unsigned long long len = hallar_len(datos_cod);
    char datos[len], datos_actualizados[len];
    procesar_Archivo(datos_cod, 5, 3, 1, datos);
    char *posicion_actual = datos;
    char *linea = strtok(posicion_actual, ".");
    int len_Datos = 0;
    while (linea != NULL) {
        char linea_copia[strlen(linea) + 1];
        strcpy(linea_copia, linea);
        char *cedula_en_archivo = strtok(linea, ";");
        if (comparar(cedula_en_archivo, cedula)) {
            // Actualizar el saldo en la línea correspondiente al usuario
            char linea_actualizada[35];  // Ajusta el tamaño según sea necesario
            sprintf(linea_actualizada, "%s;%s;%s.", cedula, clave, nuevo_saldo);
            strcpy(datos_actualizados + len_Datos, linea_actualizada);
        } else {
            // Agregar la línea tal cual está en el archivo a la variable copy
            sprintf(datos_actualizados + len_Datos, "%s.", linea_copia);
        }
        len_Datos += strlen(linea_copia) + 1;
        posicion_actual += strlen(linea_copia) + 1; // Actualizar el puntero a la posición actual en la cadena de datos
        linea = strtok(posicion_actual, ".");
    }
    len=strlen(datos_actualizados);
    escribirEnArchivo(datos_actualizados,datos_cod,len);
    procesar_Archivo(datos_cod,5,4,1,NULL);
}



