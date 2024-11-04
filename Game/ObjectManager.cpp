#include "ObjectManager.h"

const unsigned int Object::GetIndex() {
	return _index;
}

void Object::Update(double deltaTime) {
}

void Object::Draw(double deltaTime) {
}

std::vector<Object*> ObjectManager::GetCreatedObjects() {
	return _createdObjects;
}
