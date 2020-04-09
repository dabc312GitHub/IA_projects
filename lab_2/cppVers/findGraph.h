#include <vector>
#include <iostream>
using namespace std;

template <class T>
class nodo
{
public:
    T valor;
    nodo<T> *next;
    nodo(T x, nodo<T> *n = NULL)
    {
        valor = x;
        next = n;
    }

    void deleteAll()
    {
        if (next == NULL || next->valor < valor)
        {
            delete this;
            return;
        }
        next->deleteAll();
        delete this;
    }
};

template <class T>
class lista2
{
public:
    nodo<T> *head;
    lista2(T n)
    {
        head = new nodo<T>(n);
    }
    lista2(nodo<T> *n = NULL)
    {
        head = n;
    }
    void sethead(nodo<T> *n = NULL)
    {
        head = n;
    }
    void imprimir()
    {
        if (head == NULL)
        {
            cout << "lista vacia" << endl;
            return;
        }
        cout << head->valor;
        nodo<T> *aux = head->next;
        while (aux)
        {
            cout << "->" << aux->valor;
            aux = aux->next;
        }
    }
    bool buscar(T val, nodo<T> **&n)
    {
        n = &head;
        while ((*n) != NULL)
        {
            if ((*n)->valor->m_v < val->m_v)
            {
                n = &((*n)->next);
            }
            else
            {
                return (*n)->valor->m_v == val->m_v;
            }
        }
        return false;
    }
    bool buscar2(T val, nodo<T> **&n, bool flag = 0)
    {
        n = &head;
        while ((*n) != NULL)
        {
            if ((*n)->valor->m_v < val->m_v)
            {
                n = &((*n)->next);
            }
            else
            {
                if ((*n)->valor->m_v > val->m_v)
                    return false;
                if (flag)
                {
                    if (
                        (*n)->valor->m_nodos[0] == val->m_nodos[0] && 
                        (*n)->valor->m_nodos[1] == val->m_nodos[1]
                        )
                        return (*n)->valor->m_v == val->m_v;
                    else
                        n = &((*n)->next);
                }
                else
                    return (*n)->valor->m_v == val->m_v;
            }
        }
    }
    void insertar(T val)
    {
        nodo<T> **p;
        buscar(val, p);
        *p = new nodo<T>(val, *p);
    }
    void insertarN(T val)
    {
        nodo<T> **p;
        if (!buscar(val, p))
            *p = new nodo<T>(val, *p);
    }
    void eliminar(T val)
    {
        nodo<T> **p;
        if (buscar(val, p))
        {
            nodo<T> *aux = *p;
            *p = (*p)->next;
            delete aux;
        }
    }
    void deleteAll()
    {
        head->deleteAll();
        head = NULL;
    }
};

template <typename G>
struct CNode
{
    typedef typename G::Nn N;
    typedef typename G::Edge Edge;
    N m_n;
    N &m_v = m_n;
    lista2<Edge *> m_edges;
    CNode(N val)
    {
        m_n = val;
    }
    bool operator==(CNode<G> &nodoG)
    {
        return m_n == nodoG.m_n;
    }
    bool operator!=(CNode<G> &nodoG)
    {
        return m_n != nodoG.m_n;
    }
};

template <typename G>
struct CEdge
{
    typedef typename G::Ee E;
    typedef typename G::Node Node;
    E m_e;
    E &m_v = m_e;
    Node *m_nodos[2];
    bool dir; //False va de 0 a 1 y True es bidireccional
    CEdge(E peso, Node *i, Node *f, bool d)
    {
        m_e = peso;
        m_nodos[0] = i;
        m_nodos[1] = f;
        dir = d;
    }
    bool operator==(CEdge<G> &arista)
    {
        return (
            m_e == arista.m_e && 
            m_nodos[0] == arista.m_nodos[0] && 
            m_nodos[1] == arista.m_nodos[0] && 
            dir == arista.dir
            );
    }
    bool operator!=(CEdge<G> &arista)
    {
        return (
            m_e != arista.m_e || 
            m_nodos[0] != arista.m_nodos[0] || 
            m_nodos[1] != arista.m_nodos[0] || 
            dir != arista.dir
            );
    }
};

template <class N, class E>
struct CGraph
{
    typedef CGraph<N, E> Self;
    typedef CNode<Self> Node;
    typedef CEdge<Self> Edge;
    typedef N Nn;
    typedef E Ee;
    lista2<Node *> m_nodes;
    lista2<Edge *> m_edge;
    void insertarArista(E peso, N inicio, N fin, bool d)
    {
        nodo<Node *> **nodoInicio;
        nodo<Node *> **nodoLlegada;
        Node *ini = new Node(inicio);
        Node *fi = new Node(fin);
        if (m_nodes.buscar(ini, nodoInicio) && m_nodes.buscar(fi, nodoLlegada))
        {
            Edge *aux = new Edge(peso, (*nodoInicio)->valor, (*nodoLlegada)->valor, d);
            m_edge.insertar(aux);
            (*nodoInicio)->valor->m_edges.insertar(aux);
            (*nodoLlegada)->valor->m_edges.insertar(aux);
        }
        delete fi;
        delete ini;
    }
    void eliminarArista(E peso, N inicio, N fin)
    {
        nodo<Edge *> **aux;
        nodo<Node *> **nodoInicio;
        nodo<Node *> **nodoLlegada;
        Node *ini = new Node(inicio);
        Node *fi = new Node(fin);
        m_nodes.buscar(ini, nodoInicio);
        m_nodes.buscar(fi, nodoLlegada);
        Edge *e = new Edge(peso, (*nodoInicio)->valor, (*nodoLlegada)->valor, 0);
        delete ini;
        delete fi;
        if (m_edge.buscar2(e, aux, 1))
        {
            (*aux)->valor->m_nodos[0]->m_edges.eliminar((*aux)->valor);
            (*aux)->valor->m_nodos[1]->m_edges.eliminar((*aux)->valor);
            nodo<Edge *> *p = *aux;
            *aux = (*aux)->next;
            delete p;
        }
        delete e;
    }
    void insertarNodo(N val)
    {
        Node *aux = new Node(val);
        m_nodes.insertarN(aux);
    }
    bool eliminarNodo(N v)
    {
        nodo<Node *> **aux;
        Node *temp = new Node(v);
        m_nodes.buscar(temp, aux);
        delete temp;
    }
    void imprimir()
    {
        if (m_nodes.head == NULL)
        {
            cout << "lista vacia" << endl;
            return;
        }
        cout << m_nodes.head->valor->m_n;
        nodo<Node *> *aux = m_nodes.head->next;
        while (aux)
        {
            cout << "->" << aux->valor->m_n;
            aux = aux->next;
        }
        cout << endl;
        if (m_edge.head == NULL)
        {
            cout << "lista vacia" << endl;
            return;
        }
        cout << m_edge.head->valor->m_e;
        nodo<Edge *> *aux2 = m_edge.head->next;
        while (aux2)
        {
            cout << "->" << aux2->valor->m_e;
            aux2 = aux2->next;
        }
    }
};

// int main()
// {
    // CGraph<int, int> algo;
    // algo.insertarNodo(4);
    // algo.insertarNodo(3);
    // algo.insertarNodo(3);
    // algo.insertarArista(7, 4, 3, 0);
    // algo.insertarArista(6, 4, 3, 0);
    // algo.insertarArista(5, 3, 4, 1);
    // algo.eliminarArista(5, 3, 3);
    // algo.imprimir();
//     return 0;
// }
