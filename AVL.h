#ifndef AVL_H
#define AVL_H
#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED
#include<utility>
#endif
class AVL;

class AVLNode {
public:
    AVLNode* parent;
    AVLNode* left;
    AVLNode* right;
    int height;
    int num;
    int x;
    int y;

    friend class AVL;

    friend void SmallLeft(AVLNode* now);
    friend void SmallRight(AVLNode* now);
    friend void BigLeft(AVLNode* now);
    friend void BigRight(AVLNode* now);
    friend void Balance(AVLNode* now);
    friend AVLNode* FindMinValue(AVLNode* now);
    friend AVLNode* FindMaxValue(AVLNode* now);

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

    friend int GetHeight(AVLNode* now);
    friend void UpdateHeight(AVLNode* now);
};

class AVL {
public:
    AVLNode* root = nullptr;
    void SmallLeft(AVLNode* now);
    void SmallRight(AVLNode* now);
    void BigLeft(AVLNode* now);
    void BigRight(AVLNode* now);
    void Balance(AVLNode* now);
    friend AVLNode* FindMinValue(AVLNode* now);
    friend AVLNode* FindMaxValue(AVLNode* now);
    void SolveLeftRight(AVLNode* now);
    void SolveRightLeft(AVLNode* now);
    void SolveLeftLeft(AVLNode* now);
    void SolveRightRight(AVLNode* now);
    void SolveLeft(AVLNode* now);
    void SolveRight(AVLNode* now);

    AVL() = default;

    AVLNode* Find(int cur);
    void Insert(int cur);
    void Erase(int cur);
    std::pair<int,int> Print(AVLNode* now,int block_size);
    void CheckInv(AVLNode* now);
};

#endif // AVL_H
