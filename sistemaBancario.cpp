#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>

using namespace std;

// Clase Cliente

class Cliente{
    private:
        string nombre, ciudad, direccion, telefono;
        int edad, id;

    public:
        Cliente();
        void setNuevoCliente(int, string, string, string, int, string, int);
        bool setConfirmarCliente(int);
        bool busquedaCliente(string);
        int getId();
        string getNombre();
        string getCiudad();
        string getTelefono();
};

// Clase Cuenta

class Cuenta{
    private:
        int idCuenta, nip, idCliente;
        string tipoCuenta;
        long long saldo, deuda=0;

    public:
        Cuenta();
        bool buscarCuenta(int, int);
        void setNuevaCuenta(int, int, int, string, long long, long long, int);
        void deposito(int, string);
        void retiro(int, string);
        bool pagar(int, string);
        void imprimirDatos();
        int transferenciaOrigen(long long, string);
        bool transferenciaDestino(long long, string);
        void estadoCuenta();
};


// Metodos Cliente 

// Constructor
Cliente::Cliente(){
}

// Ingresar Cliente
void Cliente::setNuevoCliente(int _id, string _nombre, string _ciudad, string _direccion, int _edad, string _telefono, int origen){
    id = _id;
    nombre = _nombre;
    ciudad = _ciudad;
    direccion = _direccion;
    edad = _edad;
    telefono = _telefono;
    if(origen == 1){ // Condicional por si es un cliente creado en esa ejecucion
        cout<<"Cliente registrado correctamente, Id asignado: "<<id;
    }
}

// Busqueda Cliente por medio del id
bool Cliente::setConfirmarCliente(int idBusqueda){
    if(idBusqueda == id){
        return true;
    }

    return false;
}

// Busqueda Cliente por medio del nombre
bool Cliente::busquedaCliente(string _nombreBusqueda){

    if(_nombreBusqueda == nombre){
            system("cls");
            cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
                <<"\nCONSULTA DE CLIENTES"<<endl<<endl;
            return true;
        }
    return false;
}

// Gets

int Cliente::getId(){
    return id;
}

string Cliente::getNombre(){
    return nombre;
}

string Cliente::getCiudad(){
    return ciudad;
}

string Cliente::getTelefono(){
    return telefono;
}


// Metodos Cuenta

// Constructor
Cuenta::Cuenta(){
}

// Ingresar Nueva Cuenta

void Cuenta::setNuevaCuenta(int _idCuenta, int _idCliente, int _nip, string _tipoCuenta, long long _saldo, long long _deuda, int origen){
    
    
    idCuenta = _idCuenta;
    idCliente = _idCliente;
    nip = _nip;
    tipoCuenta = _tipoCuenta;
    saldo = _saldo;
    deuda = _deuda;

    if(origen == 1){ // Condicional por si es una cuenta ingresada en esa ejecucion
    cout<<"Cuenta registrada correctamente, Id de cuenta asignada: "<<idCuenta;
    }
}

// Funcion para Buscar cuentas por medio del id y del nip (Gran uso)

bool Cuenta::buscarCuenta(int idBusqueda, int nipBusqueda){
    if(idBusqueda == idCuenta && nipBusqueda == nip){
        return true;
    }else{
    return false;
    }
}

// Impresion de datos de una cuenta

void Cuenta::imprimirDatos(){
    
    system("cls");
    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
        <<"\nCONSULTA DE CUENTAS"<<endl<<endl;

    cout<<"Id de la Cuenta: "<<idCuenta<<endl 
        <<"Id de el Cliente: "<<idCliente<<endl
        <<"Tipo Cuenta: "<<tipoCuenta<<endl
        <<"Saldo: "<<saldo<<endl;
        if(tipoCuenta == "Credito"){
            cout<<"Deuda: "<<deuda<<endl;
        }
}

// Funcion utilizada luego de validarse los datos para depositar cargos en una cuenta

