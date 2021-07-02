#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
	return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
	boxes.push(b1);
	return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
	return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
	return this->boxes;
}


/* TODO */

unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
	vector<Object>::iterator it = objs.begin();
	while(it != objs.end()) {
		if( (*it).getWeight() <= boxCapacity ) {
			objects.push(*it);
			it = objs.erase(it);
		}
		else it++;
	}
	return objects.size();
}


Box PackagingMachine::searchBox(Object& obj) {
	vector<Box> temp;

	//procura caixa mais cheia, ainda com espaco para obj
	while ( !boxes.empty() )
	{
		Box bx = boxes.top();
		boxes.pop();
		if ( bx.getFree() >= obj.getWeight() ) {

			for (unsigned i=0; i<temp.size(); i++) //repoe na fila de boxes as boxes retiradas da frente.
		        boxes.push(temp[i]);
			return bx;
		}
		else temp.push_back(bx); //coloca as boxes nao utilizadas num vetor temporario
	}
	for (unsigned i=0; i<temp.size(); i++) //repoe as boxes nao utilizadas de volta, caso nenhuma sirva
		boxes.push(temp[i]);

    return Box(boxCapacity); //e retorna uma nova caixa
}


unsigned PackagingMachine::packObjects() {
	while ( !objects.empty() )
	{
		Object o1 = objects.top();
		objects.pop();
		Box b = searchBox(o1);
		b.addObject(o1);
		boxes.push(b);
		cout << "Object weight " << o1.getWeight() << " -> box " << b.getID() << endl;
	}
	return boxes.size();
}

string PackagingMachine::printObjectsNotPacked() const {
	stringstream ss;
	if( objects.empty() ) ss << "No objects!" << endl;
	else {
		HeapObj buffer = objects;
		while( !buffer.empty() ) {
			Object obj = buffer.top();
			buffer.pop();
			ss << obj << endl;
		}
	}
	return ss.str();
}


Box PackagingMachine::boxWithMoreObjects() const {
	if( boxes.empty() ) throw MachineWithoutBoxes();
	else {
		HeapBox buffer = boxes;
		Box boxMore = buffer.top();
		buffer.pop();
		while( !buffer.empty() ) {
			if( boxMore.getSize() < buffer.top().getSize() )
			    boxMore = buffer.top();
			buffer.pop();
		}
		return boxMore;
	}
}



