#include <funciones_string.h>

unsigned int Longitud(string NAr) //Esta funcion permite hallar el tamaño del archivo
{
    unsigned int L;
    ifstream Tamanio;

    Tamanio.open(NAr, ios::ate | ios::binary | ios::in);

    if (Tamanio.is_open()){
        L=Tamanio.tellg();
    }
    else{
        cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
        exit(1);
    }
    Tamanio.close();
    return L;
}

string LecturaSM(string NAr, string Binar, unsigned int T) //Esta funcion permite leer el archivo natural y convertirlo a binario
{
    char carac;
    string bin;
    unsigned int cnt=0;

    ifstream Lecture;

    Lecture.open(NAr, ios::binary | ios::in);

    if(Lecture.is_open()){
        carac=Lecture.get();
        while(!Lecture.eof()){
            bin=BinarioSM(carac);
            for(int s=7; s>=0 && cnt<T*8;s--, cnt++){
                Binar+=bin[s];
            }
            carac=Lecture.get();
        }
    }
    else{
        cout << "ERROR AL ABRIR EL ARCHIVO." << endl;
        exit(1);
    }
    Lecture.close();
    return Binar;
}

string BinarioSM(char ct) //Esta funcion permite convertir un caracter a binario
{
    string bina;
    int dec=ct, aux=0;
    if(dec<0) dec+=256;
    for (int j=7; j>=0; j--){
        aux=dec%2;
        bina+=aux+48;
        dec/=2;
    }
    return bina;
}

string CodificarSM(string Binar, unsigned int T, unsigned int sem, string Cod) //Esta funcion permite codificar la representacion binario del archivo natural
{
    string straux;
    unsigned int m=0,R;

    if((T*8)%sem!=0){
        for(unsigned int i=1; i<=((T*8)/sem)+1; i++){
            for (; m<sem*i && Binar[m]!='\0'; m++){
                straux+=Binar[m];
            }
            R=straux.length();
            if(R<sem){
                Cod+=straux[R-1];
                straux.pop_back();
                Cod+=straux;
                straux.clear();
            }
            else{
                Cod+=straux[sem-1];
                straux.pop_back();
                Cod+=straux;
                straux.clear();
            }
        }
    }
    else{
        for(unsigned int i=1; i<=(T*8)/sem; i++){
            for (; m<sem*i && Binar[m]!='\0'; m++){
                straux+=Binar[m];
            }

            Cod+=straux[sem-1];
            straux.pop_back();
            Cod+=straux;
            straux.clear();
        }
    }
    return  Cod;
}

void EscribirSM(string NAr, string Info) //Esta funcion permite escribir la codificacio  en el archivo codificado.dat
{
    ofstream Codi;
    Codi.open(NAr, ios::binary | ios::out);
    Codi << Info;
    Codi.close();
}

string DecodificarSM(string Cod, unsigned int T, unsigned int sem, string Binar) //Esta funcion permite decodificar la informacion que se encuentra en el archivo codificado.dat
{
    string straux;
    char aux;
    unsigned int m=0,R=0;

    if((T*8)%sem!=0){
        for (unsigned int j=1; j<=((T*8)/sem)+1; j++){
            for(; m<sem*j && Cod[m]!='\0'; m++){
                straux+=Cod[m];
            }
            R=straux.length();
            if(R<sem){
                for(unsigned int s=0; s<R; s++){
                    aux=straux[s];
                    if(straux[s+1]!='\0'){
                        straux[s]=straux[s+1];
                        straux[s+1]=aux;
                    }
                }
                Binar+=straux;
                straux.clear();
            }
            else{
                for(unsigned int s=0; s<sem; s++){
                    aux=straux[s];
                    if(straux[s+1]!='\0'){
                        straux[s]=straux[s+1];
                        straux[s+1]=aux;
                    }
                }
                Binar+=straux;
                straux.clear();
            }
        }
    }
    else{
        for (unsigned int j=1; j<=(T*8)/sem; j++){
            for(; m<sem*j && Cod[m]!='\0'; m++){
                straux+=Cod[m];
            }

            for(unsigned int s=0; s<sem; s++){
                aux=straux[s];
                if(straux[s+1]!='\0'){
                    straux[s]=straux[s+1];
                    straux[s+1]=aux;
                }
            }
            Binar+=straux;
            straux.clear();
        }
    }
    return Binar;
}


