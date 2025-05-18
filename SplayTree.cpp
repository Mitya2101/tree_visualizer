#include "SplayTree.h"

#include <iostream>
#include<cassert>

template <typename T>
void SplayNode<T>::Delete(SplayNode<T> *&root)
{
    if (this == nullptr)
    {
        return;
    }

    if (this->parent != nullptr)
    {
        if (this->parent->left == this)
        {
            this->parent->left = nullptr;
        }
        else if (this->parent->right == this)
        {
            this->parent->right = nullptr;
        }
    }
    if (this->left != nullptr)
    {
        this->left->parent = nullptr;
    }
    if (this->right != nullptr)
    {
        this->right->parent = nullptr;
    }
    this->left = nullptr;
    this->right = nullptr;
    if (root == this)
    {
        root = nullptr;
        return;
    }
    delete this;
}

template <typename T>
SplayNode<T> *GetParent(SplayNode<T> *now)
{
    if (now == nullptr)
    {
        return nullptr;
    }
    return now->parent;
}

template <typename T>
SplayNode<T> *GetGrandParent(SplayNode<T> *now)
{
    return GetParent(GetParent(now));
}

template <typename T>
int NumberForParent(SplayNode<T> *now)
{
    if (now->parent == nullptr)
    {
        return -1;
    }
    if (now->parent->left == now)
    {
        return 0;
    }
    else if (now->parent->right == now)
    {
        return 1;
    }
    return -1;
}

template <typename T>
void SplayTree<T>::Gap(SplayNode<T> *now)
{
    if (now == nullptr || now->parent == nullptr)
    {
        return;
    }
    if (now->parent->left == now)
    {
        now->parent->left = nullptr;
        now->parent = nullptr;
    }
    else if (now->parent->right == now)
    {
        now->parent->right = nullptr;
        now->parent = nullptr;
    }
}

template <typename T>
void SplayTree<T>::LinkLeft(SplayNode<T> *par, SplayNode<T> *now)
{
    if (par == nullptr)
    {
        return;
    }
    Gap(par->left);
    Gap(now);
    par->left = now;
    if (now != nullptr)
    {
        now->parent = par;
    }
}

template <typename T>
void SplayTree<T>::LinkRight(SplayNode<T> *par, SplayNode<T> *now)
{
    if (par == nullptr)
    {
        return;
    }
    Gap(par->right);
    Gap(now);
    par->right = now;
    if (now != nullptr)
    {
        now->parent = par;
    }
}

template <typename T>
void SplayTree<T>::SmallLeft(SplayNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }

    SplayNode<T> *tmp = now->parent;
    SplayNode<T> *tmp1 = now->left;

    if (GetGrandParent(now) != nullptr)
    {
        if (GetGrandParent(now)->left == now->parent)
        {
            LinkLeft(GetGrandParent(now), now);
        }
        else if (GetGrandParent(now)->right == now->parent)
        {
            LinkRight(GetGrandParent(now), now);
        }
    }
    else
    {
        now->parent = nullptr;
    }
    LinkLeft(now, tmp);
    LinkRight(tmp, tmp1);

    if (GetParent(now) == nullptr)
    {
        root = now;
    }
}

template <typename T>

void SplayTree<T>::SmallRight(SplayNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }

    SplayNode<T> *tmp = now->parent;
    SplayNode<T> *tmp1 = now->right;

    if (GetGrandParent(now) != nullptr)
    {
        if (GetGrandParent(now)->left == now->parent)
        {
            LinkLeft(GetGrandParent(now), now);
        }
        else if (GetGrandParent(now)->right == now->parent)
        {
            LinkRight(GetGrandParent(now), now);
        }
    }
    else
    {
        now->parent = nullptr;
    }
    LinkRight(now, tmp);
    LinkLeft(tmp, tmp1);

    if (GetParent(now) == nullptr)
    {
        root = now;
    }
}

template <typename T>
void SplayTree<T>::BigLeft(SplayNode<T> *now)
{
    if (now == nullptr || now->left == nullptr)
    {
        return;
    }
    SplayNode<T> *tmp = now->left;
    SmallRight(tmp);
    SmallLeft(tmp);
}

template <typename T>
void SplayTree<T>::BigRight(SplayNode<T> *now)
{
    if (now == nullptr || now->right == nullptr)
    {
        return;
    }
    SplayNode<T> *tmp = now->right;
    SmallLeft(tmp);
    SmallRight(tmp);
}

template <typename T>
void SplayTree<T>::ZigZigLeft(SplayNode<T> *now)
{
    if (GetGrandParent(now) == nullptr)
    {
        assert(0);
    }
    SmallLeft(GetParent(now));
    SmallLeft(now);
}

template <typename T>
void SplayTree<T>::ZigZigRight(SplayNode<T> *now)
{
    if (GetGrandParent(now) == nullptr)
    {
        return;
    }
    SmallRight(GetParent(now));
    SmallRight(now);
}

template <typename T>
void SplayTree<T>::Splay(SplayNode<T> *now)
{
    if (now == root)
    {
        return;
    }
    if (GetGrandParent(now) == nullptr)
    {
        if (NumberForParent(now) == 0)
        {
            SmallRight(now);
        }
        else
        {
            SmallLeft(now);
        }
        return;
    }
    if (NumberForParent(now) == NumberForParent(GetParent(now)))
    {
        if (NumberForParent(now) == 0)
        {
            ZigZigRight(now);
        }
        else
        {
            ZigZigLeft(now);
        }
    }
    else
    {
        if (NumberForParent(now) == 1)
        {
            BigRight(GetParent(now));
        }
        else
        {
            BigLeft(GetParent(now));
        }
    }
    Splay(now);
}

