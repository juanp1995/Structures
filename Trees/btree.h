#ifndef BTREE
#define BTREE

#include "Nodes/Trees/node_b.h"
#include <QDebug>

#define ERROR_INVALID_ORDER "El orden del árbol no puede ser menor a 2"
#define TWO 2


/**
 * @file btree.h
 * @brief Clase BTree: Permite crear un árbol B
 * @author Juan Pablo Brenes Coto
 * @date 6/11/2015
 */

class BTree{

public:
	BTree(int pOrder);									//Constructor
	~BTree();											//Destructor

	void insert(int pKey);								//Método para insertar una clave

	NodeB *getRoot();									//Método para obtener la raíz del árbol


private:
	int _order;											//Orden el árbol
	NodeB *_root;										//Raíz del árbol

	void insertInKeyArray(int *pArray, int pKey);		//Método para insertar una clave en orden
//	int getChildIndex(int *pArray, int pKey);			//Método para obtener el indice del hijo donde insertar

	void splitRoot(NodeB *pRoot, int pKey);				//Método que divide la raíz cuando sus claves esta llenas
	void insertAux(NodeB *pNode, int pKey, NodeB *left, NodeB *right);
	NodeB* findNodeToInsert(NodeB *pNode, int pKey);
	};

#endif // BTREE

