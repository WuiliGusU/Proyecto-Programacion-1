#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

//Definicion de medidas de pantalla en consola//
const int pant_alt = 85;
const int pant_anch = 28;

//Vector para poder grabar pantalla//
vector<string> pantalla(pant_anch, string(pant_alt, ' '));

//Ajustar cordenadas//
int adjX(int x){
    if (x < 0) return pant_alt + x;
    if (x >= pant_alt) return x - pant_alt;
    return x;
}

int adjY(int y){
    if (y < 0) return pant_anch + y;
    if (y >= pant_anch) return y - pant_anch;
    return y;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para comprobar si la combinación Ctrl + A está presionada//
bool isCtrlA() {
    return ((GetKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(0x41) & 0x8000));
}

//Funcion para detectar teclas F//
bool isKeyPressed(int keyCode) {
    return GetAsyncKeyState(keyCode) & 0x8000;
}

//Cuadrado//
void dibujarCuadrado(int x, int y, int tamlad, char orientacionCUADR, char caracter = '*') {
    switch (orientacionCUADR) {
        case 'A': // Arriba
            for (int i = 0; i < tamlad; i++) {
                for (int j = 0; j < tamlad; j++) {
                    int cx = adjX(x + j * 2);
                    int cy = adjY(y + i);
                    gotoxy(cx, cy);
                    if (i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1) {
                        cout << caracter;
                        pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                    } else {
                        cout << " ";
                        pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                    }
                }
            }
            break;

        case 'B': // Abajo
            for (int i = 0; i < tamlad; i++) {
                for (int j = 0; j < tamlad; j++) {
                    int cx = adjX(x + j * 2);
                    int cy = adjY(y - i);
                    gotoxy(cx, cy);
                    if (i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1) {
                        cout << caracter;
                        pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                    } else {
                        cout << " ";
                        pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                    }
                }
            }
            break;

        case 'D': // Derecha
            for (int i = 0; i < tamlad; i++) {
                for (int j = 0; j < tamlad; j++) {
                    int cx = adjX(x + i * 2);
                    int cy = adjY(y + j);
                    gotoxy(cx, cy);
                    if (i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1) {
                        cout << caracter;
                        pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                    } else {
                        cout << " ";
                        pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                    }
                }
            }
            break;

        case 'I': // Izquierda
            for (int i = 0; i < tamlad; i++) {
                for (int j = 0; j < tamlad; j++) {
                    int cx = adjX(x - i * 2);
                    int cy = adjY(y + j);
                    gotoxy(cx, cy);
                    if (i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1) {
                        cout << caracter;
                        pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                    } else {
                        cout << " ";
                        pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                    }
                }
            }
            break;

        default:
            cout << "   Orientacion invalida." << endl;
            break;
    }
}

//Rectangulo//
void dibujarRectangulo(int x, int y, int ancho, int alto, char orientacionREC, char caracter = '*') {
    if (orientacionREC == 'A') { // Arriba
        for (int i = 0; i < alto; ++i) {
            for (int j = 0; j < ancho; ++j) {
                int cx = adjX(x + j * 2);
                int cy = adjY(y - i);
                gotoxy(cx, cy);
                if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                    cout << caracter;
                    pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                } else {
                    cout << " ";
                    pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                }
            }
        }
    } else if (orientacionREC == 'B') { // Abajo
        for (int i = 0; i < alto; ++i) {
            for (int j = 0; j < ancho; ++j) {
                int cx = adjX(x + j * 2);
                int cy = adjY(y + i);
                gotoxy(cx, cy);
                if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                    cout << caracter;
                    pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
                } else {
                    cout << " ";
                    pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
                }
            }
        }
    }
}

