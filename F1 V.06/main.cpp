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

//Funcion para detectar F12
bool isF12Pressed() {
if (GetAsyncKeyState(VK_F12) & 0x8000) {
    return true;
    }
return false;
}

void dibujarCuadrado(int x, int y, int tamlad){
    for(int i = 0; i < tamlad; i++){

        for(int j = 0; j < tamlad; j++)
        {
            if(i == 0 || j == 0 || i == tamlad - 1 || j == tamlad - 1)
            {
                gotoxy(adjX(x + j), adjY(y + i));
                cout << "* ";
            }
            else
            {
                cout << "  ";
            }
        }

    }

}

void dibujarRectangulo(int x, int y, int ancho, int alto) {
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                gotoxy(adjX(x + j), adjY(y + i));
                cout << "* ";
            } else {
                cout << "  ";
            }
        }

    }
}


void dibujarTriangulo(int x, int y, int tamano) {
    int espacios = tamano - 1;
    int asteriscos = 1;

    for (int i = 0; i < tamano; ++i) {
        // Imprime espacios
        for (int j = 0; j < espacios; ++j) {
            gotoxy(adjX(x + j), adjY(y + i));
            cout << " ";
        }

        // Imprime asteriscos
        for (int j = 0; j < asteriscos; ++j) {
            gotoxy(adjX(x + espacios + j), adjY(y + i));
            cout << "*";
        }

        // Incrementa asteriscos y reduce espacios para formar un triángulo equilátero
        asteriscos += 2;
        espacios--;
    }
}

void dibujarCirculo(int x, int y, int n = 0){
    for(int j = 0; j <= n * 2; j++){
            gotoxy(x, y + j);
        for (int i = 0; i<= n * 2; i++){
            if (pow(i - n, 2.0) + pow(j - n, 2.0) <= pow(n,2.0)){
                cout << "* ";
            }
            else {
                cout << "  ";
            }
        }

    }

}


void limpiarMenu() {
    for (int i = 26; i <= 35; ++i) {
        gotoxy(i, 0);
        for (int j = 0; j < 80; ++j) {

            cout << " ";
        }
    }
    gotoxy(0,25);
}

void limpiarLinea(int y) {
    gotoxy(0, y);
    for (int i = 0; i < pant_alt; ++i) {
        cout << " ";
    }
    gotoxy(0, y);
}

void limpiarPantalla() {
    for (int i = 25; i <= 35; ++i) {
        gotoxy(0, i);
        for (int j = 0; j < pant_alt; ++j) {
            cout << " ";
        }
    }
}


int main() {
    char eleccion;

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
        } while (!isF12Pressed()); //No inicia hasta presionar F12

        int opcion;
        gotoxy(0, 25);
        cout << "Selecciona la forma a dibujar:" << endl;
        limpiarLinea(27);
        cout << "1. Cuadrado" << endl;
        limpiarLinea(28);
        cout << "2. Rectangulo" << endl;
        limpiarLinea(29);
        cout << "3. Triangulo" << endl;
        limpiarLinea(30);
        cout << "4. Circulo" << endl;
        limpiarLinea(31);
        cout << "5. Borrar figuras" << endl;
        limpiarLinea(32);

        cin >> opcion;



//        setColor(color);

        switch(opcion) {
            case 1:
                limpiarPantalla();
                int tamlad;
                gotoxy(0,26);
                cout << "Ingrese el tamano de los 4 lados: ";
                cin >> tamlad;
                dibujarCuadrado(x, y, tamlad);
                break;
            case 2:
                limpiarPantalla();
                int ancho, alto;
                gotoxy(0, 26);
                cout << "Ingrese el ancho del rectangulo: ";
                cin >> ancho;
                gotoxy(0, 27);
                cout << "Ingrese la altura del rectangulo: ";
                cin >> alto;
                dibujarRectangulo(x, y, ancho, alto);
                break;
            case 3:
                limpiarPantalla();
                int tamano;
                gotoxy(0, 26);
                cout << "Ingrese el tamano de la base del triangulo: ";
                cin >> tamano;
                dibujarTriangulo(x, y, tamano);
                break;
            case 4:
                limpiarPantalla();
                int n;
                gotoxy(0, 26);
                cout << "Ingrese el radio del circulo: ";
                cin >> n;
                dibujarCirculo(x, y, n);
                break;
            case 5:
                system("cls");
                break;
            default:
                cout << "¡Opcion invalida!" << endl;
        }

        limpiarLinea(23);

       gotoxy(0, 27);
        cout << "Desea dibujar otra forma? (S/N): ";
        cin >> eleccion;

        while (eleccion != 'S' && eleccion != 's' && eleccion != 'N' && eleccion != 'n') {
            cout << "Por favor, ingrese solo 'S' o 'N': ";
            cin >> eleccion;
        }

    } while (eleccion == 'S' || eleccion == 's');

    return 0;
}
