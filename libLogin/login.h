#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include "bintree.h"
#include "sha256.h"

using namespace std;

class Login 
{
    public:
        string getAccountAction();
        void setupAccount(Node* &root_node);
        void deleteAccount(Node* &root_node);
        void requestLogin(Node* root_node);
        string getLoginInfo(string info_type);
        bool authenticate(string username, string password, Node* root_node);
};

#endif