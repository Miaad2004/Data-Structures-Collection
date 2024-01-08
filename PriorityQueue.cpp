#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Node
{
    T data;
    int priority;

public:
    Node(T data, int priority)
    {
        this->data = data;
        this->priority = priority;
    }

    T getData()
    {
        return data;
    }

    int getPriority()
    {
        return priority;
    }

    void print()
    {
        cout << "Data: " << data << " Priority: " << priority << endl;
    }
};

enum PriorityMode
{
    MIN,
    MAX
};

template <typename T>
class PQ
{
protected:
    vector<Node<T>> arr;
    int size;
    PriorityMode queueMode;

public:
    PQ(PriorityMode queueMode)
    {
        size = 0;
        this->queueMode = queueMode;
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void print()
    {
        for (auto node : this->arr)
            node.print();
    }
};

// insertion-> O(1), removal->O(n)
template <typename T>
class PQFastInsertion : public PQ<T>
{
public:
    PQFastInsertion(PriorityMode queueMode) : PQ<T>(queueMode) {}
    void enqueue(T data, int priority);
    T dequeue();
};

template <typename T>
void PQFastInsertion<T>::enqueue(T data, int priority)
{
    Node<T> node(data, priority);
    this->arr.push_back(node);
    this->size++;
}

template <typename T>
T PQFastInsertion<T>::dequeue()
{
    if (this->isEmpty())
        throw "Queue is empty";

    int idx = 0;
    switch (this->queueMode)
    {
    case MIN:
        for (int i = 1; i < this->size; i++)
            if (this->arr[i].getPriority() < this->arr[idx].getPriority())
                idx = i;
        break;

    case MAX:
        for (int i = 1; i < this->size; i++)
            if (this->arr[i].getPriority() > this->arr[idx].getPriority())
                idx = i;
        break;
    }

    T data = this->arr[idx].getData();
    this->arr.erase(this->arr.begin() + idx);
    this->size--;
    return data;
}

// insertion-> O(n), removal->O(1)
template <typename T>
class PQFastRemoval : public PQ<T>
{
public:
    PQFastRemoval(PriorityMode queueMode) : PQ<T>(queueMode) {}
    void enqueue(T data, int priority);
    T dequeue();
};

template <typename T>
void PQFastRemoval<T>::enqueue(T data, int priority)
{
    // insert data into the correct position based on the queue mode
    Node<T> node(data, data);

    int insertIdx = 0;
    switch (this->queueMode)
    {
    case MIN:
        while (insertIdx < this->size && this->arr[insertIdx].getPriority() < priority)
            insertIdx++;

        break;

    case MAX:
        while (insertIdx<this->size &&this->arr[insertIdx].getPriority()> priority)
            insertIdx++;
        break;
    }

    this->arr.insert(this->arr.begin() + insertIdx, node);
    this->size++;
}

template <typename T>
T PQFastRemoval<T>::dequeue()
{
    if (this->isEmpty())
        throw "Queue is empty";

    T data = this->arr[0].getData();
    this->arr.erase(this->arr.begin());
    this->size--;
    return data;
}

int main()
{
    // tests
    printf("Min Priority Queue\n");
    PQFastInsertion<int> pqFastInsert(PriorityMode::MIN);
    pqFastInsert.enqueue(1, 1);
    pqFastInsert.enqueue(2, 2);
    pqFastInsert.enqueue(3, 3);
    pqFastInsert.enqueue(4, 4);

    pqFastInsert.print();

    printf("%d\n", pqFastInsert.dequeue());
    printf("%d\n", pqFastInsert.dequeue());
    printf("%d\n", pqFastInsert.dequeue());
    printf("%d\n", pqFastInsert.dequeue());

    printf("\n");
    printf("Max Priority Queue\n");
    PQFastRemoval<int> pqFastRemoval(PriorityMode::MAX);
    pqFastRemoval.enqueue(1, 1);
    pqFastRemoval.enqueue(2, 2);
    pqFastRemoval.enqueue(3, 3);
    pqFastRemoval.enqueue(4, 4);

    pqFastRemoval.print();

    printf("%d\n", pqFastRemoval.dequeue());
    printf("%d\n", pqFastRemoval.dequeue());
    printf("%d\n", pqFastRemoval.dequeue());
    printf("%d\n", pqFastRemoval.dequeue());

    return 0;
}