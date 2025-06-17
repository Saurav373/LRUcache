#include <iostream>
#include <unordered_map>

class Node {
   public:
    int key = 0;
    int value = 0;
    Node* next = NULL;
    Node* prev = NULL;

    Node(int key, int value, Node* next, Node* prev) {
        this->key = key;
        this->value = value;
        this->next = next;
        this->prev = prev;
    }

    Node(int key, int value) {
        this->key = key;
        this->value = value;
    }
};

class LRU {
   private:
    int capacity;
    int size;
    Node* dhead = new Node(-1, -1);        // Dummy Head
    Node* dtail = new Node(-1, -1);        // Dummy Tail
    std::unordered_map<int, Node*> addressMap;  // Address Map {key : NodeAddress}

    void moveToHead(Node* node) {
        // unlink the Node:
        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = NULL, node->prev = NULL;
        // add after dummy head
        Node* tempNext = dhead->next;
        dhead->next = node;
        node->prev = dhead;
        node->next = tempNext;
        tempNext->prev = node;
    }
    void addNode(Node* node) {  // Add Node to the front
        Node* tempNext = dhead->next;
        dhead->next = node;
        node->prev = dhead;
        node->next = tempNext;
        tempNext->prev = node;

        addressMap[node->key] = node;
        this->size++;
    }

    void deleteNode(Node* node) {  // Delete the Node in the LinkedList
        Node* tempNext = node->next;
        node->next->prev = node->prev;
        node->prev->next = tempNext;
        node->next = NULL, node->prev = NULL;
        addressMap.erase(node->key);
        delete node;
        this->size--;
    }

   public:
    LRU(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        dhead->next = dtail;
        dtail->prev = dhead;
    }
    int getsize() {
        return this->size;
    }
    void add(int key, int value) {
        if (addressMap.find(key) != addressMap.end()) {
            Node* node = addressMap[key];
            node->value = value;
            moveToHead(node);
            return;
        }

        Node* newNode = new Node(key, value);
        if (this->size == capacity) {
            deleteNode(dtail->prev);
        }
        addNode(newNode);
    }

    int get(int key) {
        if (addressMap.find(key) == addressMap.end())
            return -1;
        Node* node = addressMap[key];
        moveToHead(node);
        return node->value;
    }

    ~LRU(){
        Node* curr = dhead;
        while(curr){
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};
int main() {
    LRU lru(2);  // Cache capacity = 2

    lru.add(1, 10);
    lru.add(2, 20);

    std::cout << lru.get(1) << std::endl;  // prints 10

    lru.add(3, 30);              // evicts key 2

    std::cout << lru.get(2) << std::endl;  // prints -1 (not found)
    std::cout << lru.get(3) << std::endl;  // prints 30

    return 0;
}