void Cuenta::deposito(int cantidadDeposito, string fecha){
    int i=0;
    ifstream archivos;
    ofstream archivosReescribir;
    ifstream archivosEstado;
    ofstream archivosEstadoReescribir;

    string cuentaNumero = "Cuenta " + to_string(idCuenta), datos, intermediario;
    string estadoCuenta = "estadoCuenta " + to_string(idCuenta), registro, intermediarioEstado;

    char band;

    archivos.open(cuentaNumero.c_str(), ios::in);
    archivosEstado.open(estadoCuenta.c_str(), ios::in);
    
    // Verificamos el tipo de cuenta, Para no sobrepasar el maximo de una cuenta Credito

    if(tipoCuenta == "Credito"){
        do
        {
            if((cantidadDeposito + saldo) > 5000000){
                cout<<"\nEl maximo saldo para una cuenta credito es de $5.000.000"<<endl;
                cout<<"\nDesea ingresar una nueva cantidad: Si (s) / No (n): ";
                cin>>band;
                if(band == 's' || band == 'S'){
                    cout<<"\nIngresar nueva cantidad a depositar: ";
                    cin>>cantidadDeposito;
                }
            }
            if((cantidadDeposito + saldo) <= 5000000){
                saldo += cantidadDeposito;
                cout<<"Se han depositado "<<cantidadDeposito<<" a su saldo disponible"<<endl
                <<"\nEl nuevo saldo es: "<<saldo;
                band = 'n';

                // Buscamos intercambiar el valor del saldo en los archivos de la cuenta

                while(!archivos.eof()){
                    if(i==4){
                        getline(archivos, datos);
                        for (int j = 0; j < datos.length(); j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+3) + to_string(saldo);
                            }
                        }
                        intermediario += datos + "\n";
                    }else{
                        getline(archivos, datos);
                        intermediario += datos + "\n";
                    }
                    i++;
                }

                archivosReescribir.open(cuentaNumero.c_str(), ios::out);
                archivosReescribir<<intermediario<<endl;

                // Buscamos intercambiar el valor del saldo en los archivos de estado de la cuenta

                i=0;
                while(!archivosEstado.eof()){
                    if(i==5){
                        getline(archivosEstado, datos);
                        for (int j = 0; j < 20; j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+17) + "$" + to_string(saldo);
                            }
                        }
                        intermediarioEstado += datos + "\n";
                    } else {
                        getline(archivosEstado, datos);
                        intermediarioEstado += datos + '\n';
                    }
                    i++;
                }

                registro = " " + fecha + " \t\t\t " + "Deposito  " + " \t\t\t\t " + "$" + to_string(cantidadDeposito);
                intermediarioEstado += registro;

                archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
                archivosEstadoReescribir<<intermediarioEstado<<endl;
            
            }

        } while (((cantidadDeposito + saldo) > 5000000) && (band == 's' || band == 'S'));
        
    }else{
        saldo += cantidadDeposito;
        cout<<"Se han depositado "<<cantidadDeposito<<" de su saldo disponible"<<endl
        <<"\nEl nuevo saldo es: "<<saldo;

        // Buscamos intercambiar el valor del saldo en los archivos de la cuenta

        while(!archivos.eof()){
            if(i==4){
                getline(archivos, datos);
                for (int j = 0; j < datos.length(); j++){
                    if(datos[j] == ':'){
                        datos = datos.substr(0, i+3) + to_string(saldo);
                        }
                    }
                    intermediario += datos + "\n";
                }else{
                    getline(archivos, datos);
                    intermediario += datos + "\n";
                }
                i++;
            }

        archivosReescribir.open(cuentaNumero.c_str(), ios::out);
        archivosReescribir<<intermediario<<endl;

        // Buscamos intercambiar el valor del saldo en los archivos de estado de la cuenta

        i=0;
        while(!archivosEstado.eof()){
            if(i==5){
                getline(archivosEstado, datos);
                for (int j = 0; j < 20; j++){
                    if(datos[j] == ':'){
                        datos = datos.substr(0, i+17) + "$" + to_string(saldo);
                    }
                }
                intermediarioEstado += datos + "\n";
            } else {
                getline(archivosEstado, datos);
                intermediarioEstado += datos + '\n';
            }
            i++;
        }

        registro = " " + fecha + " \t\t\t " + "Deposito  " + " \t\t\t\t " + "$" + to_string(cantidadDeposito);
        intermediarioEstado += registro;

        archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
        archivosEstadoReescribir<<intermediarioEstado<<endl;

    }
}

// Funcion utilizada luego de validarse los datos para depositar cargos en una cuenta

void Cuenta::retiro(int cantidadRetiro, string fecha){
    int i=0;
    ifstream archivos;
    ofstream archivosReescribir;
    ifstream archivosEstado;
    ofstream archivosEstadoReescribir;

    string cuentaNumero = "Cuenta " + to_string(idCuenta), datos, intermediario;
    string estadoCuenta = "estadoCuenta " + to_string(idCuenta), registro, intermediarioEstado;

    char band;

    archivos.open(cuentaNumero.c_str(), ios::in);
    archivosEstado.open(estadoCuenta.c_str(), ios::in);
    
    do{
        if(cantidadRetiro > saldo){
            cout<<"\n La cantidad que desea retirar supera al saldo en la cuenta"<<endl;
            cout<<"Desea retirar una nueva cantidad? Si (s) / NO (n): ";
            cin>>band;
            if(band == 's' || band == 'S'){
                cout<<"\nIngrese la nueva cantidad a retirar: ";
                cin>>cantidadRetiro;
            }
        }
        if(cantidadRetiro <= saldo){
            saldo -= cantidadRetiro;

            // Apertura de los archivos para modificar sus valores respectivamente

            while(!archivos.eof()){
                    if(i==4){
                        getline(archivos, datos);
                        for (int j = 0; j < datos.length(); j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+3) + to_string(saldo);
                            }
                        }
                        intermediario += datos + "\n";
                    }else{

                        if(i==5){
                            if(tipoCuenta == "Credito"){
                                deuda += cantidadRetiro;
                                getline(archivos, datos);
                                for (int j = 0; j < datos.length(); j++){
                                    if(datos[j] == ':'){
                                    datos = datos.substr(0, i+2) + to_string(deuda);
                                    }
                                }
                                intermediario += datos + "\n";
                            }

                        } else {
                            getline(archivos, datos);
                            intermediario += datos + "\n";
                        }
                    }
                    i++;
                }

            archivosReescribir.open(cuentaNumero.c_str(), ios::out);
            archivosReescribir<<intermediario<<endl;

            i=0;
            while(!archivosEstado.eof()){
                if(i==5){
                    getline(archivosEstado, datos);
                    for (int j = 0; j < 20; j++){
                        if(datos[j] == ':'){
                            datos = datos.substr(0, i+17) + "$" + to_string(saldo);
                        }
                    }
                    intermediarioEstado += datos + "\n";
                    i++;
                } 
                if(i==6){
                    getline(archivosEstado, datos);
                    if(tipoCuenta == "Credito"){
                        for (int j = 0; j < 20; j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+16) + "$" + to_string(deuda);
                            }   
                        }
                    }
                    intermediarioEstado += datos + "\n";
                } else {
                    getline(archivosEstado, datos);
                    intermediarioEstado += datos + '\n';
                }
                i++;
            }

            registro = " " + fecha + " \t\t\t " + "Retiro    " + " \t\t\t\t " + "$" + to_string(cantidadRetiro);
            intermediarioEstado += registro;

            archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
            archivosEstadoReescribir<<intermediarioEstado<<endl;
            
            cout<<"\nRetiro realizado exitosamente";
            cout<<"\nNuevo saldo: "<<saldo;
            band = 'n';
        }

    }while(cantidadRetiro > saldo && (band == 's' || band == 'S'));
}

