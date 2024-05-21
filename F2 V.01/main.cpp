#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>

using namespace std;

const int pant_alt = 85;
const int pant_anch = 28;

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

//Funcion para detectar teclas F
bool isKeyPressed(int keyCode) {
    return GetAsyncKeyState(keyCode) & 0x8000;
}

//Cuadrado
void dibujarCuadrado(int x, int y, int tamlad, char caracter= '*'){
    for(int i = 0; i < tamlad; i++){
        for(int j = 0; j < tamlad; j++)
        {
            gotoxy(adjX(x + j*2), adjY(y + i));
            if(i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1)
            {
                cout << caracter;
            }
            else
            {
                cout << "  ";
            }
        }
    }
}

//Rectangulo
void dibujarRectangulo(int x, int y, int ancho, int alto, char caracter = '*') {
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                gotoxy(adjX(x + j*2), adjY(y + i));
                cout << caracter;
            } else {
                cout << "  ";
            }
        }

    }
}

//Triangulo
void dibujarTriangulo(int x, int y, int tamano, char caracter = '*') {
    int espacios = tamano - 1;
    int asteriscos = 1;

    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < espacios; ++j) {
            gotoxy(adjX(x + j*2), adjY(y + i));
            cout << " ";
        }

        for (int j = 0; j < asteriscos; ++j) {
            if (j == 0 || j == asteriscos - 1 || i == tamano - 1) {
                gotoxy(adjX(x + espacios * 2 + j * 2), adjY(y + i));
                cout << caracter;
            } else {
                gotoxy(adjX(x + espacios * 2 + j * 2), adjY(y + i));
                cout << " ";
            }
        }
            asteriscos += 2;
            espacios--;
    }
}

//Circulo
void dibujarCirculo(int x, int y, int n = 0, char caracter = '*') {
    for (int j = 0; j <= n * 2; j++) {
        for (int i = 0; i <= n * 2; i++) {
            double distance = sqrt(pow(i - n, 2.0) + pow(j - n, 2.0));
            if (distance <= n && distance >= n - 1) {
                gotoxy(adjX(x + i * 2), adjY(y + j));
                cout << caracter;
            } else {
                gotoxy(adjX(x + i * 2), adjY(y + j));
                cout << "  ";
            }
        }
    }
}

//linea
void dibujarLinea(int x, int y, int longi, char caracter = '*'){
    int mitad_ancho = pant_anch / 2;
    for (int i = 0; i < longi; ++i) {
        int pos_x = (x + i >= pant_alt) ? x + i - pant_alt : x + i;
        gotoxy(adjX(pos_x), adjY(y));
        cout << caracter;
    }
}

//Rombo
void dibujarRombo(int x, int y, int lados, char caracter = '*') {
    int mitad = lados / 2;
    for (int i = -mitad; i <= mitad; ++i) {
        for (int j = -mitad; j <= mitad; ++j) {
            if (abs(i) + abs(j) == mitad) {
                gotoxy(adjX(x + (j + mitad) * 2), adjY(y + i + mitad));
                cout << caracter;
            } else {
                gotoxy(adjX(x + (j + mitad) * 2), adjY(y + i + mitad));
                cout << " ";
            }
        }
    }
}

//Hexagono
void dibujarHexagono(int x, int y, int hexlad, char caracter = '*') {
    int mitad = hexlad / 2;
    for (int i = -mitad; i <= mitad; ++i) {
        int ancho = hexlad - abs(i);
        for (int j = -ancho; j <= ancho; ++j) {
            if (j == -ancho || j == ancho || i == -mitad || i == mitad)
            {
                gotoxy(adjX(x + j * 2), adjY(y + i * 2));
                cout << caracter;
            }
        }
    }
}


//Funcion para borrar menu
void limpiarPantalla() {
    for (int i = 25; i <= 45; ++i) {
        gotoxy(0, i);
        for (int j = 0; j < pant_alt; ++j) {
            cout << " ";
        }
    }
}

//**Agregar colores **//
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
    gotoxy(0, 25);
    cout << "Seleccione el color de la figura: " << endl;
    cout << "1. Azul" << endl;
    cout << "2. Verde" << endl;
    cout << "3. Celeste" << endl;
    cout << "4. Rojo" << endl;
    cout << "6. Amarillo" << endl;
    cout << "7. Blanco" << endl;

}

