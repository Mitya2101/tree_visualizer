#include "RedBlack.h"

#include <iostream>
#include <cassert>

template <typename T>
void RedBlackNode<T>::Delete(RedBlackNode<T> *&root)
{
    Gap(this);
    Gap(this->left);
    Gap(this->right);
    if (root == this)
    {
        root = nullptr;
        return;
    }

    delete this;
}

template <typename T>
bool GetColor(RedBlackNode<T> *now)
{
    if (now == nullptr)
    {
        return 0;
    }
    return now->is_red;
}

template <typename T>
RedBlackNode<T> *GetParent(RedBlackNode<T> *now)
{
    if (now == nullptr)
    {
        return nullptr;
    }
    return now->parent;
}

template <typename T>
RedBlackNode<T> *GetGrandParent(RedBlackNode<T> *now)
{
    return GetParent(GetParent(now));
}

template <typename T>
RedBlackNode<T> *GetBrother(RedBlackNode<T> *now)
{
    if (now->parent == nullptr)
    {
        return nullptr;
    }
    if (now->parent->left == now)
    {
        return now->parent->right;
    }
    return now->parent->left;
}

template <typename T>
std::pair<RedBlackNode<T> *, RedBlackNode<T> *> GetChilds(RedBlackNode<T> *now)
{
    if (now == nullptr)
    {
        return std::make_pair(nullptr, nullptr);
    }
    return std::make_pair(now->left, now->right);
}

template <typename T>
RedBlackNode<T> *GetUncle(RedBlackNode<T> *now)
{
    return GetBrother(GetParent(now));
}

template <typename T>
std::pair<RedBlackNode<T> *, RedBlackNode<T> *> GetSiblings(RedBlackNode<T> *now)
{
    return GetChilds(GetBrother(now));
}

template <typename T>
void RedBlack<T>::LinkLeft(RedBlackNode<T> *par, RedBlackNode<T> *now)
{
    if (par == nullptr)
    {
        now->parent = nullptr;
        root = now;
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
void RedBlack<T>::LinkRight(RedBlackNode<T> *par, RedBlackNode<T> *now)
{
    if (par == nullptr)
    {
        now->parent = nullptr;
        root = now;
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
void Gap(RedBlackNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }
    if (now->parent == nullptr)
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
    now->parent = nullptr;
}

template <typename T>
void RedBlack<T>::SmallLeft(RedBlackNode<T> *now)
{
    if (now == nullptr || now->parent == nullptr)
    {
        return;
    }
    RedBlackNode<T> *tmp = now->left;
    RedBlackNode<T> *tmp1 = now->parent;
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
    LinkLeft(now, tmp1);
    LinkRight(tmp1, tmp);
    if (GetParent(now) == nullptr)
    {
        root = now;
    }
}

template <typename T>
void RedBlack<T>::SmallRight(RedBlackNode<T> *now)
{
    if (now == nullptr || now->parent == nullptr)
    {
        return;
    }
    RedBlackNode<T> *tmp = now->right;
    RedBlackNode<T> *tmp1 = now->parent;
    if (GetGrandParent(now) != nullptr)
    {
        if (GetGrandParent(now)->left == now->parent)
        {
            LinkLeft(GetGrandParent(now), now);
        }
        else
        {
            LinkRight(GetGrandParent(now), now);
        }
    }
    else
    {
        now->parent = nullptr;
    }

    LinkRight(now, tmp1);
    LinkLeft(tmp1, tmp);
    if (GetParent(now) == nullptr)
    {
        root = now;
    }
}

template <typename T>
void RedBlack<T>::BigLeft(RedBlackNode<T> *now)
{
    RedBlackNode<T> *tmp = now->left;
    SmallRight(tmp);
    SmallLeft(tmp);
}

template <typename T>
void RedBlack<T>::BigRight(RedBlackNode<T> *now)
{
    RedBlackNode<T> *tmp = now->right;
    SmallLeft(tmp);
    SmallRight(tmp);
}

template <typename T>
RedBlackNode<T> *RedBlack<T>::Find(int cur)
{
    RedBlackNode<T> *now = root;
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            return now;
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
    return now;
}

template <typename T>
void RedBlack<T>::Insert(int cur)
{
    if (root == nullptr)
    {
        root = new RedBlackNode<T>(cur);
        BalanceInsert(root);
        return;
    }
    RedBlackNode<T> *now = root;
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
                now->right = new RedBlackNode<T>(cur);
                now->right->is_red = true;
                now->right->parent = now;
                BalanceInsert(now->right);
                return;
            }
            now = now->right;
        }
        else
        {
            if (now->left == nullptr)
            {
                now->left = new RedBlackNode<T>(cur);
                now->left->is_red = true;
                now->left->parent = now;
                BalanceInsert(now->left);
                return;
            }
            now = now->left;
        }
    }
    return;
}

