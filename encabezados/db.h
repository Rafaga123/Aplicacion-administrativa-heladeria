// Librerias CPP
#include <iostream>
#include <string>
#include <functional>
#include <list>
#include <windows.h>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <fstream>

// Mis archivos
#include "functions.h"

using namespace std;

const float iva = 0.16;
float tasa;
float tasa_estandar;

class Carrito{
    // Esta clase tiene todo lo necesario para trabajar con un carrito de compras
    list<unordered_map<string, string>> helados;// helados en el carrito
    // int limite=0;
public:
    // Mostrar
    int imprimir_helados() { // imprimir los helados ordenadamente por pantalla
        int contador = 1, cont_gotoxy = 5;
        for (auto helado : this->helados) {
            gotoxy(43, cont_gotoxy);
            if (contador < 10) cout << 0;
            cout << contador << " " << helado["sabor"] << helado["distancia"] << " " << stof(helado["precio"]) / 100 << " $ x" << helado["cantidad"];
            contador++;
            cont_gotoxy++;
        }
        return cont_gotoxy;
    }
    void mostrar_helados() { // Mostrar los helados del carrito

        if (this->helados.empty()) {
            gotoxy(42, 10); cout << "El carrito esta vacio";
            gotoxy(42, 12); system("pause");
            return;
        }

        int cont_gotoxy = this->imprimir_helados();

        fflush(stdin);

        gotoxy(38, 20); cout << "Total en dolares: " << "$" << this->obtener_precio() ;
        gotoxy(67, 20); cout << "Total en Bs: " << this->obtener_precio() * tasa_estandar ;
        gotoxy(45, 22); system("pause");
    }

    // Agregar
    void agregar_helado(unordered_map<string, string> helado) { // Agregar un helado al carrito
        // if (helados.size() < 13) {
        //     this->helados.push_front(helado);
        //     gotoxy(46,23);cout << "Helado agregado al carrito";
        // } else {
        //     gotoxy(46,23);cout << "Numero maximo de helados alcanzado";
        // }

        if (this->existe_helado(helado["sabor"])) {
            unordered_map<string, string> helado_extraido;
            for (unordered_map<string, string>& helado_c : this->helados) {
                if (helado["sabor"] == helado_c["sabor"]) { helado_c["cantidad"] = to_string(stoi(helado_c["cantidad"]) + 1);}
            }

        } else {
            helado["cantidad"] = "1";
            this->helados.push_front(helado);
        }
        gotoxy(46,23);cout << "Helado agregado al carrito";
        system("pause>nul");
    }
    unordered_map<string, string> pagar() { // Pide todos los datos necesarios y los valida para que se ejecute un pago correctamente
        tm *fecha = obtener_fecha();
        unordered_map<string, string> res;
        gotoxy(46, 9); cout << "Nombre del cliente: "; cin >> res["Cliente"];
        string a;
        gotoxy(46, 10); cout << "Apellido del cliente: "; cin >> a;
        res["Cliente"] += " "+a;
        gotoxy(46, 11); cout << "CI: "; cin >> res["Ci"];
        if (res["Ci"].size() > 8 || res["Ci"].size() < 7) {
            gotoxy(46, 12); cout << "Por favor digite una cedula correcta";
            gotoxy(46, 13); system("pause");
            return {{"no","no"}};
        }
        gotoxy(46, 12); cout << "Numero de Referencia: "; cin >> res["Referencia"];
        if (res["Referencia"].size() != 4 || !es_digito_puro(res["Referencia"])) {
            gotoxy(46, 13); cout << "Por favor, digite un numero de referencia valido...\n\n";
            gotoxy(46, 14); system("pause");
            return {{"no","no"}};
        }
        gotoxy(46, 13); cout << "Numero de telefono: "; cin >> res["Telefono"];
        if (res["Telefono"].size() != 11 || !es_digito_puro(res["Telefono"])) {
            gotoxy(46, 14); cout << "Por favor, digite un numero de telefono valido...\n\n";
            gotoxy(46, 15); system("pause");
            return {{"no","no"}};
        }
        gotoxy(46, 14);cout << "Banco: "; cin >> res["Banco"];
        gotoxy(46, 15);cout << "Divisa (bol\xA1vares/1 y d\xA2lares/0): "; cin >> res["Divisa"];
        if (res["Divisa"] == "1") {
            res["Divisa"] = "bol\xA1var";
        } else {
            res["Divisa"] = "d\xA2lar";
        }
        res["Fecha"] = to_string(fecha->tm_mday) + "/" + to_string(fecha->tm_mon+1) + "/2024" + " a las " + to_string(fecha->tm_hour) + ":" + to_string(fecha->tm_min) + ":" + to_string(fecha->tm_sec);
        
        res["Monto"] = to_string(this->obtener_precio());

        if (res["Divisa"] == "bol\xA1var"){
            gotoxy(46, 16);cout << "Digite la tasa de hoy: "; cin >> tasa;
            res["Monto"] = to_string(tasa*stof(res["Monto"]));
            res["IVA"] = to_string(stof(res["Monto"])*0.16);
            res["Monto + IVA"] = to_string(stof(res["Monto"]) + stof(res["IVA"]));
        } else {
            res["IVA"] = to_string(stof(res["Monto"])*0.03);;
            res["Monto + IVA"] = to_string(stof(res["Monto"]) + stof(res["IVA"]));
        }

        res["Sabores vendidos"] = to_string(this->helados.size());
        fflush(stdin);
        return res;
    }

