#ifndef AVL_H
#define AVL_H
#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED
#include<utility>
#endif
template<typename T>
class AVL;

template<typename T>
class AVLNode {
public:
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;
    int height;
    int num;
    int x;
    int y;

    friend class AVL<T>;



    template<typename T1>
    friend void Balance(AVLNode<T1>* now);

    template<typename T1>
    friend AVLNode<T1>* FindMinValue(AVLNode<T1>* now);

    template<typename T1>
    friend AVLNode<T1>* FindMaxValue(AVLNode<T1>* now);

    AVLNode(AVLNode* parent, AVLNode* left, AVLNode* right, int height)
        : parent(parent), left(left), right(right), height(height) {};
    AVLNode(AVLNode* parent, int num) : parent(parent), num(num) {
        height = 1;
        left = nullptr;
        right = nullptr;
    }
    AVLNode() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void Clear();
    ~AVLNode() = default;

    template<typename T1>
    friend int GetHeight(AVLNode<T1>* now);

    template<typename T1>
    friend void UpdateHeight(AVLNode<T1>* now);
};


template<typename T>
class AVL {
public:
    AVLNode<T>* root = nullptr;
    void SmallLeft(AVLNode<T>* now);
    void SmallRight(AVLNode<T>* now);
    void BigLeft(AVLNode<T>* now);
    void BigRight(AVLNode<T>* now);
    void Balance(AVLNode<T>* now);

    template<typename T1>
    friend AVLNode<T1>* FindMinValue(AVLNode<T1>* now);

    template<typename T1>
    friend AVLNode<T1>* FindMaxValue(AVLNode<T1>* now);

    void SolveLeftRight(AVLNode<T>* now);
    void SolveRightLeft(AVLNode<T>* now);
    void SolveLeftLeft(AVLNode<T>* now);
    void SolveRightRight(AVLNode<T>* now);
    void SolveLeft(AVLNode<T>* now);
    void SolveRight(AVLNode<T>* now);

    AVL() = default;

    AVLNode<T>* Find(T cur);
    void Insert(T cur);
    void Erase(T cur);
    int Print(AVLNode<T>* now,int block_size);
    int CheckInv(AVLNode<T>* now);
};

#endif // AVL_H