template <typename T>
void RedBlack<T>::BalanceInsert(RedBlackNode<T> *now)
{
    if (now == root)
    {
        now->is_red = false;
        return;
    }
    if (GetColor(GetParent(now)) != GetColor(now) || GetColor(now) == 0)
    {
        return;
    }
    if (GetColor(GetUncle(now)) == 1)
    {
        GetGrandParent(now)->is_red = true;
        GetUncle(now)->is_red = false;
        GetParent(now)->is_red = false;
        BalanceInsert(GetGrandParent(now));
        return;
    }
    if (GetGrandParent(now)->left == GetParent(now))
    {
        if (GetParent(now)->left == now)
        {
            SmallRight(GetParent(now));
            GetBrother(now)->is_red = 1;
            GetParent(now)->is_red = 0;
        }
        else if (GetParent(now)->right == now)
        {
            BigRight(GetParent(now));
            now->is_red = 0;
            if (now->right != nullptr)
            {
                now->right->is_red = 1;
            }
        }
    }
    else
    {
        if (GetParent(now)->right == now)
        {
            SmallLeft(GetParent(now));
            GetParent(now)->is_red = 0;
            GetBrother(now)->is_red = 1;
        }
        else if (GetParent(now)->left == now)
        {
            BigLeft(GetParent(now));
            now->is_red = 0;
            if (now->left != nullptr)
            {
                now->left->is_red = 1;
            }
        }
    }
}

template <typename T>
int RedBlack<T>::Print(RedBlackNode<T> *now,int block_size)
{
    if (now == nullptr) {
        return 0;
    }

    auto left = Print(now->left,block_size);
    auto right = Print(now->right,block_size);
    if(now->right != nullptr){
        if(now->left != nullptr){
            now->right->x += left + 7;
            right += left + 7;
        }else{
            now->right->x += left + 15;
            right += left + 15;
        }
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
    }else{
        now->y = max - 50;
    }
    if(now->left != nullptr || now->right != nullptr){
        if(now->left == nullptr){
            now->x = help_right - 15;
        }
        if(now->right == nullptr){
            now->x = help_left + 15;
        }
    }

    int ans;

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


    ans = std::max(now->x + block_size,right);




    return ans;


}

template <typename T>
void RedBlack<T>::DeleteCliffLeft(RedBlackNode<T> *now)
{
    if (now == root)
    {
        now->left->parent = nullptr;
        root = now->left;
        root->parent = nullptr;
        return;
    }
    RedBlackNode<T> *tmp = now->parent;
    RedBlackNode<T> *tmp1 = now->left;
    Gap(now->left);
    Gap(now);
    if (tmp->num > tmp1->num)
    {
        LinkLeft(tmp, tmp1);
    }
    else
    {
        LinkRight(tmp, tmp1);
    }
    now->Delete(root);
}

template <typename T>
void RedBlack<T>::DeleteCliffRight(RedBlackNode<T> *now)
{
    if (now == root)
    {
        now->right->parent = nullptr;
        root = now->right;
        return;
    }
    RedBlackNode<T> *tmp = now->parent;
    RedBlackNode<T> *tmp1 = now->right;
    Gap(now->right);
    Gap(now);
    if (tmp->num > tmp1->num)
    {
        LinkLeft(tmp, tmp1);
    }
    else
    {
        LinkRight(tmp, tmp1);
    }
    now->Delete(root);
}

