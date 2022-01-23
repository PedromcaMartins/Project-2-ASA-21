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
    vector<int> children;
    bool times_visited;
    bool aux_counter;
    bool finalResult;

      public:
    Node (int value);
    //setters
    int setParent(int p1);
    void setChild(int c);
    void setCounter();
    void setTimesVisited();
    void setFinalResult();
    //getters
    int getValue();
    Node* getParent(int p);
    vector<int> getChildren();
    int getCounter();
    int getTimesVisited();
    bool getFinalResult();
    //increments
    void incrementParents();

};

//VARIAVEIS GLOBAIS
int v1;         //vertice cujos ancestrais devem ser calculados
int v2;         //vertice cujos ancestrais devem ser calculados
int n_vertices; //numero de vertices
int n_arcos;    //numero de arcos
//dfs
vector<int> color;
vector<int> parent;
int cycle_start, cycle_end;
//grafo
vector<Node*> vertices;
vector<Node*> commonParents;

/* protótipos */
int lerVerificarInputs();
int find_cycle();
//grafo
void inicializaGrafo();
Node* getNode(int v);
void addEdge(int src, int dest);
void setCommonParents(Node* cp);

bool dfs(Node* v);
void bfs(Node* v, int x);
void solve();

int main(){
    vector<int> color = *new vector<int>();
    vector<int> parent = *new vector<int>();

    int temp = lerVerificarInputs();
    if (temp == -2){
        printf("0\n");
        return 0; //se a arvore geneologica e invalida

    } else if (temp == -1)
        return 0; //se o input está incorreto

    /* executa 2 BFS's: para cada vértice visitadol,
    incrementa o contador de visitas de vertices */
    bfs(getNode(v1), 1); //TODO: #8 BFS
    bfs(getNode(v2), 2);

    //por fim, executa a funcao solve que vai resolver o resto do problema
    solve();

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
    inicializaGrafo();

    /* loop lê cada caminho, linha a linha */
    for (int i = 0; i < n_arcos; i++){
        // verifica a validade da árvore geneologica
        if (scanf("%d %d", &x, &y) == 1)
            return -1; //ERROR

        //se o node y do grafo tiver mais que 2 pais,
        if (getNode(y)->setParent(x) == -1)
            return -2; //Arvore geneologica invalida

        //adiciona o arco ao grafo
        addEdge(x, y);
    }

    //verifica se o grafo é ciclico
    if (find_cycle() == -1){
        return -2; //se a arvore geneologica e invalida
    }

    return 0;
}

// metodos de Node
Node::Node(int num){
    value = num;
    parent1 = NULL;
    parent2 = NULL;
    children = *new vector<int>();
    times_visited = 0;
    aux_counter = 0;
    finalResult = 0;
}

int Node::setParent(int parent){
    Node* p = getNode(parent);
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

void Node::setChild(int c){ this->children.push_back(c); }

int Node::getValue(){ return this->value; }

Node* Node::getParent(int p){
    if (p == 1)
        return this->parent1;
    return this->parent2;
}

vector<int> Node::getChildren(){ return this->children; }

void Node::incrementParents(){
    //increments parent1's counter
    Node* temp;
    if ((temp = getParent(1)) != NULL){
        temp->aux_counter = 1;
    }
    //increments parent2's counter
    if ((temp = getParent(2)) != NULL){
        temp->aux_counter = 1;
    }
}

int Node::getCounter(){ return this->aux_counter; }
int Node::getTimesVisited(){ return this->times_visited; }
void Node::setCounter(){ this->aux_counter = 1; }
void Node::setTimesVisited(){ this->times_visited = 1; }
void Node::setFinalResult(){ this->finalResult = 1; }
bool Node::getFinalResult(){ return this->finalResult; }


void setCommonParents(Node* cp){ commonParents.push_back(cp);}

// metodos de graph
void inicializaGrafo() {
    vertices = *new vector<Node*>();
    commonParents = *new vector<Node*>();

    vertices.push_back(new Node(-1));
    // adiciona inicializa e adiciona os nós ao grafo
    for (int i = 1; i < n_vertices + 1; i++){
        vertices.push_back(new Node(i));
    }
}

void addEdge(int src, int dest){ getNode(src)->setChild(dest); }
Node* getNode(int v){ return vertices.at(v); }

//https://cp-algorithms.com/graph/finding-cycle.html
bool dfs(int v) {
    color[v] = 1;
    for (int u : getNode(v)->getChildren()) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u))
                return true;
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

int find_cycle() {
    color.assign(n_vertices, 0);
    parent.assign(n_vertices, -1);
    cycle_start = -1;

    for (int v = 0; v < n_vertices; v++) {
        if (color[v] == 0 && dfs(v))
            break;
    }

    if (cycle_start == -1) {
        return 0;
    } else {
        return -1;
    }
}

void bfs(Node* v, int x){
    list<Node*> queue;
    Node* parent;

    if (v->getTimesVisited() && x == 2)
        setCommonParents(v);
    v->setTimesVisited();

    queue.push_back(v);

    while (!queue.empty()) {
        Node* currVertex = queue.front();
        queue.pop_front();

        for (int i = 1; i != 3; ++i) {
            //se o node nao tiver o pai i,
            if ((parent = currVertex->getParent(i)) == NULL)
                break;
            //senao: //acrescentar explicacao
            if (!parent->getTimesVisited()) {
                queue.push_back(parent);
                if (x == 1)
                    parent->setTimesVisited();
            }
            else if (parent->getTimesVisited() && x == 2 && !parent->getFinalResult()){
                parent->setFinalResult();
                setCommonParents(parent);
                queue.push_back(parent);
            }
        }
    }
}

void solve(){
    // caso não existam pais comuns
    if (commonParents.empty()){
        printf("-\n");
        return;
        }
    // incrementa os contadores dos pais que pertencem às 2 BFS's
    for (Node* n: commonParents){
        n->incrementParents();
    }

    int i = 0;
    int finalResult[n_vertices];

    // caso o contador dos pais q pertencem as 2 BFS's seja == 0, esse nó faz parte da solucao
    for (Node* n: commonParents){
        if (!n->getCounter()){
            finalResult[i] = (n->getValue());
            i++;
        }
    }

    sort(finalResult, finalResult + i); //TODO: #6 #5 implementar a funcao sort;

    // imprime o resultado no terminal
    for (int j = 0; j < i; j++){
        printf("%d ", finalResult[j]);
    }
    printf("\n");

}
