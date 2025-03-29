#include "bintree.h"

//constructor
Node::Node(string username, string password, Node* left, Node* right) : username(username), password(password), left(nullptr), right(nullptr) {}

void Node::setUsername(const string& username)
{
    this->username = username;
}

void Node::setPassword(const string& password)
{
    this->password = password;
}

void Node::setLeftPointer(Node* leftPointer)
{
    this->left = leftPointer;
}

void Node::setRightPointer(Node* rightPointer)
{
    this->right = rightPointer;
}

string Node::getUsername() const
{
    return this->username;
}

string Node::getPassword() const
{
    return this->password;
}

Node* Node::getLeftPointer() const
{
    return this->left;
}

Node* Node::getRightPointer() const
{
    return this->right;
}

void Node::printNode() const
{
    cout << "Username: " << this->username << ", Password: " << this->password << ", Left: " << this->left << ", Right: " << this->right << endl; 
}




void Bintree::deleteNode(const string& username, Node*& root_node)
{
    if (root_node == nullptr)
    {
        return;
    }
        
    Node* current = root_node;
    Node* last = nullptr;

    while (current != nullptr && (*current).getUsername() != username)
    {
        last = current;
        if (username > (*current).getUsername())
        {
            current = (*current).getRightPointer();  // move right
        }
        else
        {
            current = (*current).getLeftPointer();   // move left
        }
    }
        
    if (current == nullptr) // username not found
    {
        return;
    }

    if((*current).getLeftPointer() == nullptr && (*current).getRightPointer() == nullptr) //leaf node
    {
        if(last == nullptr)
        {
            root_node = nullptr;
        }
        else if ((*last).getLeftPointer() == current)
        {
            (*last).setLeftPointer(nullptr);
        }
        else
        {
            (*last).setRightPointer(nullptr);
        }
        delete current;
    }
    else if ((*current).getLeftPointer() == nullptr || (*current).getRightPointer() == nullptr) // 1 child
    {
        Node* child = ((*current).getLeftPointer() != nullptr) ? (*current).getLeftPointer() : (*current).getRightPointer();
        if (last == nullptr)
        {
            root_node = child;
        }
        else if((*last).getLeftPointer() == current)
        {
            (*last).setLeftPointer(child);
        }
        else
        {
            (*last).setRightPointer(child);
        }
        delete current;
    }
    else // 2 children
    {
        Node* successorLast = current;
        Node* successor = (*current).getRightPointer();
        while((*successor).getLeftPointer() != nullptr)
        {
            successorLast = successor;
            successor = (*successor).getLeftPointer();
        }

        (*current).setUsername((*successor).getUsername());
        (*current).setPassword((*successor).getPassword());

        if((*successorLast).getLeftPointer() == successor)
        {
            (*successorLast).setLeftPointer((*successor).getRightPointer());
        }
        else // ONE OF THESE IS WRONG
        {
            (*successorLast).setRightPointer((*successor).getRightPointer());
        }
        delete successor;
    }
}


Node* Bintree::findInsertLocation(const string& username, Node* root_node) const
{
    if (root_node == nullptr)
    {
        return nullptr;
    }

    Node* last = nullptr;
    Node* current = root_node;

    while (current != nullptr)
    {
        last = current;
        if (username > (*current).getUsername())
        {
            current = (*current).getRightPointer();  // move right
        }
        else
        {
            current = (*current).getLeftPointer();   // move left
        }
    }
    
    return last;  // return the last valid node before nullptr
}


void Bintree::insertNode(const string& username, const string& password, Node* &root_node)
{
    Node* new_node = new Node(username, password);

    if(root_node == nullptr)
    {
        root_node = new_node;
    }
    else
    {
        Node* last_node = findInsertLocation(username, root_node); // returns last node 
        if(username > (*last_node).getUsername())
        {
            (*last_node).setRightPointer(new_node); // insert right
        }
        else
        {
            (*last_node).setLeftPointer(new_node); // insert left
        }
    }
}


bool Bintree::findNodeExists(const string& username, Node* root_node) const
{
    Node* current = root_node;
    while (current != nullptr)
    {
        if (username == (*current).getUsername())
        {
            return true;
        }
        else if (username > (*current).getUsername())
        {
            current = (*current).getRightPointer();  // move right
        }
        else
        {
            current = (*current).getLeftPointer();   // move left
        }
    }
    return false;
}


