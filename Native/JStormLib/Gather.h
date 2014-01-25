#ifndef _GATHER_H_
#define _GATHER_H_

#include <stdint.h>

class GatherNode {
private:
    GatherNode* _next;
    GatherNode* _prev;
    void* _data;
    uint32_t _length;
public:
    GatherNode(GatherNode& other);
    GatherNode(void* data, uint32_t length, GatherNode* prev, GatherNode* next);
    ~GatherNode();
    GatherNode& operator=(GatherNode& other);
    GatherNode* getNext();
    GatherNode* getPrev();
    uint32_t getLength();
    void* getData();
};

class Gather {
private:
    GatherNode* _first;
    GatherNode* _last;
public:
    ~Gather();
    void insertBefore(GatherNode* node, void* data, uint32_t length);
    void insertAfter(GatherNode* node, void* data, uint32_t length);
    void append(void* data, uint32_t length);
    void prepend(void* data, uint32_t length);
    void push(void* data, uint32_t length);
    uint32_t getLength();
    GatherNode* getFirst();
    GatherNode* getLast();
    void serialize(void* destination, uint32_t maxLength);
};

#endif