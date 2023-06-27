
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
