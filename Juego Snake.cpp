#include <iostream>
#include<windows.h>
#include<conio.h>
#include <cstdio>
#include <cstdlib>

// para declarar la variable sleep
#include<unistd.h>

// usuario y contraseña
#define USER "Usuario"
#define PASS "Clave"

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
#include <string>

int cuerpo[200][2];
int n = 1;
int tam = 3;
int x =10, y = 12;
int dir = 3;
int xc = 30, yc = 15;
int velocidad = 100, h = 1;
int score = 0;

char tecla;

void gotoxy(int x, int y)//funcion que posiciona el cursos en la coordenada (x,y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

void pintar(){
	system("color 17");
	//lineas horizontales
	for(int i= 2 ; i < 78 ; i++){
		gotoxy(i,3);
		printf("%c",205);
		gotoxy(i,23);
		printf("%c",205);
	}
	//lineas verticales
	for (int i = 4 ; i < 23 ; i++){
		gotoxy(2,i);
		printf("%c",186);
		gotoxy(77,i);
		printf("%c",186);
	}
	//esquinas
	gotoxy(2,3);printf("%c",201);
	gotoxy(2,23);printf("%c",200);
	gotoxy(77,3);printf("%c",187);
	gotoxy(77,23);printf("%c",188);
	system("color 17");
}

void guardar_posicion(){
	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;
	if ( n == tam) n = 1;
}

void dibujar_cuerpo(){
	for (int i = 1 ; i < tam ; i++){
		gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("+");
	}
}

void borrar_cuerpo(){
	//for (int i = 1 ; i < tam ; i++){
	//gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf(" ");
	gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");
	//}
}

void teclear(){
	if (kbhit()){
		tecla = getch();
		switch(tecla){
		case ARRIBA :
			if(dir != 2)
			dir = 1;
			break;
		case ABAJO :
			if(dir != 1)
			dir = 2;
			break;
		case DERECHA :
			if(dir != 4)
			dir = 3;
			break;
		case IZQUIERDA :
			if(dir != 3)
			dir = 4;
			break;
		}
	}
}

//Para cambiar la velocidad
void cambiar_velocidad(){
	if(score == h*2){
		velocidad -= 1;
		h++;
	}
}

void comida(){
	if(x == xc && y == yc){
		xc = (rand()%73)+4; //79 es la coordenada para que no se pase del marco
		yc = (rand()%19)+4; //19 es la coordenada para que no se pase del marco

		tam ++;
		score += 10;
		gotoxy(xc,yc);
		printf("%c",4);
		cambiar_velocidad();
	}
}

bool game_over(){
	if( y == 3 || y == 23 || x == 2 || x == 77) return false;//condicional si choca con los margenes
	for( int j = tam -1 ; j > 0 ; j--){
		if(cuerpo[j][0] == x && cuerpo[j][1] == y)
			return false;
	}
	return true;
}

void puntos(){
	gotoxy(3,1); printf("score %d", score);
	gotoxy(20,1); printf("Bienvenido al juego SNAKE");
}

using namespace std;

int main(int argc, char *argv[]) {
	system("color 17");
	string clave ;
	string user;
	char ch;
	int num=3;

	for (int i = 1; i<=num; i++){
		cout<<"\nOportunidad "<<i<<" de 3";
		cout<<"\n\nIngrese su nombre de usuario: ";
		cin>>user;
		cout<<"\n\nIngrese clave: ";
		ch = _getch();

        //Para musica, la libreria (-lwinmm) se debe agregar para el sonido de la musica
		char soundfile[] = "D:\Snake\Alan-Walker-Fade.wav";
		cout<<PlaySound((LPCSTR)soundfile, NULL, SND_FILENAME | SND_ASYNC);

		while(ch != 13){

			clave.push_back(ch);
			cout<<'*';
			ch = _getch();

		}
		if(user == "prueba" && clave == "123"){
			cout<<"\n\nBienvenido "<<user<<" acceso correcto!\n\n";
			num = 0; //si la contra y user son correctos entonces para
			// que el bucle se rompa al ser correcto
			getch();
			system("cls");

			pintar();
			gotoxy(xc,yc);
			printf("%c",4);
			while(tecla != ESC && game_over()){
				borrar_cuerpo();
				guardar_posicion();
				dibujar_cuerpo();
				comida();
				puntos();
				//x++;
				teclear();
				teclear();
				if(dir == 1) y--;
				if(dir == 2) y++;
				if(dir == 3) x++;
				if(dir == 4) x--;
				Sleep(velocidad);
			}
			gotoxy(20,24);
			system("pause>NULL");
			/*system("cls");*/
		}
		else{
			cout<<"\n\nError datos incorrectos, intente otra vez \n\n";
			clave="";
			//ch="";
			user="";
		}
	}
	return 0;
}