template <typename T>
void RedBlack<T>::SolveCliffLeft(RedBlackNode<T> *now)
{
    if (now->left == nullptr)
    {
        if (GetColor(now) == 1)
        {
            Gap(now);
            now->Delete(root);
            return;
        }
        BalanceErase(now);
        Gap(now);
        now->Delete(root);
        return;
    }
    if (GetColor(now) == GetColor(now->left))
    {
        assert(GetColor(now) == 1);
        BalanceErase(now);
        DeleteCliffLeft(now);
    }
    else if (GetColor(now) == 1)
    {
        DeleteCliffLeft(now);
    }
    else
    {
        RedBlackNode<T> *tmp1 = now->left;
        DeleteCliffLeft(now);
        assert(GetColor(tmp1) == 1);
        tmp1->is_red = 0;
    }
}

template <typename T>
void RedBlack<T>::SolveCliffRight(RedBlackNode<T> *now)
{
    if (now->right == nullptr)
    {
        if (GetColor(now) == 1)
        {
            Gap(now);
            now->Delete(root);
            return;
        }
        BalanceErase(now);
        Gap(now);
        now->Delete(root);
        return;
    }
    if (GetColor(now) == GetColor(now->right))
    {
        assert(GetColor(now) == 1);
        BalanceErase(now);
        DeleteCliffRight(now);
    }
    else if (GetColor(now) == 1)
    {
        DeleteCliffRight(now);
    }
    else
    {
        RedBlackNode<T> *tmp1 = now->right;
        DeleteCliffRight(now);
        assert(GetColor(tmp1) == 1);
        tmp1->is_red = 0;
    }
}

template <typename T>
int RedBlack<T>::Check()
{
    if (GetColor(root) == 1)
    {
        std::cout << "Root is red" << std::endl;
        return -1;
    }
    return CheckInv(root, 0);
}

template <typename T>
int RedBlack<T>::CheckInv(RedBlackNode<T> *now, int height)
{
    if (now == nullptr)
    {
        return height;
    }
    if (GetColor(now) == GetColor(now->left) && GetColor(now) == 1)
    {
        std::cout << "Two Red with left child" << std::endl;
        return -1;
    }
    if (GetColor(now) == GetColor(now->right) && GetColor(now) == 1)
    {
        std::cout << "Two Red with right child" << std::endl;
        return -1;
    }
    int cur = CheckInv(now->left, height + (1 - GetColor(now)));
    if (cur == -1)
    {
        return cur;
    }
    int cur1 = CheckInv(now->right, height + (1 - GetColor(now)));
    if (cur1 == -1)
    {
        return cur1;
    }
    if (cur != cur1)
    {
        std::cout << "Different black height" << std::endl;
        return -1;
    }
    return cur;
}

template <typename T>
RedBlackNode<T> *RedBlack<T>::FindMinValue(RedBlackNode<T> *now)
{
    if (now == nullptr)
    {
        return nullptr;
    }
    if (now->left == nullptr)
    {
        return now;
    }
    return FindMinValue(now->left);
}

template <typename T>
void UpdateColor(RedBlackNode<T> *now, int color)
{
    if (now == nullptr)
    {
        return;
    }
    now->is_red = color;
}