string DecimalSM(string Desc, string Cade, unsigned int T) //Permite convertir de la decodificacion a decimal y por tanto, a caracter
{
    unsigned int b=0;
    int pt=7, Deci=0;
    for (unsigned int d=1; d<=T; d++){
        for(;b<d*8;b++){
            Deci+=(Desc[b]-48)*pow(2,pt);
            pt--;
        }
        Cade+=char(Deci);
        Deci=0;
        pt=7;
    }
    return Cade;
}

void MenuSM()
{
    unsigned short opsm;
    unsigned int sem, Lon;
    string Nature, Codf;
    string Bin, Cadena, Cod ;
    bool banSM=true;

    cout << "Ingrese el nombre del archivo para extraer la informacion(agregue .txt): ";
    cin.get();
    getline(cin,Nature);
    fflush(stdin);
    cout << "Ingrese el nombre del archivo para guardar la codificacion(agregue.dat): ";
    getline(cin,Codf);
    system("cls");

    while(banSM){

        cout<< "Segundo Metodo" << endl;
        cout << "1. Codificar" << endl;
        cout << "2. Decodificar" << endl;
        cout << "3. Salir" << endl;
        cout << "Digite la opcion a realizar: ";
        cin >> opsm;

        switch (opsm) {

        case 1:
            cout << "Digite la semilla: ";
            cin >> sem;
            Lon=Longitud(Nature);
            Bin=LecturaSM(Nature,Bin,Lon);
            Cod=CodificarSM(Bin,Lon,sem,Cod);
            Cadena=DecimalSM(Cod,Cadena,Lon);
            EscribirSM(Codf,Cadena);

            Bin.clear();
            Cod.clear();
            Cadena.clear();

            system("PAUSE");
            system("CLS");
            break;

        case 2:
            cout << "Digite la semilla: ";
            cin >> sem;
            cout << "Ingrese el nombre donde tendras el archico decodificado(Agregar .txt al final): ";
            cin >> Nature;
            Lon=Longitud(Codf);
            Cod=LecturaSM(Codf,Cod,Lon);
            Bin=DecodificarSM(Cod,Lon,sem,Bin);
            Cadena=DecimalSM(Bin,Cadena,Lon);
            EscribirSM(Nature,Cadena);


            Bin.clear();
            Cod.clear();
            Cadena.clear();

            system("PAUSE");
            system("CLS");
            break;

        case 3:

            banSM=false;
            system("CLS");
            break;
        }
   }
}

void CodificacionPM(string& Bina, string& Cod, unsigned int sem)
{
    unsigned int Cs = 0, Us = 0;
    Cod.resize(Bina.length(), '0');
    // Invertir los números del primer grupo de tamaño "sem"
    for (unsigned int i = 0; i < sem && i < Bina.length(); i++) {
        if (Bina[i] == '0') {
            Cod[i] = '1';
        } else if (Bina[i] == '1') {
            Cod[i] = '0';
        }
    }

    // Codificar el resto de los grupos
    for (unsigned int k = 1; k < Bina.length() / sem; k++) {
        // Contar la cantidad de unos y ceros
        for (unsigned int i = k * sem; i < (k + 1) * sem && i < Bina.length(); i++) {
            if (Bina[i] == '1') {
                Us++;
            } else if (Bina[i] == '0') {
                Cs++;
            }
        }

        // Aplicar las reglas de codificación
        for (unsigned int i = k * sem; i < (k + 1) * sem && i < Bina.length(); i++) {
            if (Us == Cs) {
                if (Cod[i] == '0') {
                    Cod[i] = '1';
                } else if (Cod[i] == '1') {
                    Cod[i] = '0';
                }
            } else if (Cs > Us) {
                if ((i - k * sem + 1) % 2 == 0) {
                    if (Cod[i] == '0') {
                        Cod[i] = '1';
                    } else if (Cod[i] == '1') {
                        Cod[i] = '0';
                    }
                }
            } else {
                if ((i - k * sem + 1) % 3 == 0) {
                    if (Cod[i] == '0') {
                        Cod[i] = '1';
                    } else if (Cod[i] == '1') {
                        Cod[i] = '0';
                    }
                }
            }
        }

        // Reiniciar los contadores
        Cs = 0;
        Us = 0;
    }
}

