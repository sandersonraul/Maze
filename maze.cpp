#include <iostream> 
#include <utility>  
#include <string>   
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include "DisjSets.h"
#include <stack> 


int numeroAleatorio(int menor, int maior)
{
    return rand() % (maior - menor + 1) + menor;
}
// Utilizando código da internet
void drawMaze(int altura, int largura, unsigned char Maze[], unsigned char TopWall, unsigned char RightWall, unsigned char BottomWall, unsigned char LeftWall)
{
    system("clear");
    for (int i = 0; i < altura; i++)
    {
        for (int j = largura * i; j < largura * i + largura; j++)
        {
            if (Maze[j] & TopWall)
            {
                std::cout << "####";
            }
            else
            {
                std::cout << "#  #";
            }
        }
        std::cout << std::endl;
        for (int j = largura * i; j < largura * i + largura; j++)
        {
            if (Maze[j] & LeftWall)
            {
                std::cout << "# ";
            }
            else
            {
                std::cout << "  ";
            }
            if (Maze[j] & RightWall)
            {
                std::cout << " #";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
        for (int j = largura * i; j < largura * i + largura; j++)
        {
            if (Maze[j] & BottomWall)
            {
                std::cout << "####";
            }
            else
            {
                std::cout << "#  #";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    unsigned char TopWall = 1;
    unsigned char RightWall = 2;
    unsigned char BottomWall = 4;
    unsigned char LeftWall = 8;
    unsigned char celulasVisitadas = 16;
    unsigned char celulasErradas = 32; // arMazena os números embaralhados aleatoreamente
    int altura = 5;
    int largura = 5;
    bool valido = false; // indica se o labirinto será valido ou totalmente conexo



    // Utilizando código da internet
    if (argc > 4)
    {
        std::cout << "Há argumentos demais" << std::endl;
        return 0;
    }
    else if (argc == 4)
    {
        if (isdigit(argv[1][0]))
        {
            altura = atoi(argv[1]);
            if (isdigit(argv[2][0]))
            {
                largura = atoi(argv[2]);
                valido = true;
            }
            else
            {
                valido = true;
                largura = atoi(argv[3]);
            }
        }
        else
        {
            valido = true;
            altura = atoi(argv[2]);
            largura = atoi(argv[3]);
        }
    }
    else if (argc == 3)
    {
        if (isdigit(argv[1][0]))
        {
            altura = atoi(argv[1]);
            if (isdigit(argv[2][0]))
            {
                largura = atoi(argv[2]);
            }
            else
            {
                valido = true;
            }
        }
        else
        {
            valido = true;
            altura = atoi(argv[2]);
        }
    }
    else if (argc == 2)
    {
        if (isdigit(argv[1][0]))
        {
            altura = atoi(argv[1]);
        }
        else
        {
            valido = true;
        }
    }

    if (altura > 100 || largura > 100)
    {
        std::cout << "O limite das dimensões é 100 para a lagura e 100 para a altura" << std::endl;
        return 0;
    }

    int tamanho = altura * largura;
    DisjSets conjuntos(tamanho);
    unsigned char Maze[tamanho];
    for (int i = 0; i < (tamanho); i++)
    {
        Maze[i] = TopWall | RightWall | BottomWall | LeftWall;
        // preenche vetor v com os numeros de todas as celulas
    }
    Maze[0] &= ~LeftWall;            // apaga primeira parede
    Maze[tamanho - 1] &= ~RightWall; // apaga ultima parede

    // embaralha numeros do vetor v

    int randomCell = numeroAleatorio(0, tamanho - 1);
    unsigned char parede;
    //////////***********valido**************//////////////
    if (valido)
    {
        while (conjuntos.find(0) != conjuntos.find(tamanho - 1))
        {                                   // enquanto o conjunto da primeira casa for diferente do da última casa
            parede = numeroAleatorio(0, 3); // sorteia um numero entre 0 e 3, pra decidir qual parede quebrar
            switch (parede)
            {
            case 0: // TopWall
                if (randomCell > largura - 1)
                { // se tiver na primeira linha, nao quebra a parede de cima
                    if (Maze[randomCell] & TopWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell - largura))
                        {
                            Maze[randomCell] &= ~TopWall; // quebra a parede
                            Maze[randomCell - largura] &= ~BottomWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell - largura));
                        }
                    }
                }
                break;
            case 1: // RightWall
                if ((randomCell + 1) % largura != 0)
                { // se tiver na ultima coluna, nao quebra a parede de cima
                    if (Maze[randomCell] & RightWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell + 1))
                        {
                            Maze[randomCell] &= ~RightWall; // quebra a parede
                            Maze[randomCell + 1] &= ~LeftWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell + 1));
                        }
                    }
                }
                break;
            case 2:
                if (randomCell < tamanho - largura - 1)
                { // se tiver na ultima linha, nao quebra a parede de cima
                    if (Maze[randomCell] & BottomWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell + largura))
                        {
                            Maze[randomCell] &= ~BottomWall; // quebra a parede
                            Maze[randomCell + largura] &= ~TopWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell + largura));
                        }
                    }
                }
                break;
            case 3:
                if (randomCell % largura != 0)
                { // se tiver na primeira coluna, nao quebra a parede de cima
                    if (Maze[randomCell] & LeftWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell - 1))
                        {
                            Maze[randomCell] &= ~LeftWall; // quebra a parede
                            Maze[randomCell - 1] &= ~RightWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell - 1));
                        }
                    }
                }
                break;
            default:
                break;
            }

            // Desenha
            drawMaze(altura, largura, Maze, TopWall, RightWall, BottomWall, LeftWall);
            std::cout << "Qtd de conjuntos: " << conjuntos.size() << std::endl;
            usleep(100000);
        }
    }
    else
    {
        //////////*********totalmente conexo******/////////////
        randomCell = 0;
        // unsigned char parede;
        while (conjuntos.size() != 1)
        {                                   // enquanto não houver apenas um conjunto
            parede = numeroAleatorio(0, 3); // sorteia um numero entre 0 e 3, pra decidir qual parede quebrar
            switch (parede)
            {
            case 0: // TopWall
                if (randomCell > largura - 1)
                { // se tiver na primeira linha, nao quebra a parede de cima
                    if (Maze[randomCell] & TopWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell - largura))
                        {
                            Maze[randomCell] &= ~TopWall; // quebra a parede
                            Maze[randomCell - largura] &= ~BottomWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell - largura));
                        }
                    }
                }
                break;
            case 1: // RightWall
                if ((randomCell + 1) % largura != 0)
                { // se tiver na ultima coluna, nao quebra a parede de cima
                    if (Maze[randomCell] & RightWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell + 1))
                        {
                            Maze[randomCell] &= ~RightWall; // quebra a parede
                            Maze[randomCell + 1] &= ~LeftWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell + 1));
                        }
                    }
                }
                break;
            case 2:
                if ((randomCell) < tamanho - largura - 1)
                { // se tiver na ultima linha, nao quebra a parede de cima
                    if (Maze[randomCell] & BottomWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell + largura))
                        {
                            Maze[randomCell] &= ~BottomWall; // quebra a parede
                            Maze[randomCell + largura] &= ~TopWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell + largura));
                        }
                    }
                }
                break;
            case 3:
                if ((randomCell) % largura != 0)
                { // se tiver na primeira coluna, nao quebra a parede de cima
                    if (Maze[randomCell] & LeftWall)
                    { // A parede está intacta?
                        if (conjuntos.find(randomCell) != conjuntos.find(randomCell - 1))
                        {
                            Maze[randomCell] &= ~LeftWall; // quebra a parede
                            Maze[randomCell - 1] &= ~RightWall;
                            conjuntos.unir_altura(conjuntos.find(randomCell), conjuntos.find(randomCell - 1));
                        }
                    }
                }
                break;
            default:
                break;
            }

            // Desenha
            drawMaze(altura, largura, Maze, TopWall, RightWall, BottomWall, LeftWall);
            std::cout << "Qtd de conjuntos: " << conjuntos.size() << std::endl;
            usleep(100000);
            randomCell++;
            if (randomCell == (tamanho - 1))
            {
                randomCell = 0;
            }
        }
    }
    // Utilizando código da internet
    std::cout << "Digite f para enrandomCellrar a saída " << std::endl;
    char comando;
    std::cin >> comando;

    if (comando == 'f')
    {

        // backtracking
        std::stack<int> path; // pilha que armazena o caminho sendo percorrido

        int c = 0;    // armazena a posicao que esta sendo percorrida na matriz Maze
        path.push(c); // adiciona a posicao 0 na pilha
        Maze[c] |= celulasVisitadas;
        while (path.top() != tamanho - 1)
        {

            if (!(Maze[c] & RightWall) && !(Maze[c + 1] & celulasVisitadas))
            {        // se não tiver parede a direita e a direita ainda nao tiver sido percorrida
                c++; // posicao anda uma coluna
                path.push(c);
                Maze[c] |= celulasVisitadas; // marca essa posicao como percorrida
            }
            else if (!(Maze[c] & BottomWall) && !(Maze[c + largura] & celulasVisitadas))
            {                    // se nao tiver a parede de baixo e a celular de baixo ainda nao tiver sido percorrida
                c = c + largura; // posicao desce uma linha
                path.push(c);
                Maze[c] |= celulasVisitadas;
            }
            else if (!(Maze[c] & LeftWall) && !(Maze[c - 1] & celulasVisitadas))
            {              // se nao tiver a parede a esquerda e a esquerda nao tiver sido percorrida
                c = c - 1; // posicao volta uma coluna
                path.push(c);
                Maze[c] |= celulasVisitadas;
            }
            else if (!(Maze[c] & TopWall) && !(Maze[c - largura] & celulasVisitadas))
            { // se nao tiver a parede de cima e a celula de cima nao tiver sido percorrida
                c = c - largura;
                path.push(c);
                Maze[c] |= celulasVisitadas;
            }
            else if (!(Maze[c] & RightWall) && (Maze[c + 1] & celulasVisitadas) && !(Maze[c + 1] & celulasErradas))
            {
                Maze[c] |= celulasErradas;
                path.pop();
                c = c + 1;
            }
            else if (!(Maze[c] & BottomWall) && (Maze[c + largura] & celulasVisitadas) && !(Maze[c + largura] & celulasErradas))
            {
                Maze[c] |= celulasErradas;
                path.pop();
                c = c + largura;
            }
            else if (!(Maze[c] & LeftWall) && (Maze[c - 1] & celulasVisitadas) && !(Maze[c - 1] & celulasErradas))
            {
                Maze[c] |= celulasErradas;
                path.pop();
                c = c - 1;
            }
            else if (!(Maze[c] & TopWall) && (Maze[c - largura] & celulasVisitadas) && !(Maze[c - largura] & celulasErradas))
            {
                Maze[c] |= celulasErradas;
                path.pop();
                c = c - largura;
            }


            system("clear");
            // Desenha segunda opcao
            for (int i = 0; i < altura; i++)
            {
                for (int j = largura * i; j < largura * i + largura; j++)
                {
                    if (Maze[j] & TopWall)
                    {                        // se tem a parede de cima
                        std::cout << "####"; // desenha a parede de cima
                    }
                    else
                    {
                        std::cout << "#  #";
                    } // senao desenha apenas as diagonais
                }
                std::cout << std::endl;
                for (int j = largura * i; j < largura * i + largura; j++)
                {
                    if (Maze[j] & LeftWall)
                    {
                        if (Maze[j] & celulasErradas)
                        {
                            std::cout << "#*";
                        }
                        else if (Maze[j] & celulasVisitadas)
                        {
                            std::cout << "#@";
                        }
                        else
                        {
                            std::cout << "# ";
                        }
                    }
                    else
                    {
                        if (Maze[j] & celulasErradas)
                        {
                            std::cout << " *";
                        }
                        else if (Maze[j] & celulasVisitadas)
                        {
                            std::cout << " @";
                        }
                        else
                        {
                            std::cout << "  ";
                        }
                    }
                    if (Maze[j] & RightWall)
                    {
                        if (Maze[j] & celulasErradas)
                        {
                            std::cout << "*#";
                        }
                        else if (Maze[j] & celulasVisitadas)
                        {
                            std::cout << "@#";
                        }
                        else
                        {
                            std::cout << " #";
                        }
                    }
                    else
                    {
                        if (Maze[j] & celulasErradas)
                        {
                            std::cout << "* ";
                        }
                        else if (Maze[j] & celulasVisitadas)
                        {
                            std::cout << "@ ";
                        }
                        else
                        {
                            std::cout << "  ";
                        }
                    }
                }
                std::cout << std::endl;
                for (int j = largura * i; j < largura * i + largura; j++)
                {
                    if (Maze[j] & BottomWall)
                    {
                        std::cout << "####";
                    }
                    else
                    {
                        std::cout << "#  #";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            usleep(500000);
        }
    }

    return 0;
}
