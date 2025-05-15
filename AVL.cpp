#ifndef AVL_cpp
#define AVL_cpp


#include "AVL.h"


#include<cassert>

#include <algorithm>
#include<iostream>

void AVLNode::Clear() {
    if (parent != nullptr) {
        if (parent->left == this) {
            parent->left = nullptr;
        } else if (parent->right == this) {
            parent->right = nullptr;
        }
    }
    if (left != nullptr) {
        assert(0);
    }
    if (right != nullptr) {
        assert(0);
    }
    delete this;
}

int GetHeight(AVLNode* now) {
    if (now == nullptr) {
        return 0;
    }
    return now->height;
}

void UpdateHeight(AVLNode* now) {
    if (now == nullptr) {
        return;
    }
    now->height = std::max(GetHeight(now->left), GetHeight(now->right)) + 1;
}

void AVL::SmallLeft(AVLNode* now) {
    if (now == nullptr) {
        return;
    }
    if (now->parent == nullptr) {
        return;
    }

    bool was = false;

    if (now->parent->parent == nullptr) {
        AVLNode* tmp = now->left;
        now->left = now->parent;
        now->parent = now->left->parent;

        now->left->parent = now;
        now->left->right = tmp;
        if (tmp != nullptr) {
            tmp->parent = now->left;
        }
        root = now;
    } else {
        if (now->parent->parent->left == now->parent) {
            was = true;
        }

        AVLNode* tmp = now->left;
        now->left = now->parent;
        now->parent = now->left->parent;
        if (was) {
            now->parent->left = now;
        } else {
            now->parent->right = now;
        }

        now->left->parent = now;
        now->left->right = tmp;
        if (tmp != nullptr) {
            tmp->parent = now->left;
        }
    }
    UpdateHeight(now->left);
    UpdateHeight(now);
}

void AVL::SmallRight(AVLNode* now) {
    if (now == nullptr) {
        return;
    }
    if (now->parent == nullptr) {
        return;
    }
    bool was = false;
    if (now->parent->parent == nullptr) {
        AVLNode* tmp = now->right;
        now->right = now->parent;
        now->parent = now->right->parent;

        now->right->parent = now;
        now->right->left = tmp;
        if (tmp != nullptr) {
            tmp->parent = now->right;
        }
        root = now;
    } else {
        if (now->parent->parent->left == now->parent) {
            was = true;
        }

        AVLNode* tmp = now->right;
        now->right = now->parent;
        now->parent = now->right->parent;

        if (was) {
            now->parent->left = now;
        } else {
            now->parent->right = now;
        }

        now->right->parent = now;
        now->right->left = tmp;
        if (tmp != nullptr) {
            tmp->parent = now->right;
        }
    }

    if (now->parent == nullptr) {
        root = now;
    }

    UpdateHeight(now->right);
    UpdateHeight(now);
}

void AVL::BigLeft(AVLNode* now) {
    AVLNode* tmp = now->left;
    SmallRight(tmp);
    SmallLeft(tmp);
}

void AVL::BigRight(AVLNode* now) {
    AVLNode* tmp = now->right;
    SmallLeft(now->right);
    SmallRight(tmp);
}

void AVL::Balance(AVLNode* now) {
    if (now->parent == nullptr) {
        return;
    }
    UpdateHeight(now->parent);


    if (std::abs(GetHeight(now->parent->left) - GetHeight(now->parent->right)) <=
        1) {
        Balance(now->parent);
        return;
    }
    AVLNode* need = now;
    if(GetHeight(now->parent->left) < GetHeight(now->parent->right)){
        need = now->parent->right;
    }else{
        need = now->parent->left;
    }
    if (now->parent->left == need) {
        if (GetHeight(need->left) > GetHeight(need->right)) {
            SmallRight(need);
            Balance(need);
            return;
        } else if (GetHeight(need->right) > GetHeight(need->left)) {
            BigRight(need);
            Balance(need->parent);
            return;
        }
    } else {
        if (GetHeight(need->left) > GetHeight(need->right)) {
            BigLeft(need);
            Balance(need->parent);
            return;
        } else if (GetHeight(need->right) > GetHeight(need->left)) {
            SmallLeft(need);
            Balance(need);
            return;
        }
    }
}

void AVL::Insert(int cur) {
    AVLNode* now = root;
    if (now == nullptr) {
        root = new AVLNode(nullptr, cur);
        Balance(root);
        return;
    }
    while (now != nullptr) {
        if (now->num == cur) {
            return;
        }
        if (now->num < cur) {
            if (now->right == nullptr) {
                now->right = new AVLNode(now, cur);
                Balance(now->right);
                return;
            }
            now = now->right;
        } else {
            if (now->left == nullptr) {
                now->left = new AVLNode(now, cur);
                Balance(now->left);
                return;
            }
            now = now->left;
        }
    }
}

