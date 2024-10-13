#pragma once
#include "SimpleNode.hpp"
#include "BaseLL.hpp"

template <class T>
class SimpleLL:public BaseLL<T, SimpleNode<T>>{
    public: 
        SimpleLL();
        SimpleLL(const SimpleLL<T>& listToCopy);
        SimpleLL(std::initializer_list<T> elements);

        ~SimpleLL() override;

        const SimpleLL<T>& operator =(const SimpleLL<T>& listToCopy);

        void append(const SimpleNode<T>& nodeToAppend);
        void append(const SimpleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(SimpleLL<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void erase(int index);
        void insert(SimpleNode<T>& nodeToInsert, int index);
                
        virtual void insert(T data, int index) override;
        virtual void append(T data) override;


};

/*
PARAMETROS: void.
METODO: Construye una cabeza default con el atributo de *head = nullptr.
ORDEN: O(1).
RETURN: void. Se crea la cabeza de la lista
*/
template <class T>
SimpleLL<T>::SimpleLL():BaseLL<T, SimpleNode<T>>(){}

/*
PARAMETROS: void.
METODO: Construye una cabeza que apunta al primer elemento de la lista y sus elementos siguientes.
ORDEN: O(n). n = elements.size().
RETURN: void. Se crea la cabeza de la lista que apunta a los elementos con los que se construyó
*/
template <class T>
SimpleLL<T>::SimpleLL(std::initializer_list<T> elements):BaseLL<T, SimpleNode<T>>(elements){};

/*
PARAMETROS: void.
METODO: Construye una cabeza que apunta al primer elemento de la lista y sus elementos siguientes.
ORDEN: O(n). n = elements.size().
RETURN: void. Se crea la cabeza de la lista que apunta a los elementos con los que se construyó
*/
template <class T>
SimpleLL<T>::SimpleLL(const SimpleLL<T>& listToCopy){}

/*
PARAMETROS: void.
METODO: Llama al método empty que elimina los nodos de la lista.
ORDEN: O(n). n = elements.size().
RETURN: void. Se elimina la lista
*/
template <class T>
SimpleLL<T>::~SimpleLL(){
    this->empty();
}

/*
PARAMETROS: Recibe un dato tipo T a agregar a la lista.
METODO: Si la lista esta vacia, se vuelve el nodo al que apunta la cabeza, si no, recorre la lista hasta encontrar el ultimo elemento y hace que el ultimo apunte al nuevo nodo.
ORDEN: O(n). n = elementos de la lista actual.
RETURN: void. Se agregó el elemento data a la listo
*/
template<class T>
void SimpleLL<T>::append(const SimpleNode<T>& nodeToAppend){
    if(this->head == nullptr){
        this->head = new SimpleNode<T> (nodeToAppend.getData());
        this->size++;
        return;
    }

    SimpleNode<T>* currentNode = this->head;
    while(currentNode->getNext() != nullptr){
        currentNode = currentNode->getNext();
    }

    currentNode->setNext(new SimpleNode<T> (nodeToAppend.getData()));
    this->size++;
}

/*
PARAMETROS: Recibe una lista para copiarla.
METODO: Verifica que no se iguale con la lista original. Vacia la lista y copia los datos de cada nodo
de la nueva lista en nuevos nodos y los agrega al final de la lista actual hasta llegar al final de la lista a copiar.
ORDEN: O(n). n = elementos de la lista a copiar.
RETURN: SimpleLL<T>. Se copia la lista a copiar con nuevos nodos.
*/
template <class T>
const SimpleLL<T>& SimpleLL<T>::operator=(const SimpleLL<T>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }
    this->empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }

    SimpleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new SimpleNode<T> (currentNodeCopy->getData());
    this->head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){
        SimpleNode<T>* nextNode = new SimpleNode<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    this->size = listToCopy.length();
    
    return *this;
}

/*
PARAMETROS: Recibe un indice de un elemento a borrar.
METODO: Verifica que la lista no este vacia y el indice este en el rango del tamaño de la lista. Busca la posición del nodo y lo elimina, y une los nodos anterior y posteriores.
ORDEN: O(n). n = indice de elementos que se van a recorrer.
RETURN: void. Regresa la lista el elemento del indice del argumento.
*/
template <class T>
void SimpleLL<T>::erase(int index){

    if(index >= this->size || index < 0 || this->head == nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }

    SimpleNode<T> * prevNode = (index != 0) ? this->getNode(index-1): this->head;
    SimpleNode<T> * nodeToErase = prevNode->getNext();
    prevNode->setNext(nodeToErase->getNext());

    delete nodeToErase;

}

/*
PARAMETROS: Recibe una lista del tipo de dato T.
METODO: Coloca el inicio de la lista en el ultimo nodo la lista original, y lo hace por referencia. Luego hace que la lista a combinar apunte a nullptr, vaciandola.
ORDEN: O(1).
RETURN: void. Regresa la lista original con los elementos de la lista agregada al final por referencia.
*/
template <class T>
void SimpleLL<T>::merge(SimpleLL<T>& listToAppend){
    getNode(this->size-1)->setNext(listToAppend.head);
    listToAppend.head=nullptr;
}

/*
PARAMETROS: Recibe una lista del tipo de dato T.
METODO: Coloca el inicio de la lista en el ultimo nodo la lista original, luego itera la listToAppend copiando su contenido en nuevos nodos.
ORDEN: O(n). n = cantidad de elementos a copiar.
RETURN: void. Regresa la lista original con los elementos de la lista agregada al final.
*/
template <class T>
void SimpleLL<T>::append(const SimpleLL<T>& listToAppend){
    SimpleNode<T>* currentNode=getNode(this->size-1), *currentCopyNode=listToAppend.head;
    while(currentCopyNode != nullptr){
        SimpleNode<T> *newNode = new SimpleNode<T> (currentCopyNode.data);
        currentNode -> setNext(currentCopyNode);
        currentNode = currentNode -> getNext();
        currentCopyNode = currentCopyNode -> getNext();
    }
    listToAppend.head=nullptr;
}

/*
PARAMETROS: Recibe un nodo y un indice al cual se insertara el nodo.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
ORDEN: O(n). n = index.
RETURN: Regresa como referencia del dato del nodo para que pueda ser modificado.
*/
template <class T>
void SimpleLL<T>::insert(SimpleNode<T>& nodeToInsert, int index){
    SimpleNode<T>* currentNode= this->getNode(index);
    SimpleNode<T>* nextCurrentNode=currentNode->getNext();

    currentNode->setNext(new SimpleNode<T> (nodeToInsert.getData()));
    currentNode->getNext()->setNext(nextCurrentNode);
}

template <class T>
void SimpleLL<T>::insert(T data, int index){
    this->insert(* new SimpleNode<T> (data), index);
}

/*
PARAMETROS: Recibe un dato tipo T a agregar a la lista.
METODO: Crea una lista con 1 solo elemento y la agrega a la lista grande con append().
ORDEN: O(1).
RETURN: void. Se agregó el elemento data a la listo
*/
template <class T>
void SimpleLL<T>::append(T data){
    SimpleNode<T>* temp = new SimpleNode<T> (data);
    this->append(*temp);
    delete temp;
}

