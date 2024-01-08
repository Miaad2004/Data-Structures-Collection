#include <iostream>
#include <vector>
#include <list>

template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K &key, const V &value)
        : key(key), value(value)
    {
    }
};

template <typename K, typename V>
class Map
{

private:
    const double MAX_LOAD_FACTOR = 0.75;

    size_t N = 5;
    size_t n = 0;
    double loadFactor = 0.0;

    // MAD parameters
    size_t p = randomPrime(N);
    size_t a = random(1, p - 1);
    size_t b = random(0, p - 1);

    std::vector<std::list<Pair<K, V>>> map;

    static size_t random(size_t min, size_t max);
    static bool isPrime(size_t number);
    static size_t randomPrime(size_t min);

    size_t hash(const K &key) const;
    void rehash();

public:
    Map()
    {
        map = std::vector<std::list<Pair<K, V>>>(N);
    }

    ~Map()
    {
        clear();
    }

    void put(K &key, V &value);
    V &get(const K &key);
    void remove(const K &key);

    V &operator[](const K &key);
    bool contains(const K &key) const;

    int size() const;
    bool empty() const;
    void clear();
    void print() const;
};

template <typename K, typename V>
bool Map<K, V>::isPrime(size_t number)
{
    if (number < 2)
    {
        return false;
    }
    for (size_t i = 2; i < number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

template <typename K, typename V>
size_t Map<K, V>::randomPrime(size_t min)
{
    size_t number = random(min, 2 * min);
    while (!isPrime(number))
    {
        number++;
    }
    return number;
}

template <typename K, typename V>
size_t Map<K, V>::random(size_t min, size_t max)
{
    return min + rand() % (max - min + 1);
}

template <typename K, typename V>
size_t Map<K, V>::hash(const K &key) const
{

    return ((a * std::hash<K>()(key) + b) % p) % N;
}

template <typename K, typename V>
void Map<K, V>::rehash()
{
    // Calculate the new size
    this->N = N * 2;
    while (!isPrime(N))
    {
        N++;
    }

    // Update MAD params
    this->p = randomPrime(N);
    this->a = random(1, N - 1);
    this->b = random(0, N - 1);

    // Rehash all elements
    std::vector<std::list<Pair<K, V>>> newMap(N);

    for (const auto &list : map)
    {
        for (const auto &pair : list)
        {
            size_t newIndex = hash(pair.key);
            newMap[newIndex].push_back(pair);
        }
    }

    map = newMap;

    loadFactor = (double)n / N;
}

template <typename K, typename V>
void Map<K, V>::put(K &key, V &value)
{
    size_t index = hash(key);
    // std::cout << index << std::endl;

    // Update the value if the key already exists
    for (auto &pair : map[index])
    {
        if (pair.key == key)
        {
            pair.value = value;
            return;
        }
    }

    // Add new key
    map[index].push_back(Pair<K, V>(key, value));
    n++;

    loadFactor = (double)n / N;
    if (loadFactor > MAX_LOAD_FACTOR)
        rehash();
}

template <typename K, typename V>
V &Map<K, V>::get(const K &key)
{
    size_t index = hash(key);

    for (auto &pair : map[index])
    {
        if (pair.key == key)
        {
            return pair.value;
        }
    }

    throw std::exception("Key not found");
}

template <typename K, typename V>
void Map<K, V>::remove(const K &key)
{
    size_t index = hash(key);

    for (auto it = map[index].begin(); it != map[index].end(); it++)
    {
        if (it->key == key)
        {
            map[index].erase(it);
            n--;
            return;
        }
    }

    throw std::exception("Key not found");
}

template <typename K, typename V>
V &Map<K, V>::operator[](const K &key)
{
    size_t index = hash(key);

    for (auto &pair : map[index])
    {
        if (pair.key == key)
        {
            return pair.value;
        }
    }

    // Add new key
    map[index].push_back(Pair<K, V>(key, V()));
    n++;

    loadFactor = (double)n / N;
    if (loadFactor > MAX_LOAD_FACTOR)
        rehash();

    return map[index].back().value;
}

template <typename K, typename V>
bool Map<K, V>::contains(const K &key) const
{
    size_t index = hash(key);

    for (const auto &pair : map[index])
    {
        if (pair.key == key)
        {
            return true;
        }
    }

    return false;
}

template <typename K, typename V>
int Map<K, V>::size() const
{
    return n;
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return n == 0;
}

template <typename K, typename V>
void Map<K, V>::clear()
{
    map.clear();
    n = 0;
    N = 5;
    loadFactor = 0.0;
}

template <typename K, typename V>
void Map<K, V>::print() const
{
    for (const auto &list : map)
    {
        for (const auto &pair : list)
        {
            std::cout << pair.key << " " << pair.value << std::endl;
        }
    }
}

int main()
{
    Map<int, int> map;
    int key1 = 1;
    int value1 = 2;
    map.put(key1, value1);

    int key2 = 2;
    int value2 = 3;
    map.put(key2, value2);

    int key3 = 3;
    int value3 = 4;
    map.put(key3, value3);

    int key4 = 4;
    int value4 = 5;
    map.put(key4, value4);

    std::cout << map.get(key1) << std::endl;

    map.remove(key1);

    map.print();

    return 0;
}