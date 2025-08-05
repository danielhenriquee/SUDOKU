// Daniel Henrique da Silva, Gabriel Henrique da Silva, Jorge Luiz Siemann Pereira, Lucas dos Santos Luckow

#include <iostream>
#include <locale.h>
#include <time.h>
#define TAM 9
using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main() {
    #ifdef _WIN32
        system("chcp 65001 > nul"); // Para suportar acentos no terminal do Windows
    #endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(time(NULL));

    int menu, i, j, aleatorio, ganhou;
    int cont = 0, il; // cont é o contador de jogadas // il é varíavel utilizada para o índice de linhas da matriz jogo
    int aux, auxi, auxj; // Variáveis utilizadas na hora de criar a matriz jogo e depois para jogar o sudoku

    int principal[TAM][TAM] = { 4, 9, 5, 2, 8, 7, 3, 6, 1, 
                                7, 2, 8, 6, 1, 3, 4, 9, 5, 
                                3, 6, 1, 9, 5, 4, 7, 2, 8, 
                                6, 5, 3, 8, 4, 9, 2, 1, 7, 
                                9, 8, 4, 1, 7, 2, 6, 5, 3, 
                                2, 1, 7, 5, 3, 6, 9, 8, 4, 
                                1, 3, 2, 4, 6, 5, 8, 7, 9, 
                                5, 4, 6, 7, 9, 8, 1, 3, 2, 
                                8, 7, 9, 3, 2, 1, 5, 4, 6}; // Matriz principal
    int gabarito[TAM][TAM]; // Matriz gabarito
    int jogo[TAM][TAM]; // Matriz em que será o jogo
    
    do {
        cout << endl;
        cout << "                                                          ███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗\n"
                "                                                          ██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║\n"
                "                                                          ███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║\n"
                "                                                          ╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║\n"
                "                                                          ███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝\n"
                "                                                          ╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ \n\n\n\n";
        cout << "                                                                            1.  Jogar\n\n\n"
                "                                                                            2.  SOBRE\n\n\n"
                "                                                                            3.  SAIR\n\n\n\n";
        cin >> menu;

        switch (menu) {
        case 1: // Jogar
            system(CLEAR);
            aleatorio = rand() % 4 + 1; // Gera um número pseudo-aleatório de 1 a 4 para definir a matriz gabarito

            if (aleatorio == 1) { // Gera a matriz gabarito sem modificação
                for (i = 0; i < TAM; i++) {
                    for (j = 0; j < TAM; j++) {
                        gabarito[i][j] = principal[i][j];
                    }
                }
            } else if (aleatorio == 2) { // Gera a matriz gabarito transposta
                for (i = 0; i < TAM; i++) {
                    for (j = 0; j < TAM; j++) {
                        gabarito[i][j] = principal[j][i];
                    }
                }
            } else if (aleatorio == 3) { // Gera a matriz gabarito invertida por linha
                for (i = 0; i < TAM; i++) {
                    for (j = 0; j < TAM; j++) {
                        gabarito[8 - i][j] = principal[i][j];
                    }
                }
            } else if (aleatorio == 4) { // Gera a matriz gabarito invertida por coluna
                for (i = 0; i < TAM; i++) {
                    for (j = 0; j < TAM; j++) {
                        gabarito[i][8 - j] = principal[i][j];
                    }
                }
            }
    
            for (i = 0; i < TAM; i++) {
                for (j = 0; j < TAM; j++) {
                    jogo[i][j] = gabarito[i][j]; // Copia a matriz gabarito para a do jogo
                }
            }
    
            for (aux = 0; aux < 40;) {
                auxi = rand() % 9; // Gera um número pseudo-aleatório de 0 a 8 para definir coordenada linha
                auxj = rand() % 9; // Gera um número pseudo-aleatório de 0 a 8 para definir coordenada coluna
                if (jogo[auxi][auxj] > 0) { // Confere se o valor já foi zerado
                    aux++;
                }
                jogo[auxi][auxj] = 0; // Zera o valor
            }
    
            ganhou = 40;
            do { // Começo do jogo em si, quando o usuário começa a interagir
                il = 1;
                cout << "Contador de jogadas: " << cont << endl << endl;
                cout << " 1 2 3  4 5 6  7 8 9  \n"; // Printa o índice de colunas antes do loop que printa a matriz jogo
                cout << "╔══════╦══════╦═════╗\n"; // Printa essa borda antes do loop que printa a matriz jogo
                for (i = 0; i < TAM; i++) {
                    if (i == 3 || i == 6 ) // Printa essa linha após a 3ª e a 6ª linha da matriz
                        cout << "╠══════╬══════╬═════╣\n";
                    for (j = 0; j<TAM; j++) {
                        if (j % 3 == 0) { // Printa essa coluna a cada 3 colunas
                            cout << "║"; 
                        }
                        if (jogo[i][j] == 0 && j != 8) { // Se o valor for 0, printa vazio com espaço depois
                            cout << "  ";
                        } else if (jogo[i][j] == 0 && j == 8) { // Se o valor for 0 na última coluna, printa vazio sem espaço depois
                            cout << " ";
                        } else if (jogo[i][j] != 0 && j < 8) { // Se tiver valor e não for a último coluna, printa o valor com espaço depois
                            cout <<jogo[i][j] << " ";
                        } else { // Printa o valor sem o espaço depois (última coluna)
                            cout << jogo[i][j]; 
                        }
                    }
                    cout << "║ " << il << endl; // Após cada fim da linha, printa a ║ como borda e pula a linha
                    il++;
                }
                cout << "╚══════╩══════╩═════╝\n\n"; // Após o loop que printa a matriz jogo, printa essa linha no final
                
                cout << "Digite a linha que quer preencher...";
                cin >> auxi;
                cout << "Digite a coluna que quer preencher...";
                cin >> auxj;
                cout << "Digite o valor que quer preencher...";
                cin >> aux;
                system(CLEAR);
            
                if (aux == gabarito[auxi - 1][auxj - 1] && jogo[auxi - 1][auxj - 1] == 0) { // Confere se o valor é válido em posição não preenchida
                    jogo[auxi - 1][auxj - 1] = aux;
                    ganhou--; // Esse valor começa em 40 que é a quantidade de valores que falta descobrir, ele vai diminuindo, quando chega a zero ganha
                    cout << "Você acertou um valor!\n\n";
                } else if ((auxi < 1 || auxi > 9 || auxj < 1 || auxj > 9) && (aux < 1 || aux > 9)) { // Confere se a posição é inválida E o valor é inválido
                    cout << "Você digitou uma posição inválida e também um valor inválido! Digite apenas números naturais de 1 até 9.\n\n";
                } else if (auxi < 1 || auxi > 9 || auxj < 1 || auxj > 9) { // Confere se a posição é inválida
                    cout << "Você digitou uma posição inválida! Digite um número natural de 1 até 9.\n\n";
                } else if (jogo[auxi - 1][auxj - 1] > 0) { // Confere se a posição já foi preenchida
                    cout << "Esta posição já foi preenchida!\n\n";
                } else if (aux < 1 || aux > 9) { // Confere se o valor é inválido
                    cout << "Você digitou um valor inválido! Digite um número natural de 1 até 9.\n\n";
                } else if (aux != gabarito[auxi - 1][auxj - 1] && jogo[auxi - 1][auxj - 1] == 0) { // Confere se o valor é incorreto
                    cout << "Você digitou um valor incorreto!\n\n";
                }
            
                cont++; // Aumenta a variável contador a cada tentativa
            
            } while (ganhou > 0);
    
            system(CLEAR);
            cout << "                                                 ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗  ██╗██╗██╗\n"
                    "                                                 ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║  ██║██║██║\n"
                    "                                                  ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║  ██║██║██║\n"
                    "                                                   ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║  ╚═╝╚═╝╚═╝\n"
                    "                                                    ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║  ██╗██╗██╗\n"
                    "                                                    ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝  ╚═╝╚═╝╚═╝\n\n\n\n";
    
            cout << "Você precisou de " << cont << " jogadas para completar o sudoku.\n";
            cout << "Digite qualquer tecla para voltar ao menu...\n";
            cont = 0; // Zera o contador de jogadas
            cin.ignore();
            cin.get();
            system(CLEAR);
            break;
        
        case 2: // Sobre
            system(CLEAR);
            cout << "\nDesenvolvedores:    Daniel Henrique da Silva\n"
                    "                    Gabriel Henrique da Silva\n"
                    "                    Jorge Luiz Siemann Pereira\n"
                    "                    Lucas dos Santos Luckow\n\n"
                    "Professor:          Prof. Rafael Ballotin Martins\n"
                    "Matéria:            Algoritmos e Programação\n"
                    "Maio/2023\n\n";
            cout << "Digite qualquer tecla para voltar ao menu\n";
            cin.ignore();
            cin.get();
            system(CLEAR);
            break;

        case 3: // Sair
            break;
        } // Fecha o switch

        system(CLEAR); // Limpa tudo antes de voltar ao menu
    } while (menu != 3); // Fecha o loop do jogo
    return 0;
}
