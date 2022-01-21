#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

using namespace std;

class Node {
    int value;
    Node* parent1;
    Node* parent2;
    vector<Node*> children;
    int times_visited;
    int aux_counter;

      public:
    Node (int value);
    //setters
    int setParent(int p1);
    void setChild(int c);
    //getters
    int getValue();
    Node* getParent1();
    Node* getParent2();
    vector<Node*> getChildren();
    int getCounter();
    int getTimesVisited();

    void incrementParents();
    void incrementCounter();
    void incrementTimesVisited();

};

class Graph {
    vector<Node*> vertices;
    vector<Node*> commonParents;

        public:
    Graph();
    void addEdge(int src, int dest);
    Node* getNode(int v);

    bool dfs(int startVertex);
    void bfs(int startVertex); 
    void solve();
};

int v1;         //vertice cujos ancestrais devem ser calculados
int v2;         //vertice cujos ancestrais devem ser calculados
int n_vertices; //numero de vertices
int n_arcos;    //numero de arcos
Graph* grafo;

/* protótipos */
int lerVerificarInputs();
void removeChildren(); //remove as criancas dos vertices v1 e v2

int main(){
    int temp = lerVerificarInputs();
    if (temp == -2){
        printf("0\n");
        return 0; //se a arvore geneologica e invalida

    } else if (temp == -1)
        return 0; //se o input está incorreto

    // elimina os arcos dos filhos de v1 e v2
    /*grafo.emptyArcosFilhos();*/

    /* executa 2 BFS's: para cada vértice visitadol,
    incrementa o contador de visitas de vertices */
    //grafo->bfs(v1); //TODO: #8 BFS
    //grafo->bfs(v2);

    //por fim, executa a funcao solve que vai resolver o resto do problema
    //grafo->solve();

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
    //inicializa o grafo
    grafo = new Graph();

    /* loop lê cada caminho, linha a linha */
    for (int i = 0; i < n_arcos; i++){
        // verifica a validade da árvore geneologica
        if (scanf("%d %d", &x, &y) == 1)
            return -1; //ERROR

        //se o node y do grafo tiver mais que 2 pais,
        if (grafo->getNode(y)->setParent(x) == -1)
            return -2; //Arvore geneologica invalida

        //adiciona o arco ao grafo
        grafo->addEdge(x, y);
    }

    //verifica se o grafo é acíclico
    //if (!grafo->dfs(1)) //TODO: #7 dfs
        //return -2; //Arvore geneologica invalida

    return 0;
}

// metodos de Node
Node::Node(int num){
    value = num;
    parent1 = NULL;
    parent2 = NULL;
    children = *new vector<Node*>();
    times_visited = 0;
    aux_counter = 0;
}

int Node::setParent(int parent){
    Node* p = grafo->getNode(parent);
    //if *this* has no parents
    if (this->parent1 == NULL){
        this->parent1 = p;
        return 0;
    }
    //if *this* has one parent
    else if (this->parent2 == NULL){
        this->parent2 = p;
        return 0;
    }
    //if *this* has both parents
    else
        return -1;

}

void Node::setChild(int c){ this->children.push_back(grafo->getNode(c)); }

int Node::getValue(){ return this->value; }

Node* Node::getParent1(){ return this->parent1; }

Node* Node::getParent2(){ return this->parent2; }

vector<Node*> Node::getChildren(){ return this->children; }

void Node::incrementParents(){
    //increments parent1's counter
    Node* temp;
    if ((temp = getParent1()) != NULL){
        temp->aux_counter++;
    }
    //increments parent2's counter
    if ((temp = getParent2()) != NULL){
        temp->aux_counter++;
    }
}

int Node::getCounter(){ return this->aux_counter; }
int Node::getTimesVisited(){ return this->times_visited; }
void Node::incrementCounter(){ this->aux_counter++; }
void Node::incrementTimesVisited(){ this->times_visited++; }

// metodos de graph
Graph::Graph() {
    vertices = *new vector<Node*>();
    commonParents = *new vector<Node*>();
}

void Graph::addEdge(int src, int dest){ this->getNode(src)->setChild(dest); }
Node* Graph::getNode(int v){ return this->vertices.at(v); }
/*
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

void Graph::bfs(Node *v){
    vector<Node> queue;

    v->times_visited++;
    queue.push_back(v);

    vector<Node>::iterator i;

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
*/
void Graph::solve(){
    // incrementa os contadores dos pais que pertencem às 2 BFS's
    for (Node* n: grafo->commonParents){
        n->incrementParents();
    }
    
    int i = 0;
    int finalResult[n_vertices];

    // caso o contador dos pais q pertencem as 2 BFS's seja == 0, esse nó faz parte da solucao
    for (Node* n: grafo->commonParents){
        if (n->getCounter() == 0){
            finalResult[i] = (n->getValue());
            i++;
        }
    }

    sort(finalResult, finalResult + i+1); //TODO: #6 #5 implementar a funcao sort;

    // imprime o resultado no terminal
    for (int j = 0; j < i - 1; j++){
        printf("%d ", finalResult[j]);
    }

    printf("%d\n", finalResult[i]);

}
