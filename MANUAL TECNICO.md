# Manual Tecnico

## Descripcion del Programa

Este programa realizado en el lenguaje c++ permite dibujar ciertas figuras geometricas entre las cuales sserian: triángulo, cuadrado, rectángulo, círculo, línea, rombo, hexágono; por medio de la consola en la cual el usuario podra movilizar el cursor y posicionarse segun desee realizar el dibujo, como tambien cambiar el caracter y color que desee para cada figura.

## Estructura del Codigo

### Librerias utilizadas

- #include <iostream> : Provee funciones de entrada/salida estándar.
- #include <conio.h> : Provee funciones para manipulación de consola.
- #include <windows.h> : Provee funciones específicas de Windows, como manipulación de la posición del cursor y colores.
- #include cmath : Provee funciones matemáticas, como sqrt y pow.
- #include fstream : Permite trabajar con archivos de entrada y salida.
- #include vector : Permite el uso de contenedores dinámicos para almacenar y manipular datos de manera eficiente.

## Constantes

- const int pant_alt = 85; : Define la altura de la pantalla de la consola.
- const int pant_anch = 28; : Define el ancho de la pantalla de la consola.

## Funciones

### Ajuste de Coordenadas

int adjX(int x) {

  if (x < 0) return pant_alt + x;

  if (x >= pant_alt) return x - pant_alt;
  
  return x;
  
  }

 int adjY(int y) {  
      
      if (y < 0) return pant_anch + y;
      
      if (y >= pant_anch) return y - pant_anch;
      
      return y;
    
    }

**Estas funciones ajustan las coordenadas para que se mantengan dentro de los límites de la pantalla.**

### Posicionamiento del Cursor

void gotoxy(int x, int y) {
    
    COORD coord;
    
    coord.X = x;
    
    coord.Y = y;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

**Esta función posiciona el cursor en las coordenadas especificadas en la consola.**

### Deteccion de Teclas

bool isKeyPressed(int keyCode) {
    
    return GetAsyncKeyState(keyCode) & 0x8000;

}

**Esta función detecta si una tecla específica está siendo presionada.**

## Funciones de Dibujo

### Dibujar Cuadrado

void dibujarCuadrado(int x, int y, int tamlad, char caracter= '*')

**Dibuja un cuadrado de tamaño tamlad en la posición (x, y) con el carácter especificado.**

### Dibujar Rectangulo

void dibujarRectangulo(int x, int y, int ancho, int alto, char caracter = '*')

**Dibuja un rectángulo de ancho ancho y alto alto en la posición (x, y) con el carácter especificado.**

### Dibujar Triangulo

void dibujarTriangulo(int x, int y, int tamano, char caracter = '*')

**Dibuja un triángulo equilátero de base tamano en la posición (x, y) con el carácter especificado.**

### Dibujar Circulo

void dibujarCirculo(int x, int y, int n = 0, char caracter = '*')

**Dibuja un círculo de radio n en la posición (x, y) con el carácter especificado.**

### Dibujar Linea

void dibujarLinea(int x, int y, int longi, char caracter = '*')

**Dibuja una línea de longitud longi en la posición (x, y) con el carácter especificado.**

### Dibujar Rombo

void dibujarRombo(int x, int y, int lados, char caracter = '*')

**Dibuja un rombo de tamaño lados en la posición (x, y) con el carácter especificado.**

### Dibujar Hexagono

void dibujarHexagono(int x, int y, int hexlad, char caracter = '*')

**Dibuja un hexágono de tamaño hexlad en la posición (x, y) con el carácter especificado.**

## Funciones de Utilidad

### Limpiar Pantalla

void limpiarPantalla() {
    
    for (int i = 25; i <= 45; ++i) {
        
        gotoxy(0, i);
        
        for (int j = 0; j < pant_alt; ++j) {
            
            cout << " ";
        
        }
    
    }

}

**Limpia una sección de la pantalla de la consola.**

### Funcion de Colores

enum TextColor {
    
    Azul = 1,
    
    Verde = 2,
    
    Celeste = 3,
    
    Rojo = 4,
    
    Amarillo = 6,
    
    Blanco = 7,

};


void setTextColor(TextColor color) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    SetConsoleTextAttribute(hConsole, color);

}

**Define colores para el texto y una función para cambiar el color del texto en la consola.**

### Menu de Colores

void menucolores() {
    
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

**Grabar la Pantalla en un archivo y Luego abrirlo en la consola.**

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

## Funcion Principal 

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
            if (movimiento == 72 && y > 0) y--;
            else if (movimiento == 80 && y < 24) y++;
            else if (movimiento == 75 && x > 0) x--;
            else if (movimiento == 77 && x < 79) x++;
            gotoxy(x, y);
        } while (!isKeyPressed(VK_F12)); 

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
            if (isKeyPressed(VK_F1)) { opcion = 1; break; }
            else if (isKeyPressed(VK_F2)) { opcion = 2; break; }
            else if (isKeyPressed(VK_F3)) { opcion = 3; break; }
            else if (isKeyPressed(VK_F4)) { opcion = 4; break; }
            else if (isKeyPressed(VK_F5)) { opcion = 5; break; }
            else if (isKeyPressed(VK_F6)) { opcion = 6; break; }
            else if (isKeyPressed(VK_F7)) { opcion = 7; break; }
            else if (isKeyPressed(VK_F8)) { opcion = 8; break; }
            else if (isKeyPressed(VK_F9)) { opcion = 9; break; }
            else if (isKeyPressed(VK_F10)) { opcion = 10; break; }
            else if (isKeyPressed(VK_F11)) { opcion = 11; break; }
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
          etc...