// Funcion de pago de deudas para cuentas de credito

bool Cuenta::pagar(int pago, string fecha){
    int i=0;
    ifstream archivos;
    ofstream archivosReescribir;
    ifstream archivosEstado;
    ofstream archivosEstadoReescribir;

    string cuentaNumero = "Cuenta " + to_string(idCuenta), datos, intermediario;
    string estadoCuenta = "estadoCuenta " + to_string(idCuenta), registro, intermediarioEstado;

    char band;

    archivos.open(cuentaNumero.c_str(), ios::in);
    archivosEstado.open(estadoCuenta.c_str(), ios::in);

    // Condicional para determinar si en efecto es una cuenta de Credito

    if(tipoCuenta == "Credito"){
        do
        {
            if(pago > deuda){
                cout<<"\nLa cantidad que desea cancelar sobrepasa el costo de la deuda:  $"<<deuda;
                cout<<"\nDesea ingresar un nuevo valor? Si (s) / No (n): ";
                cin>>band;
                if(band == 's' || band == 'S'){
                    cout<<"\nIngrese la cantidad del nuevo pago: ";
                    cin>>pago;
                }
            }

                if(pago <= deuda){
                    deuda -= pago;

                    // Apertura de archivos para modificar el valor de la deuda

                    while(!archivos.eof()){
                        if(i==5){

                            getline(archivos, datos);
                            for (int j = 0; j < datos.length(); j++){
                                if(datos[j] == ':'){
                                    datos = datos.substr(0, i+2) + to_string(deuda);
                                }
                            }
                                intermediario += datos + "\n";
                            } else {
                                getline(archivos, datos);
                                intermediario += datos + "\n";
                            }
                        i++;
                    }

                    archivosReescribir.open(cuentaNumero.c_str(), ios::out);
                    archivosReescribir<<intermediario<<endl;

                    // Condicional para determinar si en efecto es un pago y registrarlo en pantalla y archivos

                    if(pago != 0){
                        i=0;
                        cout<<"\nPago realizado exitosamente";
                        cout<<"\nValor de la deuda actual: "<<deuda;


                        while(!archivosEstado.eof()){
                        if(i==6){
                            
                            getline(archivosEstado, datos);

                            for (int j = 0; j < 20; j++){
                                if(datos[j] == ':'){
                                    datos = datos.substr(0, i+16) + "$" + to_string(deuda);
                                }
                            }
                                intermediarioEstado += datos + "\n";
                            } else {
                                getline(archivosEstado, datos);
                                intermediarioEstado += datos + '\n';
                            }
                            i++;
                        }

                        registro = " " + fecha + " \t\t\t " + "Pago  " + " \t\t\t\t " + "$" + to_string(pago);
                        intermediarioEstado += registro;

                        archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
                        archivosEstadoReescribir<<intermediarioEstado<<endl;

                        }
                        
                        band = 'n';
                        return true;
                }
        } while (pago > deuda && band == 's' || band == 'S');
    }else{
        cout<<"La funcion de pago solo se encuentra habilitada para las cuentas credito";
        return false;
    }
}

// Funcion 1/2 transferencia, para editar la cuenta saliente de una transferencia

