#include "Trees/btree.h"


BTree::BTree(int pOrder){
	if(pOrder < 2) NodeB::Error(ERROR_INVALID_ORDER);
	_order = pOrder;
	_root = NULL;
}

BTree::~BTree(){

}


void BTree::insert(int pKey){
	if(_root == NULL){
		_root = new NodeB(_order);
		_root->insertKey(pKey);
	}

	else{
		if(_root->getKeyUsed() == (_order-ONE)){
			NodeB *newRoot = new NodeB(_order);
			newRoot->getChildren()[ZERO] = _root;
			_root->setParent(newRoot);
			newRoot->splitChild(ZERO, _root);

			int index = 0;
			if(newRoot->getKeys()[ZERO] < pKey)
				index++;
			newRoot->getChildren()[index]->insertNonFull(pKey);
			_root = newRoot;
		}
		else _root->insertNonFull(pKey);
	}
}
//void BTree::insert(int pKey){
//	if(_root != NULL){
//		if(_root->getKeyUsed() < (_order-1)){//Hay espacio para mas claves
//			if(_root->isLeaf()){//Es hoja
//				_root->insertKey(pKey);
//			}
//			else{//No es hoja
//				NodeB *node = this->findNodeToInsert(_root, pKey);
//				this->insertAux(node, pKey, NULL, NULL);
//			}
//		}
//		else{//No hay espacio para mas claves
//			if(_root->isLeaf()){//Es hoja
//				this->splitRoot(_root, pKey);
//			}
//			else{//No es hoja
//				//int childIndex = this->getChildIndex(_root->getKeys(), pKey);
//				//NodeB *child = _root->getChild(childIndex);
//				//#########################################################
//			}
//		}
//	}
//	else{//Árbol vacío
//		_root = new NodeB(_order);
//		_root->insertKey(pKey);
//	}
//}



void BTree::insertAux(NodeB *pNode, int pKey, NodeB *left, NodeB *right){
	if(pNode->getKeyUsed() < (_order-ONE)){//Hay espacio para mas claves
		int index = pNode->insertKey(pKey);
		pNode->setChild(index, left);
		pNode->setChild(index+ONE, right);
	}
	else{
		//int childIndex = this->getChildIndex(pNode->getKeys(), pKey);
		int indexNewParent = _order/TWO;
		NodeB *parent = pNode->getParent();
//		if(childIndex == indexNewParent){

//		}
	}

}



/**
 * @brief Método que busca el nodo donde se debe insertar la clave
 *
 * Recorre el árbol hasta encontrar el nodo hoja donde insertar
 *
 * @param pNode Nodo padre
 * @param pKey Clave a insertar
 *
 * @return Nodo hoja donde insertar
 */
NodeB *BTree::findNodeToInsert(NodeB *pNode, int pKey){
	NodeB *child= pNode;
	while(!child->isLeaf()){
//		int childIndex = this->getChildIndex(pNode->getKeys(), pKey);
//		child = child->getChild(childIndex);
	}

	return child;
}



/**
 * @brief Método que retorna la raíz del árbol
 *
 * @return Raíz del árbol
 */
NodeB *BTree::getRoot(){
	return _root;
}


///**
// * @brief Método que inserta una clave dentro del arreglo de claves de un nodo
// *
// * Este método solo es llamado cuando un arreglo de claves todavia tiene espacio
// * para insertar mas claves.
// * Se inicia con un indice menor al indice maximo y dentro de un bloque while
// * se comienza a recorrer el arreglo desde el mayor elemento hasta el menor, si
// * la clave a insertar es menor al elemento en el indice actual, este elemento
// * se mueve una posicion hacia adelante, de forma que se habre espacio para el nuevo
// * elemento. Cuando el elemento en el indice actual es menor que la clave a insertar,
// * se sale del while y se inserta la nueva clave en el espacio creado
// *
// * @param pArray Arreglo de claves de un nodo
// * @param pKey Clave a insertar
// */
//void BTree::insertInKeyArray(int *pArray, int pKey){
//	int i = _order-TWO;

//	while((pArray[i] > pKey || pArray[i] == EMPTY) && i >=ZERO){
//		pArray[i+ONE] = pArray[i];
//		i--;
//	}
//	pArray[i+ONE] = pKey;
//}



///**
// * @brief Método que permite obtener el indice del hijo donde insertar
// *
// * Este método es llamado cuando se va insertar una clave en un nodo que no
// * es hoja, por lo que se debe encontrar el hijo por el cual descender para
// * realizar la inserción
// *
// * @param pArray Arreglo de claves del nodo
// * @param pKey Clave a insertar
// *
// * @return Indice del nodo hijo por el cual se debe descender
// */
//int BTree::getChildIndex(int *pArray, int pKey){
//	int i = ZERO;
//	while((pArray[i] < pKey && pArray[i] != EMPTY) && i < (_order-ONE)){
//		i++;
//	}
//	if(i==(_order-TWO)) return i+ONE;
//	else return i;
//}



/**
 * @brief Método que divide la raíz del árbol cuando se inserta una clave
 *
 * Este método es llamado cuando la raíz tiene todas sus claves y se debe
 * insertar una mas. Se obtiene la posicion que tendria dentro del arreglo
 * si la nueva clave pudiera insertarse (index), luego se obtiene la mitad
 * del arreglo de claves y se crean los nodos correspondientes a la nueva
 * raíz y sus dos hijos. Dependiendo de "index" se insertan las claves
 * correspondientes a los dos hijos de la raíz.
 *
 * @param pRoot Raíz del árbol
 * @param pKey Clave a insertar
 */
void BTree::splitRoot(NodeB *pRoot, int pKey){
	int index = _order-ONE;

	while(pRoot->getKeys()[index] > pKey && index >=ZERO){
		index--;
	}
	index++;
	int indexNewRoot = _order/2;

	NodeB* newRoot = new NodeB(_order);
	NodeB* leftChild = new NodeB(_order);
	NodeB* rightChild = new NodeB(_order);

	if(index==indexNewRoot){
		newRoot->insertKey(pKey);

		for(int i=0; i<indexNewRoot; i++)
			leftChild->insertKey(pRoot->getKeys()[i]);
		for(int i=indexNewRoot; i<(_order-ONE); i++)
			rightChild->insertKey(pRoot->getKeys()[i]);
	}

	else{
		newRoot->insertKey(pRoot->getKeys()[indexNewRoot]);
		if(index<indexNewRoot){
			leftChild->insertKey(pKey);
			for(int i=0; i<(indexNewRoot-ONE); i++)
				leftChild->insertKey(pRoot->getKeys()[i]);
			for(int i=(indexNewRoot-ONE); i<(_order-ONE); i++){
				if(i != indexNewRoot)
					rightChild->insertKey(pRoot->getKeys()[i]);
			}
		}
		else{
			rightChild->insertKey(pKey);
			for(int i=0; i<indexNewRoot; i++)
				leftChild->insertKey(pRoot->getKeys()[i]);
			for(int i=(indexNewRoot+1); i<(_order-ONE); i++){
				rightChild->insertKey(pRoot->getKeys()[i]);
			}
		}
	}

	//delete _root;
	_root = newRoot;
	_root->setChild(ZERO, leftChild);
	_root->setChild(ONE, rightChild);
	leftChild->setParent(_root);
	rightChild->setParent(_root);

}

