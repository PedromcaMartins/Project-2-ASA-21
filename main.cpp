#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <list>

using namespace std;

// https://www.programiz.com/dsa/graph-bfs
class Node {
    int value;
    list<Node> parents;
    list<Node> children;
      public:
    Node (int value);
}

class Graph {
  int numVertices;
  list<Node>* adjLists;
  int* visited;

    public:
  Graph(int vertices);
  void addEdge(int src, int dest);
  void emptyArcosFilhos();
  bool dfs(int startVertex);
  void bfs(int startVertex); 
};

int v1;         //vertice cujos ancestrais devem ser calculados
int v2;         //vertice cujos ancestrais devem ser calculados
int n_vertices; //numero de vertices
int n_arcos;    //numero de arcos
Graph grafo;

/* protótipos */
int lerVerificarInputs();
int addToVerifyMap(int y, unordered_map<int, int> &arcos);

int main(){
    int temp = lerVerificarInputs();
    if (temp == -2){
        printf("0\n");
        return 0; //se a arvore geneologica e invalida

    } else if (temp == -1)
        return 0; //se o input está incorreto

    // elimina os arcos dos filhos de v1 e v2
    grafo.emptyArcosFilhos();

    grafo.visited = new int[grafo.numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = 0;
    grafo.bfs(v1);
    grafo.bfs(v2);




    return 0;
}

/* lê as variaveis globais necessárias para resolver o problema */
int lerVerificarInputs(){
    if (scanf("%d %d", &v1, &v2) == 1) //le os vertices v1 e v2
        return -1; //ERROR

    if (scanf("%d %d", &n_vertices, &n_arcos) == 1) //le numero de vertices e arcos
        return -1; //ERROR

    // lerArcos
    int x, y; //sendo que y é filho de x
    unordered_map<int, int> arcos;
    //inicializa o grafo
    Graph grafo (n_vertices);

    /* loop lê cada caminho, linha a linha */
    for (int i = 0; i < n_arcos; i++){
        // verifica a validade da árvore geneologica
        if (scanf("%d %d", &x, &y) == 1)
            return -1; //ERROR
        if (addToVerifyMap(y, arcos) == -1)
            return -2; //Arvore geneologica invalida

        //adiciona o arco ao grafo
        grafo.addEdge(x, y);
    }

    //verifica se o grafo é acíclico
    if (!grafo.dfs(1))
        return -2; //Arvore geneologica invalida

    return 0;
}

/* adiciona os vertices do arco ao mapa, para verificar a validade da arvore geneologica */
int addToVerifyMap(int y, unordered_map<int, int> &arcos){
    if (!arcos.count(y)) //se o mapa não contiver tiver y,
        arcos.insert(pair<int, int>(y, 1)); //adiciona-o com um progenitor
    else{ //senao,
        if (arcos.at(y) >= 2){ //se o vertice tiver mais que 2 progenitores,
            return -1; //arvore invalida
        }

        arcos.erase(y);
        arcos.insert(pair<int, int>(y, 2)); //adiciona o segundo progenitor
    }

    return 0; //arvore valida
}

Node::Node(int num){
    value = num;

}

Graph::Graph(int v) {
  numVertices = v;
  adjLists = new list<Node>[v];
}

// adiciona os arcos à estrutura do grafo
void Graph::addEdge(int src, int dest) {
  adjLists[src].push_back(dest);
}

bool Graph::dfs(int startVertex){
    int n;
    vector<int> color;
    vector<int> parent;
    color[startVertex] = 1;
    for (int u : adjLists[startVertex]) {
        if (color[u] == 0) {
            parent[u] = startVertex;
            if (Graph::dfs(u))
                return true;
        } else if (color[u] == 1) {
            return false;
        }
    }
    color[startVertex] = 2;
    return false;
}

void Graph::bfs(int starVertex){
    list<int> queue;

    visited[startVertex]++;
    queue.push_back(startVertex);

    list<int>::iterator i;

    while (!queue.empty()) {
        int currVertex = queue.front();
        queue.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
            int adjVertex = *i;
            if (visited[adjVertex] == 0) {
                visited[adjVertex]++;
                queue.push_back(adjVertex);
            }
            else if (visited[adjVertex] == 1){
                visited[adjVertex]++;
                queue.push_back(adjVertex);
            }
        }
    }
}

void Graph::emptyArcosFilhos(){
    if (adjLists[v1].size() != 0)
        adjLists[v1].erase();
    if (adjLists[v2].size() != 0)
        adjLists[v2].erase();
}
