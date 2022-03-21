#include <iostream>
#include <DisjSets.h>
using namespace std;

explicit DisjSets(int tamanho){
      for(int i=0;i<tamanho;i++){
        vetor.push_back(i);
      }
    }

    int find(int x){
         if(vetor[x]<0){
      return x;
    }else{
      return find(vetor[x]);
    }
    }

    void unir_altura(int raiz1, int raiz2){
     if(vetor[raiz2] < vetor[raiz1]){
       vetor[raiz1] = raiz2;     
     }else{
       if(vetor[raiz1] == vetor[raiz2]){
         vetor[raiz1] = vetor[raiz1] -1;
       }
       vetor[raiz2] = raiz1;
     }

     int size(){
       vector<int> vetctor_conjuntos;
        bool verifica ;
        int pai;
        int tamanho =0;
        for (int i =0;i<vetor.size();i++){
             pai=this->find(i);
             verifica = false;
             for(int j=0;j<vector_conjuntos.size();j++){
               if(pai == vector_conjuntos.at(j)){
                    verfica = true;
                    break;
               }

               if(verica == false){
                 vector_conjuntos.push_back(pai);
                 tamanho++;
               }
             }
        }
        return tamanho;
     }

     private:
      vector<int> vetor;
   }
    
