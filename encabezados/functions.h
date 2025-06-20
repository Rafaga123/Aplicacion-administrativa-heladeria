// librerias CPP
// #include <iostream>
#include <chrono> // Proporciona clases y funciones para medir y manipular el tiempo.
#include <ctime> // Ofrece funciones para convertir entre representaciones de tiempo de diferentes formatos.
#include <iomanip> // Contiene manipuladores de formato para controlar la salida de datos formateados.
#include <windows.h>
#include <cstdio> // Contiene funciones de entrada/salida de bajo nivel para archivos y dispositivos de entrada/salida estándar.
#include <vector>
#include <fstream> // Ofrece funciones para leer y escribir datos en archivos de texto y binarios.
#include <unordered_map>

// Mis archivos

using namespace std;

// Funcionalidades
void gotoxy(int x, int y) {
    // Posiciona un mensaje en cualquier coordenada de la pantalla, recibe dos parametros representando el eje X y Y
    HANDLE hcon; // Un HANDLE en C++ es un identificador opaco que representa un objeto administrado por el sistema operativo.
    hcon = GetStdHandle(STD_OUTPUT_HANDLE); // toma un identificador de objeto predefinido (STD_OUTPUT_HANDLE) y devuelve un HANDLE que representa el flujo de salida estándar (la consola).
    COORD dwPos; // COORD es una estructura definida en Windows que representa una coordenada bidimensional (X e Y).
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos); // mueve el cursor de la consola a la posición especificada por los valores de dwPos.X y dwPos.Y
}
void changeFont(int x, int y){
    static CONSOLE_FONT_INFOEX  fontex; // Declara una variable estática fontex de tipo CONSOLE_FONT_INFOEX. Esta estructura contiene información sobre la fuente de la consola, como tamaño, peso, nombre, etc.
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX); // Inicializa el miembro cbSize de la estructura fontex con el tamaño de la estructura en bytes. Esto es necesario para que las funciones de la consola puedan interpretar correctamente la estructura.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Obtiene un manejador (handle) al dispositivo de salida estándar (la consola) y lo asigna a la variable hOut. Este manejador se utilizará para interactuar con la consola.
    GetCurrentConsoleFontEx(hOut, 0, &fontex); // Obtiene la información de la fuente actual de la consola y la almacena en la estructura fontex. El segundo parámetro (0) indica que se desea obtener la fuente principal.
    fontex.FontWeight = 700; //Establece el peso de la fuente a 700, que generalmente corresponde a negrita.
    fontex.dwFontSize.X = x;
    fontex.dwFontSize.Y = y;
    SetCurrentConsoleFontEx(hOut, 0, &fontex); // Aplica los cambios realizados a la estructura fontex a la fuente de la consola. El segundo parámetro (0) indica que se está modificando la fuente principal.
}
void cuadro(int x1, int y1, int y2, int x2) {
    int i;

    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "\304"; //linea horizontal superior
		gotoxy(i,y2); cout << "\304"; //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout << "\263"; //linea vertical izquierda
		gotoxy(x2,i); cout << "\263"; //linea vertical derecha
	}

    gotoxy(x1,y1); cout << "\332";
    gotoxy(x1,y2); cout << "\300";
    gotoxy(x2,y1); cout << "\277";
    gotoxy(x2,y2); cout << "\331";
}
void cuadros_principales() { /// pinta el cuadro de toda la interfaz
    cuadro(3,0,24,115);
    cuadro(5,1,3,113);
    gotoxy(43,2); printf("Helader%ca El Sal\xA2n de los Helados",161);
    cout << endl << endl << endl << endl;
}
tm* obtener_fecha() { // Saca la fecha programada en la computadora anfitriona
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&now_c);
    return localTime;
}
vector<string> split(string cadena, char division) { // Dividir una cadena en un vector de strings
    vector<string> res;
    string cadena_actual;

    for (char c : cadena) {
        if (c != division) {
            cadena_actual += c;
        } else {
            res.push_back(cadena_actual);
            cadena_actual = "";
        }
    }

    return res;
}
bool es_digito_puro(string cadena) { // Determina si un strings es puro digito o no
  for (char caracter : cadena) {
    if (!isdigit(caracter)) {
      return false;
    }
  }
  return true;
}
vector<string> lineas_archivo(const char* ruta_archivo) { // extrae cada linea de un archivo y las almacena en un vector de strings
    fflush(stdin);
    FILE* file = fopen(ruta_archivo, "r");

    vector<string> res;
    char buffer[1024]; // Tamaño del buffer para almacenar cada línea
    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
    // Eliminar el carácter de nueva línea al final de la línea
        res.push_back(buffer);
        fflush(stdin);
    }
    
    fclose(file);
    return res;
}
void arte(string usuario) { // Imprime imagenes de helado de ASCII art en toda la interfaz
    gotoxy(11,6); cout << "     . ," <<endl;
    gotoxy(11,7); cout << "      *    ," <<endl;
    gotoxy(11,8); cout << " ` *~.|,~* '" <<endl;
    gotoxy(11,9); cout << " '  ,~*~~* `     _" <<endl;
    gotoxy(11,10); cout << "  ,* / \\`* '    //" <<endl;
    gotoxy(11,11); cout << "   ,* ; \\,O.   //" <<endl;
    gotoxy(11,12); cout << "       ,(:::)=//" <<endl;
    gotoxy(11,13); cout << "      (  `~(###)" <<endl;
    gotoxy(11,14); cout << "       %---'`'y" <<endl;
    gotoxy(11,15); cout << "        \\    /" <<endl;
    gotoxy(11,16); cout << "         \\  /" <<endl;
    gotoxy(11,17); cout << "        __)(__  " <<endl;
    gotoxy(11,18); cout << "       '------`" <<endl;

    

    gotoxy(84,6); cout << "     . ," <<endl;
    gotoxy(84,7); cout << "      *    ," <<endl;
    gotoxy(84,8); cout << " ` *~.|,~* '" <<endl;
    gotoxy(84,9); cout << " '  ,~*~~* `     _" <<endl;
    gotoxy(84,10); cout << "  ,* / \\`* '    //" <<endl;
    gotoxy(84,11); cout << "   ,* ; \\,O.   //" <<endl;
    gotoxy(84,12); cout << "       ,(:::)=//" <<endl;
    gotoxy(84,13); cout << "      (  `~(###)" <<endl;
    gotoxy(84,14); cout << "       %---'`'y" <<endl;
    gotoxy(84,15); cout << "        \\    /" <<endl;
    gotoxy(84,16); cout << "         \\  /" <<endl;
    gotoxy(84,17); cout << "        __)(__  " <<endl;
    gotoxy(84,18); cout << "       '------`" <<endl;
    
    gotoxy(8,23); cout << usuario;
}

