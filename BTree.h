#ifndef BTREE_H
#define BTREE_H

#include <utility>
#include <vector>
template <typename T>
class BTree;

template <typename T>
class BNode {
public:
    BNode* parent = nullptr;
    std::vector<T> num;
    std::vector<BNode*> childs;
    std::vector<int> coor_x;
    std::vector<int> coor_y;


    friend class BTree<T>;

    BNode() { parent = nullptr; }
    ~BNode() = default;

    void Delete(BNode<T>*& root);

    template <typename T1>
    friend T1 GiveMedian(BNode<T1>* now);

    template <typename T1>
    friend int FindInBNode(BNode<T1>* now, T1 cur);

    template <typename T1>
    friend BNode<T1>* GetRightBrother(BNode<T1>* now);

    template <typename T1>
    friend BNode<T1>* GetLeftBrother(BNode<T1>* now);

    template <typename T1>
    friend int GetSize(BNode<T1>* now);

    template <typename T1>
    friend int MyNum(BNode<T1>* now);

    template <typename T1>
    friend BNode<T1>* FindMinValue(BNode<T1>* now);

    template <typename T1>
    friend BNode<T1>* FindMaxValue(BNode<T1>* now);
};

template <typename T>
class BTree {
public:
    int size;
    BNode<T>* root = nullptr;
    int t;
    void InsertMass(BNode<T>* now, BNode<T>* left, BNode<T>* right, T cur);
    void BalanceInsert(BNode<T>* now);
    BNode<T>* BalanceErase(BNode<T>* now);
    std::pair<BNode<T>*, BNode<T>*> Split(BNode<T>* now, T cur);
    BNode<T>* Merge(BNode<T>* now, BNode<T>* left, BNode<T>* right, T cur);

    BTree() {
        root = nullptr;
        t = 2;
    }
    BTree(int t) : t(t) { root = nullptr; }
    ~BTree() = default;

    bool Find(T cur);
    void Insert(T cur);
    void EraseFirstStep(T cur);
    void EraseSecondStep(T cur, T need);
    bool Check();
    std::pair<int,int> Print(BNode<T>* now,int block_size);

private:
    void DeleteLeaf(BNode<T>* start, T cur);
    int CheckInv(BNode<T>* now, int height);
};
#endif // BTREE_H
