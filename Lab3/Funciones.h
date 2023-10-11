#ifndef FUNCIONES_H
#define FUNCIONES_H

void leer_archivo(char *archivo, char* contenido, unsigned long long longitud);
void escribirEnArchivo(char* texto, char* nombreArchivo, unsigned long long longitud);
void decimal_binario(char *texto, unsigned long long longitud, char *c_binario);
char binario_texto(char *numero_binario);
bool comparar(char *cadena1, char *cadena2);
void invertir(char* binario, int semilla);
int contar0(char *binario, int semilla);
void invertir_cada_2_bits(char* binario, int semilla);
void invertir_cada_3_bits(char* binario, int semilla);
void desplazar_der(char* binario, int n);
void desplazar_izq(char* binario, int n);
void procesar_grupo(int n, int ceros, int unos, char* codificacion, char* grupos, unsigned long long cont);
void primer_metodo(int n, unsigned long long longitud, char *binario, short opcion);
void segundo_metodo(int n, unsigned long long longitud, char *binario, short opcion);
void decod_primer_metodo(int n, unsigned long long longitud, char *binario, char* codif, short opcion);
void decod_segundo_metodo(int n, unsigned long long longitud, char *binario,  char* codif, short opcion);
unsigned long long hallar_len(char *texto);
void procesar_Archivo(char* nombreArchivo, int n, short int opcion, short int metodo, char* codif);
void administrador(short metodo, short opcion, short semilla);
void crear_usuarios(char* cedula,char* claveU,char* saldo);
bool inicio_sesion(char* cedula,char* clave, char *Susaldo);
void actualizar_saldo(char *cedula, char* Cl_ingresada, char *nuevo_saldo);

#endif // FUNCIONES_H