//Triangulo//
void dibujarTriangulo(int x, int y, int tamano, char orientacionTR, char caracter = '*') {
    switch (orientacionTR) {
        case 'A': // Arriba
            for (int i = 0; i < tamano; ++i) {
                int cx1 = adjX(x - i);
                int cy1 = adjY(y + i);
                int cx2 = adjX(x + i);
                int cy2 = adjY(y + i);
                gotoxy(cx1, cy1);
                cout << caracter;
                pantalla[cy1][cx1] = caracter; // Actualiza el vector pantalla
                if (i > 0) {
                    gotoxy(cx2, cy2);
                    cout << caracter;
                    pantalla[cy2][cx2] = caracter; // Actualiza el vector pantalla
                }
            }
            for (int i = 0; i < tamano * 2 - 1; ++i) {
                int cx = adjX(x - tamano + i);
                int cy = adjY(y + tamano - 1);
                gotoxy(cx, cy);
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            }
            break;
        case 'B': // Abajo
            for (int i = 0; i < tamano; ++i) {
                int cx1 = adjX(x - i);
                int cy1 = adjY(y - i);
                int cx2 = adjX(x + i);
                int cy2 = adjY(y - i);
                gotoxy(cx1, cy1);
                cout << caracter;
                pantalla[cy1][cx1] = caracter; // Actualiza el vector pantalla
                if (i > 0) {
                    gotoxy(cx2, cy2);
                    cout << caracter;
                    pantalla[cy2][cx2] = caracter; // Actualiza el vector pantalla
                }
            }
            for (int i = 0; i < tamano * 2 - 1; ++i) {
                int cx = adjX(x - tamano + i);
                int cy = adjY(y - tamano + 1);
                gotoxy(cx, cy);
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            }
            break;
        case 'D': // Derecha
            for (int i = 0; i < tamano; ++i) {
                int cx1 = adjX(x + i);
                int cy1 = adjY(y + i);
                int cx2 = adjX(x + i);
                int cy2 = adjY(y - i);
                gotoxy(cx1, cy1);
                cout << caracter;
                pantalla[cy1][cx1] = caracter; // Actualiza el vector pantalla
                if (i > 0 && i < tamano - 1) {
                    gotoxy(cx2, cy2);
                    cout << caracter;
                    pantalla[cy2][cx2] = caracter; // Actualiza el vector pantalla
                }
            }
            for (int i = 0; i < tamano * 2 - 1; ++i) {
                int cx = adjX(x + tamano - 1);
                int cy = adjY(y - tamano + i);
                gotoxy(cx, cy);
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            }
            break;
        case 'I': // Izquierda
            for (int i = 0; i < tamano; ++i) {
                int cx1 = adjX(x - i);
                int cy1 = adjY(y + i);
                int cx2 = adjX(x - i);
                int cy2 = adjY(y - i);
                gotoxy(cx1, cy1);
                cout << caracter;
                pantalla[cy1][cx1] = caracter; // Actualiza el vector pantalla
                if (i > 0 && i < tamano - 1) {
                    gotoxy(cx2, cy2);
                    cout << caracter;
                    pantalla[cy2][cx2] = caracter; // Actualiza el vector pantalla
                }
            }
            for (int i = 0; i < tamano * 2 - 1; ++i) {
                int cx = adjX(x - tamano + 1);
                int cy = adjY(y - tamano + i);
                gotoxy(cx, cy);
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            }
            break;
        default:
            cout << "   Orientacion invalida." << endl;
            break;
    }
}

//Circulo//
void dibujarCirculo(int x, int y, int n = 0, char caracter = '*') {
    for (int j = 0; j <= n * 2; j++) {
        for (int i = 0; i <= n * 2; i++) {
            double distance = sqrt(pow(i - n, 2.0) + pow(j - n, 2.0));
            int cx = adjX(x + i * 2);
            int cy = adjY(y + j);
            gotoxy(cx, cy);
            if (distance <= n && distance >= n - 1) {
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            } else {
                cout << " ";
                pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
            }
        }
    }
}

