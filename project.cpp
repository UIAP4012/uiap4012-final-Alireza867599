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






class Product {
public:
    int id;
    double price;
    int quantity;
    string name;

    Product(int id, double price, int quantity, string name)
        : id(id), price(price), quantity(quantity), name(name) {}
};


    class CurrencyConverter {
    public:

        double convertUsdToEur(double usd) {
            return usd * usdToEurRate;
        }

        double convertEurToUsd(double eur) {
            return eur / usdToEurRate;
        }
        void updateExchangeRate(double newRate) {
            usdToEurRate = newRate;
        }
    private:
        double usdToEurRate=0.85;
    };

    CurrencyConverter currency;



    class Inventory {
    private:
        string filename;

    public:
        Inventory(const string& filename) : filename(filename) {}

        void add(const Product& product) {

            ofstream file;
            file.open(filename, ios::app);
            file << product.id << "," << product.price << ","
                 << product.quantity << "," << product.name << endl;
            file.close();
        }

        void remove(int id) {
            vector<Product> products = readProducts();
            ofstream file;
            file.open(filename);
            for (const Product& product : products) {
                if (product.id != id) {
                    file << product.id << "," << product.price << ","
                         << product.quantity << "," << product.name << endl;
                }
            }
            file.close();
        }
        void addquantity(int id, int Quantity){
            vector<Product> products = readProducts();
            ofstream file;
            file.open(filename);
            for (const Product& product : products) {
                if (product.id == id) {
                    file << product.id << "," << product.price << ","
                         << product.quantity+Quantity << "," << product.name << endl;
                } else {
                    file << product.id << "," << product.price << ","
                         << product.quantity << "," << product.name << endl;
                }
            }
            file.close();
        }

        void updateQuantity(int id, int newQuantity) {
            vector<Product> products = readProducts();
            ofstream file;
            file.open(filename);
            for (const Product& product : products) {
                if (product.id == id) {
                    file << product.id << "," << product.price << ","
                         << product.quantity-newQuantity << "," << product.name << endl;
                } else {
                    file << product.id << "," << product.price << ","
                         << product.quantity << "," << product.name << endl;
                }
            }
            file.close();
        }


        void place_order(int id, int quantity,string ss){
            double  total=0;
            double total_in_EURO;
            time_t ttime =time(0);
            char * dt=ctime(&ttime);
            ofstream date;
            date.open("d:\\project2\\historyinvoices.txt",ios::app);
            date<<"date of this invoice is :"<<dt<<endl;
            date <<"*************************************"<<endl;
            vector<Product> products = readProducts();



            for (const Product& product : products) {
                if (product.id == id) {
                    total=product.price*quantity;
                    updateQuantity(id,quantity);
                    string rate;
                    cout<<"do you want update exchange rate ? "<<endl;
                    cin>>rate;
                    if(rate=="yes" || rate=="Yes"){
                        cout<<"enter the new rate"<<endl;
                        double newrate;
                        cin>>newrate;
                        currency.updateExchangeRate(newrate);
                    }
                    total_in_EURO=currency.convertUsdToEur(total);
                    cout<<"id of product :"<<product.id<<"\n"<<"name of product :"<<product.name<<"\n"<<"count : "<<quantity<<endl;
                    cout<<"total of your order is : "<<total<<endl;
                    cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;
                    ofstream outData;
                    outData.open(ss,ios::app);

                    outData<<"id,name,quantity, total price, total in euro "<<endl;

                    outData<<product.id<<","<<product.name<<","<<quantity<<","<<total<<","<<total_in_EURO<<endl;
                    break;
                }

                }
            }




        void display() {
            vector<Product> products = readProducts();
            for (const Product& product : products) {
                cout << "ID: " << product.id << " Name: " << product.name
                          << " Price: " << product.price
                          << " Quantity: " << product.quantity << endl;
            }
        }

    private:
        vector<Product> readProducts() {
            vector<Product> products;
            ifstream file;
            file.open(filename);
            string line;

            while (getline(file, line)) {
                stringstream ss(line);
                string token;
                vector<string> tokens;

                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                int id = stoi(tokens[0]);
                double price = stod(tokens[1]);
                int quantity = stoi(tokens[2]);
                string name = tokens[3];

                products.emplace_back(id, price, quantity, name);
            }

            file.close();
            return products;
        }
    };


    int main(){

        int m;
        string t;
        Inventory inventory("d:\\project2\\inventory.txt");

        cout<<"do you want add any products?"<<endl;
        cin>>t;
        if(t=="Yes "|| t=="yes"){
            cout<<"how many products do you want to add"<<endl;
            cin>>m;
            while(m>0){
                int id, quan;
                double price;
                string name;
                cout<<"enter id"<<endl;
                cin>>id;
                cout<<"enter price"<<endl;
                cin>>price;
                cout<<"enter quantity"<<endl;
                cin>>quan;
                cout<<"enter name"<<endl;
                cin>>name;
                Product product1(id,price,quan,name);
                inventory.add(product1);
                m--;
            }
        }



        cout << "Current Inventory: " << endl;
        inventory.display();

        cout<<"do you want remove any product ?";
        string s1;
        cin>>s1;
        if(s1=="yes" || s1=="Yes"){
            cout<<"how many products do you want to remove ? :";
            int num;
            cin>>num;
            while(num>0){
                int id;
                cout<<"enter id of product : ";
                cin>>id;
                inventory.remove(id);
                num--;
            }
        inventory.display();

        }
        cout<<"do you want add quantity of a product ?";
        string s2;
        cin>>s2;
        if(s2=="yes" || s2=="Yes"){
            int num;
            cout<<"how many products do you want to add their quantity ? :";

            cin>>num;
            while(num>0){
                int id;
                int quan;
                cout<<"enter id of product  "<<endl;
                cin>>id;
                cout<<"enter a quantity"<<endl;
                cin>>quan;
                inventory.addquantity(id,quan);
                num--;
            }
            inventory.display();
        }



        int choice;
        bool logged_in = false;

        while(true) {
            if (!logged_in) {
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "3. Exit\n";

                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    string username;
                    string password;
                    cout << "Enter username: ";
                    cin >> username;

                    cout << "Enter password: ";
                    cin >> password;

                    if (user_exists(username, password)) {
                        logged_in = true;
                        ofstream date;
                        date.open("d:\\project2\\historyinvoices.txt",ios::app);
                        date<<"name of customer is :"<<username<<endl;
                        cout << "Logged in successfully!\n";
                        int m1;



                        cout<<"how many products do you want to buy ?"<<endl;
                        cin>>m1;

                        string ss;
                        cout<<"enter path of this invoice and name of it :"<<endl;
                        cin>>ss;
                        ofstream outData;

                        outData.open(ss,ios::app);

                        outData<<"username :"<<username<<endl;
                        while(m1>0)
                        {
                            int id;
                            int quantity;
                            cout<<"enter the id of product"<<endl;
                            cin>>id;
                            cout<<"enter the quantity of product"<<endl;
                            cin>>quantity;

                            inventory.place_order(id,quantity,ss);

                            m1--;

                        }

                    } else {
                        cout << "User does not exist. Please register.\n";
                    }

                    break;
                }
                case 2:
                    register_user();
                    break;

                case 3:
                    return 0;

                default:
                    cout << "Invalid choice\n";
                    break;
                }
            } else {
                cout << "1. Logout\n";
                cout << "2. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;
            }
                switch (choice)
                case 1:{
                    logged_in = false;
                    break;

                case 2:
                    return 0;

                default:
                    cout << "Invalid choice\n";
                    break;

                }
            }
        return 0;


    }

