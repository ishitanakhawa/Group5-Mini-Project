//Module 1
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Product {
private:
    int id;
    string name;
    int quantity;
    float price;

public:
    void input() {
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;
    }

    void display() const {
        cout << id << "\t"
             << name << "\t"
             << quantity << "\t"
             << price << endl;
    }

    int getId() const {
        return id;
    }

    int getQuantity() const {
        return quantity;
    }

    void sell(int qty) {
        quantity -= qty;
    }

    void writeToFile(ofstream &file) const {
        file << id << " "
             << name << " "
             << quantity << " "
             << price << endl;
    }

    void readFromFile(ifstream &file) {
        file >> id >> name >> quantity >> price;
    }
};


//Module 2 
void loadProducts(vector<Product> &products) {
    ifstream file("inventory.txt");
    Product p;

    while (file.peek() != EOF) {
        p.readFromFile(file);
        products.push_back(p);
    }

    file.close();
}

void saveProducts(const vector<Product> &products) {
    ofstream file("inventory.txt");

    for (const auto &p : products) {
        p.writeToFile(file);
    }

    file.close();
}

//Module 3 
int main() {
    vector<Product> products;
    int choice;

    loadProducts(products);

    do {
        cout << "\nInventory Management System\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Sell Product\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Product p;
            p.input();
            products.push_back(p);
            saveProducts(products);
            cout << "Product Added Successfully!\n";
        }

        else if (choice == 2) {
            cout << "\nID\tName\tQty\tPrice\n";
            for (const auto &p : products) {
                p.display();
            }
        }

        else if (choice == 3) {
            int searchId, sellQty;
            cout << "Enter Product ID to sell: ";
            cin >> searchId;
            cout << "Enter Quantity to sell: ";
            cin >> sellQty;

            bool found = false;

            for (auto &p : products) {
                if (p.getId() == searchId) {
                    found = true;
                    if (p.getQuantity() >= sellQty) {
                        p.sell(sellQty);
                        cout << "Product Sold Successfully!\n";
                    } else {
                        cout << "Not enough stock!\n";
                    }
                    break;
                }
            }

            if (!found) {
                cout << "Product Not Found!\n";
            }

            saveProducts(products);
        }

    } while (choice != 0);

    return 0;
}