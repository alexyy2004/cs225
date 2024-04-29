/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <stack>

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    BST<K, V>::Node* & node = find(root, key);
    return node->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == nullptr) {
        return subtree;
    }
    if (subtree->key == key) {
        return subtree;
    } else {
        if (subtree->key < key) {
            return find(subtree->right, key);
        } else {
            return find(subtree->left, key);
        }
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (find(subtree, key) != nullptr) {
        return;
    } else {
        BST<K, V>::Node*& node_place = find(subtree, key);
        //BST::Node new_node(key, value);
        //BST<K, V>::Node new_node;
        node_place = new Node(key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    if (first->left == second) {

    } else if (second->left == first) {
        K sec_key = second->key;
        V sec_val = second->value;
        K fir_key = first->key;
        V fir_val = first->value;
        second->key = fir_key;
        second->value = fir_val;
        first->key = sec_key;
        first->value = sec_val;
        // Node* origin_first = first;
        // Node* origin_second = second;
        // second = origin_first;
        // delete first;
        // std::cout << "achieve" << std::endl;
        // second->right = origin_second->right;
        // std::cout << "achieve1" << std::endl;
        // origin_second->left = second->left;
        // std::cout << "achieve2" << std::endl;
        // origin_second->right = second->right;
        // std::cout << "achieve3" << std::endl;
        // second->left = origin_second;
        // std::cout << "achieve4" << std::endl;
        // first = second->left;
        // std::cout << "achieve5" << std::endl;
        // print();
    } else {
        Node* second_left = second->left;
        Node* second_right = second->right;
        Node* first_left = first->left;
        Node* first_right = first->right;
        Node* origin_second = second;
        Node* origin_first = first;
        second = origin_first;
        second->left = second_left;
        second->right = second_right;
        first = origin_second;
        first->left = first_left;
        first->right = first_right;
    }
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if (find(subtree, key) == nullptr) {
        return;
    }
    std::vector<K> inorder = getInorderTraversal();
    BST<K, V>::Node*& node_place = find(subtree, key);
    if (node_place->left == nullptr && node_place->right == nullptr) {
        //key is at leaf
        delete node_place;
        node_place = nullptr;
    } else if (node_place->left != nullptr && node_place->right == nullptr) {
        Node* temp = node_place;
        node_place = node_place->left;
        delete temp;
    } else if (node_place->left == nullptr && node_place->right != nullptr) {
        Node* temp = node_place;
        node_place = node_place->right;
        delete temp;
    } else {
        //do the swap
        K IOP_key;
        for (unsigned int i = 0; i < inorder.size(); i++) {
            if (inorder[i] == key) {
                IOP_key = inorder[i - 1];
                break;
            }
        }
        BST<K, V>::Node*& IOP = find(subtree, IOP_key);
        swap(IOP, node_place);
        //swap over, delete node, this time the key_node should only have 1 or 0 child
        //remove(subtree, key);
        if (IOP->left == nullptr && IOP->right == nullptr) {
            //key is at leaf
            delete IOP;
            IOP = nullptr;
        } else if (IOP->left != nullptr && IOP->right == nullptr) {
            Node* temp = IOP;
            IOP = IOP->left;
            delete temp;
        } else if (IOP->left == nullptr && IOP->right != nullptr) {
            Node* temp = IOP;
            IOP = IOP->right;
            delete temp;
        } else {

        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> result;
    for (std::pair<K, V> temp : inList) {
        result.insert(temp.first, temp.second);
    }
    return result;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> histogram(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> tree; 
        for (const auto& pair : inList) {
            tree.insert(pair.first, pair.second); 
        }
        int height = tree.height(); 
        histogram[height]++; 
    } while (std::next_permutation(inList.begin(), inList.end()));
    // while (std::next_permutation(inList.begin(), inList.end())) {
    //     BST<K, V> tree;
    //     for (unsigned int i = 0; i < inList.size(); i++) {
    //         std::pair<K, V> pair = inList[i];
    //         tree.insert(pair.first, pair.second);
    //     }
    //     int height = tree.height();
    //     histogram[height] += 1;
    // }
    return histogram;
}