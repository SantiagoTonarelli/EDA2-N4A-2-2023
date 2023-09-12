#include <iostream>
using namespace std;

template <class T>
class HeapNode
{
public:
    int priority;
    T data;

    // Post: Initializes a HeapNode with the given priority and data.
    HeapNode(int priority, T data) : priority(priority), data(data) {}
};

template <class T>
class Heap
{
private:
    HeapNode<T> **heapArray;
    int top;
    int maxElements;

    // Pre:  pos is a valid index in heapArray.
    // Post: Restores the heap property by floating the element at index pos upwards.
    void floatUp(int pos)
    {
        int parentPos = (pos - 1) / 2;
        while (pos > 0 && heapArray[pos]->priority < heapArray[parentPos]->priority)
        {
            swap(heapArray[pos], heapArray[parentPos]);
            pos = parentPos;
            parentPos = (pos - 1) / 2;
        }
    }

    // Pre:  pos is a valid index in heapArray.
    // Post: Restores the heap property by sinking the element at index pos downwards.
    void sinkDown(int pos)
    {
        int leftChild = 2 * pos + 1;
        int rightChild = 2 * pos + 2;
        int smallest = pos;

        if (leftChild < top && heapArray[leftChild]->priority < heapArray[smallest]->priority)
        {
            smallest = leftChild;
        }

        if (rightChild < top && heapArray[rightChild]->priority < heapArray[smallest]->priority)
        {
            smallest = rightChild;
        }

        if (smallest != pos)
        {
            swap(heapArray[pos], heapArray[smallest]);
            sinkDown(smallest);
        }
    }

public:
    // Post: Initializes an empty heap with a capacity of maxElements.
    Heap(int maxElements)
    {
        this->maxElements = maxElements;
        this->top = 0;
        this->heapArray = new HeapNode<T> *[this->maxElements];
    }

    // Post: Deletes all heap nodes and frees the heapArray.
    ~Heap()
    {
        for (int i = 0; i < top; delete this->heapArray[i++]);
        delete[] this->heapArray;
    }

    // Pre:  Heap is not full.
    // Post: Inserts a new element with the given priority and data into the heap.
    void enqueue(int priority, T data)
    {
        this->heapArray[top] = new HeapNode<T>(priority, data);
        floatUp(this->top++);
    }

    // Pre:  Heap is not empty.
    // Post: Removes the element with the minimum priority from the heap.
    void dequeue()
    {
        delete this->heapArray[0];
        this->heapArray[0] = this->heapArray[--this->top];
        sinkDown(0);
    }

    // Pre:  Heap is not empty.
    // Post: Returns the data of the element with the minimum priority.
    T getMin()
    {
        return this->heapArray[0]->data;
    }

    // Post: Returns true if the heap is empty, false otherwise.
    bool isEmpty()
    {
        return this->top == 0;
    }

    // Post: Returns the number of elements in the heap.
    int size()
    {
        return this->top;
    }
};

int main()
{
    return 0;
}
