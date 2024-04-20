
#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){

    int figuras;
    int x = 0;
    int y = 0;

    char movim;
    movim:
    do{
        movim = getch();
        if (movim == 'f'){
            cout << "Iniciando..." << endl;
            break;
        } else if (movim == 72 && y > 0){
            y--;
        } else if (movim == 80 && y < 24){
            y++;
        }else if (movim == 75 && x > 0){
            x--;
        } else if (movim == 77 && x < 79){
            x++;
        }
        gotoxy(x,y);
    } while (true);

  cout << "\nPresione F12 para iniciar menu de figuras: " << endl;

    while (true) {
        figuras = getch();//funcion para asignar teclas (getch())
        if (figuras == 224){//numero de tecla asignada f12=224
            break;
        } else if (cout << "Tecla incorrecta"){
        }
    }

    cout << "\nSeleccione figura a dibujar: " << endl;
    cout << "\nTriangulo = 1" << endl;
    cout << "Cuadrado = 2" << endl;
    cout << "Rectangulo = 3" << endl;
    cout << "Circulo = 4" << endl;

    cin >> figuras;

    switch(figuras){
    case 1 :
        cout << "Seleccionaste Triangulo" << endl;
        break;
    case 2 :
        cout << "Seleccionaste Cuadrado" << endl;
        break;
    case 3 :
        cout << "Seleccionaste Rectangulo" << endl;
        int larg, anch;

        cout << "\nIngrese el ancho: ";
        cin >> anch;

        cout << "\nIngrese el largo: ";
        cin >> larg;

        system("cls"); //funcion para limpiar la pantalla

        for (int i = 0; i < anch; ++i){
            gotoxy(x, y + i);
            for (int j = 0; j < larg; ++j) {
                if (i == 0 || i == anch - 1 || j == 0 || j == larg -1){
                    cout << "* ";
                } else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
        goto movim; //funcion para llamar a otra funcion anterior
        break;
    case 4 :
        cout << "Seleccionaste Circulo" << endl;
        break;
    }


    return 0;
}