int Cuenta::transferenciaOrigen(long long envio, string fecha){
    int i=0;
    ifstream archivos;
    ofstream archivosReescribir;
    ifstream archivosEstado;
    ofstream archivosEstadoReescribir;

    string cuentaNumero = "Cuenta " + to_string(idCuenta), datos, intermediario;
    string estadoCuenta = "estadoCuenta " + to_string(idCuenta), registro, intermediarioEstado;

    char band;

    archivos.open(cuentaNumero.c_str(), ios::in);
    archivosEstado.open(estadoCuenta.c_str(), ios::in);

    do{
        if(envio > saldo){
            cout<<"\n La cantidad que desea transferir supera al saldo en la cuenta"<<endl;
            cout<<"Desea ingredar una nueva cantidad? Si (s) / NO (n): ";
            cin>>band;
            if(band == 's' || band == 'S'){
                cout<<"\nIngrese la nueva cantidad a transferir: ";
                cin>>envio;
            }else{
                band = 'f';
            }
        }
        if(envio <= saldo){
            saldo -= envio;

            // Apertura de archivos para actualizar los nuevos datos en los archivos

            while(!archivos.eof()){
                    if(i==4){
                        getline(archivos, datos);
                        for (int j = 0; j < datos.length(); j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+3) + to_string(saldo);
                            }
                        }
                        intermediario += datos + "\n";
                    }else{

                        if(i==5){
                            if(tipoCuenta == "Credito"){
                                deuda += envio;
                                getline(archivos, datos);
                                for (int j = 0; j < datos.length(); j++){
                                    if(datos[j] == ':'){
                                    datos = datos.substr(0, i+2) + to_string(deuda);
                                    }
                                }
                                intermediario += datos + "\n";
                            }

                        } else {
                            getline(archivos, datos);
                            intermediario += datos + "\n";
                        }
                    }
                    i++;
                }

            archivosReescribir.open(cuentaNumero.c_str(), ios::out);
            archivosReescribir<<intermediario<<endl;

            i=0;
            while(!archivosEstado.eof()){
                if(i==5){
                    getline(archivosEstado, datos);
                    for (int j = 0; j < 20; j++){
                        if(datos[j] == ':'){
                            datos = datos.substr(0, i+17) + "$" + to_string(saldo);
                        }
                    }
                    intermediarioEstado += datos + "\n";
                    i++;
                } 
                if(i==6){
                    getline(archivosEstado, datos);
                    if(tipoCuenta == "Credito"){
                        for (int j = 0; j < 20; j++){
                            if(datos[j] == ':'){
                                datos = datos.substr(0, i+16) + "$" + to_string(deuda);
                            }   
                        }
                    }
                    intermediarioEstado += datos + "\n";
                } else {
                    getline(archivosEstado, datos);
                    intermediarioEstado += datos + '\n';
                }
                i++;
            }

            registro = " " + fecha + " \t\t\t " + "Tranferencia enviada" + " \t\t\t " + "$" + to_string(envio);
            intermediarioEstado += registro;

            archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
            archivosEstadoReescribir<<intermediarioEstado<<endl;

            band = 'n';
        }

    }while(envio > saldo && (band == 's' || band == 'S'));

    if(band == 'f'){
        return 0;
    }else{
        return envio;
    }
}

// Funcion 2/2 transferencia, para editar la cuenta saliente de una transferencia

bool Cuenta::transferenciaDestino(long long envio, string fecha){
    int i=0;
    ifstream archivos;
    ofstream archivosReescribir;
    ifstream archivosEstado;
    ofstream archivosEstadoReescribir;

    string cuentaNumero = "Cuenta " + to_string(idCuenta), datos, intermediario;
    string estadoCuenta = "estadoCuenta " + to_string(idCuenta), registro, intermediarioEstado;

    archivos.open(cuentaNumero.c_str(), ios::in);
    archivosEstado.open(estadoCuenta.c_str(), ios::in);

    // Esta funcion no se halla habilitada para cuentas credito

    if(tipoCuenta != "Credito"){
        saldo += envio;

        // Apertura de archivos para modificar sus respectivos valores
        
        while(!archivos.eof()){
            if(i==4){
                getline(archivos, datos);
                for (int j = 0; j < datos.length(); j++){
                    if(datos[j] == ':'){
                        datos = datos.substr(0, i+3) + to_string(saldo);
                        }
                    }
                    intermediario += datos + "\n";
                }else{
                    getline(archivos, datos);
                    intermediario += datos + "\n";
                }
                i++;
            }

        archivosReescribir.open(cuentaNumero.c_str(), ios::out);
        archivosReescribir<<intermediario<<endl;

        if(envio != 0){
            i=0;
            while(!archivosEstado.eof()){
                if(i==5){
                    getline(archivosEstado, datos);
                    for (int j = 0; j < 20; j++){
                        if(datos[j] == ':'){
                            datos = datos.substr(0, i+17) + "$" + to_string(saldo);
                        }
                    }
                    intermediarioEstado += datos + "\n";
                } else {
                    getline(archivosEstado, datos);
                    intermediarioEstado += datos + '\n';
                    }
                i++;
            }

            registro = " " + fecha + " \t\t\t " + "Transferencia Recibida" + "\t\t\t " + "$" + to_string(envio);
            intermediarioEstado += registro;

            archivosEstadoReescribir.open(estadoCuenta.c_str(), ios::out);
            archivosEstadoReescribir<<intermediarioEstado<<endl;
        }

        return true;

    }else{
        cout<<"Las cuentas de destino solo pueden ser de tipo debito";
        return false;
    }
}

// Funcion empleada para plasmar en consola el archivo de estado de la cuenta ingresada

void Cuenta::estadoCuenta(){
    system("cls");
    ifstream datosCliente;
    string datos, estadoCuenta = "estadoCuenta " + to_string(idCuenta);

    datosCliente.open(estadoCuenta.c_str(), ios::in);

    cout<<"\n\t\t\t\tESTADO DE CUENTA"<<endl<<endl;

    while(!datosCliente.eof()){
        getline(datosCliente, datos);
        cout<<datos<<endl;
        }
}

// Funciones

int idClientes();
int idCuentas();
int menu();
void clientesGuardados();
int procedimientoClientes();
void continuar();
void ingresarCliente();
void imprimirCliente();
void cuentasGuardadas();
int procedimientoCuentas();
int depositoRetiro();
void ingresarCuenta();
void registrarCuenta(int);
void imprimirCuenta();
void depositarSaldo();
void retirarSaldo();
void pago();
void transferencia();
void inversion();
void estadoCuenta();
string tiempoActual();

// Datos Globales

Cliente *clientes[100];
Cuenta *cuentas[100];

int idClienteMax, idCuentaMax;

// Funcion Main

