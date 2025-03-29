#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
    private:
        string username = "";
        string password = "";
        Node* left = nullptr;
        Node* right = nullptr;

    public:

        Node(string username = "", string password = "", Node* left = nullptr, Node* right = nullptr);

        void setUsername(const string& username);
        void setPassword(const string& password);
        void setLeftPointer(Node* leftPointer);
        void setRightPointer(Node* rightPointer);
        string getUsername() const;
        string getPassword() const;
        Node* getLeftPointer() const;
        Node* getRightPointer() const;
        void printNode() const;
};

class Bintree 
{
    public:
        void insertNode(const string& username, const string& password, Node* &root_node);
        void deleteNode(const string& username, Node*& root_node);
        Node* findInsertLocation(const string& username, Node* root_node) const;
        Node* findNode(const string& username, Node* root_node);
        bool findNodeExists(const string& username, Node* root_node) const;
        void printTree(Node* root_node, string order) const;
        string findMin(Node* root_node) const;
        string findMax(Node* root_node) const;
        int getHeight(Node* root_node) const;
        int getSize(Node* root_node) const;
        bool isEmpty(Node* root_node) const;
        void inorder(Node* root_node, vector<Node*>& inorder_vector);
        void deleteTree(Node* root_node);
        Node* split(vector<Node*>& inorder_vector, int start, int end);
        void rebalanceTree(Node*& root_node);

};
#endif