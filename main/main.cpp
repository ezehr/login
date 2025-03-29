#include <iostream>
#include <string>
#include "bintree.h"
#include "login.h"

using namespace std;


int main()
{
    Node* root = nullptr;

    Login login;
    Bintree tree;

    while(1)
    {
        // Get and verify IO
        string response = login.getAccountAction();

        if(response == "New")
        {
            login.setupAccount(root);
        }
        else if (response == "Delete")
        {
            login.deleteAccount(root);
        }
        else
        {
            login.requestLogin(root);
        }
        tree.printTree(root, "inorder");
    }
    return 69;
}
