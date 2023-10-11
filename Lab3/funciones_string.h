#ifndef FUNCIONES_STRING_H
#define FUNCIONES_STRING_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>

using namespace std;

unsigned int Longitud(string NAr);
string LecturaSM (string NAr, string Binar, unsigned int T); //Lectura del archivo y encontrar su representacion en binario
string BinarioSM(char ct);
string CodificarSM(string Binar, unsigned int T, unsigned int sem, string Cod);
void EscribirSM(string NAr,string Info);
string DecodificarSM(string Cod, unsigned int T, unsigned int sem, string Binar);
string DecimalSM(string Desc, string Cade, unsigned int T);
void MenuSM();
void CodificacionPM(string& Bina, string& Cod, unsigned int sem);
void DecodificacionPM(string& Cod, string& Desc, unsigned int T, unsigned int sem);
void MenuPM();

#endif // FUNCIONES_STRING_H
