#include <iostream>
#include <string>

#include "linkedList.cpp"
#include "HDCLinkedList.cpp"
#include "NodeC.cpp"
#include "Node.cpp"
#include "testConf.cpp"

/*
PARAMETROS: Lista que se desea invertir.
METODO: Remplaza los datos de la posición actual y la posición size-posición actual, remplazando el primer elemento y el último hasta llegar a la mitad de la lista.
ORDEN: O(n).
RETURN: Regresa la lista actual con los datos de los nodos remplazados de inicio a fin.
*/
template <class T>
HDCLinkedList<T> invertir(HDCLinkedList<T> lista){
    lista.invert();
    return lista;
}

/*
PARAMETROS: Rebibe una lista enlazada y un dato a buscar dentro de los nodos de esa lista.
METODO: Compara el dato de cada nodo en la lista hasta encontrar uno que coincida.
ORDEN: O(n).
RETURN: Regresa la posición del primer nodo que coincida con el dato, si no se encuentra, regresa 0.
*/
template <class T>
int buscar(HDCLinkedList<T>& lista, T data){
    return (lista.search(data)+1);
}

/*
PARAMETROS: Recibe una lista enlazada, un dato del tipo de dato del nodo y una posición del nodo en la lista.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
Remplaza el dato del nodo en la posición del argumento con el dato recibido en el argumento
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con un nodo extra en la posición indicada.
*/
template <class T>
void update(HDCLinkedList<T>& lista, int position, T data){
    lista.update(data, position-1);
}

/*
PARAMETROS: Rebibe la lista a ordenar.
METODO: Utiliza el algoritmo divide y venceras, que separa la lista a la mitad varias veces hasta tener listas de 1 nodo, compara los datos de estos nodos
y acomoda los nodos de menor a mayor de forma recursiva hasta ordenarlos en la lista original.
ORDEN: O(nlog(n)).
RETURN: Regresa la lista enlazada con sus nodos ordenados de menor a mayor según sus datos.
*/
template <class T>
HDCLinkedList<T> ordenar(HDCLinkedList<T> lista){
    lista.ordMerge(lista,lista.length());
    return lista;
}

template <class T>
void testLista(HDCLinkedList<T>& lista){
    std::cout<<"Lista original: ";
    lista.print();
    try{
        update(lista,POSITION_CHANGE,VALUE_CHANGE);
        std::cout<<"Cambio a "<<VALUE_CHANGE<< " en la posición "<<POSITION_CHANGE<<"\n";
        lista.print();
    } catch (std::invalid_argument){
        std::cout<<"Hubo un error intentado actualizar el valor\n";
    }

    try{
        int posicion = buscar(lista,VALUE_SEARCH);
        std::cout<<"El valor "<<VALUE_SEARCH<<" se encuentra en la posición "<<posicion<<"\n ";
    } catch (std::invalid_argument){
        
        std::cout<<"\nHubo un error buscando el valor\n"<<std::endl;
    }

    HDCLinkedList<std::string> nuevaLista = invertir(lista), nuevaLista2 = ordenar(lista);

    std::cout<<"\nLista original invertida: ";
    nuevaLista.print();
    std::cout<<"Lista original ordenada: ";
    nuevaLista2.print(); 
}

int main(){
    HDCLinkedList<std::string> lista = LIST_TEST;   
    testLista(lista);

}