int main() {
    char eleccion;
    char nuevoCaracter = '*';

    do {
        limpiarPantalla();

        int x = 0, y = 0;
        char movimiento;

        gotoxy(0, 25);
        cout << "Use las flechas para mover el cursor. Presione F12 para comenzar a dibujar formas." << endl;

        do {

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
        gotoxy(0, 26);
        cout << "Selecciona la forma a dibujar:" << endl;
        cout << "F1. Triangulo" << endl;
        cout << "F2. Cuadrado" << endl;
        cout << "F3. Rectangulo" << endl;
        cout << "F4. Circulo" << endl;
        cout << "F5. Linea" << endl;
        cout << "F6. Rombo" << endl;
        cout << "F7. Hexagono" << endl;
        cout << "F8. Nuevo Caracter" << endl;
        cout << "F9. Limpiar Pantalla" << endl;
        cout << "F10. Color de Caracter" << endl;
        cout << "F11. Grabar Pantalla" << endl;
        cout << "A. Abrir archivo y mostrar en pantalla" << endl;

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
            }
        }

        switch(opcion) {
            case 1:
                limpiarPantalla();
                int tamano;
                gotoxy(0, 26);
                cout << "Ingrese el tamano de la base del triangulo: ";
                cin >> tamano;
                dibujarTriangulo(x, y, tamano, nuevoCaracter);
                break;
            case 2:
                limpiarPantalla();
                int tamlad;
                gotoxy(0,26);
                cout << "Ingrese el tamano de los 4 lados: ";
                cin >> tamlad;
                dibujarCuadrado(x, y, tamlad, nuevoCaracter);
                break;
            case 3:
                limpiarPantalla();
                int ancho, alto;
                gotoxy(0, 26);
                cout << "Ingrese el ancho del rectangulo: ";
                cin >> ancho;
                gotoxy(0, 26);
                cout << "Ingrese la altura del rectangulo: ";
                cin >> alto;
                dibujarRectangulo(x, y, ancho, alto, nuevoCaracter);
                break;
            case 4:
                limpiarPantalla();
                int n;
                gotoxy(0, 26);
                cout << "Ingrese el radio del circulo: ";
                cin >> n;
                dibujarCirculo(x, y, n, nuevoCaracter);
                break;
            case 5:
                limpiarPantalla();
                int longi;
                gotoxy(0, 26);
                cout << "Ingrese la longitud de la linea: ";
                cin >> longi;
                dibujarLinea(x, y, longi, nuevoCaracter);
                break;
            case 6:
                limpiarPantalla();
                int lados;
                gotoxy(0, 26);
                cout << "Ingrese el tamano de los lados: ";
                cin >> lados;
                dibujarRombo(x, y, lados, nuevoCaracter);
                break;
            case 7:
                limpiarPantalla();
                int hexlad;
                gotoxy(0, 26);
                cout << "Ingrese el tamano de los 6 lados: ";
                cin >> hexlad;
                dibujarHexagono(x, y, hexlad, nuevoCaracter);
                break;
            case 8:
                limpiarPantalla();
                gotoxy(0, 26);
                cout << "Ingrese el caracter a usarse: ";
                cin >> nuevoCaracter;
                break;
            case 9:
                system("cls");
                break;
            case 10:
                limpiarPantalla();
                menucolores();
                cout << "Ingrese numero de color: ";
                int colorsel;
                cin >> colorsel;
                setTextColor((TextColor)colorsel);
                break;
            default:
                cout << "¡Opcion invalida!" << endl;
        }

        limpiarPantalla();
        gotoxy(0, 26);
        cout << "Seguir dibujando? (S/N): ";
        cin >> eleccion;

        gotoxy(0, 27);
        while (eleccion != 'S' && eleccion != 's' && eleccion != 'N' && eleccion != 'n') {
            cout << "Ingresar solo 'S' o 'N': ";
            cin >> eleccion;}
    } while (eleccion == 'S' || eleccion == 's');

    return 0;
}