    // Eliminar
    void eliminar_pedido(int id) { // elimina un pedido enumerado del carrito
        if (id > this->helados.size() || id <= 0) return;
        list<unordered_map<string, string>> nueva_lista;
 
        int i = 1;
        for (auto& pedido : this->helados) {
            if (i != id) {
                nueva_lista.push_back(pedido);
            }
            i++;
        }
        // if (helados.size() == 1) this->helados.clear();
        this->helados = nueva_lista;
        gotoxy(46, 23); cout << "Pedido eliminado, presiona cualquier tecla"; system("pause>nul");
    }
    void eliminar_cantidad (int id, int cantidad) {
        int i = 1;
        for (auto& pedido : this->helados) {
            if (i == id) {
                cantidad = stoi(pedido["cantidad"]) - cantidad;
                if (cantidad <= 0) {
                    this->eliminar_pedido(id);
                    return;
                } else {
                    pedido["cantidad"] = to_string(cantidad);
                }
                gotoxy(46, 23); cout << "Cantidad eliminada, presiona cualquier tecla"; system("pause>nul");
                return;
            }
            i++;
        }
    }

    // Obtener
    float obtener_precio() { // obtiene el precio total de todos los productos en el carrito
        float precio_total = 0;

        fflush(stdin);
        for (auto helado : this->helados) {
            precio_total += stof(helado["precio"]) * stoi(helado["cantidad"]);
        }

        return precio_total / 100;
    }
    list<unordered_map<string, string>> get_helados() {
        return this->helados;
    }
    unordered_map<string, string> get_helado(string sabor) {
        for (unordered_map<string, string>& helado : this->helados) {
            if (sabor == helado["sabor"]) return helado;
        }
        return {{"no", "no"}};
    }
    bool existe_helado(string sabor) {
        for (unordered_map<string, string>& helado : this->helados) {
            if (sabor == helado["sabor"]) return true;
        }
        return false;
    }

    // Vaciar
    void vaciar_carrito() {
        this->helados.clear();
    }
};

class Db {
    // todos los datos del sistema, desde los usuarios hasta los helados son procesados en esta clase que funciona como simulacion de base de datos
    list<unordered_map<string, string>> empleados; // empleados registrados
    list<unordered_map<string, string>> helados; 

    // Rutas de los archivos en diferentes tipos de strings dependiendo de lo que la funcion necesite
    string usuarios_file_s = "./datos/usuarios.txt", facturas_file_s = "./datos/facturas.txt";
    LPCSTR usuarios_lpcsrt = "./datos/usuarios.txt", facturas_lpcsrt = "./datos/facturas.txt";
    const char *usuarios_cc = "./datos/usuarios.txt", *facturas_cc = "./datos/facturas.txt";

