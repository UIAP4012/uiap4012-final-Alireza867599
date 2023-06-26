#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#define sep cout<<"____________________________________________________________"<<endl;
using namespace std;

class User {
public:
    string username;
    string password;

    User(string username, string password) {
        this->username = username;
        this->password = password;
    }
};

bool user_exists(string username, string password) {
    ifstream file("d:\\project2\\users.txt");
    string line;
    while (getline(file, line)) {
        if (line == "user name is :"+username + " and password is : " + password) {
            return true;
        }
    }

    return false;
}
unsigned int hash_password(const string& password) {
    unsigned int hash = 0;
    for (char c : password) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void register_user() {
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;
    unsigned int hash(hash_password(password));
    ofstream file1("d:\\project2\\hashpasswords.txt", ios::app);
    file1<<"name of user :"<<username<<"\n"<< "hash password of user :"<<hash<<endl;
    file1<<"_____________________________________________________________"<<endl;

    User user(username, password);

    ofstream file("d:\\project2\\users.txt", ios::app);
    file<< "user name is :"<< user.username<< " and password is : " << user.password << endl;
}
