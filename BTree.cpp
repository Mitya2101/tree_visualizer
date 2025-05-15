#include "BTree.h"

#include <iostream>
#include<cassert>

template <typename T>
BNode<T> *GetRightBrother(BNode<T> *now)
{
    if (now->parent == nullptr)
    {
        assert(0);
    }
    for (int i = 0; i < now->parent->childs.size(); i++)
    {
        if (now->parent->childs[i] == now)
        {
            if (i == now->parent->childs.size() - 1)
            {
                return nullptr;
            }
            return now->parent->childs[i + 1];
        }
    }
    assert(0);
}

template <typename T>
BNode<T> *GetLeftBrother(BNode<T> *now)
{
    if (now->parent == nullptr)
    {
        assert(0);
    }
    for (int i = 0; i < now->parent->childs.size(); i++)
    {
        if (now->parent->childs[i] == now)
        {
            if (i == 0)
            {
                return nullptr;
            }
            return now->parent->childs[i - 1];
        }
    }
    assert(0);
}

template <typename T>
int GetSize(BNode<T> *now)
{
    if (now == nullptr)
    {
        return -1;
    }
    return now->num.size();
}

template <typename T>
void BNode<T>::Delete(BNode<T> *&root)
{
    if (this->parent != nullptr)
    {
        for (int i = 0; i < this->parent->childs.size(); i++)
        {
            if (this->parent->childs[i] == this)
            {
                this->parent->childs[i] = nullptr;
            }
        }
    }
    // std::cout << "bbbbbbbbbbbbb" << std ::endl;

    this->parent = nullptr;

    for (int i = 0; i < this->childs.size(); i++)
    {
        if (this->childs[i] != nullptr)
        {
            if (this->childs[i]->parent == this)
            {
                this->childs[i]->parent = nullptr;
            }
        }
        this->childs[i] = nullptr;
    }
    // std::cout << "bbbbbbbbbbbbb" << std ::endl;

    if (this == root)
    {
        root = nullptr;
        return;
    }
    this->num.clear();
    this->childs.clear();
}