//linea//
void dibujarLinea(int x, int y, int longi, char orientacionLIN, char caracter = '*') {
    int dx = 0, dy = 0;

    switch (orientacionLIN) {
        case 'A': dy = -1; break;
        case 'B': dy = 1; break;
        case 'D': dx = 1; break;
        case 'I': dx = -1; break;
        default: return;
    }

    for (int i = 0; i < longi; ++i) {
        int cx = adjX(x + i * dx);
        int cy = adjY(y + i * dy);
        gotoxy(cx, cy);
        cout << caracter;
        pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
    }
}


//Rombo//
void dibujarRombo(int x, int y, int lados, char orientacionROMBO, char caracter = '*') {
    int mitad = lados / 2;
    int desplazamiento = (orientacionROMBO == 'A') ? -mitad : 0;

    for (int i = -mitad; i <= mitad; ++i) {
        for (int j = -mitad; j <= mitad; ++j) {
            int cx = adjX(x + (j + mitad) * 2);
            int cy = adjY(y + i + mitad + desplazamiento);
            gotoxy(cx, cy);
            if (abs(i) + abs(j) == mitad) {
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            } else {
                cout << " ";
                pantalla[cy][cx] = ' '; // Actualiza el vector pantalla
            }
        }
    }
}

//Hexagono//
void dibujarHexagono(int x, int y, int hexlad, char orientacionHEX, char caracter = '*') {
    int mitad = hexlad / 2;
    int desplazamiento = (orientacionHEX == 'V') ? mitad : 0;

    for (int i = -mitad; i <= mitad; ++i) {
        int ancho = hexlad - abs(i);

        for (int j = -ancho; j <= ancho; ++j) {
            int cx = adjX(x + j * 2);
            int cy = (orientacionHEX == 'V') ? adjY(y - i + desplazamiento) : adjY(y + i * 2 + desplazamiento);
            gotoxy(cx, cy);
            if (j == -ancho || j == ancho || i == -mitad || i == mitad) {
                cout << caracter;
                pantalla[cy][cx] = caracter; // Actualiza el vector pantalla
            }
        }
    }
}


//Funcion para borrar menu//
void limpiarPantalla() {
    for (int i = 25; i <= 45; ++i) {
        gotoxy(0, i);
        for (int j = 0; j < pant_alt; ++j) {
            cout << " ";
        }
    }
}

//Agregar colores//
enum TextColor {
    Azul = 1,
    Verde = 2,
    Celeste = 3,
    Rojo = 4,
    Amarillo = 6,
    Blanco = 7,
};

void setTextColor(TextColor color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void menucolores(){
    limpiarPantalla();
    gotoxy(0, 26);
    cout << "   Seleccione el color de la figura: " << endl;
    cout << "   1. Azul" << endl;
    cout << "   2. Verde" << endl;
    cout << "   3. Celeste" << endl;
    cout << "   4. Rojo" << endl;
    cout << "   6. Amarillo" << endl;
    cout << "   7. Blanco" << endl;

}

//Grabar la pantalla//
void grabarPantalla(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const string& linea : pantalla) {
            file << linea << endl;
        }
        file.close();
    }
}

//Abrir archivo guardado//
void abrirArchivo(const string& filename) {
    ifstream file(filename);
    string line;
    int y = 0;
    if (file.is_open()) {
        while (getline(file, line) && y < pant_anch) {
            pantalla[y] = line;
            gotoxy(0, y);
            cout << line << endl; // Mostrar cada línea en la consola
            ++y;
        }
        file.close();
    }
}

