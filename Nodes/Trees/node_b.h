#ifndef NODE_B
#define NODE_B

#include <stdlib.h>
#include <iostream>

#define ONE 1
#define TWO 2
#define ZERO 0
#define EMPTY -1
#define ERROR_INDEX_KEYS "Índice de clave fuera de los limites"
#define ERROR_INDEX_CHILDREN "Indice de hijos fuera de los limites"

/**
 * @file node_b.h
 * @brief Clase NodeB: Crea un nodo para un árbol B
 * @author Juan Pablo Brenes Coto
 * @date 5/11/2015
 */

class NodeB{

public:
	NodeB(int pOrder);							//Constructor
	~NodeB();									//Destructor

	int getKey(int pIndex);						//Método para obtener una clave
	int *getKeys();								//Método para obtener el arreglo de claves
	int insertKey(int pKey);					//Método para almacenar una clave
	void deleteKey(int pKey);					//Método para borrar una clave

	void insertNonFull(int pKey);
	void splitChild(int pIndex, NodeB *pChild);
	int getChildIndex(int pKey);


	NodeB *getChild(int pIndex);				//Método para obtener un hijo
	NodeB **getChildren();						//Método para obtener el arreglo de hijos
	void setChild(int pIndex, NodeB *pChild);	//Método para establecer un hijo

	NodeB *getParent();							//Método para obtener el padre
	void setParent(NodeB *pParent);				//Método para establecer el padre

	bool isLeaf();								//Método para saber si el nodo es hoja
	int getKeyUsed();							//Método para obtener la cantidad de claves usadas
	void addKeyUsed();							//Método que aumenta en 1 la cantidad de claves usadas
	void reduceKeyUsed();
	void print();								//Método que imprime la claves del nodo

	static void Error(char* const pMessage);	//Método para imprimir mensajes de error

private:
	int _order;									//Cantidad maxima de hijos
	int _keysUsed;								//Cantidad de claves en uso
	int *_keys;									//Arreglo de claves
	NodeB **_children;							//Arreglo de hijos
	NodeB *_parent;								//Puntero al nodo padre

	void initChildren();						//Método que inicializa el arreglo de hijos
	void initKeys();							//Método que inicializa el arreglo de claves
	};

#endif // NODE_B

