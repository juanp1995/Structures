#include "Nodes/Trees/node_b.h"

/**
 * @brief Constructor que recibe el orden del árbol B
 *
 * Inicializa las variables globales y los arreglos de las claves
 * y los nodos hijo
 *
 * @param pOrder Cantidad de maxima de nodos hijo
 */
NodeB::NodeB(int pOrder){
	_order = pOrder;
	_parent = NULL;
	_keysUsed = ZERO;
	_keys = new int[_order-ONE];
	_children = new NodeB*[_order];
	this->initChildren();
	this->initKeys();
}



/**
 * @brief Destructor de la clase
 *
 * Recorre el arreglo de hijo y los borra
 * Borra el arreglo de claves del nodo
 */
NodeB::~NodeB(){
	for(int i=0; i<_order; i++)
		delete _children[i];
	delete[] _keys;
}



/**
 * @brief Método para obtener una clave
 *
 * Se comprueba si el indice donde se encuentra la clave se encuentra
 * dentro de los limites del tamaño del arreglo, si es asi se retorna
 * la clave almacanada en ese indice, sino se llama al método Error
 * con un mensaje
 *
 * @see NodeB::Error(char* const pMessage);
 *
 * @param pIndex Indice donde se encuentra la clave en el arreglo
 *
 * @return Clave
 */
int NodeB::getKey(int pIndex){
	if(pIndex <= (_order-ONE))
		return _keys[pIndex];
	else
		Error(ERROR_INDEX_KEYS);
}



/**
 * @brief Método para obtener el arreglo de claves
 *
 * @return Arreglo con las claves del nodo
 */
int *NodeB::getKeys(){
	return _keys;
}



/**
 * @brief Método para obtener un hijo del nodo
 *
 * Se comprueba si el indice donde se encuentra el nodo hijo esta dentro
 * de los limites del tamaño del arreglo, si es asi se retorna el nodo
 * hijo almacenado en el indice, sino se llama al método error con un
 * mensaje
 *
 * @see NodeB::Error(char* const pMessage);
 *
 * @param pIndex Indice donde se encuentra el nodo hijo en el arreglo
 *
 * @return Nodo hijo
 */
NodeB *NodeB::getChild(int pIndex){
	if(pIndex <= _order)
		return _children[pIndex];
	else
		Error(ERROR_INDEX_CHILDREN);
}



/**
 * @brief Método para obtener el arreglo de hijos del nodo
 *
 * @return Arreglo de hijos
 */
NodeB **NodeB::getChildren(){
	return _children;
}



/**
 * @brief Método para obtener el nodo padre
 *
 * @return Nodo padre
 */
NodeB *NodeB::getParent(){
	return _parent;
}



/**
 * @brief Método para establecer un nodo hijo
 *
 * Se comprueba si el indice donde se almacenara el nuevo nodo
 * se encuentra dentro de los limites del tamaño del arreglo,
 * si es asi se almacena el nodo en ese indice, sino se llama
 * al método Error con un mensaje
 *
 * @see NodeB::Error(char* const pMessage);
 *
 * @param pIndex Indice donde se almacena el nodo hijo
 * @param pChild Nuevo nodo hijo
 */
void NodeB::setChild(int pIndex, NodeB *pChild){
	if(pIndex <= _order){
		_children[pIndex] = pChild;
		pChild->setParent(this);
	}
	else
		Error(ERROR_INDEX_CHILDREN);
}



/**
 * @brief Método para almacenar una clave
 *
 * Se inicia con un indice menor al indice maximo y dentro de un bloque while
 * se comienza a recorrer el arreglo desde el mayor elemento hasta el menor, si
 * la clave a insertar es menor al elemento en el indice actual, este elemento
 * se mueve una posicion hacia adelante, de forma que se habre espacio para el nuevo
 * elemento. Cuando el elemento en el indice actual es menor que la clave a insertar,
 * se sale del while y se inserta la nueva clave en el espacio creado
 *
 * @param pKey Clave a insertar
 *
 * @return Indice dentro del arreglo donde se inserto la clave
 */
int NodeB::insertKey(int pKey){
	int i = _order-TWO;

	while((_keys[i] > pKey || _keys[i] == EMPTY) && i >=ZERO){
		_keys[i+ONE] = _keys[i];
		i--;
	}
	_keys[i+ONE] = pKey;
	_keysUsed++;

	return i+ONE;
}



/**
 * @brief Método que borra una clave
 *
 * Recorre el arreglo de claves hasta encontrar la clave a borrar,
 * luego almacena sobre esta la clave adyacente, asi hasta alcanzar
 * el final del arreglo. De modo que los espacios vacios quedan al
 * final del arreglo
 *
 * @param pKey Clave a borrar
 */