template <typename T>
int FindInBNode(BNode<T> *now, T cur)
{
    int l = -1, r = now->num.size();
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (now->num[mid] == cur)
        {
            return mid;
        }
        if (now->num[mid] <= cur)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

template <typename T>
int MyNum(BNode<T> *now)
{
    if (now->parent == nullptr)
    {
        assert(0);
    }
    for (int i = 0; i < now->parent->childs.size(); i++)
    {
        if (now->parent->childs[i] == now)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
std::pair<BNode<T> *, BNode<T> *> BTree<T>::Split(BNode<T> *now, T x)
{
    if (now == nullptr)
    {
        return {nullptr, nullptr};
    }
    int ind = FindInBNode(now, x);
    if (now->num[ind] != x)
    {
        assert(0);
    }

    BNode<T> *left = new BNode<T>();
    BNode<T> *right = new BNode<T>();
    for (int i = 0; i < ind; i++)
    {
        left->num.push_back(now->num[i]);
        left->childs.push_back(now->childs[i]);
        if (now->childs[i] != nullptr)
        {
            now->childs[i]->parent = left;
        }
    }
    left->childs.push_back(now->childs[ind]);
    if (now->childs[ind] != nullptr)
    {
        now->childs[ind]->parent = left;
    }
    for (int i = ind + 1; i < now->num.size(); i++)
    {
        right->num.push_back(now->num[i]);
        right->childs.push_back(now->childs[i]);
        if (now->childs[i] != nullptr)
        {
            now->childs[i]->parent = right;
        }
    }
    right->childs.push_back(now->childs.back());
    if (now->childs.back() != nullptr)
    {
        now->childs.back()->parent = right;
    }
    now->Delete(root);
    return {left, right};
}

template <typename T>
T GiveMedian(BNode<T> *now)
{
    return now->num[now->num.size() / 2];
}

template <typename T>
void BTree<T>::InsertMass(BNode<T> *now, BNode<T> *left, BNode<T> *right, T cur)
{
    int ind = FindInBNode(now, cur);
    if (now->num.size() == 0)
    {
        now->num.insert(now->num.begin() + ind + 1, cur);
        now->childs.push_back(left);
        now->childs.push_back(right);
        if (left != nullptr)
            left->parent = now;
        if (right != nullptr)
            right->parent = now;
        return;
    }
    now->num.insert(now->num.begin() + ind + 1, cur);

    now->childs[ind + 1] = left;
    now->childs.insert(now->childs.begin() + ind + 2, right);
    if (left != nullptr)
        left->parent = now;
    if (right != nullptr)
        right->parent = now;
}

template <typename T>
void BTree<T>::BalanceInsert(BNode<T> *now)
{
    if (now == root)
    {
        BNode<T> *new_root = new BNode<T>();
        T median = GiveMedian(root);
        auto tmp = Split(root, median);
        InsertMass(new_root, tmp.first, tmp.second, median);
        root = new_root;
        return;
    }
    if (now->parent == nullptr)
    {
        assert(0);
        exit(0);
    }
    T median = GiveMedian(now);
    BNode<T> *help = now->parent;
    auto tmp = Split(now, median);
    InsertMass(help, tmp.first, tmp.second, median);
}

template <typename T>
bool BTree<T>::Find(T cur)
{
    BNode<T> *now = root;
    while (now != nullptr)
    {
        int ind = FindInBNode(now, cur);
        if (ind != -1 && now->num[ind] == cur)
        {
            return true;
        }
        now = now->childs[ind + 1];
    }
    return false;
}

template <typename T>
void BTree<T>::Insert(T cur)
{
    size++;
    if (root == nullptr)
    {
        root = new BNode<T>();
        root->num.push_back(cur);
        root->childs.push_back(nullptr);
        root->childs.push_back(nullptr);
        return;
    }
    BNode<T> *now = root;

    if (root->num.size() == 2 * t - 1)
    {
        BalanceInsert(root);
        now = root;
    }
    while (now != nullptr)
    {
        int ind = FindInBNode(now, cur);
        if (ind != -1 && now->num[ind] == cur)
        {
            size--;
            return;
        }
        if (now->childs[ind + 1] == nullptr)
        {
            InsertMass(now, nullptr, nullptr, cur);
            return;
        }
        if (now->childs[ind + 1]->num.size() == 2 * t - 1)
        {
            if (GiveMedian(now->childs[ind + 1]) == cur)
            {
                return;
            }
            BalanceInsert(now->childs[ind + 1]);
            ind = FindInBNode(now, cur);
        }
        now = now->childs[ind + 1];
    }
}

template <typename T>
int BTree<T>::CheckInv(BNode<T> *now, int height)
{
    if (now == nullptr)
    {
        return height;
    }
    int cur = -2;
    for (int i = 0; i < now->childs.size(); i++)
    {
        int tmp = CheckInv(now->childs[i], height + 1);
        if (tmp == -1)
        {
            return -1;
        }
        if (cur == -2)
        {
            cur = tmp;
        }
        else if (cur != tmp)
        {
            std::cout << "Not equal height of lists" << std::endl;
            return -1;
        }
    }

    if (now == root)
    {
        if (now->num.size() > 2 * t - 1)
        {
            std::cout << "Not right count of BNode in root" << std ::endl;
            return -1;
        }
    }
    else
    {
        if (now->num.size() < t - 1 || now->num.size() > 2 * t - 1)
        {
            std::cout << "Not right count of BNode in vertex" << now->num.size()
            << std ::endl;
            return -1;
        }
    }
    return cur;
}

template <typename T>
BNode<T> *BTree<T>::Merge(BNode<T> *now, BNode<T> *left, BNode<T> *right, T cur)
{
    BNode<T> *new_now = new BNode<T>();
    if (left != nullptr)
    {
        for (int i = 0; i < left->num.size(); i++)
        {
            new_now->num.push_back(left->num[i]);
        }
        for (int i = 0; i < left->childs.size(); i++)
        {
            new_now->childs.push_back(left->childs[i]);
            if (left->childs[i] != nullptr)
            {
                new_now->childs.back()->parent = new_now;
            }
        }
    }
    else
    {
        new_now->childs.push_back(nullptr);
    }
    new_now->num.push_back(cur);
    if (right != nullptr)
    {
        for (int i = 0; i < right->num.size(); i++)
        {
            new_now->num.push_back(right->num[i]);
        }
        for (int i = 0; i < right->childs.size(); i++)
        {
            new_now->childs.push_back(right->childs[i]);
            if (right->childs[i] != nullptr)
            {
                new_now->childs.back()->parent = new_now;
            }
        }
    }
    else
    {
        new_now->childs.push_back(nullptr);
    }
    new_now->parent = now;

    return new_now;
}

template <typename T>
BNode<T> *FindMinValue(BNode<T> *now)
{
    if (now->childs[0] == nullptr)
    {
        return now;
    }
    return FindMinValue(now->childs[0]);
}

template <typename T>
BNode<T> *FindMaxValue(BNode<T> *now)
{
    if (now->childs.back() == nullptr)
    {
        return now;
    }
    return FindMaxValue(now->childs.back());
}

template <typename T>
BNode<T> *BTree<T>::BalanceErase(BNode<T> *now)
{
    if (now == nullptr)
    {
        return nullptr;
    }
    if (now == root)
    {
        if (GetSize(root->childs[0]) > t - 1 || GetSize(root->childs[1]) > t - 1)
        {
            return root;
        }
        BNode<T> *new_root = new BNode<T>();
        T cur = root->num[0];
        BNode<T> *left = root->childs[0];
        BNode<T> *right = root->childs[1];
        new_root = Merge(nullptr, left, right, cur);
        root = new_root;
        return root;
    }
    int my_ind = MyNum(now);
    if (my_ind != now->parent->childs.size() - 1)
    {
        if (GetSize(GetRightBrother(now)) == t - 1)
        {
            BNode<T> *left = now->parent->childs[my_ind];
            BNode<T> *right = now->parent->childs[my_ind + 1];
            T cur = now->parent->num[my_ind];
            BNode<T> *new_now = Merge(now->parent, left, right, cur);
            now->parent->num.erase(now->parent->num.begin() + my_ind);
            now->parent->childs.erase(now->parent->childs.begin() + my_ind + 1);
            now->parent->childs[my_ind] = new_now;
            new_now->parent = now->parent;
            now->Delete(root);
            if (left != nullptr)
            {
                left->Delete(root);
            }
            if (right != nullptr)
            {
                right->Delete(root);
            }
            assert(new_now->num.size() >= 2);
            return new_now;
        }
        else
        {
            BNode<T> *right = GetRightBrother(now);
            assert(right != nullptr);
            T x = now->parent->num[my_ind];
            T y = right->num[0];
            T z = now->num.back();
            BNode<T> *alpha = right->childs[0];
            now->num.push_back(x);
            now->childs.push_back(alpha);
            if (alpha != nullptr)
            {
                alpha->parent = now;
            }
            std::swap(now->parent->num[my_ind], right->num[0]);
            right->num.erase(right->num.begin());
            right->childs.erase(right->childs.begin());
            assert(now->num.size() >= 2);
            return now;
        }
    }
    else
    {
        if (GetSize(GetLeftBrother(now)) == t - 1)
        {
            BNode<T> *left = now->parent->childs[my_ind - 1];
            BNode<T> *right = now->parent->childs[my_ind];

            T cur = now->parent->num[my_ind - 1];
            BNode<T> *new_now = Merge(now->parent, left, right, cur);
            now->parent->num.erase(now->parent->num.begin() + my_ind - 1);
            now->parent->childs.erase(now->parent->childs.begin() + my_ind);
            now->parent->childs[my_ind - 1] = new_now;
            new_now->parent = now->parent;
            now->Delete(root);
            if (left != nullptr)
            {
                left->Delete(root);
            }
            if (right != nullptr)
            {
                right->Delete(root);
            }
            now = new_now;
            assert(new_now->num.size() >= 2);
            return new_now;
        }
        else
        {
            BNode<T> *left = GetLeftBrother(now);
            assert(left != nullptr);
            T x = now->parent->num[my_ind - 1];
            T y = now->num[0];

            BNode<T> *alpha = left->childs.back();
            now->num.insert(now->num.begin(), x);
            now->childs.insert(now->childs.begin(), alpha);
            if (alpha != nullptr)
            {
                alpha->parent = now;
            }
            std::swap(now->parent->num[my_ind - 1], left->num.back());
            left->num.pop_back();
            left->childs.pop_back();
            assert(now->num.size() >= 2);
            return now;
        }
    }
}

template <typename T>
void BTree<T>::DeleteLeaf(BNode<T> *start, T cur)
{
    if (start == nullptr)
    {
        return;
    }

    if ((GetSize(start) == t - 1 && start != root) ||
        (GetSize(start) == 1 && start == root))
    {
        if (start != root)
        {
            start = BalanceErase(start);
        }
        else
        {
            start = BalanceErase(start);
            start = root;
        }
    }

    int ind = FindInBNode(start, cur);
    if (start->childs.back() == nullptr)
    {
        start->num.erase(start->num.begin() + ind);
        start->childs.erase(start->childs.begin() + ind);
        return;
    }
    return DeleteLeaf(start->childs[ind + 1], cur);
}

template <typename T>
void BTree<T>::EraseSecondStep(T cur, T need)
{
    BNode<T> *now = root;
    while (now != nullptr)
    {
        int ind = FindInBNode(now, cur);
        if (ind != -1 && now->num[ind] == cur)
        {
            now->num[ind] = need;
            return;
        }
        now = now->childs[ind + 1];
    }
}

template <typename T>
void BTree<T>::EraseFirstStep(T cur)
{
    if(size == 1 && root->num[0] == cur){
        size = 0;
        root = nullptr;
        return;
    }
    BNode<T> *now = root;
    while (now != nullptr)
    {
        int ind = FindInBNode(now, cur);
        if ((GetSize(now) == t - 1 && now != root) ||
            (now == root && GetSize(now) == 1))
        {
            if (now == root)
            {
                now = BalanceErase(now);
                now = root;
            }
            else
            {
                now = BalanceErase(now);
            }
            ind = FindInBNode(now, cur);
        }
        assert(now->num.size() != 0);

        if (ind != -1 && now->num[ind] == cur)
        {
            size--;
            if (now->childs[0] != nullptr)
            {
                BNode<T> *tmp = FindMaxValue(now->childs[ind]);
                T er = tmp->num.back();
                DeleteLeaf(now->childs[ind], tmp->num.back());
                EraseSecondStep(cur, er);
            }
            else
            {
                now->num.erase(now->num.begin() + ind);
                now->childs.erase(now->childs.begin() + ind);
                if (now->num.size() == 0)
                {
                    assert(now == root);
                    now->Delete(root);
                }
            }
            return;
        }

        now = now->childs[ind + 1];
        // std::cout << "aaaaa" << std::endl;
    }
}

template <typename T>
std::pair<int,int> BTree<T>::Print(BNode<T> *now,int block_size)
{
    if (now == nullptr)
    {
        return std::make_pair(0,0);
    }

    now->coor_x.clear();
    now->coor_y.clear();
    now->coor_x.resize(now->num.size());
    now->coor_y.resize(now->num.size());

    if(now->childs.size() == 0 || now->childs[0] == nullptr){
        for(int i = 0;i < now->num.size();i++){
            now->coor_y[i] = 0;
        }

        now->coor_x[0] = 0;
        for(int i = 1;i < now->num.size();i++){
            now->coor_x[i] = now->coor_x[i - 1] + block_size;
        }
        return {now->coor_x[0],now->coor_x.back() + block_size};
    }
    int cur_sum = 0;
    std::vector<std::pair<int,int>> help;
    int min = 1e9;

    for(int i = 0;i < now->childs.size();i++){
        auto tmp = Print(now->childs[i],block_size);
        if(i != 0){
            tmp.first += cur_sum + 7;
            tmp.second += cur_sum + 7;
            for(int j = 0;j < now->childs[i]->coor_x.size();j++){
                now->childs[i]->coor_x[j] += cur_sum + 7;
            }
        }
        for(int j = 0;j < now->childs[i]->coor_x.size();j++){
            min = std::min(min,now->childs[i]->coor_y[j]);
        }
        help.push_back(tmp);
        cur_sum = tmp.second;
    }


    for(int i = 0;i < now->num.size();i++){
        now->coor_y[i] = min - 50;
    }

    now->coor_x[0] = (help.back().second + help[0].first - block_size * now->num.size()) / 2;
    for(int i = 1;i < now->num.size();i++){
        now->coor_x[i] = now->coor_x[i - 1] + block_size;
    }

    for(int i = 0;i < now->childs.size();i++){
        for(int j = 0;j< now->childs[i]->num.size();j++){
            now->childs[i]->coor_y[j] = min;
            now->childs[i]->coor_x[j] = now->childs[i]->coor_x[j]- now->coor_x[0];
            now->childs[i]->coor_y[j] = now->childs[i]->coor_y[j] - now->coor_y[0];
        }
    }
    return {std::min(help[0].first,now->coor_x[0]),std::max(help.back().second,now->coor_x.back() + block_size)};
}

template <typename T>
bool BTree<T>::Check()
{
    int cur = CheckInv(root, 0);
    if (cur == -1)
    {
        return false;
    }
    return true;
}

