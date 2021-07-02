#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;

    vector< Edge<N,E> > edges;
    /**
     * construtor de node
     * @param inf
     */
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
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g){
    g.print(out);
    return out;
};


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) { info = inf; }
};

//exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
public:
    N info1, info2;
    EdgeAlreadyExists(N info1, N info2) {this->info1 = info1; this->info2 = info2;}
};

//exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist{
public:
    N info1, info2;
    EdgeDoesNotExist<N>(N info1, N info2) : info1(info1), info2(info2){}
};

//...........................................................

template <class N>
std::ostream &operator << (ostream &out, const EdgeAlreadyExists<N> &ed){
    out << "Edge already exists: " << ed.info1 << " , " << ed.info2; return out;}

template <class N>
std::ostream &operator << (ostream &out, const EdgeDoesNotExist<N> &ed){
    out << "Edge does not exist: " << ed.info1 << " , " << ed.info2;
    return out;
}

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out;}



//...........................................................

//Constructor
template <class N, class E>
Graph<N, E>::Graph() {}

//Desctructor
template <class N, class E>
Graph<N, E>::~Graph() {
    for(typename std::vector< Node<N, E>* >::const_iterator it = nodes.begin(); it != nodes.end(); it++)
        delete (*it);
}

//Getters
template <class N, class E>
unsigned Graph<N, E>::numNodes() const {return nodes.size();}

template <class N, class E>
unsigned Graph<N, E>::numEdges() const {
    unsigned eCount = 0;
    for(typename std::vector< Node<N, E>* >::const_iterator it = nodes.begin(); it != nodes.end(); it++)
        eCount += (*it)->edges.size();
    return eCount;
}


//Something
template <class N, class E>
Graph<N, E> & Graph<N, E>::addNode(const N &inf) {
    //Checking if node already exists
    typename vector< Node<N,E> *>::const_iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++)
        if ((*it)->info == inf) throw NodeAlreadyExists<N>(inf);
    //Creating node
    Node <N, E> *node = new Node<N, E>(inf);
    nodes.push_back(node);
    return *this;
}

template <class N, class E>
Graph<N, E> & Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    typename std::vector< Node<N, E> *>::const_iterator itNodes, beg, e;
    typename std::vector< Edge<N, E> >::const_iterator itEdges;

    bool beginFound = false;
    bool endFound = false;
    //Finding nodes
    for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++){
        if((*itNodes)->info == begin){
            beg = itNodes;
            beginFound = true;
            //Checking if edge already exists
            for (itEdges = (*itNodes)->edges.begin(); itEdges != (*itNodes)->edges.end(); itEdges++) {
                if (itEdges->destination->info == end) throw EdgeAlreadyExists<N>(begin, end);
            }
            if (endFound) break;
        }
        else if((*itNodes)->info == end){
            e = itNodes;
            endFound = true;
            if(beginFound) break;
        }
    }
    //Checking if nodes do exist after all
    if(!beginFound) throw NodeDoesNotExist<N>(begin);
    if(!endFound) throw NodeDoesNotExist<N>(end);

    //Creating edge
    Edge<N, E> edge(*e, val);
    (*beg)->edges.push_back(edge);

    return *this;
}

template <class N, class E>
E & Graph<N, E>::edgeValue(const N &begin, const N &end) {
    typename std::vector < Node<N, E> *>::iterator it1;
    typename std::vector < Edge<N, E> >::iterator it2;

    //Finding the edge
    for(it1 = nodes.begin(); it1 != nodes.end(); it1++){
        if((*it1)->info == begin){

            for(it2 = (*it1)->edges.begin(); it2 != (*it1)->edges.end();it2++){
                if (it2->destination->info == end) return it2->value;
            }
            //In case edge is not found
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    //In case node is not found
    throw NodeDoesNotExist<N>(begin);
}

template <class N, class E>
Graph<N, E>& Graph<N, E>::removeEdge(const N &begin, const N &end) {
    typename std::vector < Node<N, E> *>::iterator it1;
    typename std::vector < Edge<N, E> >::iterator it2;

    //Finding the edge
    for(it1 = nodes.begin(); it1 != nodes.end(); it1++){
        if((*it1)->info == begin){

            for(it2 = (*it1)->edges.begin(); it2 != (*it1)->edges.end(); it2++){
                if (it2->destination->info == end) {
                    (*it1)->edges.erase(it2);
                    return *this;
                }
            }
            //In case edge is not found
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    //In case node is not found
    throw NodeDoesNotExist<N>(begin);
    return *this;
}

template <class N, class E>
void Graph<N, E>::print(std::ostream &os) const {
    typename std::vector < Node<N, E> *>::const_iterator it1;
    typename std::vector < Edge<N, E> >::const_iterator it2;
    for (it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        os << "( " << (*it1)->info;
        for (it2 = (*it1)->edges.begin(); it2 != (*it1)->edges.end(); it2++){
            os << "[ " << it2->destination->info << " " << it2->value << "] ";
        }
        os << ") ";
    }
}
