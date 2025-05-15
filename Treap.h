#ifndef TREAP_H
#define TREAP_H


#include <random>
#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED
#include <utility>
#endif


template <typename T>
class Treap;

template <typename T>
class TreapNode {
public:
    TreapNode* left;
    TreapNode* right;
    TreapNode* parent;
    T num;
    int prior;
    int x;
    int y;

    friend class Treap<T>;

    TreapNode();
    TreapNode(T num,std::mt19937& rng) : num(num) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        prior = rng();
    }
    ~TreapNode() = default;
};

template <typename T>
class Treap {
public:

    std::mt19937 rng;
    TreapNode<T>* root = nullptr;

    Treap();

    void Insert(const T& cur);
    void Erase(const T& cur);
    TreapNode<T>* Find(const T& cur);
    std::pair<int,int> Print(TreapNode<T>* now,int block_size);

private:
    TreapNode<T>* Merge(TreapNode<T>* first, TreapNode<T>* second);
    std::pair<TreapNode<T>*, TreapNode<T>*> Split(TreapNode<T>* a, const T& key);
};
#endif // TREAP_H
