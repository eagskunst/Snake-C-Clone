//Juego simple: Snake.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define V 21
#define H 65
#define N 100

typedef struct{
	int x,y;
	int ModX,ModY;
	char imagen;
}snk;

typedef struct{
	int x,y;
}frt;

snk snake[N];
frt fruta;

void inicio(int *tam, char campo[V][H]);
void Intro_campo(char campo[V][H]);
void Intro_datos(char campo[V][H], int tam);
void draw(char campo[V][H]);
void loop (char campo[V][H], int tam);
void input(char campo[V][H], int *tam,int *muerto);
void update(char campo[V][H],int tam);
void Intro_datos2(char campo[V][H], int tam);

int main (){
	
	int tam;
	char campo[V][H];
	
	inicio(&tam,campo); //Iniciar todos nuestros elementos
	system("pause");
	loop(campo,tam);
	
	system("pause");
	return 0;
}

void inicio(int *tam, char campo[V][H]){
	int i;
	
	//La cabeza de nuestra serpiente
	snake[0].x = 32;
	snake[0].y = 10;
	
	//Tamaño de la serpiente
	
	*tam = 4;
	
	//Posicion de la fruta
	
	srand(time(NULL));
	
	fruta.x = rand() % (H-1);
	fruta.y = rand() % (V-1);
	
	while(fruta.x == 0){
		fruta.x = rand() % (H-1);
	}
	
	while(fruta.y == 0){
		fruta.y = rand() % (V-1);
	}
	
	for(i = 0;i < *tam;i++){
		snake[i].ModX = 1;
		snake[i].ModY = 0;
	}
	
	Intro_campo(campo);
	Intro_datos(campo,*tam);
	
}

//Creacion del campo de juego
void Intro_campo(char campo[V][H]){
	int i,j;
	
	for(i = 0;i < V; i++){
		for(j = 0;j < H; j++){
			if (i == 0 || i == V-1){
				campo[i][j] = '=';
			}
			else if(j == 0 || j == H-1){
				campo[i][j] = '|';
			}
			else{
				campo[i][j] = ' ';
			}
		}
	}
}

//Metera todos los datos en la matriz campo
void Intro_datos(char campo[V][H], int tam){
	int i;
	char key;
	
	for(i = 1;i < tam; i++){
		snake[i].x = snake[i-1].x - 1;
		snake[i].y = snake[i-1].y;
		
		snake[i].imagen = 'X';
	}
	
	snake[0].imagen = 1;
	
	for(i = 0;i < tam; i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}

void draw(char campo[V][H]){
	int i,j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
	
}

void loop (char campo[V][H], int tam){
	int dead;
	
	dead = 0;
	
	do{
		system("cls");
		draw(campo);
		input(campo,&tam,&dead);
		update(campo,tam);
	}while (dead == 0);
}

void input(char campo[V][H], int *tam,int *muerto){
	int i;
	char key;
	
	//Comprobación en caso de morir
	
	if(snake[0].x == 0 || snake[0].x == H-1 || snake[0].y == 0 || snake[0].y == V-1){
		*muerto = 1;
	}
	
	for(i = 1;i<*tam && *muerto == 0;i++){
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
			*muerto = 1;
		}
	}
	
	//Comprobar si nos hemos comido la fruta
	
	if(snake[0].x == fruta.x && snake[0].y == fruta.y){
		*tam += 1;
		snake[*tam-1].imagen = 'X';
		
		fruta.x = rand() % (H-1);
		fruta.y = rand() % (V-1);
	
		while(fruta.x == 0){
			fruta.x = rand() % (H-1);
		}
	
		while(fruta.y == 0){
			fruta.y = rand() % (V-1);
		}
	}
	
	if(*muerto == 0){
		if(kbhit() == 1){
			key = getch();
			
			if (key == 's' && snake[0].ModY != -1){
				snake[0].ModX = 0;
				snake[0].ModY = 1;
			}
			
			if (key == 'w' && snake[0].ModY != 1){
				snake[0].ModX = 0;
				snake[0].ModY = -1;
			}
			if (key == 'a' && snake[0].ModX != 1 ){
				snake[0].ModX = -1;
				snake[0].ModY = 0;
			}
			if(key == 'd' && snake[0].ModX != -1){
				snake[0].ModX = 1;
				snake[0].ModY = 0;
			} 
		}
	}
}

void update(char campo[V][H],int tam){
	//Borrar datos de la matriz
	
	Intro_campo(campo);
	
	//Introducir los nuevos datos:
	
	Intro_datos2(campo,tam);
}

void Intro_datos2(char campo[V][H], int tam){
	int i,j;
	
	//Crear la persecusión de los elementos del cuerpo
	
	for(i = tam-1; i > 0 ; i--){
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	
	snake[0].x += snake[0].ModX;
	snake[0].y += snake[0].ModY;
	
	for(i = 0; i< tam; i++){
		campo[snake[i].y][snake[i].x] = snake[i].imagen;
	}
	
	campo[fruta.y][fruta.x] = '%';
}
