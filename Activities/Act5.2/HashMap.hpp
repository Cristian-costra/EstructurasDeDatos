#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

bool isPrime(int n)
{
    if(n < 2) return false;
    if(n == 2) return true;
    
    if(n % 2 == 0) return false;

    for(int i = 3; i * i <= n; i += 2){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

template <class _key, class _value>
struct mapElement{
    public: 
        _key key;
        int state;
        _value value;
        
        mapElement():key(_key()), state(-1), value(_value()){};

        friend std::ostream& operator<<(std::ostream& os, const mapElement<_key,_value>& mapElement){ // Se tuvo que agregar const para que aceptara tanto objetos temporales como persistentes. Para la impresión, se usa getData, que regresa un valor temporal. Al intentar ingresarlo a la función, que acepta por referencia, arroja un error de compilación. Por ende, se cambia a const que acepta ambos valores, y no copia ipFreq.
            os <<"["<< mapElement.key<<"] = "<<mapElement.value<<"  State: "<<mapElement.state;
            return os;
        }
        bool operator>(const mapElement<_key,_value>& otherMap){
            return value > otherMap.value;
        }
        bool operator == (const mapElement<_key,_value>& otherMap){
            return value == otherMap.value;
        }
        bool operator <= (const mapElement<_key,_value>& otherMap){
            return value < otherMap.value || value == otherMap.value ;
        }
        bool operator<(const mapElement<_key,_value>& otherMap){
            return value < otherMap.value;
        }
        bool operator!=(const mapElement<_key,_value>& otherMap){
            return value != otherMap.value;
        }
};


template <class _key = int, class _value = int> 
class HashMap{
    private: 
        mapElement<_key, _value> *map;
        size_t tableSize, size;
        hash(const _key& key);
    public:
        HashMap();
        HashMap(int _tableSize);
        ~HashMap();

        const HashMap& operator=(const HashMap& otherHashMap);
        _value& operator [](const _key& key);
        void insert(const _key& key, const _value& value);
        void show();
        void eliminate(const _key& key);

        void redimension(size_t newCapacity);

        int capacity();
        int getIndex(const _key& key);

};

/*
PARÁMETROS: void.
MÉTODO: Inicializa una tabla hash con tamaño de 23.
ORDEN: O(1).
RETURN: void.
*/
template <class _key, class _value> 
HashMap<_key, _value>::HashMap():tableSize(23), size(0){ // Número primo
    map = new mapElement<_key, _value>[tableSize];
}

template <class _key, class _value> 
HashMap<_key, _value>::~HashMap(){
    delete[] map;
}
/*
PARÁMETROS: `int _tableSize`.
MÉTODO: Inicializa una tabla hash con el tamaño de `_tableSize` vacío. Si `_tableSize` no es primo, busca el primer primo que le sigue.
ORDEN: O(k), donde k es la diferencia entre `_tableSize` y su siguiente primo.
RETURN: void.
*/
template <class _key, class _value> 
HashMap<_key, _value>::HashMap(int _tableSize): size(0){
    if(_tableSize < 0){
        throw(std::invalid_argument("negative argument for capacity constructor"));
    }

    if (_tableSize % 2 == 0){
        _tableSize ++;
    }
    while (!isPrime(_tableSize)){
        _tableSize += 2;
    }
    tableSize = _tableSize;
    map = new mapElement<_key,_value>[tableSize];
}


/*
PARÁMETROS: _key& key, llave a encontrar el hash.
MÉTODO: Regresa el hash de la llave `key` dependiendo del tipo de dato.
ORDEN: O(1).
RETURN: int, hash de la llave.
*/
template <class _key, class _value>
int HashMap<_key, _value>::hash(const _key& key) {
    if constexpr (std::is_same<_key, int>::value) {
        return key; 
    } else if constexpr (std::is_same<_key, std::string>::value) {
        int hash = 0;
        std::stringstream ss(key);
        std::string octet;

        while (std::getline(ss, octet, '.')) {
            int octetValue = std::stoi(octet);
            hash = (hash << 4) | ((octetValue & 60) >> 2); // Procesar el octeto.
        }

        return hash;
    } else {
        static_assert(false, "No se puede hacer hash de este tipo de dato");
    }
}


/*
PARÁMETROS: _key& key, llave a encontrar el hash.
MÉTODO: Regresa el índice base de la llave `key` con el método modular.
ORDEN: O(1).
RETURN: int, hash (índice base) de la llave.
*/
template <class _key, class _value> 
int HashMap<_key, _value>::getIndex(const _key& key){
    return hash(key) % tableSize;
}

/*
PARÁMETROS: _key& key, llave donde se insertará valor.
            _value& value, valor asociado a la llave.
MÉTODO: Usa la busqueda con el hash de la llave, e inserta el valor en la tabla hash hasta encontrar un espacio vacío.
        Si la tabla hash está llena, no inserta el valor.
        Si la llave ya existe, actualiza el valor asociado a la llave.
ORDEN: Mejor caso O(1). Peor caso O(n), donde n es la capacidad de la tabla hash `tableSize`.
RETURN: int, el tamaño de la tabla hash.
*/
template <class _key, class _value> 
void HashMap<_key, _value>::insert(const _key& key, const _value& value){

    if(float(size)/float(tableSize) > 0.75){
        redimension(2*tableSize);
    }

    int index = getIndex(key), i = 0; // se obtiene el índice a partir de la función hash
    
    for(int i = 0; map[index].state != -1 && i < tableSize; index = (index + 1) % tableSize, i++){
        if(map[index].key == key) { // Verifica si la llave ya existe
            map[index].value = value;
            return;
        }
    }

    if(map[index].state != 1){
        map[index].value = value;
        map[index].state = 1;
        map[index].key = key;
        size++;
    }

    if(float(size)/float(tableSize) > 0.75){
        redimension(2*tableSize);
    }
    
}

/*
PARÁMETROS: void.
MÉTODO: Busca el valor asociado a la llave `key` en la tabla hash. Si no lo encuentra, lo inserta. 
ORDEN: Mejor caso O(1). Peor caso O(n), donde n es la capacidad de la tabla hash `tableSize`.
RETURN: int, el tamaño de la tabla hash.
*/
template <class _key, class _value> 
void HashMap<_key, _value>::eliminate(const _key& key){
    int index = getIndex(key); // se obtiene el índice a partir de la función hash

    for(int i = 0; (map[index].key != key && map[index].state != -1) && i < tableSize; index = (index + 1) % tableSize, i++){} // NO sé cual de las dos condiciones sea más costosa en assembly. !(hash(index) + 1) o hash(index) == -1
    
    if(map[index].key == key && map[index].state == 1){
        map[index].key = _key();
        map[index].state = 0;
        map[index].value = _value();
    } else {
        throw(std::logic_error("No such value exists"));
    }
}

/*
PARÁMETROS: void.
MÉTODO: Imprime cada indice del array `map` que contiene los elementos insertados o vacios de la tabla hasg
ORDEN: O(n), donde n es el la capacidad de la tabla hash `tableSize`.
RETURN: void.
*/
template <class _key, class _value> 
void HashMap<_key, _value>::show(){
    mapElement<_key,_value> *current = map;
    for(int i = 0; i < tableSize; i++) {
        std::cout<< *(current + i) << "\n";
    }
    std::cout<<"\n";
}


/*
PARÁMETROS: void.
MÉTODO: Retorna la el atributo `tableSize` de la tabla hash. 
ORDEN: O(1).
RETURN: int, el tamaño de la tabla hash.
*/
template <class _key, class _value> 
int HashMap<_key, _value>::capacity(){
    return tableSize;
}

/*
PARÁMETROS: const _key& key, la llave a buscar en la tabla hash.
MÉTODO: Busca el valor asociado a la llave `key` en la tabla hash. Si no lo encuentra, lo inserta como valor default. 
ORDEN: Mejor caso O(1). Peor caso O(n), donde n es la capacidad de la tabla hash `tableSize`.
RETURN: int, el tamaño de la tabla hash.
*/
template <class _key, class _value> 
_value& HashMap<_key, _value>::operator[](const _key& key){

    if(size * 4 > tableSize * 3){
        redimension(2*tableSize);
    }

    int index = getIndex(key), i = 0;

    for(; (map[index].key != key && map[index].state == 1) && i < tableSize; index = (index + 1) % tableSize, i++){}

    if((map[index].key != key && map[index].state != 1) || (key==_key() && map[index].state != 1)){ // Si no lo encuentra, marca como encontrado, porque muy posiblemente, al valor que se regresa se asigne otro. Y si no se le asigna otro, no debería usarse esta función sino find.
        map[index].key=key;
        map[index].state = 1;
        size++;
    }
    
    return map[index].value;

}

/*
PARÁMETROS: `size_t newCapacity `.
MÉTODO: Redimenciona `map` con el nuevo tamaño, y por cada elemento ocupado en la lista pasada, los inserta en el nuevo `map`. 
ORDEN: O(n), donde n es `size`.
RETURN: void.
*/
template <class _key, class _value>
void HashMap<_key, _value>::redimension(size_t newCapacity){
    mapElement<_key,_value> *pastMap = map;
    map = new mapElement<_key,_value>[newCapacity];

    /* Rehashing*/
    int pastSize = tableSize;
    tableSize = newCapacity;
    size = 0;
    for(int i = 0; i < pastSize; i++){
        if(pastMap[i].state == 1)
            insert(pastMap[i].key, pastMap[i].value);
    }
    delete[] pastMap;    
}

/*
PARÁMETROS: const HashMap<_key, _value>& otherHash, tabla hash a copiar.
MÉTODO: Itera sobre la tabla hash `otherHash` y copia los elementos en estado `ocupado` en la tabla hash actual.
ORDEN: O(n), donde n es la cantidad de elementos de la tabla hash `size`.
RETURN: const HashMap<_key, _value>&, tabla hash a donde copiar.
*/
template <class _key, class _value>
const HashMap<_key, _value>& HashMap<_key, _value>::operator=(const HashMap<_key, _value>& otherHash){
    delete[] map;
    tableSize = otherHash.tableSize;
    for(int i = 0; i < tableSize; i++){
        if(otherHash.map[i].state != -1){
            map[i] = otherHash.map[i];
        }
    }
}