int main(){
    system("mode con: cols=90 lines=25");
    int navegacion;

    cout<<"hola";

    do
    {   
        // Registro de los clientes y cuentas ya guardadas anteriormente por medio de los archivos

        clientesGuardados();
        cuentasGuardadas();   
        navegacion = menu();    

        switch(navegacion){
            case 1:
                navegacion = procedimientoClientes();
                    switch (navegacion){
                    case 1:
                        ingresarCliente();
                        break;
                    case 2:
                        imprimirCliente();
                        break;
                    }
                    break;
            case 2:
                navegacion = procedimientoCuentas();
                switch (navegacion){
                case 1:
                    ingresarCuenta();
                    break;
                case 2:
                    imprimirCuenta();
                    break;
                }
                break;

            case 3:
                navegacion =  depositoRetiro();
                switch (navegacion){
                case 1:
                    depositarSaldo();
                    break;
                
                case 2:
                    retirarSaldo();
                    break;
                }
                break;

            case 4:
                pago();
                break;

            case 5:
                transferencia();
                break;

            case 6:
                inversion();
                break;

            case 7:
                estadoCuenta();
                break;
            }
    }while(navegacion != 8);
    

    getch();
    return 0;
}

// Manejo optimizado del iD de los clientes por medio de archivos

int idClientes(){
    ifstream identificador;
    ofstream clientes;
    string idNueva, idUltima;
    int idUltimaInt, idNuevaInt;

    identificador.open("idClientes", ios::in);
    clientes.open("idClientes", ios::app);

    while(!identificador.eof()){
        getline(identificador, idUltima);
    }

    idUltimaInt = stoi(idUltima);
    idNuevaInt = idUltimaInt + 1;
    idNueva = "\n" + to_string(idNuevaInt);

    clientes<<idNueva;

    return idNuevaInt;
}

// Manejo Optimizado del Id de las cuentas por medio de archivos

int idCuentas(){
    ifstream identificador;
    ofstream cuentas;
    string idNueva, idUltima;
    int idUltimaInt, idNuevaInt;

    identificador.open("idCuentas", ios::in);
    cuentas.open("idCuentas", ios::app);

    while(!identificador.eof()){
        getline(identificador, idUltima);
    }

    idUltimaInt = stoi(idUltima);
    idNuevaInt = idUltimaInt + 1;
    idNueva = "\n" + to_string(idNuevaInt);

    cuentas<<idNueva;

    return idNuevaInt;
}

// Funcion utilizada frecuentemente para permitir una salida limpia de una funcion

void continuar(){
    cout<<"\n\nPresione una tecla para volver al menu principal...";
        getch();
}

// Impresion del menu y seleccion de opcion

int menu(){
    system("cls");
    int opcion;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl;
    cout<<"\nMENU PRINCIPAL"<<endl<<endl
        <<"1. Clientes"<<endl
        <<"2. Cuentas"<<endl
        <<"3. Depositos/Retiros"<<endl
        <<"4. Pagos"<<endl
        <<"5. Transferencias"<<endl
        <<"6. Inversion"<<endl
        <<"7. Estado de Cuenta"<<endl
        <<"8. Salir"<<endl<<endl
        <<"Ingrese Opcion: ";
        cin>>opcion;
    
    return opcion;
}

// Registro de los clientes guardados en los archivos en el vector global 'Clientes'

void clientesGuardados(){
    ifstream idCliente;
    string texto, cliente, dato, nombre, ciudad, direccion, telefono, idStr;
    int i=0, edad, datoInt, idInt;
    char band;

    idCliente.open("idClientes", ios::in);

    while(!idCliente.eof()){
        getline(idCliente, idStr);
        idInt = stoi(idStr);
        
        if(idInt != 0){

            int j=0;

            cliente = "Cliente " + to_string(idInt);

            ifstream archivos;

            archivos.open(cliente.c_str(), ios::in);

            while (!archivos.eof()){
                getline(archivos, texto);
                for(int i=0; i<texto.length(); i++){
                    if(texto[i] == ':'){
                        dato = texto.substr(i+2,(i-texto.length()));
                        switch (j){
                            case 0:
                                nombre = dato;
                                break;
                            
                            case 1:
                                ciudad = dato;
                                break;

                            case 2:
                                direccion = dato;
                                break;

                            case 3:
                                datoInt = stoi(dato);
                                edad = datoInt;
                                break;

                            case 4:
                                telefono = dato;
                                break;
                            }
                        j++;
                        break;
                    }
                }
            }
            
            clientes[idInt] = new Cliente();
            clientes[idInt]->setNuevoCliente(idInt, nombre, ciudad, direccion, edad, telefono, 0);
        }

    }

    // Id importante a lo largo del codigo para manejar busqueda de clientes

    idClienteMax = idInt;
}

// Impresion y eleccion de opciones de los clientes

int procedimientoClientes(){
    int opcion;

    system("cls");
    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl;
    cout<<"\nCLIENTES"<<endl<<endl
        <<"1. Registro"<<endl
        <<"2. Consulta"<<endl
        <<"3. Regresar menu principal"<<endl<<endl
        <<"Ingrese Opcion: ";
        cin>>opcion;

    return opcion;
}

// Ingreso y registro de un nuevo cliente

