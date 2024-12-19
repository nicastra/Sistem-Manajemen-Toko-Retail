#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

struct Item {
    string code;
    string name;
    double costPrice;
    double sellPrice;
    int minStock;
    int stock;
};

enum class PaymentMethod {
    CASH,
    QRIS
};

int main() {
 
    int choice;
    
    while (true) {
        cout << "\n1. Admin\n2. Kasir\n3. Exit\nPilih: ";
        cin >> choice;
        
        if (choice == 1) {
            // Admin functionalities
            cout << "Pilihan 1." << endl;

        } else if (choice == 2) {
            // Cashier functionalities
           cout << "Pilihan 2." << endl;

  
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}