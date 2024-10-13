// Act2_3
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

#include "BaseLL.hpp"
#include "SimpleLL.hpp"
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

int main(){

    std::ifstream bitacoraIn("bitacora.txt");
    DoubleLL<std::string> linkedList;

    if(!bitacoraIn.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    } else {
        std::string line;
        while(std::getline(bitacoraIn, line)){
            linkedList.append(line);
        }
        bitacoraIn.close();
    }

    DoubleLL<std::string>::Iterator itHalf=linkedList.begin()+linkedList.length()/2;
    ordMerge(linkedList, itHalf, linkedList.length());
    std::string ipInicial, ipFinal;

    std::cout<<"Ingresa a partir de cuál IP se desea filtrar: ";
    std::cin>>ipInicial;
    ipInicial=lastIP(ipInicial);

    std::cout<<"Ingrese la mayor IP que se desea mostrar: ";
    std::cin>>ipFinal;
    ipFinal=nextIP(ipFinal);
        
    int posInic=busquedaBinaria(linkedList, ipInicial), posFin=busquedaBinaria(linkedList, ipFinal);
    class DoubleLL<std::string>::Iterator it=linkedList.begin()+posInic, itFinal= linkedList.begin()+posFin;

    std::map <int, DoubleLL<std::string>, std::greater<int>> frequenceLists;
    std::ofstream bitacoraOut("bitacoraOut.txt");
    std::ofstream bitacoraOutAccessDescIP("bitacoraOutAccessDescIP.txt");
    bool complete= false; 

    if(!bitacoraOut.is_open()){
        std::cerr << "No se pudo abrir el documento bitacoraOut.txt" << std::endl;
        return 1;
    } else if (posInic <= posFin){
        if(posInic != posFin && !(it != itFinal)){
            --itFinal;
            complete = true; 
        }

        DoubleLL<std::string> temp; 
        while(it != itFinal){
            temp.append(*it);
            bitacoraOut << *it << std::endl;
            ++it;
            if(*temp.end() != *it){
                frequenceLists[temp.length()].merge(temp);
            }
        }

        if (complete){
            temp.append(*it);
            bitacoraOut << *it << std::endl;
            ++it;
            if(*temp.end() != *it){
                frequenceLists[temp.length()].merge(temp);
            }        
        }

        for(auto& element : frequenceLists){
            element.second.invert();
            bitacoraOutAccessDescIP<<element.second.turnToText();
        }

        bitacoraOut.close();
        bitacoraOutAccessDescIP.close();        
    }
    
    std::map<std::string, std::pair<int, DoubleLL<std::string>>> mapFrequency;
    DoubleLL<std::string> temp;
    it= linkedList.begin()+posInic;
    while(it != itFinal){
        std::string port=obtainPort(*it);
        mapFrequency[port].first++;
        mapFrequency[port].second.append(*it);
        ++it;
    }

    std::multimap<int, DoubleLL<std::string>, std::greater<int>> sortedPorts;
    for(auto& [port, stats]: mapFrequency){
        stats.second.invert();
        sortedPorts.insert({stats.first,stats.second});
    }

    std::ofstream bitacoraOutAccessDescPORT("bitacoraOutAccessDescPORT.txt");
    for(auto& portSection:sortedPorts){
        bitacoraOutAccessDescPORT<<portSection.second.turnToText();
    }
    bitacoraOutAccessDescPORT.close();
    return 0;

}