void ingresarCliente(){
    system("cls");

    ofstream archivo;

    int id, edad;
    string nombre, ciudad, direccion, telefono;
    char band;

    id = idClientes();

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
        <<"\nREGISTRO DE CLIENTE"<<endl<<endl;

    fflush(stdin);
    cout<<"Nombre:           \t"; getline(cin, nombre);
    cout<<"Ciudad:           \t"; getline(cin, ciudad);
    cout<<"Direccion:        \t"; getline(cin, direccion);
    cout<<"Edad:             \t"; cin>>edad;
    fflush(stdin);
    cout<<"Telefono:         \t"; getline(cin, telefono);

    cout<<"\nConfirmar Registro del cliente : Si (s) / No (n): ";
    cin>>band;

    // Registro del cliente en los archivos

    if(band == 's' || band == 'S'){
        string cliente = "Cliente " + to_string(id);
        archivo.open(cliente.c_str(), ios::out);
        archivo<<"Nombre: "<<nombre<<endl
            <<"Ciudad: "<<ciudad<<endl
            <<"Direccion: "<<direccion<<endl
            <<"Edad: "<<edad<<endl
            <<"Telefono: "<<telefono<<endl;

        clientes[id] = new Cliente();
        clientes[id]->setNuevoCliente(id, nombre, ciudad, direccion, edad, telefono, 1);
        continuar();
    }
}

// Impresion del cliente ingresado mediante la lectura de su archivo

void imprimirCliente(){
    system("cls");
    ifstream archivo;
    string texto;
    char band;

    string nombreBusqueda, id;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nCONSULTA DE CLIENTES"<<endl<<endl;

    cout<<"Ingrese nombre del cliente: ";
    fflush(stdin);
    getline(cin, nombreBusqueda);

    for(int i=1; i<=idClienteMax; i++){
        if(clientes[i]->busquedaCliente(nombreBusqueda)){
            archivo.open("Cliente " + to_string(i), ios::in);
            band = 'v';
            break;
        }
    }

    // Apertura del archivo propio del cliente

    while(!archivo.eof()){
        getline(archivo, texto);
        cout<<texto<<endl;
    }

    if(band != 'v'){
        cout<<"\nEl nombre ingresado no pertenece a un cliente registrado"<<endl;
    }

    continuar();
}

// Registro de las cuentas guardadas en los archivos en el vector global 'Cuentas'

void cuentasGuardadas(){
    ifstream idCuentas;
    string tipoCuenta, cuenta, dato, texto, idStr;
    int idCuenta=0, idCliente, nip, datoInt, aux, idInt;

    char band;

    idCuentas.open("idCuentas", ios::in);

    while(!idCuentas.eof()){
        long long saldo=0, deuda=0;
        getline(idCuentas, idStr);
        idInt = stoi(idStr);

        if(idInt != 0){

            int j=0;

            cuenta = "Cuenta " + idStr;

            ifstream archivos;

            archivos.open(cuenta.c_str(), ios::in);

            while (!archivos.eof()){
                getline(archivos, texto);
                for(int i=0; i<texto.length(); i++){
                    if(texto[i] == ':'){
                        dato = texto.substr(i+2,(i-texto.length()));
                        switch (j){

                            case 0:
                                datoInt = stoi(dato);
                                idCliente = datoInt;
                                break;

                            case 1:
                                datoInt = stoi(dato);
                                idCuenta = datoInt;

                                break;

                            case 2:
                                datoInt = stoi(dato);
                                nip = datoInt;
                                break;

                            case 3:
                                tipoCuenta = dato;
                                break;

                            case 4:
                                datoInt = stoi(dato);
                                saldo += datoInt;
                                break;

                            case 5:
                                datoInt = stoi(dato);
                                deuda += datoInt;
                                break;
                        }

                        j++;

                    }
                }
            }
            
            cuentas[idCuenta] = new Cuenta();
            cuentas[idCuenta]->setNuevaCuenta(idCuenta, idCliente, nip, tipoCuenta, saldo, deuda, 0);
        }


    }

    // Id Importante a lo largo del codigo para manejar una optima busqueda de cuentas

    idCuentaMax = idInt;
}

// Impresion y eleccion de opciones de las cuentas

int procedimientoCuentas(){
    system("cls");
    int opcion;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl;
    cout<<"\nCuentas"<<endl<<endl
        <<"1. Registro"<<endl
        <<"2. Consulta"<<endl
        <<"3. Regresar menu principal"<<endl<<endl
        <<"Ingrese Opcion: ";
        cin>>opcion;

    return opcion;
}

// Funcion de confirmacion de existencia del cliente que desea abrir una cuenta

void ingresarCuenta(){
    system("cls");
    int idBusqueda;
    bool band = false;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
        <<"\nCuentas"<<endl<<endl;

    cout<<"Ingrese el id de un cliente registrado: ";
    cin>>idBusqueda;


    for (int i = 1; i <= idClienteMax; i++){
        if(clientes[i]->setConfirmarCliente(idBusqueda)){ // Confirmacion de existencia de cliente
            registrarCuenta(i); // Se dirige a registrar la cuenta
            band = true;
            break;
        }
    }
    

    if(not band){
        cout<<"No se ha encontrado una cuenta con el id registrado \n";
    }

    continuar();
}

// Creacion de cuenta de cliente con existencia confirmada

