#pragma once
#include "BaseLL.hpp"
#include "DoubleNode.hpp"
#include <stdexcept>
#include <string>

template<class T>
class DoubleLL:public BaseLL<T, DoubleNode<T>>{
    public:
        DoubleLL();
        DoubleLL(const DoubleLL<T>& listToCopy);
        DoubleLL(std::initializer_list<T> elements);
        ~DoubleLL() override;

        const DoubleLL<T>& operator=(const DoubleLL<T> & listToCopy);

        void append(const DoubleNode<T>& nodeToAppend);
        virtual void append(T data) override;

        void append(const DoubleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(DoubleLL<T>& listToAppend); // Conecta el último elemento de la primera al primero de la segunda. 

        virtual void erase(int index) ;

        virtual void insert(T data, int index) override;
        virtual void insert(DoubleNode<T>& nodeToInsert, int index);

        std::string turnToText();

        void empty() override;
        void print();

        class Iterator{
            private:
                DoubleNode<T> *current;
            public:
                Iterator(DoubleNode<T> *currentNode);

                T& operator*();
                Iterator& operator++();
                Iterator& operator--();
                Iterator& operator+(unsigned int transIndex);
                Iterator& operator-(unsigned int transIndex);
                bool operator!=(const Iterator& otro) const;
        };
        Iterator begin();
        Iterator end();
};

/*
PARAMETROS: void.
METODO: Construye una lista doblemente enlazada con un nodo cabeza apuntando a nullptr.
ORDEN: O(1).
RETURN: void. Se construye una nueva lista por defecto.
*/
template <class T>
DoubleLL<T>::DoubleLL(){ 
    this->head =new DoubleNode<T> (T());        
    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
    this->size=0;
}

/*
PARAMETROS: void.
METODO: Llama al método empty que elimina los nodos de la lista y a la cabeza.
ORDEN: O(n). n = tamaño de la lista.
RETURN: void. Se elimina la lista.
*/
template <class T> 
DoubleLL<T>::~DoubleLL(){
    empty();
    delete this->head;
}

/*
PARAMETROS: void.
METODO: Mientras que la lista no este vacia, recorre la lista de inicio a fin y elimina cada nodo hasta llegar al que apunta la cabeza, borra todos y crea un nuevo nodo default a la cabeza, .
ORDEN: O(n). n = tamaño de la lista.
RETURN: void. Se elimina la lista.
*/
template <class T>
void DoubleLL<T>::empty(){
    if(this->size == 0){
        return;
    }

    DoubleNode<T>* current = this->head;

    do{
        DoubleNode<T> *temp = current; 
        current = current->getNext();
        delete temp; 
    }while ( current != this->head);

    this->head=new DoubleNode<T> (T());
    this->size=0;
}

/*
PARAMETROS: std::initializer_list<T> elements, lista de elementos.
METODO: Agrega los elementos de la lista a agregar al final de la lista actual.
ORDEN: O(n). n = tamaño de la lista a agregar.
RETURN: void. Regresa la lista doble con esos elementos.
*/
template <class T>
DoubleLL<T>::DoubleLL(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head = nullptr;
    } else{
        auto iterador = elements.begin(); 

        this->head = new DoubleNode<T> (*iterador); 
        DoubleNode<T>* currentNode = this->head;
        currentNode->setPrevious(this->head);
        iterador++;
        this->size = 1;

        for (; iterador != elements.end(); ++iterador){
            DoubleNode<T>* nextNode = new DoubleNode<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode = nextNode;
            this->size++;
        }
        
        currentNode->setNext(this->head);
        this->head->setPrevious(currentNode);
    }
}

