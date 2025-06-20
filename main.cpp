// CPP 
#include <iostream> // Libreria estandar
#include <string.h> // libreria para trabajar con strings de c++
#include <windows.h> // libreria de funciones de Windows
#include <list> // libreria para trabajar con listas enlazadas de c++
#include <unordered_map> // importa la estructura de datos unordered_map
#include <fileapi.h> // proporciona funciones para trabajar con archivos
// #include <sys


// Mis archivos
// #include "encabezados/functions.h"
// #include "encabezados/structs.h"
#include "encabezados/db.h" // es el archivo de encabezado donde se creo la simulacion de una base de datos con una clase

using namespace std;

int main() {
    system("COLOR 30");
    changeFont(20, 20);

    cuadros_principales();

    Db db = Db(); // Crear una instancia de Db
    db.llenar_empleados(); // llenamos las respectivas estructuras de datos con valores de archivos
    db.llenar_helados();
    int opcion_principal;
    
    do {
        db.carrito.vaciar_carrito(); // siempre que se cierre una sesion el carrito de compras se vacia
        db.usuario_registrado_ci="";
        db.usuario_registrado="";
        cuadros_principales();
        arte("");
        pagina_de_inicio(); cin >> opcion_principal;
        system("cls");

        switch (opcion_principal) {
            case 1: {
                // Opcion para iniciar sesion
                string ci; 
                string contrasenia;
                cuadros_principales();
                arte(db.usuario_registrado);
                fflush(stdin);
                getline(cin, ci);
                gotoxy(46,10); cout << "CI: "; getline(cin, ci); cout << '\n';
                gotoxy(46,11); cout << "Clave: "; getline(cin, contrasenia); cout << '\n';

                // transformamos la clave en hash por seguridad
                size_t cont_hash = hash<string>{}(contrasenia);
                contrasenia = to_string(cont_hash);
                
                // verificamos si el usuario existe
                if (db.buscar_empleado(ci, contrasenia)) {
                    // le pedimos la tasa de bolivares a dolares para cuando mostremos los productos del carrito
                    gotoxy(46,13); cout << "Tasa estandar del dia: "; cin >> tasa_estandar;
                    system("cls");
                    auto em =  db.extraer_empleado(ci);
                    db.usuario_registrado = em["nombre"] + " " + em["apellido"] + " " + ci + " " + em["superusuario"];
                    db.usuario_registrado_ci = ci;
                    unordered_map<string, string> empleado = db.extraer_empleado(ci);
                    int opcion_inicio;

                    do{
                        fflush(stdin);

                        cuadros_principales();
                        arte(db.usuario_registrado);
                        inicio(stoi(empleado["superusuario"])); cin >> opcion_inicio;
                        system("cls");
                        
                        cuadros_principales();
                        arte(db.usuario_registrado);
                        // si el usuario es superusuario tendra opciones adicionales
                        if (stoi(empleado["superusuario"])){
                            switch (opcion_inicio) {
                                case 1:{
                                    // agregar helados al carrito
                                    int opcion_helado;
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        db.mostrar_helados(); cin >> opcion_helado;
                                        if (db.buscar_helado(opcion_helado)) {
                                            db.agregar_helado_carrito(opcion_helado);
                                        }
                                        system("cls");
                                    }while(opcion_helado!=0);
                                    
                                    break;
                                } // mostrar los helados reservados
                                case 2:{
                                    db.carrito.mostrar_helados();
                                    break;
                                } // eliminar pedidos no deseados
                                case 3:{
                                    int opcion_helado_e, cont_gotoxy;
                                    if(db.carrito.get_helados().empty()) {
                                        gotoxy(42, 10); cout << "El carrito esta vacio";
                                        gotoxy(42, 12); system("pause");
                                        break;
                                    }
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        if(db.carrito.get_helados().empty()) {
                                            // cout <<"si";
                                            gotoxy(42, 10); cout << "El carrito esta vacio";
                                            gotoxy(42, 12); system("pause");
                                            break;
                                        }
                                        cont_gotoxy = db.carrito.imprimir_helados(); 
                                        // cout << cont_gotoxy;
                                        gotoxy(46, 19); cout << "0. Volver";
                                        gotoxy(46, 21); cout << "Opcion: ";
                                        cin >> opcion_helado_e;
                                        db.carrito.eliminar_pedido(opcion_helado_e);
                                        system("cls");
                                    }while(opcion_helado_e!=0);
                                    break;
                                }// Opcion de pago
                                case 4:{
                                    int opcion_helado_e, cont_gotoxy;
                                    if(db.carrito.get_helados().empty()) {
                                        gotoxy(42, 10); cout << "El carrito esta vacio";
                                        gotoxy(42, 12); system("pause");
                                        break;
                                    }
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        if(db.carrito.get_helados().empty()) {
                                            // cout <<"si";
                                            gotoxy(42, 10); cout << "El carrito esta vacio";
                                            gotoxy(42, 12); system("pause");
                                            break;
                                        }
                                        cont_gotoxy = db.carrito.imprimir_helados(); 
                                        // cout << cont_gotoxy;
                                        gotoxy(46, 19); cout << "0. Volver";
                                        gotoxy(46, 20); cout << "Opcion: ";
                                        cin >> opcion_helado_e;
                                        if (opcion_helado_e == 0) break;
                                        int cantidad;
                                        gotoxy(46, 21); cout << "digite la cantidad que desea eliminar: "; cin >> cantidad;
                                        db.carrito.eliminar_cantidad(opcion_helado_e, cantidad);
                                        system("cls");
                                    }while(opcion_helado_e!=0);
                                    break;
                                }
                                case 5:{
                                    if (!db.carrito.get_helados().empty()) {
                                        int cont_gotoxy = db.carrito.imprimir_helados();
                                        int opcion_pagar;
                                        
                                        gotoxy(45, 19); cout << "1. Proceder al pago"; 
                                        gotoxy(70, 19); cout << "0. Volver";
                                        gotoxy(47, 21); cout << "Opcion: ";
                                        cin >> opcion_pagar;
                                        
                                        if (opcion_pagar == 1) {
                                            system("cls");
                                            cuadros_principales();
                                            arte(db.usuario_registrado);
                                            db.pagar();
                                        } 
                                    } else {
                                        gotoxy(42,10); cout << "El carrito esta vacio";
                                        gotoxy(42,12);system("pause");
                                    }
                                    break;
                                }
                                case 6:{ // Opcion para agregar un nuevo empleado en caso de que seas superusuario
                                    unordered_map<string, string> empleado; empleado["nombre"];
                                    fflush(stdin);
                                    getline(cin, empleado["nombre"]); 
                                    gotoxy(50,10); cout << "Nombre: " ; getline(cin, empleado["nombre"]); 
                                    fflush(stdin);
                                    gotoxy(50,11); cout << "Apellido: " ; getline(cin, empleado["apellido"]); 
                                    fflush(stdin);
                                    gotoxy(50,12); cout << "CI: " ; getline(cin, empleado["ci"]); 
                                    if (empleado["ci"].size() > 8 || empleado["ci"].size() < 7) {
                                        gotoxy(50,14); cout << "Por favor digite una cedula correcta";
                                        gotoxy(50,15); system("pause");
                                        break;
                                    }
                                    if (!es_digito_puro(empleado["ci"])) {
                                        gotoxy(50,14); cout << "Por favor digite una cedula correcta";
                                        gotoxy(50,15); system("pause");
                                        break;
                                    }
                                    gotoxy(50,13); cout << "Clave: " ; getline(cin, empleado["contrasenia"]);
                                    gotoxy(50,14); cout << "Superusuario s/n: " ; getline(cin, empleado["superusuario"]);
                                    fflush(stdin);
                                    if (empleado["superusuario"] == "S" || empleado["superusuario"] == "s" ) {
                                        empleado["superusuario"] = "1";
                                    } else { empleado["superusuario"] = "0"; }

                                    empleado["contrasenia"] = to_string(hash<string>{}(empleado["contrasenia"]));

                                    db.agregar_empleados(empleado);
                                    gotoxy(50,15); cout << "Usuario agregado con exito"; 
                                    gotoxy(50,17); system("pause");
                                    break;
                                }
                                case 7:{// lista con todos los empleados para poder eliminarlos por numero
                                    int opcion_empleado_e;
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        db.mostrar_empleados(); cin >> opcion_empleado_e;
                                        db.eliminar_empleado(opcion_empleado_e);
                                        system("cls");
                                    }while(opcion_empleado_e!=0);
                                    system("cls");
                                    break;
                                }
                                case 8:{// Acerca de la empresa
                                    system("cls");
                                    
                                    cuadros_principales();
                                    gotoxy(8,23); cout << db.usuario_registrado;
                                    db.acerca_de();
                                }
                                default:{
                                    break;
                                }
                            }
                        } else {// Esto se ejecutaria si el usuario no es el superusuario y tiene todas las misma opciones que arriba pero sin la opcion
                            switch (opcion_inicio) { // de edicion de empleados
                                case 1:{
                                    
                                    int opcion_helado;
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        db.mostrar_helados(); cin >> opcion_helado;
                                        if (db.buscar_helado(opcion_helado)) {
                                            db.agregar_helado_carrito(opcion_helado);
                                            system("cls");
                                        }
                                    }while(opcion_helado!=0);
                                    
                                    break;
                                }
                                case 2:{
                                    db.carrito.mostrar_helados();
                                    break;
                                }
                                case 3:{
                                    int opcion_helado_e, cont_gotoxy;
                                    if(db.carrito.get_helados().empty()) {
                                        gotoxy(42, 10); cout << "El carrito esta vacio";
                                        gotoxy(42, 12); system("pause");
                                        break;
                                    }
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        if(db.carrito.get_helados().empty()) {
                                            // cout <<"si";
                                            gotoxy(42, 10); cout << "El carrito esta vacio";
                                            gotoxy(42, 12); system("pause");
                                            break;
                                        }
                                        cont_gotoxy = db.carrito.imprimir_helados(); 
                                        // cout << cont_gotoxy;
                                        gotoxy(46, 19); cout << "0. Volver";
                                        gotoxy(46, 21); cout << "Opcion: ";
                                        cin >> opcion_helado_e;
                                        db.carrito.eliminar_pedido(opcion_helado_e);
                                        system("cls");
                                    }while(opcion_helado_e!=0);
                                    break;
                                }
                                case 4:{
                                    int opcion_helado_e, cont_gotoxy;
                                    if(db.carrito.get_helados().empty()) {
                                        gotoxy(42, 10); cout << "El carrito esta vacio";
                                        gotoxy(42, 12); system("pause");
                                        break;
                                    }
                                    do{
                                        cuadros_principales();
                                        arte(db.usuario_registrado);
                                        if(db.carrito.get_helados().empty()) {
                                            // cout <<"si";
                                            gotoxy(42, 10); cout << "El carrito esta vacio";
                                            gotoxy(42, 12); system("pause");
                                            break;
                                        }
                                        cont_gotoxy = db.carrito.imprimir_helados(); 
                                        // cout << cont_gotoxy;
                                        gotoxy(46, 19); cout << "0. Volver";
                                        gotoxy(46, 20); cout << "Opcion: ";
                                        cin >> opcion_helado_e;
                                        if (opcion_helado_e == 0) break;
                                        int cantidad;
                                        gotoxy(46, 21); cout << "digite la cantidad que desea eliminar: "; cin >> cantidad;
                                        db.carrito.eliminar_cantidad(opcion_helado_e, cantidad);
                                        system("cls");
                                    }while(opcion_helado_e!=0);
                                    break;
                                    
                                }
                                case 5: {
                                    if (!db.carrito.get_helados().empty()) {
                                        int cont_gotoxy = db.carrito.imprimir_helados();
                                        int opcion_pagar;

                                        gotoxy(45, 19); cout << "1. Proceder al pago"; 
                                        gotoxy(70, 19); cout << "0. Volver";
                                        gotoxy(47, 21); cout << "Opcion: ";
                                        cin >> opcion_pagar;
                                        
                                        if (opcion_pagar == 1) {
                                            system("cls");
                                            cuadros_principales();
                                            arte(db.usuario_registrado);
                                            db.pagar();
                                        } 
                                    } else {
                                        gotoxy(42,10); cout << "El carrito esta vacio";
                                        gotoxy(42,12);system("pause");
                                    }
                                    break;
                                }
                                case 6: {
                                    system("cls");
                                    
                                    cuadros_principales();
                                    gotoxy(8,23); cout << db.usuario_registrado;
                                    db.acerca_de();
                                    break;
                                }
                                default:{
                                    break;
                                }
                            }
                        }
                            
                        system("cls");
                    }while(opcion_inicio != 0);

                } else {
                    gotoxy(45,13);cout << "Usuario o contrasenia incorrectos";
                    system("pause>nul");
                }

                break;
            }
            case 2:
                break;
            default:
                break;
        }

        system("cls");
    } while(opcion_principal != 2);
    
    system("pause>nul");
    return 0;
}