void registrarCuenta(int idCliente){
    int nip, idCuenta;
    string tipoCuenta, nombre, ciudad, telefono;
    long long saldo, deuda=0;
    
    ofstream archivo;
    ofstream archivoEstado;

    char band;

    idCuenta = idCuentas();

    do{
        cout<<"\nNIP: ";cin>>nip;
        if(nip < 1000 || nip > 9999){
            cout<<"*El nip debe ser de 4 caractetes\n";
            }
        }while(nip < 1000 || nip > 9999);
    
    fflush(stdin);
    do
    {
        cout<<"Tipo de Cuenta (Debito/Credito): "; getline(cin, tipoCuenta);
        if(tipoCuenta != "Credito" && tipoCuenta != "Debito"){
            cout<<"Tipo de cuenta invalido\n\n";
        }
    } while (tipoCuenta != "Credito" && tipoCuenta != "Debito");
    
    do
    {
        cout<<"Saldo Inicial: $"; cin>>saldo;
        if(tipoCuenta == "Credito" && saldo > 5000000){
            cout<<"Las cuentas de credito no pueden tener saldo mayor a cinco millones\n\n";
        }
    }while(tipoCuenta == "Credito" && saldo > 5000000);

    cout<<"\nConfirmar Registro de Cuenta : Si (s) / No (n): ";
    cin>>band;

    // Registro de cuentas en sus respectivos archivos

    if(band == 's' || band == 'S'){
        
        string cuenta = "Cuenta " + to_string(idCuenta);
        archivo.open(cuenta.c_str(), ios::out);
        archivo<<"id de Cliente: "<<idCliente<<endl
           <<"id de Cuenta: "<<idCuenta<<endl
           <<"Nip: "<<nip<<endl
           <<"Tipo de Cuenta: "<<tipoCuenta<<endl
           <<"Saldo: "<<saldo<<endl;

        cuentas[idCuenta] = new Cuenta();
        cuentas[idCuenta]->setNuevaCuenta(idCuenta, idCliente, nip, tipoCuenta, saldo, deuda, 1);
    }

    string estadoCuenta = "estadoCuenta " + to_string(idCuenta);
    archivoEstado.open(estadoCuenta.c_str(), ios::out);

    nombre = clientes[idCliente]->getNombre();
    ciudad = clientes[idCliente]->getCiudad();
    telefono = clientes[idCliente]->getTelefono();
    
    archivoEstado<<" Id Cliente:          "<<idCliente<<endl
                <<" Nombre:              "<<nombre<<endl
                <<" Ciudad:              "<<ciudad<<endl
                <<" Telefono:            "<<telefono<<endl
                <<" Id Cuenta:           "<<idCuenta<<endl
                <<" Saldo:               $"<<saldo<<endl;

    if(tipoCuenta == "Credito"){
        archivo<<"Deuda: "<<deuda<<endl;
        archivoEstado<<" Deuda:               $"<<deuda<<endl;
       }

    archivoEstado<<"\n Mov Fecha \t\t\t Tipo Movimiento \t\t\t Valor "<<endl;


}

// Impresion de la cuenta ingresada mediante la lectura de su archivo

void imprimirCuenta(){
    system("cls");
    int idBusqueda, nip, aux;
    bool band;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
        <<"\nCONSULTA DE CUENTAS"<<endl<<endl;

    cout<<"Ingrese el id de una cuenta registada: ";
    cin>>idBusqueda;
    fflush(stdin);
    cout<<"Digite el nip de la cuenta: ";
    cin>>nip;

    for (int i = 1; i <= idCuentaMax; i++){
        if(cuentas[i]->buscarCuenta(idBusqueda,nip)){
            cuentas[i]->imprimirDatos();
            band = true;
            break;
        }
    }
    
    if(not band){
        cout<<"El id y el nip no coinciden con una cuenta registrada"<<endl;
    }

    continuar();
}

// Impresion y eleccion de opciones de las cuentas

int depositoRetiro(){
    int opcion;

    system("cls");
    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nDEPOSITO / RETIRO"<<endl<<endl;
            
    cout<<"1. Deposito"<<endl
        <<"2. Retiro"<<endl
        <<"3. Regresar Menu Principal"<<endl<<endl
        <<"Ingrese Opcion: ";
        cin>>opcion;

    return opcion;
}

// Funcion empleada para ingresar y determinar existencia de la cuenta

void depositarSaldo(){
    system("cls");
    int idBusqueda, nip;
    long long cantidadDeposito;
    string fecha = tiempoActual();
    bool band;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nDEPOSITO"<<endl<<endl;

    cout<<"Ingrese ID de la cuenta: ";
    cin>>idBusqueda;
    fflush(stdin);
    cout<<"Ingrese el nip de la cuenta: ";
    cin>>nip;

    // Busqueda de existencia de la cuenta

    for (int i = 1; i <= idCuentaMax; i++)
    {
        if(cuentas[i]->buscarCuenta(idBusqueda, nip)){
            cout<<"Ingrese la cantidad a depositar: ";
            cin>>cantidadDeposito;
            cuentas[i]->deposito(cantidadDeposito, fecha); // Invocacion de la funcion para agregar saldo a la cuenta
            band = true;
            break;
        }
    }
    
    if(not band){
        cout<<"El id y el nip no coinciden a una cuenta registrada"<<endl;
    }
    
    continuar();
}

// Funcion empleada para ingresar y determinar existencia de la cuenta

void retirarSaldo(){
    system("cls");
    int idBusqueda, nip;
    long long cantidadRetiro;
    string fecha = tiempoActual();
    bool band;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nRETIRO"<<endl<<endl;

    cout<<"Ingrese ID de la cuenta: ";
    cin>>idBusqueda;
    fflush(stdin);
    cout<<"Ingrese el nip de la cuenta: ";
    cin>>nip;

    // Busqueda existencia de la cuenta

    for(int i=1; i<=idCuentaMax; i++){
        if(cuentas[i]->buscarCuenta(idBusqueda, nip)){
            cout<<"Ingrese la cantidad a retirar: ";
            cin>>cantidadRetiro;
            cuentas[i]->retiro(cantidadRetiro, fecha); // Invocacion de la cuenta para realizar el retiro
            band = true;
            break;
        }
    }
    
    if(not band){
        cout<<"El id o el nip no coinciden al de una cuenta registrada"<<endl;
    }
    
    continuar();
}

