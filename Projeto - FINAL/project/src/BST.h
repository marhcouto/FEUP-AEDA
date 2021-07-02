#ifndef CENTRALPORTAGENS_CPP_BST_H
#define CENTRALPORTAGENS_CPP_BST_H
#include <stack>

template <class Interv> class BST;
template <class Interv> class BSTiterator;

template <class Interv>
class Node {
    Node *left;
    Node *right;
    Interv value;
    Node(const Interv &val, Node *l = nullptr, Node *r = nullptr) : left(l), right(r), value(val) {};
    friend class BST<Interv>;
    friend class BSTiterator<Interv>;
};

template <class Interv>
class BST {
    Interv notFound;
    Node<Interv> *root;
    bool insert (const Interv &val, Node<Interv> * & n) const;
    bool remove (const Interv &val, Node<Interv> * & n) const;
    const Interv& findMin(Node<Intervention>*& node) const;
    const Interv& findMax(Node<Intervention>*& node) const;
    void clear (Node<Interv> * & ptr);
    Node<Interv>* clone (Node<Interv>* node) const;
    friend class BSTiterator<Interv>;
public:
    BST (const Interv &notfound);
    BST (const BST &bst);
    ~BST();
    bool insert (const Interv &val);
    bool remove (const Interv &val);
    const Interv& findMin() const;
    const Interv& findMax() const;
    void operator= (const BST& bst);
    void clear ();
    BSTiterator<Interv> begin () const;
    BSTiterator<Interv> end () const;
};

template <class Interv>
class BSTiterator {
    std::stack<Node<Interv>*> Stack;
    void setTree(Node<Interv>* root);
    void slideLeft(Node<Interv>* node);
    friend class BST<Interv>;
public:
    BSTiterator<Interv>& operator++ (int);
    Interv operator* ();
    bool operator == (const BSTiterator<Interv> &it) const;
};









template <class Interv>
BST<Interv>::BST (const BST<Interv> &bst) {
    *this = bst;
}

template <class Interv>
BST<Interv>::BST (const Interv &notfound) : root(nullptr), notFound(notfound) {};

template <class Interv>
BST<Interv>::~BST() {
    clear();
}

template <class Interv>
bool BST<Interv>::insert (const Interv &val) {
    return insert (val, root);
}

template <class Interv>
bool BST<Interv>::insert (const Interv &val, Node<Interv> * & node) const {
    if (node == nullptr) {
        node = new Node<Interv>(val);
        return true;
    }
    else if (val < node->value) {
        return insert (val, node->left);
    }
    else if (node->value < val) {
        return insert (val, node->right);
    }
    else return false;
}

template <class Interv>
const Interv& BST<Interv>::findMin () const {
    Node<Interv> *node = root;
    if (node == nullptr) return notFound;
    while (node->left != nullptr) node = node->left;
    return node->value;
}

template <class Interv>
const Interv& BST<Interv>::findMin(Node<Intervention> *&node) const {
    if (node == nullptr) return notFound;
    while (node->left != nullptr) node = node->left;
    return node->value;
}

template <class Interv>
const Interv& BST<Interv>::findMax (Node<Intervention> *& node) const {
    if (node == nullptr) return notFound;
    while (node->right != nullptr) node = node->right;
    return node->value;
}

template <class Interv>
const Interv& BST<Interv>::findMax () const {
    Node<Interv> *node = root;
    if (node == nullptr) return notFound;
    while (node->right != nullptr) node = node->right;
    return node->value;
}

template <class Interv>
bool BST<Interv>::remove (const Interv &val) {
    return remove (val, root);
}

template <class Interv>
bool BST<Interv>::remove (const Interv &val, Node<Interv> * & node) const {
    if (node == nullptr) return false;
    if (val < node->value) return remove (val, node->left);
    else if (node->value < val) return remove (val, node->right);
    else if (node->right != nullptr && node->left != nullptr) {
        node->value = findMin (node->right);
        return remove (node->value, node->left);
    }
    else {
        Node<Interv> *n = node;
        node = node->left != nullptr ? node->left : node->right;
        delete n;
        return true;
    }
}

template <class Interv>
void BST<Interv>::clear() {
    clear(root);
}

template <class Interv>
void BST<Interv>::clear(Node<Interv> * & ptr) {
    if (ptr != nullptr) {
        clear (ptr->left);
        clear (ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}

template <class Interv>
Node<Interv>* BST<Interv>::clone (Node<Interv>* node) const {
    if (node == nullptr) return nullptr;
    else return new Node<Interv> (node->value, clone (node->left), clone (node->right));
}

template <class Interv>
void BST<Interv>::operator=(const BST<Interv> &bst) {
    if (this != &bst) {
        this->clear ();
        root = this->clone (bst.root);
    }
}

template <class Interv>
BSTiterator<Interv> BST<Interv>::begin() const {
    BSTiterator<Interv> it;
    it.setTree(root);
    return it;
}

template <class Interv>
BSTiterator<Interv> BST<Interv>::end() const {
    BSTiterator<Interv> it;
    it.setTree(nullptr);
    return it;
}

/* --Iterator-- */

template <class Interv>
void BSTiterator<Interv>::setTree (Node<Interv> *root) {
    if (root!= nullptr)
        slideLeft(root);
}

template <class Interv>
void BSTiterator<Interv>::slideLeft (Node<Interv> *node) {
    while (node != nullptr) {
        Stack.push(node);
        node = node->left;
    }
}

template <class Interv>
BSTiterator<Interv>& BSTiterator<Interv>::operator++(int) {
    Node<Interv>* top = Stack.top();
    Stack.pop();
    Node<Interv>* next = top->right;
    slideLeft(next);
    return *this;
}

template <class Interv>
Interv BSTiterator<Interv>::operator*() {
    return Stack.top()->value;
}

template <class Interv>
bool BSTiterator<Interv>::operator==(const BSTiterator<Interv> &it) const {
    return this->Stack == it.Stack;
}


#endif //CENTRALPORTAGENS_CPP_BST_H