    // un dato LPCSTR "Long Pointer to Constant STRing" y es un tipo de dato en C++ que se utiliza para representar una cadena de caracteres 
    // constante de 8 bits (ASCII) en sistemas Windows.

public:
    string usuario_registrado;
    string usuario_registrado_ci;
    Carrito carrito = Carrito();
    // Mostrar
    void acerca_de() { // Acerca de la empresa
        gotoxy(22, 4); cout << "El Sal\xA2n de los Helados es una tienda de helados innovadora fundada por \n";
        gotoxy(22, 5); cout << "tres estudiantes apasionados que combinan su amor por los helados con la \n";
        gotoxy(22, 6); cout << "infom\xA0tica para ofrecer una experiencia \xA3nica a sus clientes. \n";
        gotoxy(22, 7); cout << "Nos distinguimos por nuestros deliciosos sabores, elaborados \n";
        gotoxy(22, 8); cout << "con ingredientes frescos y de alta calidad utilizando m\x82todos artesanales, y \n";
        gotoxy(22, 9); cout << "por nuestra aplicaci\xA2n m\xA2vil que optimiza los pedidos y mejora la accesibilidad.\n";

        gotoxy(22, 11); cout << "Nuestra visi\xA2n es convertirnos en la tienda de helados n\xA3mero uno en innovaci\xA2n y calidad,\n";
        gotoxy(22, 12); cout << "expandi\x82ndonos a nivel nacional e internacional, y siendo un ejemplo de c\xA2mo una\n";
        gotoxy(22, 13); cout << "no muy grande empresa puede prosperar con pasi\xA2n por los productos artesanales.\n";

        gotoxy(22, 15); cout << "Objetivos: Ser reconocidos por la creatividad y calidad de nuestros helados,\n ";
        gotoxy(22, 16); cout << "implementar obras tecnol\xA2gicas para mejorar la experiencia del cliente y fomentar la \n";
        gotoxy(22, 17); cout << "sostenibilidad y la responsabilidad social.\n";

        gotoxy(22, 19); cout << "En El Sal\xA2n de los Helados, cada visita es especial y memorable\n";
        gotoxy(22, 20); cout << "gracias a la pasi\xA2n de nuestro equipo por crear una experiencia \xA3nica que combina\n";
        gotoxy(22, 21); cout << "tradici\xA2n e innovaci\xA2n.\n";

        gotoxy(40, 23); system("pause");
        
    }
    void mostrar_helados() { // Mostrar los helados disponibles en el sistema
        int contador = 1, cont_gotoxy = 7;

        fflush(stdin);

        for (auto helado : this->helados) {
            gotoxy(46, cont_gotoxy); 
            if (contador < 10) cout << 0;
            cout << contador << " " << helado["sabor"] << helado["distancia"] << " " << stof(helado["precio"]) / 100 << " $";
            contador++;
            cont_gotoxy++;
        }// cout << cont_gotoxy;
        gotoxy(46, 21); cout << "0. Volver ";
        gotoxy(46, 22); cout << "Opcion: ";
    }
    void mostrar_empleados() { // Mostrar los empleados registrados
        int contador = 1, cont_gotoxy = 7;

        fflush(stdin);

        for (unordered_map<string, string>& empleado : this->empleados) {
            gotoxy(43, cont_gotoxy); 
            if (contador < 10) cout << 0;
            cout << contador << ". " << empleado["nombre"] << " " << empleado["apellido"] << " " << empleado["ci"] << " " << empleado["superusuario"];
            contador++;
            cont_gotoxy++;
        }
        gotoxy(43, cont_gotoxy); cout << "0. Volver ";
        gotoxy(43, cont_gotoxy + 2); cout << "Opcion: ";
    }