AVLNode* AVL::Find(int cur) {
    AVLNode* now = root;
    while (now != nullptr) {
        if (now->num == cur) {
            break;
        }
        if (now->num < cur) {
            now = now->right;
        } else {
            now = now->left;
        }
    }
    return now;
}

AVLNode* FindMinValue(AVLNode* now) {
    if (now->left != nullptr) {
        return FindMinValue(now->left);
    }
    return now;
}

AVLNode* FindMaxValue(AVLNode* now) {
    if (now->right != nullptr) {
        return FindMaxValue(now->right);
    }
    return now;
}

void AVL::SolveLeftLeft(AVLNode* now) {
    if (now->parent == nullptr) {
        root = now->left;
        if (now->left != nullptr) {
            now->left->parent = nullptr;
        }
    } else {
        now->parent->left = now->left;
        if (now->left != nullptr) {
            now->left->parent = now->parent;
            Balance(now->left);
        }
    }
}

void AVL::SolveRightLeft(AVLNode* now) {
    if (now->parent == nullptr) {
        root = now->left;
        if (now->left != nullptr) {
            now->left->parent = nullptr;
        }
    } else {
        now->parent->right = now->left;
        if (now->left != nullptr) {
            now->left->parent = now->parent;
            Balance(now->left);
        }
    }
}

void AVL::SolveRightRight(AVLNode* now) {
    if (now->parent == nullptr) {
        root = now->right;
        if (now->right != nullptr) {
            now->right->parent = nullptr;
        }
    } else {
        now->parent->right = now->right;
        if (now->right != nullptr) {
            now->right->parent = now->parent;
            Balance(now->right);
        }
    }
}

void AVL::SolveLeftRight(AVLNode* now) {
    if (now->parent == nullptr) {
        root = now->left;
        if (now->right != nullptr) {
            now->right->parent = nullptr;
        }
    } else {
        now->parent->left = now->right;
        if (now->right != nullptr) {
            now->right->parent = now->parent;

            Balance(now->right);
        }
    }
}

void AVL::SolveLeft(AVLNode* now) {
    if (now->parent == nullptr) {
        SolveLeftLeft(now);
    } else {
        if (now->parent->left == now) {
            SolveLeftLeft(now);
        } else {
            SolveRightLeft(now);
        }
    }
    now->left = nullptr;
}

void AVL::SolveRight(AVLNode* now) {
    if (now->parent == nullptr) {
        SolveRightRight(now);
    } else {
        if (now->parent->left == now) {
            SolveLeftRight(now);
        } else {
            SolveRightRight(now);
        }
    }
    now->right = nullptr;
}

void AVL::Erase(int cur) {
    AVLNode* now = root;
    while (now != nullptr) {
        if (now->num == cur) {
            if (now->left == nullptr && now->right == nullptr) {
                now->height = 0;
                Balance(now);
                if (now->parent != nullptr) {
                    if (now->parent->left == now) {
                        now->parent->left = nullptr;
                    } else if (now->parent->right == now) {
                        now->parent->right = nullptr;
                    }
                }

                if (now == root) {
                    root = nullptr;
                }
            } else if (now->left == nullptr) {
                SolveRight(now);
                if (now != root) {
                    now->Clear();
                }
            } else if (now->right == nullptr) {
                SolveLeft(now);
                if (now != root) {
                    now->Clear();
                }
            } else {
                AVLNode* tmp = FindMinValue(now->right);
                std::swap(tmp->num, now->num);
                SolveRight(tmp);

                if (root != tmp) {
                    tmp->Clear();
                }
            }
            // Print(root);
            return;
        }

        if (now->num < cur) {
            now = now->right;
        } else {
            now = now->left;
        }
    }
}



std::pair<int,int> AVL::Print(AVLNode* now,int block_size) {
    if (now == nullptr) {
        return std::make_pair(0,0);
    }

    auto left = Print(now->left,block_size);
    auto right = Print(now->right,block_size);
    if(now->right != nullptr){
        if(now->left != nullptr){
            now->right->x += left.second + 7;
            right.second += left.second + 7;
            left.second += left.second + 7;
        }else{
            now->right->x += left.second + 15;
            right.second += left.second + 15;
            left.second += left.second + 15;
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

    int all = left.second - left.first+ right.second  - right.first;


    now->x = left.first + (help_left + help_right) / 2;

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
    if(now->left != nullptr || now->right != nullptr){
        if(now->left == nullptr){
            now->x = help_right - 15;
        }
        if(now->right == nullptr){
            now->x = help_left + 15;
        }
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
        left.first = 1e9;
    }


    ans.first = 0;
    ans.second = std::max(now->x + block_size,right.second);

    if(ans.first == 0 && ans.second == 0){
        ans.second = block_size;
    }


    return ans;



}

void AVL::CheckInv(AVLNode* now) {
    if (now == nullptr) {
        return;
    }
    CheckInv(now->left);
    assert(std::abs(GetHeight(now->left) - GetHeight(now->right)) <= 1);
    CheckInv(now->right);
}

#endif // AVL_cpp
