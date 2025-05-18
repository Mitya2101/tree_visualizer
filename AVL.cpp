#ifndef AVL_cpp
#define AVL_cpp

#include "AVL.h"

#include <cassert>
#include <algorithm>

template <typename T>
void AVLNode<T>::Clear()
{
    if (parent != nullptr)
    {
        if (parent->left == this)
        {
            parent->left = nullptr;
        }
        else if (parent->right == this)
        {
            parent->right = nullptr;
        }
    }
    if (left != nullptr)
    {
        assert(0);
    }
    if (right != nullptr)
    {
        assert(0);
    }
    delete this;
}

template <typename T>
int GetHeight(AVLNode<T> *now)
{
    if (now == nullptr)
    {
        return 0;
    }
    return now->height;
}

template <typename T>
void UpdateHeight(AVLNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }
    now->height = std::max(GetHeight(now->left), GetHeight(now->right)) + 1;
}

template <typename T>
void AVL<T>::SmallLeft(AVLNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }
    if (now->parent == nullptr)
    {
        return;
    }

    bool was = false;

    if (now->parent->parent == nullptr)
    {
        AVLNode<T> *tmp = now->left;
        now->left = now->parent;
        now->parent = now->left->parent;

        now->left->parent = now;
        now->left->right = tmp;
        if (tmp != nullptr)
        {
            tmp->parent = now->left;
        }
        root = now;
    }
    else
    {
        if (now->parent->parent->left == now->parent)
        {
            was = true;
        }

        AVLNode<T> *tmp = now->left;
        now->left = now->parent;
        now->parent = now->left->parent;
        if (was)
        {
            now->parent->left = now;
        }
        else
        {
            now->parent->right = now;
        }

        now->left->parent = now;
        now->left->right = tmp;
        if (tmp != nullptr)
        {
            tmp->parent = now->left;
        }
    }
    UpdateHeight(now->left);
    UpdateHeight(now);
}

template <typename T>
void AVL<T>::SmallRight(AVLNode<T> *now)
{
    if (now == nullptr)
    {
        return;
    }
    if (now->parent == nullptr)
    {
        return;
    }
    bool was = false;
    if (now->parent->parent == nullptr)
    {
        AVLNode<T> *tmp = now->right;
        now->right = now->parent;
        now->parent = now->right->parent;

        now->right->parent = now;
        now->right->left = tmp;
        if (tmp != nullptr)
        {
            tmp->parent = now->right;
        }
        root = now;
    }
    else
    {
        if (now->parent->parent->left == now->parent)
        {
            was = true;
        }

        AVLNode<T> *tmp = now->right;
        now->right = now->parent;
        now->parent = now->right->parent;

        if (was)
        {
            now->parent->left = now;
        }
        else
        {
            now->parent->right = now;
        }

        now->right->parent = now;
        now->right->left = tmp;
        if (tmp != nullptr)
        {
            tmp->parent = now->right;
        }
    }

    if (now->parent == nullptr)
    {
        root = now;
    }

    UpdateHeight(now->right);
    UpdateHeight(now);
}

template <typename T>
void AVL<T>::BigLeft(AVLNode<T> *now)
{
    AVLNode<T> *tmp = now->left;
    SmallRight(tmp);
    SmallLeft(tmp);
}

template <typename T>
void AVL<T>::BigRight(AVLNode<T> *now)
{
    AVLNode<T> *tmp = now->right;
    SmallLeft(now->right);
    SmallRight(tmp);
}

template <typename T>
void AVL<T>::Balance(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        return;
    }
    UpdateHeight(now->parent);

    if (std::abs(GetHeight(now->parent->left) - GetHeight(now->parent->right)) <=
        1)
    {
        Balance(now->parent);
        return;
    }
    AVLNode<T> *need = now;
    if (GetHeight(now->parent->left) < GetHeight(now->parent->right))
    {
        need = now->parent->right;
    }
    else
    {
        need = now->parent->left;
    }
    if (now->parent->left == need)
    {
        if (GetHeight(need->left) >= GetHeight(need->right))
        {
            SmallRight(need);
            Balance(need);
            return;
        }
        else if (GetHeight(need->right) > GetHeight(need->left))
        {
            BigRight(need);
            Balance(need->parent);
            return;
        }
    }
    else
    {
        if (GetHeight(need->left) > GetHeight(need->right))
        {
            BigLeft(need);
            Balance(need->parent);
            return;
        }
        else if (GetHeight(need->right) >= GetHeight(need->left))
        {
            SmallLeft(need);
            Balance(need);
            return;
        }
    }
}

template <typename T>
void AVL<T>::Insert(T cur)
{
    AVLNode<T> *now = root;
    if (now == nullptr)
    {
        root = new AVLNode<T>(nullptr, cur);
        Balance(root);
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
                now->right = new AVLNode<T>(now, cur);
                Balance(now->right);
                return;
            }
            now = now->right;
        }
        else
        {
            if (now->left == nullptr)
            {
                now->left = new AVLNode<T>(now, cur);
                Balance(now->left);
                return;
            }
            now = now->left;
        }
    }
}

template <typename T>
AVLNode<T> *AVL<T>::Find(T cur)
{
    AVLNode<T> *now = root;
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            break;
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
AVLNode<T> *FindMinValue(AVLNode<T> *now)
{
    if (now->left != nullptr)
    {
        return FindMinValue(now->left);
    }
    return now;
}

template <typename T>
AVLNode<T> *FindMaxValue(AVLNode<T> *now)
{
    if (now->right != nullptr)
    {
        return FindMaxValue(now->right);
    }
    return now;
}

template <typename T>
void AVL<T>::SolveLeftLeft(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        root = now->left;
        if (now->left != nullptr)
        {
            now->left->parent = nullptr;
        }
    }
    else
    {
        now->parent->left = now->left;
        if (now->left != nullptr)
        {
            now->left->parent = now->parent;
            Balance(now->left);
        }
        else
        {
            Balance(now);
        }
    }
}

