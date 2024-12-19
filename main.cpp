#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>



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
    Item* items; // Array dinamis dari item
    int itemCount; // Jumlah item yang ada
    map<string, int> dailySales; // Untuk melacak penjualan harian per item
    map<string, PaymentMethod>* paymentMethods; // Menyimpan metode pembayaran per transaksi
    int paymentMethodCount; // Jumlah transaksi

public:
    RetailStore() : items(nullptr), itemCount(0), paymentMethods(nullptr), paymentMethodCount(0) {}

    ~RetailStore() {
        delete[] items;
        delete[] paymentMethods;
    }

    void addItem() {
        Item* newItems = new Item[itemCount + 1];
        for (int i = 0; i < itemCount; ++i) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;

        cout << "Masukkan kode barang: ";
        cin >> items[itemCount].code;
        cout << "Masukkan nama barang: ";
        cin.ignore(); // Clear the newline character from the buffer
        getline(cin, items[itemCount].name);
        cout << "Masukkan harga modal: ";
        cin >> items[itemCount].costPrice;
        cout << "Masukkan harga jual: ";
        cin >> items[itemCount].sellPrice;
        cout << "Masukkan stok minimal: ";
        cin >> items[itemCount].minStock;
        cout << "Masukkan stok awal: ";
        cin >> items[itemCount].stock;
        itemCount++;
        cout << "Barang berhasil ditambahkan!" << endl;
    }

    void viewStock() {
        cout << "--- Semua Barang ---" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << "Kode: " << items[i].code << ", Nama: " << items[i].name << ", Stok: " << items[i].stock << endl;
        }
        cout << "--- Stok Menipis ---" << endl;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].stock <= items[i].minStock) {
                cout << "Kode: " << items[i].code << ", Nama: " << items[i].name << ", Stok: " << items[i].stock << endl;
            }
        }
    }

    void updateStock() {
        string code;
        cout << "Masukkan kode barang: ";
        cin >> code;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].code == code) {
                int increment;
                cout << "Masukkan jumlah stok masuk: ";
                cin >> increment;
                items[i].stock += increment;
                cout << "Stok barang " << items[i].name << " diperbarui menjadi " << items[i].stock << endl;
                return;
            }
        }
        cout << "Barang tidak ditemukan." << endl;
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