#include <iostream>
#include "Queue\Queue.hpp"

template <class T>
class PriorityQueue: public Queue<T>{
    public: 
        PriorityQueue();
        PriorityQueue(std::initializer_list list):Queue<T>(list){};

        T& pop();
        void push(T data);
        void rearrangeUp(T data);
        void rearrangeDown(int index);

        void relocateUp(int index);

        top();
        empty();
        size();

};

