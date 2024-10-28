// Act3_4
// Última modificación: 12/10/2024
// Cristian Ricardo Luque Arámbula - A01741850
// Oliver Moreno Ibarra - A01742930
// Rodolfo Blas Romero Valdez - A01741665

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <tuple>

#include "..\..\DataStructures\List\BaseLL.hpp"
#include "..\..\DataStructures\List\DoubleLL.hpp"
#include "..\..\DataStructures\Tree\SplayTree\SplayTree.hpp"

#include "algoritmos.cpp"

std::string lastIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }

    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]-1);

}

std::string nextIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }

    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]+1);
}

struct IpFreq{
    int freq;
    std::string ip;

    bool operator>(const IpFreq& other){
        return freq > other.freq;
    }
    bool operator<(const IpFreq& other){
        return freq < other.freq;
    }
    bool operator==(const IpFreq& other){
        return freq == other.freq;
    }
    bool operator!=(const IpFreq& other){
        return freq != other.freq;
    }
    friend std::ostream& operator<<(std::ostream& os, const IpFreq& ipFreq){
        os << "Frecuencia: " << ipFreq.freq << " IP: " << ipFreq.ip;
        return os;
    }
};

int main(){

    // std::ifstream bitacoraIn("bitacora.txt");
    // DoubleLL<std::string> linkedList;

    // if(!bitacoraIn.is_open()){
    //     std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
    //     return 1;
    // } else {
    //     std::string line;
    //     while(std::getline(bitacoraIn, line)){
    //         linkedList.append(line);
    //     }
    //     bitacoraIn.close();
    // }

    // DoubleLL<std::string>::Iterator itHalf=linkedList.begin()+linkedList.length()/2;
    // ordMerge(linkedList, itHalf, linkedList.length());
    // std::string ipInicial, ipFinal;

    // std::cout<<"Ingresa a partir de cuál IP se desea filtrar: ";
    // std::cin>>ipInicial;
    // ipInicial=lastIP(ipInicial);

    // std::cout<<"Ingrese la mayor IP que se desea mostrar: ";
    // std::cin>>ipFinal;
    // ipFinal=nextIP(ipFinal);
        
    // int posInic=busquedaBinaria(linkedList, ipInicial), posFin=busquedaBinaria(linkedList, ipFinal);
    // class DoubleLL<std::string>::Iterator it=linkedList.begin()+posInic, itFinal= linkedList.begin()+posFin;

    // std::map <int, DoubleLL<std::string>, std::greater<int>> frequenceLists;
    // std::ofstream bitacoraOut("bitacoraOut.txt");
    // std::ofstream bitacoraOutAccessDescIP("bitacoraOutAccessDescIP.txt");
    // bool complete= false; 

    // if(!bitacoraOut.is_open()){
    //     std::cerr << "No se pudo abrir el documento bitacoraOut.txt" << std::endl;
    //     return 1;
    // } else if (posInic <= posFin){
    //     if(posInic != posFin && !(it != itFinal)){
    //         --itFinal;
    //         complete = true; 
    //     }

    //     DoubleLL<std::string> temp; 
    //     while(it != itFinal){
    //         temp.append(*it);
    //         bitacoraOut << *it << std::endl;
    //         ++it;
    //         if(*temp.end() != *it){
    //             frequenceLists[temp.length()].merge(temp);
    //         }
    //     }

    //     if (complete){
    //         temp.append(*it);
    //         bitacoraOut << *it << std::endl;
    //         ++it;
    //         if(*temp.end() != *it){
    //             frequenceLists[temp.length()].merge(temp);
    //         }        
    //     }

    //     for(auto& element : frequenceLists){
    //         element.second.invert();
    //         bitacoraOutAccessDescIP<<element.second.turnToText();
    //     }

    //     bitacoraOut.close();
    //     bitacoraOutAccessDescIP.close();        
    // }
    
    // std::map<std::string, std::pair<int, DoubleLL<std::string>>> mapFrequency;
    // DoubleLL<std::string> temp;
    // it= linkedList.begin()+posInic;
    // while(it != itFinal){
    //     std::string port=obtainPort(*it);
    //     mapFrequency[port].first++;
    //     mapFrequency[port].second.append(*it);
    //     ++it;
    // }

    // std::multimap<int, DoubleLL<std::string>, std::greater<int>> sortedPorts;
    // for(auto& [port, stats]: mapFrequency){
    //     stats.second.invert();
    //     sortedPorts.insert({stats.first,stats.second});
    // }

    // std::ofstream bitacoraOutAccessDescPORT("bitacoraOutAccessDescPORT.txt");
    // for(auto& portSection:sortedPorts){
    //     bitacoraOutAccessDescPORT<<portSection.second.turnToText();
    // }
    // bitacoraOutAccessDescPORT.close();



    // -----------------------------------

    std::cout << "\n\n";
    std::cout << "Oliver \n\n" << std::endl;
    // 1. Leer el archivo bitacora.txt
    std::ifstream myBitacora("bitacora.txt");
    if(!myBitacora.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    }

    // 2. Crear una lista doblemente ligada con los registros de la bitácora
    std::string myLine;
    DoubleLL<std::string> myBitacoraList;
    while(std::getline(myBitacora, myLine)){
        myBitacoraList.append(myLine);
    }
    myBitacora.close();

    // 3. Ordenar la lista con el algoritmo Merge Sort
    ordMerge(myBitacoraList, myBitacoraList.begin(), myBitacoraList.length());
    myBitacoraList.print();
    std::cout << "\n\n\n\n\n";

    // 4. Separar la lista por frecuencia de IP en un mapa
    std::map<int, DoubleLL<std::string>, std::greater<int>> myMap;
    DoubleLL<std::string> temp;
    temp.empty();
    for(auto it=myBitacoraList.begin(); it!=myBitacoraList.end(); ++it){
        if(!temp.isEmpty() && obtainIp(*temp.end()) != obtainIp(*it)){
            myMap[temp.length()] = temp;
            temp.empty();
        }
        temp.append(*it);
    }
    // Añadir la ultima lista
    if (!temp.isEmpty()) {
        myMap[temp.length()] = temp;
    }

    // for(auto& [key, value] : myMap){
    //     std::cout << "Key: " << key << "\nValue:\n";
    //     value.print();
    //     std::cout << "\n";
    // }


    // 5. Crear un struct con frecuencia y ip de las 5 ips más frecuentes

    IpFreq myIpFreq[5];
    int i = 0;
    for (auto& [key, value] : myMap){
        if (i < 5){
            myIpFreq[i].freq = key;
            myIpFreq[i].ip = obtainIp(*value.begin());
            i++;
        }
    }
    for(int i=0; i<5; i++){
        std::cout << "Frecuencia: " << myIpFreq[i].freq << " IP: " << myIpFreq[i].ip << std::endl;
    }

    // 6. Crear un árbol splay con las ips

    SplayTree<IpFreq> mySplayTree;
    for(int i=0; i<5; i++){
        mySplayTree.insert(myIpFreq[i]);
    }

    // 7. Imprimir el árbol en inOrder
    std::cout << "\n";
    std::cout << "InOrder:\n";
    mySplayTree.inOrder();
    std::cout << "PreOrder:\n";
    mySplayTree.preOrder();
    std::cout << "PostOrder:\n";
    mySplayTree.postOrder();



    // 7. Crear 3 arboles, para clase A, B y C
    SplayTree<IpFreq> mySplayTreeA; // 0.0.0.0 - 127.255.255.255
    SplayTree<IpFreq> mySplayTreeB; // 128.0.0.0 - 191.255.255.255
    SplayTree<IpFreq> mySplayTreeC; // 192.0.0.0 - 223.255.255.255

    // 8. Insertar en los arboles todas las ips correspondientes
    for(auto& [key, value] : myMap){
        std::string ip = obtainIp(*value.begin());
        IpFreq classIpFrec;
        classIpFrec.freq = key;
        classIpFrec.ip = ip;
        if(ip == "") continue;
        int ip1 = std::stoi(ip.substr(0, ip.find('.')));
        if (ip1 >= 0 && ip1 <= 127){
            mySplayTreeA.insert(classIpFrec);
        } else if (ip1 >= 128 && ip1 <= 191){
            mySplayTreeB.insert(classIpFrec);
        } else if (ip1 >= 192 && ip1 <= 223){
            mySplayTreeC.insert(classIpFrec);
        }
    }

    // 9. Imprimir los arboles
    std::cout << "\n";
    std::cout << "Mayor a menor A:\n";
    mySplayTreeA.inReverseOrder();
    std::cout << "Mayor a menor B:\n";
    mySplayTreeB.inReverseOrder();
    std::cout << "Mayor a menor C:\n";
    mySplayTreeC.inReverseOrder();
    

    // -----------------------------------
    return 0;

}