/*
PARAMETROS: DoubleLL<T>& listToCopy, lista de elementos.
METODO: Agrega los elementos de la lista a agregar al final de la lista actual.
ORDEN: O(n). n = tamaño de la lista a agregar.
RETURN: void. Regresa la lista doble con esos elementos.
*/
template <class T>
DoubleLL<T>:: DoubleLL(const DoubleLL<T>& listToCopy){
    this->head = new DoubleNode<T> (T());

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    *this = listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

/*
PARAMETROS: DoubleNode<T>& nodeToAppend, nodo a agregar.
METODO: Agrega un nuevo nodo a un elemento atras de la cabeza.
ORDEN: O(1).
RETURN: void. Regresa la lista doble con un nodo nuevo al final.
*/
template <class T>
void DoubleLL<T>::append(const DoubleNode<T>& nodeToAppend){
    DoubleNode<T>* newNode = (this->size == 0) ? this->head : new DoubleNode<T> (nodeToAppend.getData());
    if(this->size == 0){
        this->head->setData(nodeToAppend.getData());
    } else {
        this->head->getPrevious()->setNext(newNode);
        newNode->setPrevious(this->head->getPrevious());
    }

    newNode->setNext(this->head);
    this->head->setPrevious(newNode);
    this->size++;
}

/*
PARAMETROS: Recibe una lista del tipo de dato T.
METODO: Coloca el inicio de la lista en el ultimo nodo la lista original, luego itera la listToAppend copiando su contenido en nuevos nodos y los une.
ORDEN: O(n). n = cantidad de elementos a copiar.
RETURN: void. Regresa la lista original con los elementos de la lista agregada al final.
*/
template <class T>
void DoubleLL<T>::append(const DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    DoubleNode<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;

    if(this->size == 0){
        this -> head -> setData(listToAppend.head->getData());
        currentNode=this->head;
        this->head->setNext(currentNode);
        this->head->setPrevious(currentNode);
    } else{
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
    }

    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy != listToAppend.head){
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
        
        currentNodeCopy = currentNodeCopy->getNext();
    }
    
    currentNode->setNext(this->head);
    currentNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(currentNode);
    this->size += listToAppend.size;
}

/*
PARAMETROS: Recibe una lista del tipo de dato T.
METODO: Verifica que el tamaño de la nueva lista no sea 0, y agrega el primer elemento y ultimo al final e inicio de la lista actual, vaciando la lista que se agrego.
ORDEN: O(1).
RETURN: void. Regresa la lista original con los elementos de la lista agregada al final por referencia.
*/
template <class T>
void DoubleLL<T>::merge(DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    if(this->size==0){
        this->head=listToAppend.head;
        listToAppend.head=new DoubleNode<T> (T());
        listToAppend.head->setNext(listToAppend.head);
        listToAppend.head->setPrevious(listToAppend.head);
        listToAppend.size=0;
        this->size++;
        return;
    }

    DoubleNode<T>* listToAppendHeadCopy = listToAppend.head;    
    DoubleNode<T>* temp = listToAppend.head->getPrevious();

    temp->setNext(this->head);
    this->head->getPrevious()->setNext(listToAppend.head);
    this->head->setPrevious(temp);
    this->size+=listToAppend.size;

    listToAppend.head=new DoubleNode<T> (T());
    listToAppend.head->setNext(listToAppend.head);
    listToAppend.head->setPrevious(listToAppend.head);

    listToAppend.size=0;
}

/*
PARAMETROS: DoubleLL<T>, Recibe una lista para copiarla.
METODO: Verifica que no se iguale con la lista original. Vacia la lista y copia los datos de cada nodo
de la nueva lista en nuevos nodos y los agrega al final de la lista actual hasta llegar al final de la lista a copiar.
ORDEN: O(n). n = elementos de la lista a copiar.
RETURN: DoubleLL<T>. Se copia la lista a copiar con nuevos nodos.
*/
template<class T>
const DoubleLL<T> & DoubleLL<T>::operator=(const DoubleLL<T> & listToCopy) {
    if (this == &listToCopy){ 
        return *this;
    }
    
    empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    DoubleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new DoubleNode<T> (currentNodeCopy->getData());
    this->head = currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != listToCopy.head){

        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }

    currentNode->setNext(this->head);
    this->head->setPrevious(currentNode);

    this->size = listToCopy.size;

    return *this;
}

