
#ifndef TREAP_CPP
#define TREAP_CPP
#include "Treap.h"
#include<iostream>

template <typename T>
std::pair<TreapNode<T>*, TreapNode<T>*> Treap<T>::Split(TreapNode<T>* a, const T& key) {
    if (a == nullptr) {
        return {nullptr, nullptr};
    }
    if (a->num <= key) {
        auto tmp = Split(a->right, key);
        a->right = tmp.first;
        return {a, tmp.second};
    } else {
        auto tmp = Split(a->left, key);
        a->left = tmp.second;
        return {tmp.first, a};
    }
}

template<typename T>
Treap<T>::Treap(){
    rng.seed(69);
    root = nullptr;
}

template<typename T>
TreapNode<T>::TreapNode(){
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <typename T>
TreapNode<T>* Treap<T>::Merge(TreapNode<T>* first, TreapNode<T>* second) {
    if (first == nullptr) {
        return second;
    }
    if (second == nullptr) {
        return first;
    }

    if (first->prior < second->prior) {
        first->right = Merge(first->right, second);
        return first;
    } else {
        second->left = Merge(first, second->left);
        return second;
    }
}

template <typename T>
TreapNode<T>* Treap<T>::Find(const T& cur) {
    TreapNode<T>* now = root;
    while (now != nullptr) {
        if (now->num == cur) {
            return now;
        }
        if (now->num < cur) {
            now = now->right;
        } else {
            now = now->left;
        }
    }
    return nullptr;
}

template <typename T>
void Treap<T>::Insert(const T& cur) {
    if (Find(cur) != nullptr) {
        return;
    }
    auto tmp = Split(root, cur);
    tmp.first = Merge(tmp.first, new TreapNode<T>(cur,rng));
    root = Merge(tmp.first, tmp.second);
}

template <typename T>
void Treap<T>::Erase(const T& cur) {
    auto tmp = Split(root, cur);
    auto tmp1 = Split(tmp.first, cur - 1);
    root = Merge(tmp1.first, tmp.second);
}

template<typename T>
std::pair<int,int> Treap<T>::Print(TreapNode<T>* now,int block_size){
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

    int all = left.second - left.first+ right.second  - right.first;


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
        ans.first =0 ;

    }
    return ans;


}

#endif // TREAP_CPP


