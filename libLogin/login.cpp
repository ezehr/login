#include "bintree.h"
#include "login.h"
#include "sha256.h"

Bintree tree;

string Login::getAccountAction()
{
    string response;
    cout << "Login to, Make or Delete an Account\n";
    cout << "Enter New, Delete, Login: ";
    cin >> response;
    while(response != "New" && response != "Login" && response != "Delete")
    {
        cout << "Please enter New or Login: ";
        cin >> response;

    }
    return response;
}


string Login::getLoginInfo(string info_type)
{
    string login_info;
    if(info_type == "user")
    {
        cout << "Enter Username: ";
    }
    else
    {
        cout << "Enter Password: ";
    }
    cin >> login_info;

    SHA256 sha; // hash login data
    sha.update(login_info);
    array<uint8_t, 32> digest = sha.digest();

    return SHA256::toString(digest);
}


void Login::setupAccount(Node* &root_node)
{
    string username = getLoginInfo("user");
    // search if user exists
    while(tree.findNodeExists(username, root_node))
    {
        cout << "Username already exists\n";
        cout << "Please try a differnt username\n";
        username = getLoginInfo("user");
    }
    string password;
    string password_confirm;
    do
    {
        password = getLoginInfo("pass");
        cout << "Confirm Password\n";
        password_confirm = getLoginInfo("pass");
        if (password != password_confirm)
        {
            cout << "Passwords do not match\n";
            cout << "Enter new password\n";
        }
    } while(password != password_confirm);
    cout << "Credentials Set\n\n";
    tree.insertNode(username, password, root_node);
}


bool Login::authenticate(string username, string password, Node* root_node)
{
    Node* user = tree.findNode(username, root_node);
    if(password == (*user).getPassword())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void Login::requestLogin(Node* root_node)
{
    string username = getLoginInfo("user");
    while(!tree.findNodeExists(username, root_node))
    {
        cout << "User does not exist\n";
        username = getLoginInfo("user");
    }
    string password = getLoginInfo("pass");
    while(!authenticate(username, password, root_node))
    {
        cout << "Incorrect Password\n";
        password = getLoginInfo("pass");
    }
}


void Login::deleteAccount(Node* &root_node)
{
    string username = getLoginInfo("user");

    if(!tree.findNodeExists(username, root_node))
    {
        cout << "User: " << username << " does not exist." << endl;
    }
    else
    {
        tree.deleteNode(username, root_node);
        cout << "User: " << username << " deleted." << endl;
    }
}
