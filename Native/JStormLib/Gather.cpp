#include "Gather.h"
#include <string.h>

GatherNode::GatherNode(GatherNode& other)
    : _data(new char[other._length]), _length(other._length), _prev(other._prev), _next(other._next)
{
    memcpy(this->_data, other._data, this->_length);
    if (this->_prev) this->_prev->_next = this;
    if (this->_next) this->_next->_prev = this;
}

GatherNode::GatherNode(void* data, uint32_t length, GatherNode* prev, GatherNode* next)
     : _data(new char[length]), _length(length), _prev(prev), _next(next)
{
    memcpy(_data, data, length);
    if (prev) prev->_next = this;
    if (next) next->_prev = this;
}

GatherNode::~GatherNode() {
    delete[] _data;
    if (this->_prev) this->_prev->_next = this->_next;
    if (this->_next) this->_next->_prev = this->_prev;
}

GatherNode& GatherNode::operator=(GatherNode& other) {
    if (this != &other) {
        void* data = new char[other._length];
        memcpy(data, other._data, other._length);

        delete[] this->_data;
        this->_data = data;
        this->_length = other._length;
        this->_prev = other._prev;
        this->_next = other._next;

        if (this->_prev) this->_prev->_next = this;
        if (this->_next) this->_next->_prev = this;
    }
    return *this;
}

GatherNode* GatherNode::getNext() {
    return this->_next;
}

GatherNode* GatherNode::getPrev() {
    return this->_prev;
}

uint32_t GatherNode::getLength() {
    return this->_length;
}

void* GatherNode::getData() {
    return this->_data;
}

//

Gather::~Gather() {
    GatherNode* node = this->_first;
    while(node) {
        GatherNode* temp = node->getNext();
        delete node;
        node = temp;
    }
}

void Gather::insertBefore(GatherNode* node, void* data, uint32_t length) {
    GatherNode* current = this->_first;
    while(current != NULL && current->getNext() != NULL && current != node) {
        current = current->getNext();
    }
    GatherNode *newNode = new GatherNode(data, length, current ? current->getPrev() : 0 , current);
    if (current == this->_first) {
        this->_first = newNode;
    }
}

void Gather::insertAfter(GatherNode* node, void* data, uint32_t length) {
    GatherNode* current = this->_last;
    while(current != NULL && current->getPrev() != NULL && current != node) {
        current = current->getPrev();
    }
    GatherNode *newNode = new GatherNode(data, length, current, current ? current->getNext() : 0);
    if (current == this->_last) {
        this->_last = newNode;
    }
}

void Gather::append(void* data, uint32_t length) {
    this->insertAfter(this->_last, data, length);
}

void Gather::prepend(void* data, uint32_t length) {
    this->insertBefore(this->_first, data, length);
}

void Gather::push(void* data, uint32_t length) {
    this->prepend(data, length);
}

uint32_t Gather::getLength() {
    uint32_t length = 0;

    GatherNode* node = this->_first;
    while(node) {
        length += node->getLength();
        node = node->getNext();
    }

    return length;
}

GatherNode* Gather::getFirst() {
    return this->_first;
}

GatherNode* Gather::getLast() {
    return this->_last;
}

void Gather::serialize(void* destination, uint32_t maxLength) {
    char* typedDestination = reinterpret_cast<char*>(destination);
    GatherNode* node = _first;
    while(node && (maxLength > 0)) {
        uint32_t length = node->getLength();
        if (length > maxLength) length = maxLength;

        memcpy(typedDestination, node->getData(), length);

        maxLength -= length;
        typedDestination += length;
        node = node->getNext();
    }
}