/*
PARAMETROS: Recibe un indice de un elemento a borrar.
METODO: Verifica que la lista no este vacia y el indice este en el rango del tamaño de la lista. Busca la posición del nodo y lo elimina, y une los nodos anterior y posteriores.
ORDEN: O(n). n = indice de elementos que se van a recorrer.
RETURN: void. Regresa la lista el elemento del indice del argumento.
*/
template <class T>
void DoubleLL<T>::erase(int index){


    if(index >= this->size || index < 0 || this->head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }


    DoubleNode<T>* currentNode = this->head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (index == 1){
        this->head = currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i = 0;i <= index; i++){
            currentNode = currentNode->getNext();
        }
        DoubleNode<T>*temp = currentNode->getNext();
        temp->getNext()->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    this->size--;
}

/*
PARAMETROS: Recibe un nodo y un indice al cual se insertara el nodo.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
ORDEN: O(n). n = index.
RETURN: Regresa como referencia del dato del nodo para que pueda ser modificado.
*/
template <class T>
void DoubleLL<T>::insert(T data, int index){
    this->insert(* new DoubleNode<T> (data), index);
}

/*
PARAMETROS: Recibe un dato tipo T a agregar a la lista.
METODO: Crea una lista con 1 solo elemento y la agrega a la lista grande con append().
ORDEN: O(1).
RETURN: void. Se agregó el elemento data a la listo
*/
template <class T>
void DoubleLL<T>::append(T data){
    DoubleNode<T> temp(data);
    this->append(temp);
}

/*
PARAMETROS: void.
METODO: Recorre cada elemento de la lista e imprime cada valor de sus nodos.
ORDEN: O(n). n = tamaño de la lista
RETURN: void. Imprime cada elemento de la lista.
*/
template <class T>
void DoubleLL<T>::print(){
    DoubleNode<T>* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    do{
        std::cout<<currentNode->getData()<<"\n";
        currentNode=currentNode->getNext();
    } while(currentNode -> getNext() != this->head);
    std::cout<<std::endl;
}

template <class T>
std::string DoubleLL<T>::turnToText(){
    std::string text;
    DoubleLL<T>::Iterator it = this->begin();
    for(; it != this->end(); ++it){
        text+=*it+"\n";
    }
    text+=*it+"\n";
    return text; 
}

/*
PARAMETROS: Recibe un nodo y un indice al cual se insertara el nodo.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
ORDEN: O(n). n = index.
RETURN: Regresa como referencia del dato del nodo para que pueda ser modificado.
*/
template <class T>
void DoubleLL<T>::insert(DoubleNode<T>& nodeToInsert, int index){
    if(index >= this->size || index < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    DoubleNode<T>* currentNode = this->head;
    for(int i = 1; i < index; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    DoubleNode<T>* newNode = new DoubleNode<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    newNode->setPrevious(currentNode);
    
    newNode->getNext() -> setPrevious(newNode);

    currentNode->setNext(newNode);
    this->size++;
}

template <class T>
DoubleLL<T>::Iterator::Iterator(DoubleNode<T>* currentNode) 
    : current(currentNode){}

template <class T>
T& DoubleLL<T>::Iterator::operator*() {
    return current->getData();
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator++() {
    current = current->getNext();
    return *this;
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator--() {
    if(current)
    current = current->getPrevious();
    return *this;
}

template <class T>
typename DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator+(unsigned int transIndex)
{
    if(this == nullptr){
        throw(std::invalid_argument("La lista está vacía. "));
    }
    for(int i=0; i<transIndex; i++){
        current=current->getNext();
    }
    return *this;
}

template <class T>
typename DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator-(unsigned int transIndex)
{
    if(this == nullptr){
        throw(std::invalid_argument("La lista está vacía. "));
    }
    for(int i=0; i<transIndex; i++){
        current=current->getPrevious();
    }
    return *this;
}

template <class T>
bool DoubleLL<T>::Iterator::operator!=(const Iterator& otro) const {
    return current != otro.current;
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::begin() {
    return Iterator(this->head);
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::end() {
    return Iterator(this->head->getPrevious());
}
