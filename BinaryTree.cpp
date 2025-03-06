#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
#include <random>
#include <numeric>

// Implementation of a basic Binary Search Tree (BST) class
class BinaryTree {
public:
    // Structure representing a single node in the BST
    struct Node {
        int key; // Key (value) of the node
        Node *left; // Pointer to the left child
        Node *right; // Pointer to the right child

        Node(int k) : key(k), left(nullptr), right(nullptr) {
        } // Constructor for a node
    };

    Node *root; // Pointer to the root of the tree

    BinaryTree() : root(nullptr) {
    } // Constructor initializing an empty tree

    // Public method to insert a key into the tree
    void insert(int key) {
        root = insertRec(root, key);
    }

    // Public method to remove a key from the tree
    void remove(int key) {
        root = removeRec(root, key);
    }

private:
    // Helper method for inserting a key recursively
    Node *insertRec(Node *node, int key) {
        if (!node) // Base case: empty spot found, insert the key here
            return new Node(key);
        if (key < node->key) // If key is smaller, go left
            node->left = insertRec(node->left, key);
        else // If key is larger or equal, go right
            node->right = insertRec(node->right, key);
        return node; // Return the unchanged node
    }

    // Helper method for removing a key recursively
    Node *removeRec(Node *node, int key) {
        if (!node) return node; // Base case: key not found

        if (key < node->key) {
            // If key is smaller, continue to search in the left subtree
            node->left = removeRec(node->left, key);
        } else if (key > node->key) {
            // If key is larger, continue to search in the right subtree
            node->right = removeRec(node->right, key);
        } else {
            // Key found, perform deletion
            if (!node->left) return node->right; // Node has no left child
            if (!node->right) return node->left; // Node has no right child

            // Node has two children: find the in-order successor (smallest in the right subtree)
            node->key = minValue(node->right);
            node->right = removeRec(node->right, node->key); // Remove the successor node
        }
        return node; // Return the updated node
    }

    // Helper method to find the smallest value in a subtree
    int minValue(Node *node) {
        while (node->left) node = node->left; // Traverse left to find the minimum value
        return node->key;
    }
};

// Helper function to generate the best-case order for a balanced BST
void bestCaseOrder(const std::vector<int> &keys, std::vector<int> &output, int start, int end) {
    if (start > end) return; // Base case: no elements in this range

    int mid = (start + end) / 2; // Find the middle element
    output.push_back(keys[mid]); // Add the middle element to the output

    // Recur for the left and right subtrees
    bestCaseOrder(keys, output, start, mid - 1);
    bestCaseOrder(keys, output, mid + 1, end);
}

int main() {
    const int n = (1 << 10) - 1; // Example: 1023 keys (2^10 - 1)
    std::vector<int> keys(n);

    // Fill the vector with values from 1 to n
    std::iota(keys.begin(), keys.end(), 1);

    // Shuffle the keys to create a random order
    std::random_device rd;
    std::mt19937 rng(rd()); // Use random_device to seed mt19937
    std::shuffle(keys.begin(), keys.end(), rng);

    // --- Binary Tree Insertion in Random Order ---
    BinaryTree treeRandom;
    auto start = std::chrono::high_resolution_clock::now();
    for (int key: keys) treeRandom.insert(key); // Insert keys in random order
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Random Order Insertion Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // --- Binary Tree Insertion in Best-Case Order ---
    std::sort(keys.begin(), keys.end()); // Sort keys for best-case arrangement
    std::vector<int> bestKeys;
    bestCaseOrder(keys, bestKeys, 0, keys.size() - 1); // Compute best-case order

    BinaryTree treeBest;
    start = std::chrono::high_resolution_clock::now();
    for (int key: bestKeys) treeBest.insert(key); // Insert keys in best-case order
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Best Case Order Insertion Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // --- Insertion Using std::set ---
    std::set<int> stdSet;
    start = std::chrono::high_resolution_clock::now();
    for (int key: keys) stdSet.insert(key); // Insert keys into std::set
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::set Insertion Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // --- Key Removal from Random Order Tree ---
    start = std::chrono::high_resolution_clock::now();
    for (int key: keys) treeRandom.remove(key); // Remove keys from tree in random order
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Random Order Removal Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // --- Key Removal from std::set ---
    start = std::chrono::high_resolution_clock::now();
    for (int key: keys) stdSet.erase(key); // Remove keys from std::set in random order
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::set Removal Time: "
            << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    return 0; // End of program
}