template <typename T>
void RedBlack<T>::SolveForRedParent(RedBlackNode<T> *now)
{
    std::pair<RedBlackNode<T> *, RedBlackNode<T> *> sib = GetSiblings(now);
    if (GetColor(sib.first) == 0 && GetColor(sib.second) == 0)
    {
        UpdateColor(GetParent(now), 0);
        UpdateColor(GetBrother(now), 1);
        return;
    }
    if (GetParent(now)->left == GetBrother(now))
    {
        if (GetColor(sib.first) == 1)
        {
            SmallRight(GetBrother(now));
            UpdateColor(GetParent(now), 0);
            UpdateColor(GetGrandParent(now), 1);
            assert(sib.first == GetUncle(now));
            UpdateColor(sib.first, 0);
            return;
        }
        else if (GetColor(sib.second) == 1)
        {
            BigRight(GetBrother(now));
            UpdateColor(GetParent(now), 0);
            return;
        }
        else
        {
            assert(0);
        }
    }
    else if (GetParent(now)->right == GetBrother(now))
    {
        if (GetColor(sib.first) == 1)
        {
            BigLeft(GetBrother(now));
            assert(sib.first == GetGrandParent(now));
            UpdateColor(GetParent(now), 0);
            return;
        }
        else if (GetColor(sib.second) == 1)
        {
            SmallLeft(GetBrother(now));
            assert(sib.second == GetUncle(now));
            UpdateColor(GetParent(now), 0);
            UpdateColor(GetGrandParent(now), 1);
            UpdateColor(GetUncle(now), 0);
            return;
        }
        else
        {
            assert(0);
        }
    }
}

template <typename T>
void RedBlack<T>::BalanceErase(RedBlackNode<T> *now)
{
    if (now == root)
    {
        return;
    }
    if (GetColor(GetParent(now)) == 1)
    {
        SolveForRedParent(now);
    }
    else
    {
        if (GetColor(GetBrother(now)) == 1)
        {
            if (GetParent(now)->left == GetBrother(now))
            {
                SmallRight(GetBrother(now));
            }
            else
            {
                SmallLeft(GetBrother(now));
            }
            UpdateColor(GetGrandParent(now), 0);
            UpdateColor(GetParent(now), 1);

            // Print(root);
            SolveForRedParent(now);
            return;
        }
        std::pair<RedBlackNode<T> *, RedBlackNode<T> *> sib = GetSiblings(now);
        if (GetParent(now)->left == GetBrother(now))
        {
            if (GetColor(sib.first) == 1)
            {
                SmallRight(GetBrother(now));
                assert(sib.first == GetUncle(now));
                UpdateColor(GetUncle(now), 0);
                return;
            }
            else if (GetColor(sib.second) == 1)
            {
                BigRight(GetBrother(now));
                assert(sib.second == GetGrandParent(now));
                UpdateColor(GetGrandParent(now), 0);
                return;
            }
            else if (GetColor(sib.second) == 0 && GetColor(sib.first) == 0)
            {
                UpdateColor(GetBrother(now), 1);
                BalanceErase(GetParent(now));
            }
            else
            {
                assert(0);
            }
        }
        else if (GetParent(now)->right == GetBrother(now))
        {
            if (GetColor(sib.first) == 1)
            {
                BigLeft(GetBrother(now));
                assert(sib.first == GetGrandParent(now));
                UpdateColor(GetGrandParent(now), 0);
                return;
            }
            else if (GetColor(sib.second) == 1)
            {
                SmallLeft(GetBrother(now));
                assert(sib.second == GetUncle(now));
                UpdateColor(GetUncle(now), 0);
                return;
            }
            else if (GetColor(sib.first) == 0 && GetColor(sib.second) == 0)
            {
                UpdateColor(GetBrother(now), 1);
                BalanceErase(GetParent(now));
            }
            else
            {
                assert(0);
            }
        }
    }
}

template <typename T>
void RedBlack<T>::Erase(int cur)
{
    RedBlackNode<T> *now = root;
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            if (now->left == nullptr && now->right == nullptr)
            {
                // std::cout << "fjg" << std::endl;
                SolveCliffLeft(now);
            }
            else if (now->left == nullptr)
            {
                SolveCliffRight(now);
            }
            else if (now->right == nullptr)
            {
                SolveCliffLeft(now);
            }
            else
            {
                RedBlackNode<T> *help = FindMinValue(now->right);
                std::swap(help->num, now->num);
                SolveCliffRight(help);
            }
            return;
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
}

