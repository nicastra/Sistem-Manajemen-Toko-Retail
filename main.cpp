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

class RetailStore {
private:
    vector<Item> items;
    map<string, int> dailySales; 
    vector<pair<string, PaymentMethod>> paymentMethods; 

public:
    void addItem() {
        Item newItem;
        cout << "Masukkan kode barang: ";
        cin >> newItem.code;
        cout << "Masukkan nama barang: ";
        cin.ignore(); 
        getline(cin, newItem.name);
        cout << "Masukkan harga modal: ";
        cin >> newItem.costPrice;
        cout << "Masukkan harga jual: ";
        cin >> newItem.sellPrice;
        cout << "Masukkan stok minimal: ";
        cin >> newItem.minStock;
        cout << "Masukkan stok awal: ";
        cin >> newItem.stock;
        items.push_back(newItem);
        cout << "Barang berhasil ditambahkan!" << endl;
    }

    void viewStock() {
        cout << "--- Semua Barang ---" << endl;
        for (const auto& item : items) {
            cout << "Kode: " << item.code << ", Nama: " << item.name << ", Stok: " << item.stock << endl;
        }
        cout << "--- Stok Menipis ---" << endl;
        for (const auto& item : items) {
            if (item.stock <= item.minStock) {
                cout << "Kode: " << item.code << ", Nama: " << item.name << ", Stok: " << item.stock << endl;
            }
        }
    }

    void updateStock() {
        string code;
        cout << "Masukkan kode barang: ";
        cin >> code;
        for (auto& item : items) {
            if (item.code == code) {
                int increment;
                cout << "Masukkan jumlah stok masuk: ";
                cin >> increment;
                item.stock += increment;
                cout << "Stok barang " << item.name << " diperbarui menjadi " << item.stock << endl;
                return;
            }
        }
        cout << "Barang tidak ditemukan." << endl;
    }


    string get_item_name(const string& code) {
        for (const auto& item : items) {
            if (item.code == code) return item.name;
        }
        return "Tidak Diketahui";
    }

   

    // Admin functionalities
    void adminMenu() {
        int choice;
        do {
            cout << "\nAdmin Menu:\n"
                 << "1. Input Barang\n"
                 << "2. Lihat Stok\n"
                 << "3. Update Stok\n"
             
                 << "4. Kembali\n"
                 << "Pilih: ";
            cin >> choice;
            switch (choice) {
                case 1: addItem(); break;
                case 2: viewStock(); break;
                case 3: updateStock(); break;
          
                case 4: break;
                default: cout << "Pilihan tidak valid." << endl;
            }
        } while (choice != 7);
    }

    
   
};

int main() {
    RetailStore store;
    int choice;
    
    while (true) {
        cout << "\n1. Admin\n2. Kasir\n3. Exit\nPilih: ";
        cin >> choice;
        
        if (choice == 1) {
            store.adminMenu();
        } else if (choice == 2) {
        // kasirb
            break;
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}