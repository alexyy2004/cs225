/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    if (t->left != nullptr && t->right != nullptr) {
        t->height = std::max(t->left->height, t->right->height) + 1;
    } else {
        int left_height;
        int right_height;
        if (t->left == nullptr) {
            left_height = -1;
        } else {
            left_height = t->left->height;
        }
        if (t->right == nullptr) {
            right_height = -1;
        } else {
            right_height = t->right->height;
        }
        t->height = std::max(left_height, right_height) + 1;
    }
    if (temp->left != nullptr && temp->right != nullptr) {
        temp->height = std::max(temp->left->height, temp->right->height) + 1;
    } else {
        int left_height;
        int right_height;
        if (temp->left == nullptr) {
            left_height = -1;
        } else {
            left_height = temp->left->height;
        }
        if (temp->right == nullptr) {
            right_height = -1;
        } else {
            right_height = temp->right->height;
        }
        temp->height = std::max(left_height, right_height) + 1;
    }
    //temp->height = std::max(temp->left->height, temp->right->height) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    if (t->left != nullptr && t->right != nullptr) {
        t->height = std::max(t->left->height, t->right->height) + 1;
    } else {
        int left_height;
        int right_height;
        if (t->left == nullptr) {
            left_height = -1;
        } else {
            left_height = t->left->height;
        }
        if (t->right == nullptr) {
            right_height = -1;
        } else {
            right_height = t->right->height;
        }
        t->height = std::max(left_height, right_height) + 1;
    }

    if (temp->left != nullptr && temp->right != nullptr) {
        temp->height = std::max(temp->left->height, temp->right->height) + 1;
    } else {
        int left_height;
        int right_height;
        if (temp->left == nullptr) {
            left_height = -1;
        } else {
            left_height = temp->left->height;
        }
        if (temp->right == nullptr) {
            right_height = -1;
        } else {
            right_height = temp->right->height;
        }
        temp->height = std::max(left_height, right_height) + 1;
    }
    //temp->height = std::max(temp->left->height, temp->right->height) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::getbalance(Node*& subtree)
{
    if (subtree == nullptr) {
        return 0;
    }
    return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == nullptr) {
        return;
    }
    //std::cout << getbalance(subtree) << std::endl;
    if (getbalance(subtree) == 2) {
        if (getbalance(subtree->right) == 1) {
            rotateLeft(subtree);
        } else if (getbalance(subtree->right) == -1) {
            rotateRightLeft(subtree);
        }
    } else if (getbalance(subtree) == -2) {
        if (getbalance(subtree->left) == 1) {
            rotateLeftRight(subtree);
        } else if (getbalance(subtree->left) == -1) {
            rotateRight(subtree);
        }
    }
    subtree->height = updateheight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
int AVLTree<K, V>::updateheight(Node* subtree) {
    if (subtree == nullptr) {
        return -1;
    }
    return std::max(updateheight(subtree->left), updateheight(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) {
        subtree = new Node(key, value);
    } else if (subtree->key <= key) {
        insert(subtree->right, key, value);
    } else {
        insert(subtree->left, key, value);
    }
    subtree->height = updateheight(subtree);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node* temp = subtree;
            subtree = nullptr;
            delete temp;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* IOP = subtree->left;
            while (IOP->right != nullptr) {
                IOP = IOP->right;
            }
            std::cout << "before swap" << std::endl;
            
            swap(IOP, subtree);
            std::cout << "after swap" << std::endl;
            std::cout << subtree->key << std::endl;
            remove(subtree->left, key);
            subtree->height = updateheight(subtree);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != nullptr) {
                Node* temp = subtree->left;
                delete subtree;
                subtree = temp;
                subtree->height = updateheight(subtree);
            } else {
                Node* temp = subtree->right;
                delete subtree;
                subtree = temp;
                subtree->height = updateheight(subtree);
            }
            this->print();
        }
        // your code here
        //rebalance(subtree);
    }
    rebalance(subtree);
}
