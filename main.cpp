#include "miniwin.h"                    // Libreria grafica
#include <iostream>                     // Usada para debugging
#include <time.h>                       // Usada para semillas aleatorias
#include <cstdlib>                      // Usada para la funcion rand
#include <sstream>                      // Usada para convertir de int a string
#include <fstream>                      // Usada para flujos

using namespace miniwin;
using namespace std;

const int t = 20;                       // Tamaño de los cuadros
const int col = 10, fil = 20;           // Numero de Columnas y Filas
const int ancho_v = 220, alto_v = 120;  // Ancho y alto de ventana aux
int te = tecla();                       // Detecta la tecla que se oprime
int tab[col][fil];                      // Declaracion del tablero
bool tem = false;                       // Se usa para un (para todo)
int sc;                                 // Puntuacion
int es = 0;                             // *Modulador de tiempo
int nivel;                              // Velocidad del nivel
int contfila = 0;                       // Contador de filas
int ale = rand()%7;                     // Numero aleatorio entre 0 y 6 (El numero de piezas)
int ale2 = rand()%7;

const int tTexto = 19;       // Maximo tamaño de texto
// Texto para mostrar en pantalla
const string pal[tTexto] = {"iniciar juego","Multijugador","Puntajes","Creditos"};
// Impresion de textos
struct Letter{
    bool mapa[8][5];
                //pos x,pos y, tam x, tam y,  degradado
    void pintar(int x, int y, int xt, int yt, double deg){
        for(int i=0; i<8; i++){
            for(int j=0; j<5; j++){
                if(mapa[i][j]){
                    rectangulo_lleno(x+xt*j,y+yt*i*deg,x+xt*j+xt,y+yt*i+yt);
                }
            }
        }
    }
};
// Declaracion de todas las letras del abecedario
Letter todas[36] =  {{ {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1}} }, //A
                     { {{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0}} }, //B
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,1},{0,1,1,1,0}} }, //C
                     { {{1,1,1,0,0},{1,0,0,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0}} }, //D
                     { {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}} }, //E
                     { {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0}} }, //F
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,0},{1,0,0,0,0},{1,0,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //G
                     { {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1}} }, //H
                     { {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1}} }, //I
                     { {{0,1,1,1,1},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{1,0,0,1,0},{0,1,1,0,0}} }, //J
                     { {{1,0,0,0,1},{1,0,0,1,0},{1,0,1,0,0},{1,1,0,0,0},{1,1,0,0,0},{1,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1}} }, //K
                     { {{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}} }, //L
                     { {{1,0,0,0,1},{1,1,0,1,1},{1,0,1,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1}} }, //M
                     { {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,0,0,1},{1,0,1,0,1},{1,0,0,1,1},{1,0,0,0,1},{1,0,0,0,1}} }, //N
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //O
                     { {{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0}} }, //P
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,1,0,1},{0,1,1,1,0}} }, //Q
                     { {{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0},{1,1,0,0,0},{1,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1}} }, //R
                     { {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{1,1,1,1,1}} }, //S
                     { {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}} }, //T
                     { {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //U
                     { {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0}} }, //V
                     { {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,1,0,1},{1,1,0,1,1},{1,0,0,0,1}} }, //W
                     { {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1}} }, //X
                     { {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}} }, //Y
                     { {{1,1,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0},{1,0,0,0,0},{1,1,1,1,1}} }, //Z
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //0
                     { {{0,0,0,1,0},{0,0,1,1,0},{0,1,0,1,0},{1,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{1,1,1,1,1}} }, //1
                     { {{0,1,1,1,0},{1,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0},{1,1,1,1,1}} }, //2
                     { {{0,1,1,1,0},{1,0,0,0,1},{0,0,0,0,1},{0,0,1,1,0},{0,0,0,0,1},{0,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //3
                     { {{1,0,0,1,0},{1,0,0,1,0},{1,0,0,1,0},{1,1,1,1,1},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0},{0,0,0,1,0}} }, //4
                     { {{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,0},{0,0,0,0,1},{0,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //5
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //6
                     { {{1,1,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0},{0,1,0,0,0},{0,1,0,0,0}} }, //7
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}} }, //8
                     { {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1},{0,0,0,0,1}} }  //9
};
        // pos x, pos y, cadena de char, tamañoX, tamañoY, pix entre letraas, degradado, coordenadas en medio
void d_text(int x, int y, const std::string& s, int xt, int yt, int esp, double deg, bool xMedio){   // Funcion que pinta un caracter con el tamaño que uno desee
    const char *c = s.c_str();
    if(xMedio) x -=5*(s.size()/2)*xt+(s.size()/2)*esp;

    for(int j = 0; j<s.size(); j++){
        for(int i = 97; i<=122; i++){
            if(c[j] == i){
                todas[i-97].pintar((x+j*xt*5)+(j*esp), y, xt, yt, deg);
            }else if(c[j] == i-32){
                todas[i-97].pintar((x+j*xt*5)+(j*esp), y, xt, yt, deg);
            }
        }
        for(int i = 48; i<=57; i++){
            if(c[j] == i){
                todas[i-22].pintar((x+j*xt*5)+(j*esp), y, xt, yt, deg);
            }
        }
    }
}
// Fin impresion de textos

//Incializacion por recursividad
int main();
void teletransportar();
// Funciones base
void tablero(){                         // Pinta el fondo del tablero
    for(int i = 0; i<col; i++){
        for(int j = 0; j<fil; j++){
            color(tab[i][j]);                                               // El color depende del numero guardado en la posicion
            rectangulo_lleno(i*t+1,j*t+ancho_v/2+1,i*t+t,j*t+t+ancho_v/2);  // Pinta tablero y piezas del tablero
            color_rgb(160,160,160);                                         // Color Gris
            rectangulo(i*t,j*t+ancho_v/2,i*t+t,j*t+t+ancho_v/2);            // Pinta Malla
        }
    }
}
void aleatorio(){                       // Genera numero aleatorio entre 0 y 6
    srand(time(0));
    ale = rand()%7;
    if(ale == ale2){                    // Si la pieza siguiente es igual a la que esta en juego la cambia (En teoria)
        ale += 1;
        if(ale > 6) ale = 1;
    }
}
string toString(int s){                 //Convierte de entero a string
    stringstream sout;
    sout << s;
    return sout.str();
}

// Estructuras
struct Cord{                            // Estructura de cordenadas x y
    int x, y;
};
struct Pieza{
    Cord ori;                           // Coordenadas cuadrado origen
    Cord late[3];                       // Coordenadas relativas al origen
    int c;                              // Color de la pieza

    // Metodos
    void pintar(){                      // Muestra la pieza en pantalla
        color(c);
        rectangulo_lleno(ori.x*t + 1,
                         ori.y*t + 1 + ancho_v/2,
                         ori.x*t + t,
                         ori.y*t + t + ancho_v/2);
        for(int i = 0; i<3; i++){
            rectangulo_lleno((ori.x + late[i].x)*t + 1,
                             (ori.y + late[i].y)*t + 1 + ancho_v/2,
                             (ori.x + late[i].x)*t + t,
                             (ori.y + late[i].y)*t + t + ancho_v/2);
        }
    }
    int choque(){                       // Return 0 = no hay choque, 1 = choque lateral, 2 = choque inferior o con piezas del tablero
        for(int i = 0; i<3; i++){
                 if((ori.y           > fil-1 ||
                     ori.y+late[i].y > fil-1 ||
                     tab[ori.x][ori.y]                     != NEGRO ||
                     tab[ori.x+late[i].x][ori.y+late[i].y] != NEGRO)&&
                     te == ABAJO) return 2;
            else if( ori.x           < 0 ||
                     ori.x+late[i].x < 0 ||
                     ori.x           > col-1 ||
                     ori.x+late[i].x > col-1||
                     tab[ori.x][ori.y]                     != NEGRO ||
                     tab[ori.x+late[i].x][ori.y+late[i].y] != NEGRO) return 1;
        }
        return 0;
    }
    void rotar(){                       // Rota la pieza 90° hacia la derecha
        int prev;
        for(int i = 0; i<3; i++){
            prev      =  late[i].x;
            late[i].x = -late[i].y;
            late[i].y =  prev;
        }
    }
    void mover(){                       // Permite mover la pieza dependiendo de la accion con las teclas
        Cord mov, mov1[3];
        mov = ori;                                                              // Guardar posicion de origen
        for(int i = 0; i<3; i++) mov1[i] = late[i];                             //Guardar Posiciones relativas
        if(es >= 1000){
            te = ABAJO;
            es = 0;
        }
             if(te == ABAJO    ) ori.y++;
        else if(te == DERECHA  ) ori.x++;
        else if(te == IZQUIERDA) ori.x--;
             if(te == ESPACIO  ) rotar();

        if(choque() == 1){
            ori = mov;                                                          //Devolver a posicion guardada el origen
            for(int i = 0; i<3; i++) late[i] = mov1[i];                         //Devolver a posicion guardada las relativas
        }
        if(choque() == 2){
            ori = mov;                                                          //Devolver a posicion guardada el origen
            for(int i = 0; i<3; i++) late[i] = mov1[i];                         //Devolver a posicion guardada las relativas
            tab[ori.x][ori.y] = c;                                              //Guarda las coordenadas origen en el tablero
            for(int i = 0; i<3; i++) tab[late[i].x+ori.x][late[i].y+ori.y] = c; //Guarda las coordenadas relativas en el tablero
            ale2 = ale;
            teletransportar();
            aleatorio();
            ori = {col+6,6};                                                    //Devuelve la posicion origen de la pieza al inicio
        }
    }
};
// Inicializaciones
Pieza piezas[7] = {     { {col+6,6},{ {-1, 0},{ 1, 0},{ 0,-1} },MAGENTA  },   //T
                        { {col+6,6},{ { 1, 0},{ 1, 1},{ 0, 1} },AMARILLO },   //C
                        { {col+6,6},{ { 1, 0},{ 2, 0},{-1, 0} },CYAN     },   //I
                        { {col+6,6},{ { 0,-1},{ 1,-1},{-1, 0} },VERDE    },   //S
                        { {col+6,6},{ { 0,-1},{-1,-1},{ 1, 0} },ROJO     },   //Z
                        { {col+6,6},{ { 1, 0},{-1, 0},{ 1,-1} },BLANCO  },   //L
                        { {col+6,6},{ { 1, 0},{-1, 0},{-1,-1} },AZUL     } }; //J

void in_tab(){                          // Inicializa todo el juego
    nivel = 80;                         // Devuelve al primer nivel
    sc = 0;                             // Devuelve el puntaje a 0
    teletransportar();
    for(int i = 0; i<col; i++){         // Inicializar tablero con todo en NEGRO
        for(int j = 0; j<fil; j++){
            tab[i][j] = NEGRO;
        }
    }
}

string nombres[10];
int scores[10];
void guardarPuntaje(ofstream& os){
    for(int i = 0; i<10; i++){
        if(sc > scores[i]){
            for(int j = 9; j>i; j--){
                nombres[j]=nombres[j-1];
                scores[j]=scores[j-1];
            }
	mensaje("Escribe tu nombre en la consola");
            cin>> nombres[i];
            scores[i] = sc;
            i = 10;
        }
    }
    for(int i = 0; i<10; i++){
        os << nombres[i] << " ";
        os << scores[i] << '\n';
    }

}
void leerPuntaje(ifstream& is){
    for(int i = 0; i<10; i++){
        is >> nombres[i];
        is >> scores[i];
    }
}
void imprimirPuntaje(){
    borra();
    color(BLANCO);
    for(int i = 0; i<10; i++){
        d_text(vancho()/4,(valto()/11)*(i+1),nombres[i],4,valto()/100,2,1,1);
        d_text(vancho()-vancho()/4,(valto()/11)*(i+1),toString(scores[i]),4,valto()/100,2,1,1);
    }
}

// Funciones Principales
void teletransportar(){
    piezas[ale2].ori = {(int)(col/2),1};
}
void d_linea(){                         // Detecta cuando hay una linea llena
    for(int i = 0; i<fil; i++){
        for(int j = 0; j<col; j++)tem = (tem || (tab[j][i] == NEGRO));  // Mira si hay una pieza negra en cada fila
        if(!tem){                                                       // Si no, es porque la linea esta completa
            contfila++;                                                 // Determina cuantas filas se crean a la vez
            for(int j = 0; j<col; j++){
                tab[j][i] = NEGRO;                                      // Elimina la fila
                for(int k = i; k>=0; k--){
                    if(k == 0) tab[j][k] = NEGRO;
                    else tab[j][k] = tab[j][k-1];                       // Le da los valores de la fila anterior
                }
            }
        }else contfila = 0;
        sc += 40*contfila;                                              // Aumenta el puntaje con el combo dependiendo del contfila
        tem = false;
    }
}
void score(){                           // Muestra el puntaje que se lleva
    color(BLANCO);
    rectangulo(vancho()-105,75,vancho()-45,120);
    texto(vancho()-100, 80,"Puntaje: ");
    texto(vancho()-100,100,toString(sc));
}
void level(){                           // Muestra el puntaje que se lleva
    if(sc> 150 && sc<= 500)nivel = 100;  // Pasar a nivel    2
    if(sc> 500 && sc<=1000)nivel = 120;  //                  3
    if(sc>1000 && sc<=1500)nivel = 140;  //                  4
    if(sc>1500 && sc<=2000)nivel = 160;  //                  5
    if(sc>2000 && sc<=2500)nivel = 180;  //                  6
    if(sc>2500 && sc<=3000)nivel = 200;  //                  7
    if(sc>3000 && sc<=3500)nivel = 220;  //                  8
    if(sc>3500 && sc<=4000)nivel = 240;  //                  9
    if(sc>4000 && sc<=6000)nivel = 260;  //                  10

    color(BLANCO);
    rectangulo(vancho()-105,135,vancho()-45,180);
    texto(vancho()-100,140,"Nivel: ");
    texto(vancho()-100,160,toString((nivel/10-8)/2+1));
}
void atras(){
    d_text(vancho()-120,valto()-40, "Menu",4,5,1,0.7,0);
    if(raton_x() > vancho()-120 && raton_y() > valto()-40 &&
       raton_x() < vancho()- 10 && raton_y() < valto()-10 &&
       raton_boton_izq())te = ESCAPE;

}
void guardar_puntaje(){
    ifstream leerPuntajes ("puntajes.txt");
    leerPuntaje(leerPuntajes);
    imprimirPuntaje();
    ofstream nuevoPuntaje ("puntajes.txt");
    guardarPuntaje(nuevoPuntaje);
    leerPuntaje(leerPuntajes);
    imprimirPuntaje();
}
void inGame(){                          // Ciclo de juego
    do{
        te = tecla();
        tablero();
        piezas[ale].pintar();

        piezas[ale2].pintar();
        if(piezas[ale2].choque() == 2||piezas[ale2].choque() == 1){  // Detecta si al salir la pieza ya hay una en donde aparece
            mensaje("Game over");
            guardar_puntaje();
            main();
        }
        piezas[ale2].mover();
        es += nivel;                    // Se usa el modulador de tiempo para que cada 10 ms sume la velocidad dependiendo del nivel
        d_linea();
        score();
        level();
        atras();
        refresca();
        espera(10);
        borra();
    }while(te != ESCAPE);
}
void multijugador(){
}
void puntajes(){
    do{
        te = tecla();
        ifstream leerPuntajes ("puntajes.txt");
        leerPuntaje(leerPuntajes);
        imprimirPuntaje();
        refresca();
        espera(10);
        borra();
    }while(te != ESCAPE);
}
void creditos(){
    do{
        te = tecla();
        d_text(vancho()/2, (valto()/3)*0+60,"Sebastian Garnica",vancho()/130,valto()/130,5,0.8,1);
        d_text(vancho()/2, (valto()/3)*1+60,"Melinda Duran",vancho()/130,valto()/130,5,0.8,1);
        d_text(vancho()/2, (valto()/3)*2+60," Diego Ruiz",vancho()/130,valto()/130,5,0.8,1);
        refresca();
        espera(10);
        borra();
    }while(te != ESCAPE);
}

void opciones(){
    for(int i = 0; i<4;i++){
        color(BLANCO);
        rectangulo_lleno(vancho()/5,(valto()/6)*(i+2)-15,vancho()-vancho()/5,(valto()/6)*(i+3)-(valto()/14));
        color(AZUL);
        d_text(vancho()/2,(valto()/6)*(i+2),pal[i],vancho()/130,valto()/130,1,0.7,1);
    }
}
void seleccion(){
    bool s = true;
    while(s){
        ale = rand()%6+1;
        color(ale);
        d_text(vancho()/2,valto()/8,"tetris",vancho()/60,valto()/100,2,0.7,1);
        refresca();
        espera(200);
        for(int i = 0; i<4;i++){
            if(raton_x() > vancho()/5                       &&    //Detecta la seleccion del raton
               raton_y() > (valto()/6)*(i+2)-15             &&
               raton_x() < vancho()-vancho()/5              &&
               raton_y() < (valto()/6)*(i+3)-(valto()/14)   &&
               raton_boton_izq()){
                s = false;
                if(i == 0)inGame();
                if(i == 1) multijugador();
                if(i == 2) puntajes();
                if(i == 3) creditos();
            }
        }
        te = tecla();
        if(te == ESCAPE)s=false;
    }
}
void menu(){
    opciones();
    refresca();
}
int main(){
    vredimensiona(col*t+ancho_v,fil*t+alto_v);
    in_tab();
    do{
        menu();
        seleccion();
    }while(te != ESCAPE);
    if(pregunta("¿Seguro deseas salir?"))vcierra();//Acabar Juego
    else main();
    return 0;
}
