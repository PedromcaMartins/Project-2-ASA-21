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
    vector<Node*> children;
    bool is_visited;
    int times_visited;
    bool aux_counter;
    bool finalResult;

      public:
    Node (int num, vector<Node*>* vector_children);
    //setters
    int setParent(int p1);
    void setChild(int c);
    void setCounter();
    void setTimesVisited(int t);
    void setIsVisited();
    void setFinalResult();
    //getters
    int getValue();
    Node* getParent(int p);
    vector<Node*> getChildren();
    int getCounter();
    int getTimesVisited();
    bool getIsVisited();
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
bool cyclic;
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
    int temp = lerVerificarInputs();
    if (temp == -2){
        printf("0\n");
        return 0; //se a arvore geneologica e invalida

    } else if (temp == -1)
        return 0; //se o input está incorreto

    /* executa 2 BFS's: para cada vértice visitado,
    incrementa o contador de visitas de vertices */
    bfs(getNode(v1), 1); 
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

// construtor de Node
Node::Node(int num, vector<Node*>* vector_children){
    value = num;
    parent1 = NULL;
    parent2 = NULL;
    children = *vector_children;
    is_visited = 0;
    aux_counter = 0;
    finalResult = 0;
    times_visited = 0;
}

int Node::setParent(int int_parent){
    Node* p = getNode(int_parent);
    //se *this* não tem pais
    if (this->parent1 == NULL){
        this->parent1 = p;
        return 0;
    }
    //se *this* tem um pai
    else if (this->parent2 == NULL){
        this->parent2 = p;
        return 0;
    }
    //se *this* tem os dois pais
    else
        return -1;
}

void Node::setChild(int c){ this->children.push_back(getNode(c)); }

int Node::getValue(){ return this->value; }

Node* Node::getParent(int p){
    if (p == 1)
        return this->parent1;
    return this->parent2;
}

vector<Node*> Node::getChildren(){ return this->children; }

void Node::incrementParents(){
    //incrementa aux_counter do parent1
    Node* temp;
    if ((temp = getParent(1)) != NULL){
        temp->aux_counter = 1;
    }
    //incrementa aux_counter do parent2
    if ((temp = getParent(2)) != NULL){
        temp->aux_counter = 1;
    }
}

int Node::getCounter(){ return this->aux_counter; }
int Node::getTimesVisited(){ return this->times_visited; }
bool Node::getIsVisited(){ return this->is_visited; }
void Node::setCounter(){ this->aux_counter = 1; }
void Node::setTimesVisited(int t){ this->times_visited = t; }
void Node::setIsVisited(){ this->is_visited = 1; }
void Node::setFinalResult(){ this->finalResult = 1; }
bool Node::getFinalResult(){ return this->finalResult; }


void setCommonParents(Node* cp){ commonParents.push_back(cp);}

// inicializa os vetores globais do grafo
void inicializaGrafo() {
    vertices = *new vector<Node*>();
    commonParents = *new vector<Node*>();

    vertices.push_back(NULL);
    // inicializa e adiciona os nós ao grafo
    for (int i = 1; i < n_vertices + 1; i++){
        vector<Node*> *temp  = new vector<Node*>;
        vertices.push_back(new Node(i, temp));
    }
}

void addEdge(int src, int dest){ getNode(src)->setChild(dest); }
Node* getNode(int v){ return vertices.at(v); }


bool dfs(Node* v) {
    /*começa no nó do input, logo timesVisited passa a 1*/
    v->setTimesVisited(1);
    /*percorre os filhos (adjacências) do nó do input*/
    for (Node* u: v->getChildren()) {
        /*se ainda não tiver sido visitado e a dfs seja possivel*/
        if (u->getTimesVisited() == 0) {
            if (dfs(u))
                return true;
        /*se já tiver sido visitado então houve um backedge(cíclico)*/
        } else if (u->getTimesVisited() == 1) {
            cyclic = true;
            return true;
        }
    }
    v->setTimesVisited(2);
    return false;
}

int find_cycle() {
    cyclic = false;

    /*percorre a dfs para todos os vértices que ainda não foram visitados*/
    for (int v = 1; v < n_vertices + 1; v++) {
        if (getNode(v)->getTimesVisited() == 0 && dfs(getNode(v)))
            break;
    }

    /*caso se tenha detetado um backedge nalguma das dfs devolve -1,
    caso contrário devolve 0*/
    if (cyclic == false) {
        return 0;
    } else {
        return -1;
    }
}

void bfs(Node* v, int x){
    list<Node*> queue = *new list<Node*>();
    Node* Node_parent;

    /*caso v1 e v2 sejam familiares direta ou indiretamente*/
    if (v->getIsVisited() && x == 2)
        setCommonParents(v);
    v->setIsVisited();

    queue.push_back(v);

    while (!queue.empty()) {
        Node* currVertex = queue.front();
        queue.pop_front();

        for (int i = 1; i != 3; ++i) {
            //se o node nao tiver o pai i,
            if ((Node_parent = currVertex->getParent(i)) == NULL)
                break;
            //se o pai ainda não tiver sido visitado
            if (!Node_parent->getIsVisited()) {
                queue.push_back(Node_parent);
                if (x == 1)
                    Node_parent->setIsVisited();
            }
            /*caso o pai ja esteja visitado e estiver na 2a BFS e o pai ainda não estiver no vetor da solução*/
            else if (Node_parent->getIsVisited() && x == 2 && !Node_parent->getFinalResult()){
                Node_parent->setFinalResult();
                setCommonParents(Node_parent);
                queue.push_back(Node_parent);
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

    vector<int> finalResult = *new vector<int>();

    // caso o contador dos pais q pertencem as 2 BFS's seja == 0, esse nó faz parte da solucao
    for (Node* n: commonParents){
        if (!n->getCounter())
            finalResult.push_back(n->getValue());
    }

    /*ordena o vetor final por ordem crescente*/
    sort(finalResult.begin(), finalResult.end());

    // imprime o resultado no terminal
    for (int j: finalResult){
        printf("%d ", j);
    }
    printf("\n");

}
