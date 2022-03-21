#include<iostream>
#include"DisjSets.h"
#include <stack>
#include <utility>    
#include <random>     
#include <string>     
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
int numeroAleatorio(int menor, int maior) {
       return rand()%(maior-menor+1) + menor;
}
int main (int argc, char** argv){
    unsigned char TopWall = 1;
    unsigned char RightWall = 2;
    unsigned char BottomWall = 4;
    unsigned char LeftWall = 8;
    unsigned char trackedPath = 16;
    unsigned char wrongTrackedPath = 32;
    std::vector<int> v; //arMazena os números embaralhados aleatoreamente
    int altura=10;
    int largura=10;
    bool valido=false; //indica se o labirinto será valido ou totalmente conexo

     int tamanho=altura * largura;
    DisjSets conjuntos(tamanho);
    unsigned char Maze[ tamanho];
        for ( int i=0; i < (tamanho); i++ ){
            Maze[ i ] = TopWall | RightWall | BottomWall | LeftWall;
            v.push_back(i); //preenche vetor v com os numeros de todas as celulas
        }
        Maze[0] &= ~LeftWall; //apaga primeira parede
        Maze[tamanho-1] &= ~RightWall; //apaga ultima parede
}