void Bintree::printTree(Node* root_node, string order) const
{
    if (root_node == nullptr)
    {
        return;
    }
    
    if(order == "preorder")
    {
        cout << "Username: " << (*root_node).getUsername() << ", Password: " << (*root_node).getPassword() << endl; // Print current node
        printTree((*root_node).getLeftPointer(), "preorder"); // Go left
        printTree((*root_node).getRightPointer(), "preorder"); // Go right
    }
    else if(order == "postorder")
    {
        printTree((*root_node).getLeftPointer(), "postorder"); // Go left
        printTree((*root_node).getRightPointer(), "postorder"); // Go right
        cout << "Username: " << (*root_node).getUsername() << ", Password: " << (*root_node).getPassword() << endl; // Print current node
    }
    else // inorder
    {
        printTree((*root_node).getLeftPointer(), "inorder"); // Go left
        cout << "Username: " << (*root_node).getUsername() << ", Password: " << (*root_node).getPassword() << endl; // Print current node
        printTree((*root_node).getRightPointer(), "inorder"); // Go right
    }
}


string Bintree::findMin(Node* root_node) const
{
    if (root_node == nullptr)
    {
        return "";
    }
    else if ((*root_node).getLeftPointer() == nullptr) 
    {
        return (*root_node).getUsername();
    }
    else
    {   Node* current_node = root_node;
        while((*current_node).getLeftPointer() != nullptr)
        {
            current_node = (*current_node).getLeftPointer();
        }
        return (*current_node).getUsername();
    }
}


string Bintree::findMax(Node* root_node) const
{
    if (root_node == nullptr)
    {
        return "";
    }
    else if ((*root_node).getRightPointer() == nullptr) 
    {
        return (*root_node).getUsername();
    }
    else
    {   Node* current_node = root_node;
        while((*current_node).getRightPointer() != nullptr)
        {
            current_node = (*current_node).getRightPointer();
        }
        return (*current_node).getUsername();
    }
}


int Bintree::getHeight(Node* root_node) const
{
    if (root_node == nullptr)
    {
        return -1;
    }
    return 1 + max(getHeight((*root_node).getLeftPointer()), getHeight((*root_node).getRightPointer()));
}


int Bintree::getSize(Node* root_node) const
{
    if (root_node == nullptr)
    {
        return 0;
    }
    return 1 + getSize((*root_node).getLeftPointer()) + getSize((*root_node).getRightPointer());
}


bool Bintree::isEmpty(Node* root_node) const
{
    if (root_node == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

 
void Bintree::inorder(Node* root_node, vector<Node*>& inorder_vector)
{
    if(root_node == nullptr)
    {
        return;
    }

    inorder((*root_node).getLeftPointer(), inorder_vector);
    inorder_vector.push_back(root_node);
    inorder((*root_node).getRightPointer(), inorder_vector);
}


void Bintree::deleteTree(Node* root_node) {
    if (root_node == nullptr) {
        return;
    }
    deleteTree((*root_node).getLeftPointer());
    deleteTree((*root_node).getRightPointer());
    delete root_node;
    root_node = nullptr;
}

Node* Bintree::split(vector<Node*>& inorder_vector, int start, int end)
{
    if(start > end)
    {
        return nullptr;
    }

    int mid = (start + end) / 2;
    Node* newRoot = inorder_vector[mid];

    (*newRoot).setLeftPointer(split(inorder_vector, start, mid - 1));
    (*newRoot).setRightPointer(split(inorder_vector, mid + 1, end));

    return newRoot;
}


void Bintree::rebalanceTree(Node*& root_node)
{
    if (root_node == nullptr)
    {
        return;
    }

    vector<Node*> inorder_vector;
    inorder(root_node, inorder_vector);

    deleteTree(root_node);
    
    root_node = split(inorder_vector, 0, inorder_vector.size() - 1);
}


Node* Bintree::findNode(const string& username, Node* root_node)
{
    if(root_node == nullptr)
    {
        return nullptr;
    }

    Node* current = root_node;
    while (current != nullptr)
    {
        if (username == (*current).getUsername())
        {
            return current;
        }
        else if (username > (*current).getUsername())
        {
            current = (*current).getRightPointer();  // move right
        }
        else
        {
            current = (*current).getLeftPointer();   // move left
        }
    }
    return nullptr;
}