int main() {
    char eleccion;
    char nuevoCaracter = '*';

    do {
        limpiarPantalla();

        int x = 0, y = 0;
        char movimiento;

        gotoxy(0, 26);
        cout << "   Use las flechas para mover el cursor. Presione F12 para comenzar a dibujar formas." << endl;

        do {
            //Movimiento de cursor en pantalla con flechas//
            movimiento = getch();
            if (movimiento == 72 && y > 0) {
                y--;
            } else if (movimiento == 80 && y < 24) {
                y++;
            } else if (movimiento == 75 && x > 0) {
                x--;
            } else if (movimiento == 77 && x < 79) {
                x++;
            }
            gotoxy(x, y);
        } while (!isKeyPressed(VK_F12)); //No inicia hasta presionar F12

        int opcion;
        gotoxy(0, 27);
        cout << "   Selecciona la forma a dibujar:" << endl;
        cout << "   F1. Triangulo" << endl;
        cout << "   F2. Cuadrado" << endl;
        cout << "   F3. Rectangulo" << endl;
        cout << "   F4. Circulo" << endl;
        cout << "   F5. Linea" << endl;
        cout << "   F6. Rombo" << endl;
        cout << "   F7. Hexagono" << endl;
        cout << "   F8. Nuevo Caracter" << endl;
        cout << "   F9. Limpiar Pantalla" << endl;
        cout << "   F10. Color de Caracter" << endl;
        cout << "   F11. Grabar Pantalla" << endl;
        cout << "   Ctrl + A. Abrir archivo y mostrar en pantalla" << endl;

        //Ciclo para detectar teclas F y Ctrl + A//
        while (true){
            if (isKeyPressed(VK_F1)){
                opcion = 1;
                break;
            }else if (isKeyPressed(VK_F2)){
                opcion = 2;
                break;
            }else if (isKeyPressed(VK_F3)){
                opcion = 3;
                break;
            }else if (isKeyPressed(VK_F4)){
                opcion = 4;
                break;
            }else if (isKeyPressed(VK_F5)){
                opcion = 5;
                break;
            }else if (isKeyPressed(VK_F6)){
                opcion = 6;
                break;
            }else if (isKeyPressed(VK_F7)){
                opcion = 7;
                break;
            }else if (isKeyPressed(VK_F8)){
                opcion = 8;
                break;
            }else if (isKeyPressed(VK_F9)){
                opcion = 9;
                break;
            }else if (isKeyPressed(VK_F10)){
                opcion = 10;
                break;
            }else if (isKeyPressed(VK_F11)){
                opcion = 11;
                break;
            }else if (isCtrlA()){
                opcion = 12;
                break;
            }
        }

        {
        switch(opcion) {
            case 1:
                limpiarPantalla();
                int tamano;
                char orientacionTR;
                gotoxy(0, 26);
                cout << "   Ingrese el tamano de la base del triangulo: ";
                cin >> tamano;
                cout << "   Seleccione la orientacion del triangulo: " << endl;
                cout << "   A - Arriba" << endl;
                cout << "   B - Abajo" << endl;
                cout << "   D - Derecha" << endl;
                cout << "   I - Izquierda" << endl;
                cout << "   Ingrese la orientacion: ";
                cin >> orientacionTR;
            switch (orientacionTR) {
                case 'A':
                case 'B':
                dibujarTriangulo(x, y, tamano, orientacionTR, nuevoCaracter);
                break;
                case 'D':
                dibujarTriangulo(x + tamano - 1, y, tamano, 'I', nuevoCaracter);
                break;
                case 'I':
                dibujarTriangulo(x, y, tamano, 'D', nuevoCaracter);
                break;
                default:
                cout << "Orientacion invalida." << endl;
                break;}
                break;
            case 2:
                limpiarPantalla();
                int tamlad;
                char orientacionCUADR;
                gotoxy(0, 26);
                cout << "   Ingrese el tamano de los 4 lados: ";
                cin >> tamlad;
                cout << "   Seleccione la orientacion: " << endl;
                cout << "   A - Arriba" << endl;
                cout << "   B - Abajo" << endl;
                cout << "   D - Derecha" << endl;
                cout << "   I - Izquierda" << endl;
                cout << "   Ingrese orientacion: ";
                cin >> orientacionCUADR;
                dibujarCuadrado(x, y, tamlad, orientacionCUADR, nuevoCaracter);
                break;
            case 3:
                limpiarPantalla();
                int ancho, alto;
                char orientacionREC;
                gotoxy(0, 26);
                cout << "   Ingrese el ancho del rectangulo: ";
                cin >> ancho;
                cout << "   Ingrese el alto del rectangulo: ";
                cin >> alto;
                cout << "   Seleccione la orientacion: " << endl;
                cout << "   A - Arriba" << endl;
                cout << "   B - Abajo" << endl;
                cout << "   Ingrese orientacion: ";
                cin >> orientacionREC;
                dibujarRectangulo(x, y, ancho, alto, orientacionREC, nuevoCaracter);
                break;
            case 4:
                limpiarPantalla();
                int n;
                gotoxy(0, 26);
                cout << "   Ingrese el radio del circulo: ";
                cin >> n;
                dibujarCirculo(x, y, n, nuevoCaracter);
                break;
            case 5:
                limpiarPantalla();
                int longi;
                char orientacionLIN;
                gotoxy(0, 26);
                cout << "   Ingrese la longitud de la linea: ";
                cin >> longi;
                cout << "   Seleccione la orientación de la línea: " << endl;
                cout << "   A - Arriba" << endl;
                cout << "   B - Abajo" << endl;
                cout << "   D - Derecha" << endl;
                cout << "   I - Izquierda" << endl;
                cout << "   Ingrese la orientacion: ";
                cin >> orientacionLIN;
                dibujarLinea(x, y, longi, orientacionLIN, nuevoCaracter);
                break;
            case 6:
                limpiarPantalla();
                int lados;
                char orientacionROMBO;
                gotoxy(0, 26);
                cout << "   Ingrese el tamano de los lados: ";
                cin >> lados;
                cout << "   Seleccione la orientacion: " << endl;
                cout << "   A - Arriba" << endl;
                cout << "   B - Abajo" << endl;
                cout << "   Ingrese orientacion: ";
                cin >> orientacionROMBO;
                dibujarRombo(x, y, lados,orientacionROMBO, nuevoCaracter);
                break;
            case 7:
                limpiarPantalla();
                int hexlad;
                char orientacionHEX;
                gotoxy(0, 26);
                cout << "   Ingrese la longitud de uno de los lados del hexagono: ";
                cin >> hexlad;
                cout << "   Seleccione la orientacion del hexagono: " << endl;
                cout << "   V - Vertical" << endl;
                cout << "   H - Horizontal" << endl;
                cout << "   Ingrese la orientacion: ";
                cin >> orientacionHEX;
                dibujarHexagono(x, y, hexlad, orientacionHEX, nuevoCaracter);
                break;
            case 8:
                limpiarPantalla();
                gotoxy(0, 26);
                cout << "   Ingrese el caracter a usarse: ";
                cin >> nuevoCaracter;
                break;
            case 9:
                system("cls");
                break;
            case 10:
                limpiarPantalla();
                menucolores();
                cout << "   Ingrese numero de color: ";
                int colorsel;
                cin >> colorsel;
                setTextColor((TextColor)colorsel);
                break;
            case 11:{
                cout << "   Ingresa el nombre del archivo para grabar la pantalla: ";
                string filename;
                cin >> filename;
                grabarPantalla(filename);
                break;
                }
            case 12: {
                if (isCtrlA()) {
                cout << "   Ingresa el nombre del archivo para abrir: ";
                string filename;
                cin >> filename;
                abrirArchivo(filename);
                }
                break;
                }
                default:
                cout << "¡Opcion invalida!" << endl;}
        }
        limpiarPantalla();
        gotoxy(0, 26);
        cout << "   Seguir dibujando? (S/N): ";
        cin >> eleccion;

        gotoxy(0, 27);
        while (eleccion != 'S' && eleccion != 's' && eleccion != 'N' && eleccion != 'n') {
            cout << "   Ingresar solo 'S' o 'N': ";
            cin >> eleccion;}
    } while (eleccion == 'S' || eleccion == 's');

    return 0;
}
