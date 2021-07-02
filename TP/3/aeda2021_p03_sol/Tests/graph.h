#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
	N info;
	vector< Edge<N,E> > edges;
	Node(N inf) {
		info = inf;
	}
};

template <class N, class E>
class Edge {
public:
	E value;
	Node<N,E> *destination;
	Edge(Node<N,E> *dest, E val) {
		value = val;
		destination = dest;
	}
};

template <class N, class E> 
class Graph { 
	vector< Node<N,E> *> nodes;
  public: 
    Graph();
    ~Graph(); 
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};

template <class N, class E> 
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists
{
public:
   N info1, info2;
   EdgeAlreadyExists(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &e)
{ out << "Edge already exists: " << e.info1 << " , " << e.info2 ; return out; }


// exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist
{
public:
   N info1, info2;
   EdgeDoesNotExist(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &e)
{ out << "Edge does not exist: " << e.info1 << " , " << e.info2 ; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
	N info;
    NodeDoesNotExist(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }



// class Graph

template <class N, class E> 
Graph<N,E>::Graph() {}

template <class N, class E> 
Graph<N,E>::~Graph() {
	typename vector< Node<N,E> *>::const_iterator it;
	for (it=nodes.begin(); it!=nodes.end(); it++)
		delete *it;
}

/**
 * counts the number of graph nodes
 * @tparam N data type of the node content
 * @tparam E data type of the edge
 * @return number of nodes
 */
template <class N, class E>
unsigned Graph<N,E>::numNodes() const {
	return nodes.size();
}

template <class N, class E>   
unsigned Graph<N,E>::numEdges() const {
	int nEdges = 0;
    typename vector< Node<N,E> *>::const_iterator it;
	for (it = nodes.begin(); it != nodes.end(); it++) {
		nEdges += (*it)->edges.size();
	}
	return nEdges;
}

template<class N, class E>
Graph<N, E> & Graph<N, E>::addNode(const N &inf) {
    typename vector< Node<N,E> *>::const_iterator it;
    // see if node already exists and throws exception
	for (it = nodes.begin(); it != nodes.end(); it++) {
		if ((*it)->info == inf) throw NodeAlreadyExists<N>(inf);
	}
	Node<N,E> *no1 = new Node<N,E>(inf);
	nodes.push_back(no1);
	return *this;
}

template<class N, class E>
Graph<N, E> & Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
	// see the nodes vector for node where info= begin
	typename vector< Node<N,E> *>::iterator it;
	typename vector< Edge<N,E> >::iterator itedge;
	bool foundBegin = false;
	bool foundEnd = false;

	Node<N,E> *noBegin_apt=NULL;
	Node<N,E> *noEnd_apt=NULL;

	for (it = nodes.begin(); it != nodes.end(); it++)
	{
		// search vector nodes for node where info=begin
		if ( (*it)->info == begin )
		{
			// verifiy if vector edges already has an edge where destination=end
			foundBegin = true;
			noBegin_apt=*it;
			for (itedge = (*it)->edges.begin();  itedge != (*it)->edges.end(); itedge++)
			{
				// throw exception if edge already exists
				if ( itedge->destination->info == end) throw EdgeAlreadyExists<N> (begin, end);
			}
			if (foundEnd==true) break;
		}
		else if ( (*it)->info == end ) {
			foundEnd=true;
			noEnd_apt=*it;
			if (foundBegin==true) break;
		}
	}

	// if one of the nodes was not found, throws an exception
	if (!foundBegin) throw NodeDoesNotExist<N>(begin);
	if (!foundEnd) throw NodeDoesNotExist<N>(end);

	// creates a new Edge
	Edge<N,E> edge1(noEnd_apt, val);
	// add to edges vector
	noBegin_apt->edges.push_back(edge1);

	return *this;
} 


template<class N, class E>
E & Graph<N, E>::edgeValue(const N &begin, const N &end) {
	// Percorrer o vetor de nos para obter no em que info=inicio
	typename vector< Node<N,E> *>::iterator it;
	typename vector< Edge<N,E> >::iterator itedge;
	for (it = nodes.begin(); it != nodes.end(); it++) {
		// procura no vetor de nos o no em que info==inicio
		if ( (*it)->info == begin ) {
			// verificar se o vetor de Edges tem uma Edge para destino=fim
			for (itedge = (*it)->edges.begin();  itedge != (*it)->edges.end(); itedge++) {
				// Caso encontre faz o return do seu valor
				if ( itedge->destination->info == end) return itedge->value;
			}
			// se nao encontrar a Edge, lanca excecao
			throw EdgeDoesNotExist<N> (begin, end);
		}
	}
	// se nao encontrar o no, lanca excecao tipo NodeInexistente
	throw NodeDoesNotExist<N>(begin);
}

template <class N, class E>
Graph<N,E> & Graph<N,E>::removeEdge(const N &begin, const N &end)
{
	// Percorrer o vetor de nos para obter no em que info=inicio
	typename vector< Node<N,E> *>::iterator it;
	typename vector< Edge<N,E> >::iterator itedge;
	for (it = nodes.begin(); it != nodes.end(); it++) {
		// procura no vetor de nos o no em que info==inicio
		if ( (*it)->info == begin ) {
			// verificar se o vetor de Edges tem uma Edge para destino=fim
			for (itedge = (*it)->edges.begin();  itedge != (*it)->edges.end(); itedge++) {
				// Caso encontre elimina a Edge
				if ( itedge->destination->info == end) {
					(*it)->edges.erase(itedge);
					return *this;
				}
			}
			// Nao encontrando a Edge lanca excecao
			throw EdgeDoesNotExist<N> (begin, end);
		}
	}
	// se nao encontrar o no, lanca excecao tipo NodeInexistente
	throw NodeDoesNotExist<N>(begin);
	return *this;
}


template <class N, class E>
void Graph<N,E>::print(std::ostream &os) const
{
	typename vector< Node<N,E> *>::const_iterator it;
	typename vector< Edge<N,E> >::const_iterator itedge;
	for (it = nodes.begin(); it != nodes.end(); it++) {
		os << "( " << (*it)->info ;
		for (itedge = (*it)->edges.begin();  itedge != (*it)->edges.end(); itedge++) {
			os << "[ " <<  itedge->destination->info << " " << itedge->value << "] " ;
		}
		os << ") ";
	}
}

template <class N, class E> 
std::ostream & operator<<(std::ostream &out, const Graph<N, E> &g)
{
   g.print(out);
   return out;
}


