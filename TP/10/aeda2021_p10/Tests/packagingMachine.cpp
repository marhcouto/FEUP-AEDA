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



unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
	for (std::vector<Object>::const_iterator it = objs.begin(); it != objs.end(); ) {
	    if (it->getWeight() > boxCapacity) {
	        it++;
	        continue;
	    }
        objects.push(*it);
	    it = objs.erase(it);
	}
	return objects.size();
}


Box PackagingMachine::searchBox(Object& obj) {
	std::vector<Box> v;
	while (!boxes.empty()) {
        Box b = boxes.top();
	    boxes.pop();
	    if (b.getFree() >= obj.getWeight()) {
	        for (std::vector<Box>::const_iterator it = v.begin(); it != v.end(); it++)
	            boxes.push(*it);
	        return b;
	    }
	    else
	        v.push_back(b);
	}
    for (std::vector<Box>::const_iterator it = v.begin(); it != v.end();) {
        boxes.push(*it);
        it = v.erase(it);
    }
    return Box();
}


unsigned PackagingMachine::packObjects() {
	while (!objects.empty()) {
	    Object ob = objects.top();
	    objects.pop();
	    Box b = searchBox(ob);
        b.addObject(ob);
        boxes.push(b);
	}
	return boxes.size();
}


string PackagingMachine::printObjectsNotPacked() const {
    std::stringstream ss;
    HeapObj temp = objects;
    if (temp.empty()) ss << "No objects!\n";
	while (!temp.empty()) {
        ss << temp.top() << std::endl;
        temp.pop();
	}
	return ss.str();
}


Box PackagingMachine::boxWithMoreObjects() const {
	HeapBox temp = boxes;
	if (temp.empty()) throw MachineWithoutBoxes();
    Box b = temp.top();
    temp.pop();
	while (!temp.empty()) {
	    if (temp.top().getSize() > b.getSize()) {
	        b = temp.top();
	    }
	    temp.pop();
	}
	return b;
}

