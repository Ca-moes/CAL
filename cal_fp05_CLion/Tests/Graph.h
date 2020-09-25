/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    double ** W = nullptr; // dist
    int **P = nullptr; // path
    int findVertexIdx(const T &in) const;
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

    Vertex<T> * initSingleSource(const T &orig);
    bool relax(Vertex<T> *v, Vertex<T> *w, double weight);

	// Fp05 - single source
	void unweightedShortestPath(const T &orig);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

    ~Graph();
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}

/**
* Initializes single-source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
    for (auto v : vertexSet) {
        v->dist = INF;
        v->path = nullptr;
    }
    auto s = findVertex(origin);
    s->dist = 0;
    return s;
}
/**
* Analyzes an edge in single-source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/
template<class T>
bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->dist + weight < w->dist) {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

/**
* Finds the index of the vertex with a given content.
*/
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == in)
            return i;
    return -1;
}

template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
	/*
	SHORTEST-PATH-UNWEIGHTED(G=(V,E), s):
    1. for each v in V do
    2.      dist(v) <- INF
    3.      path(v) <- nil
    4. dist(s) <- 0
    5. Q <- 0
    6. ENQUEUE(Q, s)
    7. while Q != 0 do
    8.      v <- DEQUEUE(Q)
    9.      for each w in Adj(v) do
    10.         if dist(w) = INF then
    11.             ENQUEUE(Q, w)
    12.             dist(w) <- dist(v) + 1
    13.             path(w) <- v
	 */
	// Para 1º teste passar, necessário fazer Graph<T>::getPathTo
    Vertex<T> *src = findVertex(orig), *v;

	for (auto ver : vertexSet){
	    ver->dist = INF;
	    ver->path = NULL;
	}
    src->dist=0;
    queue<Vertex<T>*> Q;
    Q.push(src);
    while(!Q.empty()){
        v = Q.front(); Q.pop();
        typename vector<Edge<T>>::const_iterator it = v->adj.begin();
        while (it != v->adj.end()){
            if (it->dest->dist == INF){
                Q.push(it->dest);
                it->dest->dist = v->dist + 1;
                it->dest->path = v;
            }
            it++;
        }
    }

}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    /* DIJKSTRA(G, s): // G=(V,E), s in V
    1. for each v in V do
    2.      dist(v) <- INF
    3.      path(v) <- nil
    4. dist(s) <- 0
    5. Q <- 0 // min-priority queue
    6. INSERT(Q, (s, 0)) // inserts s with key 0
    7. while Q != 0 do
    8.      v <- EXTRACT-MIN(Q) // greedy
    9.      for each w in Adj(v) do
    10.         if dist(w) > dist(v) + weight(v,w) then
    11.             dist(w) <- dist(v)+ weight(v,w)
    12.             path(w) <- v
    13.             if w not in Q then // old dist(w) was 
    14.                 INSERT(Q, (w, dist(w)))
    15.             else
    16.                 DECREASE-KEY(Q, (w, dist(w)))
     * */
    auto s = initSingleSource(origin);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
    while ( ! q.empty() ) {
        auto v = q.extractMin();
        for (auto e : v->adj) {
            auto oldDist = e.dest->dist;
            if (relax(v, e.dest, e.weight)) {
                if (oldDist == INF)
                    q.insert(e.dest);
                else
                    q.decreaseKey(e.dest);
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	/*BELLMAN-FORD(G, s): // G=(V,E), s in V
    1. for each v in V do
    2.      dist(v) <- INF
    3.      path(v) <- nil
    4. dist(s) <- 0
    5. for i = 1 to |V|-1 do
    6.      for each (v, w) in E do
    7.          if dist(w) > dist(v) + weight(v,w) then
    8.              dist(w) <- dist(v) + weight(v,w)
    9.              path(w) <- v
    10. for each (v, w) in E do
    11.     if dist(v) + weight(v,w) < dist(w) then
    12.         fail("there are cycles of negative weight")
	 * */
    initSingleSource(orig);
    for (unsigned i = 1; i < vertexSet.size(); i++)
        for (auto v: vertexSet)
            for (auto e: v->adj)
                relax(v, e.dest, e.weight);
    for (auto v: vertexSet)
        for (auto e: v->adj)
            if (relax(v, e.dest, e.weight))
                cout << "Negative cycle!" << endl;
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
    // Ao começar no destino, vê o vertex em path até encontrar a origem (path == NULL)
	vector<T> res;

	Vertex<T> *v = findVertex(dest);
	res.push_back(v->getInfo());
    do{
        v = v->getPath();
        res.insert(res.begin(), v->getInfo());
    }while(v->getPath() != NULL);

	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    unsigned n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double *[n];
    P = new int *[n];
    for (unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j? 0 : INF;
            P[i][j] = -1;
        }
        for (auto e : vertexSet[i]->adj) {
            int j = findVertexIdx(e.dest->info);
            W[i][j] = e.weight;
            P[i][j] = i;
        }
    }
    for(unsigned k = 0; k < n; k++)
        for(unsigned i = 0; i < n; i++)
            for(unsigned j = 0; j < n; j++) {
                if(W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for ( ; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->info);
    reverse(res.begin(), res.end());
    return res;
}


#endif /* GRAPH_H_ */
