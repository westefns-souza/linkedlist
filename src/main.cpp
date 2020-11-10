#include <iostream>
#include <limits>

struct Node {
    int value;
    Node* next;
};

struct LinkedList
{
    Node* first = nullptr;
    size_t nodeCount = 0;

    LinkedList() {}

    LinkedList(const LinkedList& other) {
        clone(other);
    }
    
    LinkedList operator=(const LinkedList& other) {
        if (&other == this) {
            return *this;
        }

        clear();
        clone(other);

        return *this;
    }

    ~LinkedList() {
        clear();     
    }

    void clear()
    {
        if (nodeCount == 0) {
            return;
        }

        Node* currentNode = first;

        while (currentNode != nullptr)
        {
            Node* tmp = currentNode->next;
            delete currentNode;
            currentNode = tmp->next;
        }    
    }

    void clone(const LinkedList& other) {
        if (other.nodeCount == 0) {
            return;
        }

        Node* currentNode = other.first;

        while (currentNode != nullptr)
        {
            insert(currentNode->value);
            currentNode = currentNode->next;
        }
    }

    void insert(int value) {
        if(first != nullptr) {
            Node* last = first;

            while (last->next != nullptr) {
                last = last->next;
            }

            Node* other = new Node();
            other->value = value;
            last->next = other;            

            ++nodeCount;
        } else {
            first = new Node();
            first->value = value;
            
            ++nodeCount;
        }
    };

    void print() {
        if (size() <= 0) {
            return;
        }

        Node* current = first;
        
        do {
            std::cout << current->value << std::endl;
            current = current->next;
        } while (current != nullptr);
        
    }

    void insertAt(size_t position, int value) {
        if (position >= size()) {
            return;
        }

        Node* newNode = new Node();
        newNode->value = value;

        size_t currentPosition = 0;
        Node* previousNode = nullptr; 
        Node* currentNode = first;

        while (currentPosition < position) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            currentPosition++;
        }

        newNode->next = currentNode;
        
        if (position == 0){
            first = newNode; 
        }else {
            previousNode->next = newNode; 
        }

        ++nodeCount;
    };

    void removeAt(size_t position) {
        if (position >= size()) {
            return;
        }

        size_t currentPosition = 0;
        Node* previousNode = nullptr;
        Node* currentNode = first;

        while (currentPosition < position) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            currentPosition++;
        }

        if (position == 0){
            first = currentNode->next;
        } else {
            previousNode->next = currentNode->next;
        }
          
        delete currentNode;
        --nodeCount;
    };

    size_t size() {
        return nodeCount;
    };

    size_t search(int value) {
        Node* currentNode = first;
        size_t position = 0;

        while (currentNode != nullptr)
        {
            std::cout << "x: " << currentNode->value << std::endl;
            if (currentNode->value == value) {
                return position;
            }

            currentNode = currentNode->next;
            position++;
        }

        position = std::numeric_limits<size_t>::infinity();
        return position;
    };
};

int main(int argc, char const *argv[]) {
    LinkedList list;

    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    list.print();
    LinkedList list2 = list;
    list2.print();

    return 0;
}