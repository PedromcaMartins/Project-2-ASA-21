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

class Node {
    int value;
    Node* parent1;
    Node* parent2;
    list<Node*>* children;
    int times_visited;
    int aux_counter;

      public:
    Node (int value);
    //setters
    int setParent(Node* p1);
    void setChild(Node* c);
    //getters
    Node* getParent1();
    Node* getParent2();
    list<Node*> getChildren();

};

class Graph {
  list<Node*>* vertices;
    public:
  Graph();
  void addVertice();
  void emptyArcosFilhos();
  bool dfs(int startVertex);
  void bfs(int startVertex); 
};

int v1;         //vertice cujos ancestrais devem ser calculados
int v2;         //vertice cujos ancestrais devem ser calculados
int n_vertices; //numero de vertices
int n_arcos;    //numero de arcos
Graph grafo;
Node node;

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
    /*grafo.emptyArcosFilhos();*/

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
    Graph grafo ();

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
    times_visited = 0;
    aux_counter = 0;
    children = new list<Node*>();
}

Node::setParent(Node* p){
    
}

Graph::Graph() {
  vertices = new list<Node*>[n_vertices + 1];
}

// adiciona os arcos à estrutura do grafo
void Node::addEdge(int src, int dest) {
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

void Graph::bfs(Node v){
    list<Node> queue;

    v.times_visited++;
    queue.push_back(v);

    list<Node>::iterator i;

    while (!queue.empty()) {
        Node currVertex = queue.front();
        queue.pop_front();

        for (i = currVertex.parents.begin(); i != currVertex.parents.end(); ++i) {
            if (i.times_visited == 0) {
                i.times_visited++;
                queue.push_back(i);
            }
            else if (i.times_visited == 1){
                i.times_visited++;
                if (i.aux_counter == 0)
                    grafo.push_back(i.value);
                if ()
                
                queue.push_back(adjVertex);
            }
        }
    }
}

/*void Graph::emptyArcosFilhos(){
    if (adjLists[v1].size() != 0)
        adjLists[v1].erase();
    if (adjLists[v2].size() != 0)
        adjLists[v2].erase();*/
}
