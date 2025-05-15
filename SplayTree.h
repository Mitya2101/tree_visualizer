#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <utility>

template <typename T>
class SplayTree;

template <typename T>
class SplayNode {
public:
    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;
    T num;
    int x;
    int y;

    friend class SplayTree<T>;

    SplayNode() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    SplayNode(T num) : num(num) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void Delete(SplayNode<T>*& root);
    ~SplayNode() = default;

    template <typename T1>
    friend SplayNode<T1>* GetParent(SplayNode<T1>* now);

    template <typename T1>
    friend SplayNode<T1>* GetGrandParent(SplayNode<T1>* now);

    template <typename T1>
    friend int NumberForParent(SplayNode<T1>* now);
};

template <typename T>
class SplayTree {
public:
    SplayNode<T>* root = nullptr;

    SplayTree() { root = nullptr; }
    SplayTree(SplayNode<T>* root) : root(root) {};

    ~SplayTree() = default;

    void Insert(const T& cur);
    void Erase(const T& cur);
    SplayNode<T>* Find(const T& cur);

    std::pair<int,int> Print(SplayNode<T>* now, int block_size);

private:
    std::pair<SplayNode<T>*, SplayNode<T>*> Split(SplayNode<T>* now, const T& key);
    SplayNode<T>* Merge(SplayTree<T>* first, SplayTree<T>* second);

    SplayNode<T>* FindMinValue(SplayNode<T>* now);

    SplayNode<T>* FindFirstMore(SplayNode<T>* now, const T& x);

    void SmallLeft(SplayNode<T>* now);
    void SmallRight(SplayNode<T>* now);
    void BigLeft(SplayNode<T>* now);
    void BigRight(SplayNode<T>* now);
    void ZigZigLeft(SplayNode<T>* now);
    void ZigZigRight(SplayNode<T>* now);

    void Splay(SplayNode<T>* now);

    void LinkLeft(SplayNode<T>* par, SplayNode<T>* now);
    void LinkRight(SplayNode<T>* par, SplayNode<T>* now);

    void Gap(SplayNode<T>* now);
};


#endif // SPLAYTREE_H
