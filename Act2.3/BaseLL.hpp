#pragma once

#include <iostream>
#include <sstream>
#include <cstring>

#include "SimpleNode.hpp"
#include "DoubleNode.hpp"

template <class T, class NodeType>
class BaseLL{
    protected:
        int size;
        NodeType *head;
    public: 
        // Constructors
        BaseLL();
        BaseLL(const BaseLL<T,NodeType>& listToCopy);
        BaseLL(std::initializer_list<T> elements);
        virtual ~BaseLL();

        // Operators 
        auto& operator=(const BaseLL<T,NodeType>& listToCopy);
        T& operator[](unsigned int index); 

        // Data addition 
        virtual void append(T data) = 0;
        virtual void insert(T data, int index) = 0;

        virtual void update(T data, int index);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);
        NodeType* getNode(int index);

        virtual void print();
        void exchange(int index1, int index2);
        void invert();
        virtual void empty();
};

/*
PARAMETROS: void.
METODO: Construye una cabeza para la lista apuntando a nullptr.
ORDEN: O(1).
RETURN: void. Construye la cabeza de la lista.
*/
template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL():head(nullptr), size(0){}

/*
PARAMETROS: void.
METODO: Construye una cabeza que apunta al primer elemento de la lista y sus elementos siguientes.
ORDEN: O(n). n = elements.size().
RETURN: void. Se crea la cabeza de la lista que apunta a los elementos con los que se construyó
*/
template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL(std::initializer_list<T> elements){

    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new NodeType (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        NodeType* currentNode = head;
        iterador++;
        size=1;

        for (; iterador != elements.end(); ++iterador){ // se puede no inicializar nada en for
            NodeType* nextNode = new NodeType (*iterador); 

            currentNode->setNext(nextNode);
            currentNode=nextNode;
            size++;
        }
        currentNode->setNext(nullptr);

    }
}


template <class T, class NodeType> 
BaseLL<T, NodeType>:: BaseLL(const BaseLL<T, NodeType>& listToCopy):head(nullptr), size(0){
    operator=(listToCopy);
}

template <class T, class NodeType>
BaseLL<T, NodeType>:: ~BaseLL(){
    if (size != 0){

        while(head != nullptr){ 
            NodeType *temp=head; 
            head=head->getNext();
            delete temp; 
        }
        size=0;
    }
}

/*
PARAMETROS: Recibe una lista para copiarla.
METODO: Verifica que no se iguale con la cabeza original. Vacia los elementos a los que apunta la cabeza y copia los datos de cada nodo
de la nueva cabeza en nuevos nodos y los agrega al final de la lista actual hasta llegar al final de la lista a copiar.
ORDEN: O(n). n = elementos de la lista a copiar.
RETURN: BaseLL<T, NodeType>. Se copia la lista a copiar con nuevos nodos.
*/
template <class T, class NodeType>
auto & BaseLL<T, NodeType>::operator=(const BaseLL<T, NodeType>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }

    empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }
    
    NodeType* currentNodeCopy = listToCopy.head, *currentNode = new NodeType (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){

        NodeType* nextNode = new NodeType (currentNodeCopy.data); //usar los getters.
        currentNode->setNext(nextNode);

        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    size = listToCopy.length();
    
    return *this;
}

/*
PARAMETROS: Recibe un indice de un elemento que se quiere regresar.
METODO: Verifica que el indice este en el rango del tamaño de la lista. Recorre la lista regresa el valor del nodo que encuentra.
ORDEN: O(n). n = indice de elementos que se van a recorrer.
RETURN: T. Regresa el dato de un nodo por referencia.
*/
template <class T, class NodeType>
T& BaseLL<T, NodeType>::operator[](unsigned int index){
    
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

/*
PARAMETROS: void.
METODO: Elimina cada nodo de inicio a fin hasta llegar al final.
ORDEN: O(n). n = tamaño de la lista.
RETURN: void. Vacia la lista.
*/
template <class T, class NodeType>
void BaseLL <T, NodeType>::empty(){
    while(head != nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        NodeType *temp=this->head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}

/*
PARAMETROS: Recibe un valor de tipo T y el indice de un elemento a cambiar su valor.
METODO: Verifica que el indice este en el rango del tamaño de la lista. Busca la posición del nodo y remplaza su dato por referencia.
ORDEN: O(n). n = indice de elementos que se van a recorrer.
RETURN: void. Regresa la lista el elemento del indice intercambiado con el argumento data.
*/
template <class T, class NodeType>
void BaseLL<T, NodeType>::update(T data, int index){
    
    if(index < 0 || index >= size){
        return; 
    }

    operator[](index)=data;
}

/*
PARAMETROS: Recibe un indice de un nodo a buscar.
METODO: Verifica que el indice este en el rango del tamaño de la lista. Recorre cada nodo hasta llegar al nodo de indice.
ORDEN: O(n). n = indice de elementos que se van a recorrer.
RETURN: NodeType. Regresa el nodo que esta en el indice del argumento.
*/
template <class T, class NodeType>
NodeType* BaseLL<T, NodeType>::getNode(int index){
        
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode; 
}

template <class T, class NodeType>
int BaseLL<T,NodeType>::length() const {
    return size;
}

template <class T,class NodeType>
bool BaseLL<T,NodeType>::isEmpty(){
    if (head == nullptr){
        return true;
    }
    return false;
}

/*
PARAMETROS: Recibe un dato de tipo T para buscar su indice.
METODO: Itera la lista de inicio a fun hasta encontrar el primer valor que se iguale con el argumento data, si no se encuentra regresa -1.
ORDEN: O(n). n = tamaño de la lista.
RETURN: int. Indece donde se encuentra el valor buscado.
*/
template <class T, class NodeType>
int BaseLL<T,NodeType>::search(T data){
    NodeType* currentNode=this->head;

    int i=0;
    while(currentNode->getNext() != nullptr && currentNode->getNext() != head ){
        if (currentNode->getData() == data){
            return i;
        }
        i++;
        currentNode=currentNode->getNext();
    }
    return -1;
}

/*
PARAMETROS: Recibe 2 indices que remplazaran valor.
METODO: Toma el dato de los 2 indices con un buffer y los remplaza.
ORDEN: O(1).
RETURN: void. Regresa la lista con esos 2 datos remplazados.
*/
template <class T, class NodeType>
void BaseLL<T,NodeType>::exchange(int indexA, int indexB){
    T buffer = operator[](indexA);
    operator[](indexA) = operator[](indexB);
    operator[](indexB) = buffer;
}

/*
PARAMETROS: void.
METODO: Toma el indice a la mitad de la lista e itera cada elemento con su reflejo y los intercambia hasta llegar al dato en medio de la lista.
ORDEN: O(n).
RETURN: void. Regresa la lista invertida de inicio a fin.
*/
template <class T, class NodeType>
void BaseLL<T,NodeType>::invert(){
    int positionA = 0, half = (size % 2 ==0) ? size/2: 1 + size/2;
    while(positionA < half){
        exchange(positionA,size-positionA-1);
        positionA++;
    }
}

/*
PARAMETROS: void.
METODO: Recorre cada elemento de la lista e imprime cada valor de sus nodos.
ORDEN: O(n). n = tamaño de la lista
RETURN: void. Imprime cada elemento de la lista.
*/
template <class T, class NodeType>
void BaseLL<T,NodeType>::print(){
    NodeType* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    while(currentNode != nullptr){
        std::cout<<currentNode->getData()<<" ";
        currentNode=currentNode->getNext();
    }
    std::cout<<std::endl;
}