template <typename T>
SplayNode<T> *SplayTree<T>::FindMinValue(SplayNode<T> *now)
{
    if (now->left == nullptr)
    {
        return now;
    }
    return FindMinValue(now->left);
}

template <typename T>
SplayNode<T> *SplayTree<T>::Find(const T &cur)
{
    SplayNode<T> *now = root;
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            Splay(now);
            return root;
        }
        if (now->num < cur)
        {
            now = now->right;
        }
        else
        {
            now = now->left;
        }
    }
    return nullptr;
}

template <typename T>
SplayNode<T> *SplayTree<T>::FindFirstMore(SplayNode<T> *now, const T &x)
{
    if (now == nullptr)
        return nullptr;
    if (now->num == x)
    {
        return now;
    }
    if (now->num < x)
    {
        return FindFirstMore(now->right, x);
    }
    else
    {
        SplayNode<T> *tmp = FindFirstMore(now->left, x);
        if (tmp != nullptr)
        {
            return tmp;
        }
        return now;
    }
}

template <typename T>
SplayNode<T> *SplayTree<T>::Merge(SplayTree<T> *first, SplayTree<T> *second)
{
    if (first->root == nullptr)
    {
        return second->root;
    }
    if (second->root == nullptr)
    {
        return first->root;
    }
    SplayNode<T> *tmp = FindMinValue(second->root);
    second->Splay(tmp);
    assert(second->root == tmp);
    tmp->parent = nullptr;
    LinkLeft(tmp, first->root);
    return tmp;
}

template <typename T>
std::pair<SplayNode<T> *, SplayNode<T> *> SplayTree<T>::Split(SplayNode<T> *now, const T &x)
{
    SplayNode<T> *tmp = FindFirstMore(now, x);

    if (tmp == nullptr)
    {
        return {now, nullptr};
    }
    Splay(tmp);
    assert(tmp == root);
    SplayNode<T> *first = root->left;
    root->left = nullptr;
    return {first, root};
}

template <typename T>
void SplayTree<T>::Insert(const T &cur)
{
    if(Find(cur) != nullptr){
        return;
    }
    SplayNode<T> *now = root;
    if (root == nullptr)
    {
        root = new SplayNode<T>(cur);
        return;
    }
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            return;
        }
        if (now->num < cur)
        {
            if (now->right == nullptr)
            {

                now->right = new SplayNode<T>(cur);
                LinkRight(now, now->right);
                Splay(now->right);
                return;
            }
            now = now->right;
        }
        else
        {
            if (now->left == nullptr)
            {
                now->left = new SplayNode<T>(cur);
                LinkLeft(now, now->left);
                Splay(now->left);
                return;
            }
            now = now->left;
        }
    }
}

template <typename T>
void SplayTree<T>::Erase(const T &cur)
{
    SplayNode<T> *tmp = Find(cur);
    if (tmp == nullptr)
    {
        return;
    }
    Splay(tmp);
    SplayNode<T> *tmp1 = root->left;
    SplayNode<T> *tmp2 = root->right;
    tmp->Delete(tmp);
    root = Merge(new SplayTree(tmp1), new SplayTree(tmp2));
}

template <typename T>
std::pair<int,int> SplayTree<T>::Print(SplayNode<T> *now, int block_size)
{
    if (now == nullptr) {
        return std::make_pair(0,0);
    }

    auto left = Print(now->left,block_size);
    auto right = Print(now->right,block_size);
    if(now->right != nullptr){
        now->right->x += left.second + 7;
        right.second += left.second + 7;
        right.first += left.second + 7;
    }
    int help_left = 0;
    if(now->left != nullptr){
        help_left = now->left->x;
    }
    int help_right = 0;
    if(now->right != nullptr){
        help_right = now->right->x;
    }


    now->x = (help_left + help_right) / 2;
    if(now->left == nullptr){
        if(now->right != nullptr){

            now->x = now->right->x - 2 - block_size;
        }
    }
    if(now->right == nullptr){
        if(now->left != nullptr){
            now->x = now->left->x + 2 + block_size;
        }
    }

    int max = 1e9;
    if(now->left != nullptr){
        max = std::min(max,now->left->y);
    }
    if(now->right != nullptr){
        max = std::min(max,now->right->y);
    }
    if(max == 1e9){
        max = 0;
    }


    if(now->left == nullptr && now->right == nullptr){
        now->y = 0;
    }else if(now->left != nullptr){
        now->y = max - 50;
    }else{
        now->y = max - 50;
    }
    std::pair<int,int> ans;

    if(now->left != nullptr){
        now->left->y = max;
        now->left->x = now->left->x - now->x;
        now->left->y = now->left->y - now->y;
    }
    if(now->right != nullptr){
        now->right->y = max;
        now->right->x = now->right->x - now->x;
        now->right->y = now->right->y - now->y;
    }

    if(now->left == nullptr){
        left.first = right.first;
    }
    if(now->right == nullptr){
        right.second = left.second;
    }


    ans.first = std::min(left.first,now->x);
    ans.second = std::max(now->x + block_size,right.second);

    if(ans.first < 0){
        ans.second -= ans.first;
        now->x -= ans.first;
        ans.first = 0;

    }
    return ans;


}