    // Llenar
    void llenar_helados() { // Llena la lista de los helados
        this->helados.push_front(
            {{"sabor", "Fresa"},
             {"precio", "100"},
             {"distancia", " ------------------"}});
        this->helados.push_front(
            {{"sabor", "Pistacho"},
             {"precio", "550"},
             {"distancia", " ---------------"}});
        this->helados.push_front(
            {{"sabor", "Maracuya"},
             {"precio", "350"},
             {"distancia", " ---------------"}});
        this->helados.push_front(
            {{"sabor", "Avena y miel"},
             {"precio", "400"},
             {"distancia", " -----------"}});
        this->helados.push_front(
            {{"sabor", "Frambuesa"},
             {"precio", "200"},
             {"distancia", " --------------"}});
        this->helados.push_front(
            {{"sabor", "Dulce de leche"},
             {"precio", "300"},
             {"distancia", " ---------"}});
        this->helados.push_front(
            {{"sabor", "Stracciatella"},
             {"precio", "450"},
             {"distancia", " ----------"}});
        this->helados.push_front(
            {{"sabor", "Regaliz"},
             {"precio", "300"},
             {"distancia", " ----------------"}});
        this->helados.push_front(
            {{"sabor", "Chocolate blanco"},
             {"precio", "400"},
             {"distancia", " -------"}});
        this->helados.push_front(
            {{"sabor", "Mantecado"},
             {"precio", "300"},
             {"distancia", " --------------"}});
        this->helados.push_front(
            {{"sabor", "Chocolate"},
             {"precio", "400"},
             {"distancia", " --------------"}});
        this->helados.push_front(
            {{"sabor", "Torta suiza"},
             {"precio", "500"},
             {"distancia", " ------------"}});
        this->helados.push_front(
            {{"sabor", "Lluvia de chapas"},
             {"precio", "700"},
             {"distancia", " -------"}});
        // unordered_map<string, string> Mantecado,300,
        // hocolate,400,
        // orta suiza,500,
        // resa,200,
        // luvia de chapas,1000,
    }
    void llenar_empleados() { // Llena la lista de los empleados con la informacion del archivo usuarios.txt
        llenar(this->usuarios_lpcsrt, this->usuarios_cc, this->empleados, {"nombre", "apellido", "ci", "contrasenia", "superusuario"});
    }

    // Agregar
    void agregar_empleados(unordered_map<string, string> &empleado) { // Agrega un nuevo empleado al archivo y a la lista de empleados
        agregarConComas(this->usuarios_lpcsrt, this->usuarios_cc, this->usuarios_file_s, empleado, this->empleados, {"nombre", "apellido", "ci", "contrasenia", "superusuario"});
    }
    void agregar_factura(unordered_map<string, string> &factura) { // Agrega una factura al archivo y muestra informacion relevante por pantalla
        list<unordered_map<string, string>> lista_fantasma;
        vector<string> atributos = {"Cliente","Ci","Referencia","Telefono","Banco","Divisa","Fecha","IVA","Monto","Monto + IVA","Cajero","Ci cajero"};
        for (int i=1; i <= this->carrito.get_helados().size(); i++) {
            atributos.push_back("Helado "+to_string(i));
        }
        agregar(this->facturas_lpcsrt, this->facturas_cc, this->facturas_file_s, factura, lista_fantasma, atributos);
        // Mostrar la factura agregada
        system("cls");
        cuadros_principales();
        arte(this->usuario_registrado);
        gotoxy(55, 6); cout << "SENIAT";
        gotoxy(45, 7); cout << "Av. Constituci\xA2n, con Bermudez Nro.18";
        gotoxy(52, 8); cout << "J-1204578963";
        gotoxy(49, 10); cout << atributos[0] << ": " << factura[atributos[0]];
        gotoxy(49, 11); cout << atributos[1] << ": " << factura[atributos[1]];
        gotoxy(49, 12); cout << atributos[2] << ": " << factura[atributos[2]];
        gotoxy(49, 13); cout << atributos[3] << ": " << factura[atributos[3]];
        gotoxy(49, 14); cout << atributos[4] << ": " << factura[atributos[4]];
        gotoxy(49, 15); cout << atributos[5] << ": " << factura[atributos[5]];
        gotoxy(49, 16); cout << atributos[6] << ": " << factura[atributos[6]];
        gotoxy(49, 17); cout << atributos[7] << ": " << factura[atributos[7]];
        gotoxy(49, 18); cout << atributos[8] << ": " << factura[atributos[8]];
        gotoxy(49, 19); cout << atributos[9] << ": " << factura[atributos[9]];
        gotoxy(49, 20); cout << "Sabores vendidos: " << factura["Sabores vendidos"];
        
        

    }
    void agregar_helado_carrito(int opcion) { //Agregar helado al carrito
        this->carrito.agregar_helado(this->extraer_helado(opcion));
    }
    void pagar() { // Ejecutar las funcionalidades de pago y agregar informacion sobre el cajero encargado
        unordered_map<string, string> pago = this->carrito.pagar();

        if (pago["no"] == "no") {
            return;
        }

        unordered_map<string, string> cajero = this->extraer_empleado(this->usuario_registrado_ci);
        pago["Cajero"] = cajero["nombre"] + " " + cajero["apellido"];
        pago["Ci cajero"] = cajero["ci"];

        int count = 1;

        for (auto &helado : this->carrito.get_helados()) {
            pago["Helado " + to_string(count)] = helado["sabor"] + " " + to_string(stof(helado["precio"])/100) + " x"+helado["cantidad"];
            count++;
        }
        this->agregar_factura(pago);
        this->carrito.vaciar_carrito();
        gotoxy(46, 22); cout << "Pago realizado exitosamente";
        gotoxy(46, 23); system("pause");
    }