void NodeB::deleteKey(int pKey){
	if(_keys[_order-TWO] == pKey) _keys[_order-TWO] = EMPTY;
	else{
		bool flag = false;
		for(int i=ZERO; i<(_order-ONE); i++){
			if(flag){
				if(i == (_order-TWO))
					_keys[i] = EMPTY;
				else
					_keys[i] = _keys[i+ONE];
			}
			else{
				if(_keys[i] == pKey){
					_keysUsed--;
					_keys[i] = _keys[i+ONE];
					flag = true;
				}
			}
		}
	}
}




void NodeB::insertNonFull(int pKey){
	if(this->isLeaf()){
		this->insertKey(pKey);
	}

	else{
		int indexChild = this->getChildIndex(pKey);

		if(_children[indexChild]->getKeyUsed() == (_order-ONE)){
			this->splitChild(indexChild, _children[indexChild]);

			if(_keys[indexChild] < pKey)
				indexChild++;
		}
		_children[indexChild]->insertNonFull(pKey);
	}
}




void NodeB::splitChild(int pIndex, NodeB *pChild){
	NodeB *newChild = new NodeB(_order);
	newChild->setParent(this);

	int middle = (_order-ONE)/TWO;
	if(middle < (_order-ONE)){
		for(int i=(middle+ONE); i<(_order-ONE); i++){
			newChild->insertKey(pChild->getKeys()[i]);
			pChild->getKeys()[i] = EMPTY;
			pChild->reduceKeyUsed();
		}


		if(!pChild->isLeaf()){
			for(int i=0; i<_order; i++){
				newChild->getChildren()[i] = pChild->getChildren()[(middle+ONE)+i];
				pChild->getChildren()[(middle+ONE)+i] = NULL;
			}
		}
	}

	for(int i=(_order-ONE); i>pIndex; i--)
		_children[i] = _children[i-ONE];
	_children[pIndex+ONE] = newChild;

	this->insertKey(pChild->getKeys()[middle]);
	pChild->getKeys()[middle] = EMPTY;

}




int NodeB::getChildIndex(int pKey){
	int i = ZERO;
	while((_keys[i] < pKey && _keys[i] != EMPTY) && i < (_order-ONE)){
		i++;
	}
	return i;
}



/**
 * @brief Método para establecer el nodo padre
 *
 * @param pParent Nodo padre
 */
void NodeB::setParent(NodeB *pParent){
	_parent = pParent;
}



/**
 * @brief Método para saber si el nodo es hoja
 *
 * Recorre la lista de hijos comprobando si son nulos o no
 *
 * @return True si es hoja, false en caso contrario
 */
bool NodeB::isLeaf(){
	bool flag = true;
	for(int i=0; i<_order; i++){
		if(_children[i] != NULL){
			flag = false;
			break;
		}
	}
	return flag;
}



/**
 * @brief NodeB::getKeyUsed
 * @return
 */
int NodeB::getKeyUsed(){
	return _keysUsed;
}



/**
 * @brief Método que permite aumentar en 1 la cantidad de claves usadas
 */
void NodeB::addKeyUsed(){
	_keysUsed++;
}




void NodeB::reduceKeyUsed(){
	_keysUsed--;
}



/**
 * @brief Método que imprime las claves almacenadas por el nodo
 */
void NodeB::print(){
	int i;
	for(i=0; i<(_order-ONE); i++){
		if(!this->isLeaf())
			_children[i]->print();
		if(_keys[i] != EMPTY) std::cout << _keys[i] << std::endl;
	}
	if(!this->isLeaf())
		_children[i]->print();
}



/**
 * @brief Método que inicializa el arreglo de hijos
 *
 * Recorre el arreglo que contiene los punteros a los nodos hijo
 * y los inicializa el NULL
 */
void NodeB::initChildren(){
	for(int i=0; i<_order; i++){
		_children[i] = NULL;
	}
}



/**
 * @brief Método que inicializa el arreglo de claves
 *
 * Recorre el arreglo que contiene las claves del nodo y las
 * inicializa en 0 (NULL)
 */
void NodeB::initKeys(){
	for(int i=0; i<(_order-ONE); i++){
		_keys[i] = EMPTY;
	}
}



/**
 * @brief Método estatico que imprime un mensaje de error y cierra el programa
 *
 * @param pMessage Mensaje a imprimir
 */
void NodeB::Error(char * const pMessage){
	std::cerr << pMessage << std::endl;
	exit(ONE);

}

