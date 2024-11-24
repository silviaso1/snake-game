#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int largura = 40;
const int altura = 40;
int x, y, frutaX, frutaY, pontuacao;
int caudaX[100], caudaY[100];
int tamanhoCauda;
enum eDirecao { PARADO = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
eDirecao direcao;

void setup() {
    gameOver = false;
    direcao = PARADO;
    x = largura / 2;
    y = altura / 2;
    frutaX = rand() % largura;
    frutaY = rand() % altura;
    pontuacao = 0;
    tamanhoCauda = 0;
}

void desenhar() {
    system("cls"); 

    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;


    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O"; 
            else if (i == frutaY && j == frutaX)
                cout << "F"; 
            else {
                bool printar = false;
                for (int k = 0; k < tamanhoCauda; k++) {
                    if (caudaX[k] == j && caudaY[k] == i) {
                        cout << "o"; 
                        printar = true;
                    }
                }
                if (!printar)
                    cout << " ";
            }

            if (j == largura - 1)
                cout << "#"; 
        }
        cout << endl;
    }


    for (int i = 0; i < largura + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Pontuacao: " << pontuacao << endl;
}

void entrada() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (direcao != DIREITA) direcao = ESQUERDA;
            break;
        case 'd':
            if (direcao != ESQUERDA) direcao = DIREITA;
            break;
        case 'w':
            if (direcao != BAIXO) direcao = CIMA;
            break;
        case 's':
            if (direcao != CIMA) direcao = BAIXO;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void logica() {
    int prevX = caudaX[0];
    int prevY = caudaY[0];
    int prev2X, prev2Y;
    caudaX[0] = x;
    caudaY[0] = y;
    for (int i = 1; i < tamanhoCauda; i++) {
        prev2X = caudaX[i];
        prev2Y = caudaY[i];
        caudaX[i] = prevX;
        caudaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direcao) {
    case ESQUERDA:
        x--;
        break;
    case DIREITA:
        x++;
        break;
    case CIMA:
        y--;
        break;
    case BAIXO:
        y++;
        break;
    default:
        break;
    }


    if (x >= largura || x < 0 || y >= altura || y < 0)
        gameOver = true;


    for (int i = 0; i < tamanhoCauda; i++)
        if (caudaX[i] == x && caudaY[i] == y)
            gameOver = true;


    if (x == frutaX && y == frutaY) {
        pontuacao += 10;
        frutaX = rand() % largura;
        frutaY = rand() % altura;
        tamanhoCauda++;
    }
}

void menu() {
    char escolha;
    cout << "\nFim de jogo! Sua pontuacao foi: " << pontuacao << endl;
    cout << "Deseja jogar novamente? (s/n): ";
    cin >> escolha;
    if (escolha == 's' || escolha == 'S') {
        setup(); 
    } else {
        cout << "Obrigado por jogar!\n";
        exit(0); 
    }
}

int main() {
    setup();
    while (true) {
        while (!gameOver) {
            desenhar();
            entrada();
            logica();
            Sleep(100); 
        }
        menu();
    }
    return 0;
}