void DecodificacionPM(string& Cod, string& Desc, unsigned int T, unsigned int sem)
{
    unsigned int j=0, Cs=0, Us=0, aux=0, cnt=0;
    Cod.resize(Desc.length(), '0');
    if((T*8)%sem==0){
        for (unsigned int m=1; m<=(T*8)/sem; m++){
            for(;j<sem*m && j < Cod.size(); j++){
                if(j<sem){
                    if(Desc[j]=='0'){
                        Cod[j]='1';
                    }
                    else if (Desc[j]=='1'){
                        Cod[j]='0';
                    }
                }
                else{
                    Cod[j]=Desc[j];
                }
            }
        }
        j=sem;

        for(unsigned int k=1; k<(T*8)/sem; k++){
            for(; j<sem*k && j < Desc.size(); j++){
                if(Desc[j]=='1'){
                    Us++;
                }
                else if(Desc[j]=='0'){
                    Cs++;
                }
            }
            aux=j-sem;
            if(Us==Cs){ //Primer regla
                for(; aux<sem*(k+1) && aux < Desc.size(); aux++){
                    if(Desc[aux]=='0'){
                        Cod[aux]='1';
                    }
                    else if (Cod[aux]=='1'){
                        Cod[aux]='0';
                    }
                }
            }
            else if(Cs>Us){ //Segunda regla
                cnt=1;
                for(; aux<sem*(k+1) && aux < Desc.size(); aux++){
                    if(cnt%2==0){
                        if(Desc[aux]=='0'){
                            Cod[aux]='1';
                        }
                        else if (Cod[aux]=='1'){
                            Cod[aux]='0';
                        }
                    }
                    cnt++;
                }
            }
            else{ //Tercer regla
                cnt=1;
                for(; aux<sem*(k+1) && aux < Desc.size(); aux++){
                    if(cnt%3==0){
                        if(Desc[aux]=='0'){
                            Cod[aux]='1';
                        }
                        else if (Cod[aux]=='1'){
                            Cod[aux]='0';
                        }
                    }
                    cnt++;
                }
            }
            Cs=0;
            Us=0;
        }
    }
    else{ //para longitud impar
        for (unsigned int m=1; m<=((T*8)/sem)+1; m++){
            for(;j<sem*m && j < Cod.size(); j++){
                if(j<sem){
                    if(Desc[j]=='0'){
                        Cod[j]='1';
                    }
                    else if (Desc[j]=='1'){
                        Cod[j]='0';
                    }
                }
                else{
                    Desc[j]=Cod[j];
                }
            }
        }
        j=0;

        for(unsigned int k=1; k<((T*8)/sem)+1; k++){
            for(; j<sem*k && j < Desc.size(); j++){
                if(Desc[j]=='1'){
                    Us++;
                }
                else if(Desc[j]=='0'){
                    Cs++;
                }
            }
            aux=j;
            if(Us==Cs){ //Primer regla
                for(; aux<sem*(k+1) && aux < Desc.size(); aux++){
                    if(Desc[aux]=='0'){
                        Cod[aux]='1';
                    }
                    else if (Cod[aux]=='1'){
                        Cod[aux]='0';
                    }
                }
            }
        }
    }
}

void MenuPM()
{
    unsigned short opsm;
    unsigned int sem, Lon;
    string Nature, Codf;
    string Bin, Cadena, Cod ;
    bool banSM=true;

    cout << "Ingrese el nombre del archivo para extraer la informacion(agregue .txt): ";
    cin.get();
    getline(cin,Nature);
    fflush(stdin);
    cout << "Ingrese el nombre del archivo para guardar la codificacion(agregue.dat): ";
    getline(cin,Codf);
    system("cls");

    while(banSM){

        cout<< "Segundo Metodo" << endl;
        cout << "1. Codificar" << endl;
        cout << "2. Decodificar" << endl;
        cout << "3. Salir" << endl;
        cout << "Digite la opcion a realizar: ";
        cin >> opsm;

        switch (opsm) {

        case 1:
            cout << "Digite la semilla: ";
            cin >> sem;

            Lon=Longitud(Nature);
            Bin=LecturaSM(Nature,Bin,Lon);
            CodificacionPM(Bin,Cod,sem);
            Cadena=DecimalSM(Cod,Cadena,Lon);
            EscribirSM(Codf,Cadena);
            system("PAUSE");
            system("CLS");
            break;
        case 2:{
            cout << "Introduzca la semilla: ";
            cin >> sem;
            Lon = Longitud(Nature);
            Bin=LecturaSM(Nature,Bin,Lon);
            DecodificacionPM(Cod, Bin, Lon, sem);
            Cadena=DecimalSM(Cod,Cadena,Lon);
            EscribirSM(Codf,Cadena);

            system("PAUSE");
            system("CLS");
            break;
        }
        case 3:
            banSM = false;
            system("CLS");
            break;
        default:
            cout << "No se pudo encontrar la opcion. Digitela nuevamente" << endl;
            system("PAUSE");
            system("CLS");
            break;
        }
    }
}