    // Eliminar
    void eliminar_empleado(int id) { // eliminar un empleado del archivo
        if (id > this->empleados.size() || id <= 0) return;
        SetFileAttributesA(this->usuarios_lpcsrt, FILE_ATTRIBUTE_NORMAL);
        vector<string> lineas = lineas_archivo(this->usuarios_cc);
        std::ofstream file(this->usuarios_file_s, std::ios::out);
        list<unordered_map<string, string>> nueva_lista;
        if (file.is_open()) {

            vector<string> splited;
            int i = 1;
            for (auto& empleado : this->empleados) {
                if (i != id || empleado["ci"] == usuario_registrado_ci) {
                    file << lineas[i-1];
                    nueva_lista.push_back(empleado);
                }
                i++;
            }
            // Cerrar el archivo
            this->empleados = nueva_lista;
            file.close();
        }
        else {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
        }
        gotoxy(43, 19); cout << "Usuario eliminado correctamente";
        gotoxy(43, 20); system("pause");
        SetFileAttributesA(this->usuarios_lpcsrt, FILE_ATTRIBUTE_READONLY);
    }

    // buscar
    bool buscar_empleado_por_ci(string ci) { // verifica si un empleado existe por la cedula
        for (auto &empleado : this->empleados) {
            if (empleado["ci"] == ci) {
                return true;
            }
        }
        return false;
    }
    bool buscar_empleado(string ci, string contrasenia) { //verifica si un empleado existe por la cedula y la clave

        for (auto &empleado : this->empleados) {
            if (empleado["ci"] == ci && empleado["contrasenia"] == contrasenia) {
                return true;
            }
        }
        return false;
    }
    unordered_map<string, string> extraer_empleado(string ci) { // extrae un empleado completo si se envia su cedula
        for (auto &empleado : this->empleados) {
            if (empleado["ci"] == ci) {
                return empleado;
            }
        }
        unordered_map<string, string> empleado = {{"empleado", "no encontrado"}};
        return empleado;
    }

    bool buscar_helado(int opcion) { // verifica si un helado existe por su numero
        int count = 1;
        for (auto &helado : this->helados) {
            if (count == opcion) {
                return true;
            }
            count++;
        }
        return false;
    }
    unordered_map<string, string> extraer_helado(int opcion) { // extrae un helado completo por su numero en orden
        int count = 1;
        for (auto &helado : this->helados) {
            if (count == opcion) {
                return helado;
            }
            count++;
        }
        unordered_map<string, string> helado = {{"helado", "no encontrado"}};
        return helado;
    }
};
