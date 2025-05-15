#ifndef REDBLACK_H
#define REDBLACK_H

#include <utility>
template <typename T>
class RedBlack;

template <typename T>
class RedBlackNode {
public:
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;
    bool is_red = false;
    T num;
    int x;
    int y;
    friend class RedBlack<T>;

    RedBlackNode() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    RedBlackNode(int num) : num(num) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    };

    void Delete(RedBlackNode<T>*& root);
    ~RedBlackNode() = default;

    template <typename T1>
    friend bool GetColor(RedBlackNode<T1>* now);

    template <typename T1>
    friend RedBlackNode<T1>* GetParent(RedBlackNode<T1>* now);

    template <typename T1>
    friend RedBlackNode<T1>* GetGrandParent(RedBlackNode<T1>* now);

    template <typename T1>
    friend RedBlackNode<T1>* GetBrother(RedBlackNode<T1>* now);

    template <typename T1>
    friend RedBlackNode<T1>* GetUncle(RedBlackNode<T1>* now);

    template <typename T1>
    friend void Gap(RedBlackNode<T1>* now);

    template <typename T1>
    friend std::pair<RedBlackNode<T1>*, RedBlackNode<T1>*> GetChilds(RedBlackNode<T1>* now);

    template <typename T1>
    friend std::pair<RedBlackNode<T1>*, RedBlackNode<T1>*> GetSiblings(RedBlackNode<T1>* now);

    template <typename T1>
    friend void UpdateColor(RedBlackNode<T1>* now, int color);
};

template <typename T>
class RedBlack {
public:
    RedBlackNode<T>* root = nullptr;

    RedBlack() { root = nullptr; }
    ~RedBlack() = default;

    void Insert(int cur);
    RedBlackNode<T>* Find(int cur);
    std::pair<int,int> Print(RedBlackNode<T>* now,int block_size);
    void Erase(int cur);
    int Check();

private:
    void BalanceInsert(RedBlackNode<T>* now);
    void BalanceErase(RedBlackNode<T>* now);
    void SolveForRedParent(RedBlackNode<T>* now);

    void DeleteCliffLeft(RedBlackNode<T>* now);
    void DeleteCliffRight(RedBlackNode<T>* now);

    void SolveCliffRight(RedBlackNode<T>* now);
    void SolveCliffLeft(RedBlackNode<T>* now);

    void SmallLeft(RedBlackNode<T>* now);
    void SmallRight(RedBlackNode<T>* now);
    void BigLeft(RedBlackNode<T>* now);
    void BigRight(RedBlackNode<T>* now);
    int CheckInv(RedBlackNode<T>* now, int height);

    void LinkLeft(RedBlackNode<T>* par, RedBlackNode<T>* now);
    void LinkRight(RedBlackNode<T>* par, RedBlackNode<T>* now);

    RedBlackNode<T>* FindMinValue(RedBlackNode<T>* now);
};



#endif // REDBLACK_H
