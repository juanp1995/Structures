#ifndef STACK_H
#define STACK_H

#include "Nodes/Lists/node_dll.h"

/**
 * @file Stack.h
 * @brief Clase Stack
 * @author Juan Pablo Brenes
 * @date 26/11/15
 */

template<class T>
class Stack{
private:
    Node_DLL<T> *_head;
    Node_DLL<T> *_tail;

public:
    Stack();
    void push(const T &pData);
    Node_DLL<T>* pop();

};

#endif // STACK_H


/**
 * Constructor de la clase
 * Inicializa los puntero al head y tail en nulo;
 */
template<class T>
Stack<T>::Stack(){
    _head = 0;
    _tail = 0;
}



/**
 * Metodo que permite apilar un dato
 */
template<class T>
void Stack<T>::push(const T &pData){
    if(_head == 0){
        _head = _tail = new Node_DLL<T>(pData);
    }
    else{
        Node_DLL<T> *node = new Node_DLL<T>(pData);
        node->setPrev(_tail);
        _tail->setNext(node);
        _tail = node;
    }
}



/**
 * Metodo que permite desapilar un dato
 */
template<class T>
Node_DLL<T>* Stack<T>::pop(){
    if(_head == 0) return 0;
    else{
        Node_DLL<T> *tmp = _tail;
        _tail = _tail->getPrev();
        return tmp;
    }
}


