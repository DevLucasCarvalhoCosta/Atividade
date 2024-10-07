#include <iostream>
#include <sstream>
#include <list>
#include <time.h>
using namespace std;

class Jogada{
    friend class JogoVelha;
    int jogador;
    int linha;
    int coluna;
    Jogada(int Jogador, int Linha, int Coluna){
        if (Jogador > 2 || Jogador < 1){throw "Dados Inválidos!";}
        if (Linha < 0 || Linha > 2){throw "Dados Inválidos!";}
        if (Coluna < 0 || Coluna > 2){throw "Dados Inválidos!";}
        jogador = Jogador;
        linha = Linha;
        coluna = Coluna;
    }
    string ToString(){
        stringstream ss;
        ss << "Jogador " << jogador << ": {" << linha << ", " << coluna << "}";
        return ss.str();
    }
};

class JogoVelha{
    int jogo[3][3];
    int computador;
    int humano;
    list<Jogada*> jogadas;
public:
    JogoVelha(int Computador=1){
        if (Computador > 2 || Computador < 1){throw "O jogador pode ser 1 ou 2";}
        computador = Computador;
        if (computador == 1){
            humano = 2;
        }else{
            humano = 1;
        }
        for(int l=0; l<3; l++){
            for(int c=0;c<3;c++){
                jogo[l][c]=0;
            }
        }
        if(computador == 1){
            JogaCompuptador();
        }else{
            JogaHumano();
        }
    }
    void Mostra(){
        system("cls");
        cout << endl << "  0 1 2"<< endl;
        for(int l=0; l<3; l++){
            if (l==0){
                cout << " " << char(218) << char(196) << char(194) << char(196) << char(194) << char(196) << char(191)<< endl;
            }else if(l == 1){
                cout << " " << char(195) << char(196) << char(197) << char(196) << char(197) << char(196) << char(180) << endl;
            }else{
                cout << " " << char(195) << char(196) << char(197) << char(196) << char(197) << char(196) << char(180) << endl;
            }
            cout << l;
            for(int c=0;c<3;c++){
                char car = ' ';
                if (jogo[l][c] == 1){car = 'X';}
                if (jogo[l][c] == 2){car = 'O';}
                cout << char(179) << car;
            }
            cout << char(179) << endl;
        }
        cout << " " << char(192) << char(196) << char(193) << char(196) << char(193) << char(196) << char(217) << endl;
    }
private:
    void RegistraJogada(Jogada* j) {
        // Preenche a jogada na matriz
        jogo[j->linha][j->coluna] = j->jogador;
        // Adiciona a jogada na lista de jogadas
        jogadas.push_back(j);
    }

    bool EstaCheia() {
        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                if (jogo[l][c] == 0) {
                    return false; // Ainda há espaço vazio
                }
            }
        }
        return true; // Todos os espaços estão preenchidos
    }

    int Ganhador() {
        // Verificar linhas
        for (int l = 0; l < 3; l++) {
            if (jogo[l][0] != 0 && jogo[l][0] == jogo[l][1] && jogo[l][1] == jogo[l][2]) {
                return jogo[l][0];
            }
        }

        // Verificar colunas
        for (int c = 0; c < 3; c++) {
            if (jogo[0][c] != 0 && jogo[0][c] == jogo[1][c] && jogo[1][c] == jogo[2][c]) {
                return jogo[0][c];
            }
        }

        // Verificar diagonais
        if (jogo[0][0] != 0 && jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2]) {
            return jogo[0][0];
        }
        if (jogo[0][2] != 0 && jogo[0][2] == jogo[1][1] && jogo[1][1] == jogo[2][0]) {
            return jogo[0][2];
        }

        // Se a matriz está cheia e não há ganhador, retorna empate
        if (EstaCheia()) {
            return -1;
        }

        // Jogo continua
        return 0;
    }

    void JogaHumano() {
        int linha, coluna;
        cout << "Sua vez! Informe a linha e coluna: ";
        cin >> linha >> coluna;

        try {
            Jogada* jogada = new Jogada(humano, linha, coluna);
            RegistraJogada(jogada);
        } catch (const char* msg) {
            cout << msg << endl;
            JogaHumano(); // Repetir a jogada se houver erro
        }

        // Verifica se há ganhador após a jogada
        int ganhador = Ganhador();
        if (ganhador != 0) {
            Encerra(ganhador);
        } else {
            JogaCompuptador();
        }
    }

    void JogaCompuptador() {
        list<Jogada*> possibilidades = Possibilidades();
        Jogada* jogada = Escolha(possibilidades);

        RegistraJogada(jogada);

        // Verifica se há ganhador após a jogada
        int ganhador = Ganhador();
        if (ganhador != 0) {
            Encerra(ganhador);
        } else {
            JogaHumano();
        }
    }

    Jogada* Escolha(list<Jogada*> lista) {
        // Estratégia simples: escolha aleatória de uma das possibilidades
        list<Jogada*>::iterator it = lista.begin();
        advance(it, rand() % lista.size());
        return *it;
    }

    list<Jogada*> Possibilidades() {
        list<Jogada*> possibilidades;

        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                if (jogo[l][c] == 0) {
                    possibilidades.push_back(new Jogada(computador, l, c));
                }
            }
        }

        return possibilidades;
    }

    void Encerra(int ganhador=0){
        Mostra();
        if (ganhador == humano){
            cout << endl << "###   O GANHADOR Foi:  VOCE!!!!!!   ###"<< endl;
        }else if (ganhador == computador){
            cout << endl << "###   SE LASCOU!!!!!   ###"<< endl;
        }else{
            cout << endl << "###   CONSEGUIU EMPATAR HEIN!!!!   ###"<< endl;
        }
        cout << endl << "###   Fim do jogo   ###"<< endl;
        exit(0);
    }
};