template <typename T>
void AVL<T>::SolveRightLeft(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        root = now->left;
        if (now->left != nullptr)
        {
            now->left->parent = nullptr;
        }
    }
    else
    {
        now->parent->right = now->left;
        if (now->left != nullptr)
        {

            now->left->parent = now->parent;
            Balance(now->left);
        }
        else
        {
            Balance(now);
        }
    }
}

template <typename T>
void AVL<T>::SolveRightRight(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        root = now->right;
        if (now->right != nullptr)
        {
            now->right->parent = nullptr;
        }
    }
    else
    {
        now->parent->right = now->right;
        if (now->right != nullptr)
        {
            now->right->parent = now->parent;
            Balance(now->right);
        }
        else
        {
            Balance(now);
        }
    }
}

template <typename T>
void AVL<T>::SolveLeftRight(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        root = now->left;
        if (now->right != nullptr)
        {
            now->right->parent = nullptr;
        }
    }
    else
    {
        now->parent->left = now->right;
        if (now->right != nullptr)
        {
            now->right->parent = now->parent;

            Balance(now->right);
        }
        else
        {
            Balance(now);
        }
    }
}

template <typename T>
void AVL<T>::SolveLeft(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        SolveLeftLeft(now);
    }
    else
    {
        if (now->parent->left == now)
        {
            SolveLeftLeft(now);
        }
        else
        {
            SolveRightLeft(now);
        }
    }
    now->left = nullptr;
}

template <typename T>
void AVL<T>::SolveRight(AVLNode<T> *now)
{
    if (now->parent == nullptr)
    {
        SolveRightRight(now);
    }
    else
    {
        if (now->parent->left == now)
        {
            SolveLeftRight(now);
        }
        else
        {
            SolveRightRight(now);
        }
    }
    now->right = nullptr;
}

template <typename T>
void AVL<T>::Erase(T cur)
{
    AVLNode<T> *now = root;
    while (now != nullptr)
    {
        if (now->num == cur)
        {
            if (now->left == nullptr && now->right == nullptr)
            {
                now->height = 0;
                Balance(now);
                if (now->parent != nullptr)
                {
                    if (now->parent->left == now)
                    {
                        now->parent->left = nullptr;
                    }
                    else if (now->parent->right == now)
                    {
                        now->parent->right = nullptr;
                    }
                }

                if (now == root)
                {
                    root = nullptr;
                }
            }
            else if (now->left == nullptr)
            {
                SolveRight(now);
                if (now != root)
                {
                    now->Clear();
                }
            }
            else if (now->right == nullptr)
            {
                SolveLeft(now);
                if (now != root)
                {
                    now->Clear();
                }
            }
            else
            {
                AVLNode<T> *tmp = FindMinValue(now->right);
                std::swap(tmp->num, now->num);
                tmp->height = 0;
                SolveRight(tmp);

                if (root != tmp)
                {
                    tmp->Clear();
                }
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

template <typename T>
int AVL<T>::Print(AVLNode<T> *now, int block_size)
{
    if (now == nullptr)
    {
        return 0;
    }

    auto left = Print(now->left, block_size);
    auto right = Print(now->right, block_size);
    if (now->right != nullptr)
    {
        if (now->left != nullptr)
        {
            now->right->x += left + 7;
            right += left + 7;
        }
        else
        {
            now->right->x += left + 15;
            right += left + 15;
        }
    }
    int help_left = 0;
    if (now->left != nullptr)
    {
        help_left = now->left->x;
    }
    int help_right = 0;
    if (now->right != nullptr)
    {
        help_right = now->right->x;
    }
    now->x = (help_left + help_right) / 2;

    int max = 1e9;
    if (now->left != nullptr)
    {
        max = std::min(max, now->left->y);
    }
    if (now->right != nullptr)
    {
        max = std::min(max, now->right->y);
    }
    if (max == 1e9)
    {
        max = 0;
    }

    if (now->left == nullptr && now->right == nullptr)
    {
        now->y = 0;
    }
    else
    {
        now->y = max - 50;
    }
    if (now->left != nullptr || now->right != nullptr)
    {
        if (now->left == nullptr)
        {
            now->x = help_right - 15;
        }
        if (now->right == nullptr)
        {
            now->x = help_left + 15;
        }
    }

    int ans;

    if (now->left != nullptr)
    {
        now->left->y = max;
        now->left->x = now->left->x - now->x;
        now->left->y = now->left->y - now->y;
    }
    if (now->right != nullptr)
    {
        now->right->y = max;
        now->right->x = now->right->x - now->x;
        now->right->y = now->right->y - now->y;
    }

    ans = std::max(now->x + block_size, right);
    return ans;
}

template <typename T>
int AVL<T>::CheckInv(AVLNode<T> *now)
{
    if (now == nullptr)
    {
        return 0;
    }
    int left = CheckInv(now->left);
    int right = CheckInv(now->right);
    if (left == -1 || right == -1)
        return -1;
    if (std::abs(left - right) >= 2)
        return -1;
    if (GetHeight(now) != std::max(left, right) + 1)
    {
        return -1;
    }
    return std::max(left, right) + 1;
}

#endif // AVL_cpp