// Menus
void pagina_de_inicio () { 
    cuadro(47,8,16,70);
    gotoxy(50,10); cout << "1. Iniciar sesi\xA2n" << endl;
    gotoxy(50,12); cout << "2. Salir" << endl << endl;

    
    gotoxy(50,14); cout << "Opcion: ";
}
void inicio(bool es_superusuario) {
    if (es_superusuario) {
        gotoxy(50,8); cout << "1. Helados";
        gotoxy(50,9); cout << "2. Carrito ";
        gotoxy(50,10); cout << "3. Eliminar pedidos ";
        gotoxy(50,11); cout << "4. Eliminar cantidad de helado ";
        gotoxy(50,12); cout << "5. Pagar ";
        gotoxy(50,13); cout << "6. Agregar empleado ";
        gotoxy(50,14); cout << "7. Eliminar empleado ";
        gotoxy(50,15); cout << "8. Acerca de la empresa";
        gotoxy(50,16); cout << "0. Volver ";
        gotoxy(50,18); cout << "Opci\xA2n: ";
    } else {
        gotoxy(50,10); cout << "1. Helados";
        gotoxy(50,11); cout << "2. Carrito ";
        gotoxy(50,12); cout << "3. Eliminar pedidos ";
        gotoxy(50,13); cout << "4. Eliminar cantidad de helado ";
        gotoxy(50,14); cout << "5. Pagar ";
        gotoxy(50,15); cout << "6. Acerca de la empresa";
        gotoxy(50,16); cout << "0. Volver ";
        gotoxy(50,18); cout << "Opci\xA2n: ";
    }
}

// archivos 
void llenar(LPCSTR lpcsrt_path, const char *file_route, list<unordered_map<string, string>>& lista_a_llenar, vector<string> atributos) {
    // llena una lista de unordered_map con informacion de las lineas de un archivo
    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_NORMAL); // Esta función es utilizada en Windows para modificar los atributos de un archivo.

    fflush(stdin);
    FILE* file = fopen(file_route, "r"); // abrir un archivo en modo lectura

    vector<string> objeto_actual;
    char buffer[1024];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) != nullptr) { // extraer cada linea del archivo hasta que sea nullptr

        buffer[strcspn(buffer, "\n")] = '\0';
        objeto_actual = split(buffer, ',');
        unordered_map<string, string> empleado;

        for (string& attr: atributos) {
            empleado[attr] = objeto_actual[i]; i++;
        }
        i = 0;
        lista_a_llenar.push_back(empleado);
        fflush(stdin);
    }
        
    fclose(file);
    
    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_READONLY);

}
void agregar(LPCSTR lpcsrt_path, const char *file_route, string file_path, unordered_map<string, string>& objeto_a_agregar, list<unordered_map<string, string>>& lista, vector<string> atributos) {
    // Funcion para agregar los elementos de un unordered_map a un archivo con sus atributos
    fflush(stdin);

    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_NORMAL);
    vector<string> lineas = lineas_archivo(file_route);
    std::ofstream file(file_path, std::ios::out); // abrir un archivo para leer y escribir en el
    string nueva_linea="";
    // unordered_map<int, int> unordered_mapa;
    if (file.is_open()) {
        
        for (string attr : atributos) {
            file << attr << ": " << objeto_a_agregar[attr] << "\n";
        }
        file << "\n";
        for (string& s : lineas) {
            file << s;
        }
        // Cerrar el archivo
        file.close();
        lista.push_front(objeto_a_agregar);
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
    
    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_READONLY);
}
void agregarConComas(LPCSTR lpcsrt_path, const char *file_route, string file_path, unordered_map<string, string>& objeto_a_agregar, list<unordered_map<string, string>>& lista, vector<string> atributos) {
    // Agregar elementos divididos por comas en cada linea
    fflush(stdin);

    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_NORMAL);
    vector<string> lineas = lineas_archivo(file_route);
    std::ofstream file(file_path, std::ios::out);
    string nueva_linea="";
    if (file.is_open()) {
        for (string& key : atributos) {
            nueva_linea += objeto_a_agregar[key]+',';
        }
        // Escribir en el archivo
        // file << empleado["nombre"] << "," << empleado["apellido"] << "," << empleado["ci"] << "," << empleado["contrasenia"] << "," << empleado["superusuario"] << "," << std::endl;
        file << nueva_linea << endl;
        for (string& s : lineas) {
            file << s;
        }
        // Cerrar el archivo
        file.close();
        lista.push_front(objeto_a_agregar);
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
    
    SetFileAttributesA(lpcsrt_path, FILE_ATTRIBUTE_READONLY);
}