// Funcion exclusiva para las cuentas credito, en el pago de monto especifico de la deuda

void pago(){
    system("cls");
    int idBusqueda, nip;
    long long cantidadPagar=0;
    string fecha = tiempoActual();
    bool band;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nPagos"<<endl<<endl;

    cout<<"Ingrese ID de la cuenta: ";
    cin>>idBusqueda;
    fflush(stdin);
    cout<<"Ingrese el nip de la cuenta: ";
    cin>>nip;

    // Busqueda de existencia de la cuenta

    for(int i=1; i<=idCuentaMax; i++){
        if(cuentas[i]->buscarCuenta(idBusqueda, nip)){
            if(cuentas[i]->pagar(cantidadPagar, fecha)){
                cout<<"Ingrese la cantidad a pagar: ";
                cin>>cantidadPagar; // Cantidad ingresada a parte del saldo
                cuentas[i]->pagar(cantidadPagar, fecha); // invocacion de Funcion para realizar pago
            }
            band = true;
            break;
        }
    }
    
    if(not band){
        cout<<"El id o el nip no coinciden al de una cuenta registrada"<<endl;
    }
    
    continuar();
}

// Funcion empleada para ingresar y determinar existencia de las cuentas involucradas en la transaccion

void transferencia(){
    system("cls");
    int idOrigen, idDestino, i=0, nipOrigen, nipDestino;
    long long envio=0;
    string fecha = tiempoActual();
    bool band;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nTRANSFERENCIA"<<endl;

        do{
            cout<<"\nIngrese ID de cuenta de origen: ";
            cin>>idOrigen;
            cout<<"NIP de cuenta de origen: ";
            cin>>nipOrigen;

            cout<<"Ingrese ID de cuenta de destino: ";
            cin>>idDestino;
            cout<<"NIP de cuenta de destino: ";
            cin>>nipDestino;
            
            // Busqueda de existencia de la cuenta

            for (int k = 1; k <= idCuentaMax; k++){
                if(cuentas[k]->buscarCuenta(idOrigen,nipOrigen)){
                    i++;
                }
                if(cuentas[k]->buscarCuenta(idDestino, nipDestino)){
                    i++;
                }
            }      
                if(i==2){
                    if(cuentas[idDestino]->transferenciaDestino(envio, fecha)){
                        cout<<"Ingrese la cantidad de que desea transferir: ";
                        cin>>envio;
                        envio = cuentas[idOrigen]->transferenciaOrigen(envio, fecha); // Invocacion de la cuenta para retirar saldo de la cuenta de origen
                        cuentas[idDestino]->transferenciaDestino(envio, fecha); // Invocacion de la cuenta para consignar saldo a la cuenta destino
                        cout<<"\nLa transferencia ha sido exitosa";
                        band = true;
                    }
                    
                }else{
                    cout<<"\n"<<i<<"\n";
                    cout<<"\nLos datos ingresados no coinciden con cuentas registradas"<<endl;
                    cout<<"Desea ingresar nuevos datos? SI (s) / NO (n): ";
                    cin>>band;
                    i=0;
                }

        }while(not band);

    continuar();
}

// Funcion informativa para el usuario del monto del interes respecto a su porcentaje

void inversion(){
    system("cls");
    float capital, tasaInteres, interes;
    int meses;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nInformacion de Inversion"<<endl<<endl;

    cout<<"Ingrese el capital a invertir:             $"; cin>>capital;
    cout<<"Ingrese los meses a los que se dispondra:  "; cin>>meses;
    cout<<"Ingrese la tasa de interes:                "; cin>>tasaInteres;
    interes = (capital * meses) * (tasaInteres /100);
    cout<<"Intereses obtenidos:                       $"<<interes;

    continuar();
}

// Funcion de determinacion de la existencia de la cuenta

void estadoCuenta(){
    system("cls");
    bool band;
    int idBusqueda, nipBusqueda, nip;

    cout<<"\n\t\t\t\tSISTEMA BANCARIO"<<endl
            <<"\nESTADO DE CUENTA"<<endl<<endl;

    cout<<"Ingrese el ID de la cuenta: ";
    cin>>idBusqueda;
    fflush(stdin);
    cout<<"Ingrese el nip de la cuenta: ";
    cin>>nip;

    // Busqueda de existencia de la cuenta

    for(int i=1; i<=idCuentaMax; i++){
        if(cuentas[i]->buscarCuenta(idBusqueda, nip)){
            cuentas[i]->estadoCuenta(); // Invocacion de la funcion de impresion del archivo de su estado 
            band = true;
            break;
        }
    }
    
    if(not band){
        cout<<"El id o el nip no coinciden al de una cuenta registrada"<<endl;
    }
    
    continuar();
}

// Funcion empleada para determinar la fecha de los diferentes movimientos realizados

string tiempoActual(){

    int dia, mes, anio;
    string diaStr, mesStr, anioStr;

    string fecha;

    time_t now;

    time(&now);

    struct tm *local = localtime(&now);

    dia = local->tm_mday;
    diaStr = to_string(dia);
    anio = local->tm_year;
    anioStr = to_string(anio);
    mes = local->tm_mon;
    mesStr = to_string(mes) + anioStr.substr(0, 1);
    anioStr = anioStr.substr(1, anioStr.length());

    fecha = diaStr + '/' + mesStr + '/' + anioStr;
    

    return fecha;
}