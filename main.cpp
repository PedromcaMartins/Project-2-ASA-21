#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

int v1;         //vertice cujos ancestrais devem ser calculados
int v2;         //vertice cujos ancestrais devem ser calculados
int n_vertices; //numero de vertices
int n_arcos;    //numero de arcos

/* protótipos */
int lerVariaveisGlobais();
int lerArcos();
int addToVerifyMap(int y, unordered_map<int, int> &arcos);

int main(){
    assert(lerVariaveisGlobais() != 1);

    //if lerArcos retornar -1, a arvore geneologica e invalida
    if (lerArcos() == 1){
        printf("0");
        return 0;
    }

    return 0;
}

/* lê as variaveis globais necessárias para resolver o problema */
int lerVariaveisGlobais(){
    if (scanf("%d %d", &v1, &v2) == 1) //le os vertices v1 e v2
        return -1; //ERROR

    if (scanf("%d %d", &n_vertices, &n_arcos) == 1) //le numero de vertices e arcos
        return -1; //ERROR

    return 0;
}

/* lê e verifica todos os arcos lidos */
int lerArcos(){
    int x, y; //sendo que y é filho de x
    unordered_map<int, int> arcos;

    /* loop lê cada caminho, linha a linha e verifica,
    usando um mapa, a validade da árvore que este representa */
    for (int i = 0; i < n_arcos; i++){
        if (scanf("%d %d", &x, &y) == 1)
            return -1; //ERROR
        if (addToVerifyMap(y, arcos) == -1)
            return -1; //Arvore geneologica invalida

        //TODO: adicionar uma maneira de guardar os valores do input (o mapa apenas verifica - os)
    }

    return 0;
}

/* adiciona os vertices do arco ao mapa, para verificar a validade da arvore geneologica */
int addToVerifyMap(int y, unordered_map<int, int> &arcos){
    if (arcos.count(y) == 0) //se o mapa não contiver tiver y,
        arcos.insert(y, 1); //adiciona-o com um progenitor
    else{ //senao,
        if (arcos.at(y) >= 2) //se o vertice tiver mais que 2 progenitores,
            return -1; //arvore invalida

        arcos.insert(y, 2); //adiciona o segundo progenitor
    }

    return 0; //arvore valida
}