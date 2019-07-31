class LRUCache {
private:
    // Doubly Linked List Node
    struct DLinkedNode {
        int key;
        int value;
        DLinkedNode * next;
        DLinkedNode * prev;
        DLinkedNode(){};
        DLinkedNode(int k, int v): key(k), value(v), 
        next(NULL), prev(NULL) {};
    }; 
    
    DLinkedNode * head, * tail;
    int size, capacity;
    map<int, DLinkedNode *> cacheMap;
    
    // adds a node by setting pointers of the prev to current
    // and the current to next
    void addNode(DLinkedNode * newNode)
    {
        newNode->prev = head;
        newNode->next  = head->next;
        newNode->next->prev = newNode;
        head->next = newNode;
    }
    
    // Sets prev pointers to next and
    // next pointers to prev nodes
    void removeNode(DLinkedNode * removedNode)
    {   
        DLinkedNode * prevNode = removedNode->prev;
        DLinkedNode * nextNode = removedNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }
    
    // moves node to front
    
    void moveToHead(DLinkedNode * node)
    {
        removeNode(node);
        addNode(node);
    }
    
    
public:
    LRUCache(int capacity):capacity(capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->prev = NULL;
        tail->next = NULL;
        head->next = tail;
        tail->prev = head;
    }
    
    // returns keys int 
    int get(int key) {
        auto it = cacheMap.find(key);
        if(it == cacheMap.end())
            return -1;
        moveToHead(it->second);
        return it->second->value;
    }
    
    // adds a key and node to map
    void put(int key, int value) {
        auto it = cacheMap.find(key);
        
        if(it == cacheMap.end())
        {
            DLinkedNode * newNode = new DLinkedNode(key, value);
            cacheMap.insert({key,newNode});
            addNode(newNode);
            size++;
            if(size > capacity)
            {
                DLinkedNode * last = tail->prev;
                cacheMap.erase(last->key);
                removeNode(last);
                size--;
            }
        }
        else
        {
            it->second->value = value;
            moveToHead(it->second);
        }    
    }
};
