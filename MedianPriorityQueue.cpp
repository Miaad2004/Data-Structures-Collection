#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
class Node
{
    T priority;

public:
    Node(T priority)
    {
        this->priority = priority;
    }

    T getPriority()
    {
        return priority;
    }

    void print()
    {
        cout << "Priority: " << priority << endl;
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
    void enqueue(T priority);
    T dequeue();
    T top();
};

template <typename T>
void PQFastInsertion<T>::enqueue(T priority)
{
    Node<T> node(priority);
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

    T priority = this->arr[idx].getPriority();
    this->arr.erase(this->arr.begin() + idx);
    this->size--;
    return priority;
}

template <typename T>
T PQFastInsertion<T>::top()
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

    return this->arr[idx].getPriority();
}

template <typename T>
class MedianPQ
{
    PQFastInsertion<T> min_heap;
    PQFastInsertion<T> max_heap;

public:
    MedianPQ() : min_heap(MIN), max_heap(MAX)
    {
    }

    void Build(vector<T> arr)
    {
        for (auto priority : arr)
            Insert(priority);
    }

    void Insert(T priority)
    {
        if (max_heap.isEmpty() || priority < max_heap.top())
            max_heap.enqueue(priority);

        else
            min_heap.enqueue(priority);

        // balance the heaps
        if (max_heap.getSize() - min_heap.getSize() > 1)
            min_heap.enqueue(max_heap.dequeue());

        else if (min_heap.getSize() - max_heap.getSize() > 1)
            max_heap.enqueue(min_heap.dequeue());
    }

    T RemoveMedian()
    {
        if (max_heap.getSize() >= min_heap.getSize())
            return max_heap.dequeue();

        else
            return min_heap.dequeue();
    }
};

int main()
{
    /*
    6
    build(1,2,3,4,5)
    remove
    remove
    insert(7)
    insert(9)
    remove
    */
   
    MedianPQ<int> MPQ;

    int n;
    cin >> n;

    string command;

    for (int i = 0; i < n; i++)
    {
        cin >> command;

        if (command == "remove")
            cout << MPQ.RemoveMedian() << endl;

        else if (command.find("insert") != string::npos)
        {
            int openBracketPos = command.find("(");
            int closeBracketPos = command.find(")");
            int number = stoi(command.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1));
            MPQ.Insert(number);
        }

        else if (command.find("build") != string::npos)
        {
            int openBracketPos = command.find("(");
            int closeBracketPos = command.find(")");
            string numbers = command.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);

            vector<int> arr;
            istringstream iss(numbers);

            std::string token;
            while (std::getline(iss, token, ','))
                arr.push_back(stoi(token));

            MPQ.Build(arr);
        }
    }
}