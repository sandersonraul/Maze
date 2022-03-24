/**
 * Disjoint set class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */

#include <vector>
#include <iostream>
using namespace std;

class DisjSets
{
public:
  // Generates the disjoint sets, one for each element.
  explicit DisjSets(int tamanho)
  {
    for (int i = 0; i < tamanho; i++)
    {
      vetor.push_back(i);
    }
  }

  // acha apenas o pai
  // int find(int x) const
  // {
  //   if (vetor[x] < 0)
  //   {
  //     return x;
  //   }
  //   else
  //   {
  //     return find(vetor[x]);
  //   }
  // }

  int find(int x)
  {
    int aux;
    aux = x;
    while (vetor.at(aux) != aux)
    {
      aux = vetor.at(aux); // aux vai armazenar o pai do conjunto
    }
    int aux2;
    while (vetor.at(x) != x)
    {
      aux2 = x;
      x = vetor.at(x);
      vetor.at(aux2) = aux; // todos vao apontar pro pai do conjunto
    }
    return aux;
  }
  // Return set's name containing x, with path compression.

  // Merge two sets, by size or by estimated heigh (also knwon as rank).
  void unir_altura(int raiz1, int raiz2)
  {
    if (vetor[raiz2] < vetor[raiz1])
    {
      vetor[raiz1] = raiz2;
    }
    else
    {
      if (vetor[raiz1] == vetor[raiz2])
      {
        vetor[raiz1] = vetor[raiz1] - 1;
      }
      vetor[raiz2] = raiz1;
    }
  }

  // Return the current number of disjoint sets
  int size()
  {
    vector<int> vector_conjuntos;

    int pai;
    int tamanho = 0;
    bool verifica;
    for (int i = 0; i < vetor.size(); i++)
    {
      pai = this->find(i);
      verifica = false;
      for (int j = 0; j < vector_conjuntos.size(); j++)
      {
        if (pai == vector_conjuntos.at(j))
        {
          verifica = true;
          break;
        }
      }

      if (verifica == false)
      {
        vector_conjuntos.push_back(pai);
        tamanho++;
      }
    }

    return tamanho;
  }

private:
  vector<int> vetor;
};
