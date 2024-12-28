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

const int MAX_ITEMS = 100;

class RetailStore {
private:
    Item* items; // Array dinamis dari item
    int itemCount; // Jumlah item yang ada
    map<string, int> dailySales; // Untuk melacak penjualan harian per item
    pair<string, PaymentMethod>* paymentMethods; // Menyimpan metode pembayaran per transaksi
    int paymentMethodCount; // Jumlah transaksi

public:
    RetailStore() : items(nullptr), itemCount(0), paymentMethodCount(0) {
        paymentMethods = new pair<string, PaymentMethod>[MAX_ITEMS];
    }

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

    void dailySalesReport() {
        cout << "--- Laporan Penjualan Harian ---" << endl;
        for (const auto& sale : dailySales) {
            cout << "Barang: " << get_item_name(sale.first) << ", Jumlah: " << sale.second << endl;
        }
    }

    void profitPerItem() {
        cout << "--- Keuntungan per Item ---" << endl;
        for (int i = 0; i < itemCount; ++i) {
            if (dailySales.find(items[i].code) != dailySales.end()) {
                double profit = (items[i].sellPrice - items[i].costPrice) * dailySales[items[i].code];
                cout << "Barang: " << items[i].name << ", Keuntungan: " << profit << endl;
            }
        }
    }

    void topSellingItems() {
        cout << "--- Barang Terlaris ---" << endl;

        // Convert map to static array
        pair<string, int> salesArray[MAX_ITEMS];
        int salesCount = 0;

        for (const auto& sale : dailySales) {
            if (salesCount < MAX_ITEMS) {
                salesArray[salesCount++] = sale;
            } else {
                cout << "Terlalu banyak item untuk ditampilkan." << endl;
                return;
            }
        }

        // Sort using std::sort
        sort(salesArray, salesArray + salesCount, [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

        // Print top 3 items or less if there are fewer than 3 sales
        for (int i = 0; i < min(3, salesCount); ++i) {
            cout << "Barang: " << get_item_name(salesArray[i].first) << ", Jumlah: " << salesArray[i].second << endl;
        }
    }

    string get_item_name(const string& code) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].code == code) return items[i].name;
        }
        return "Tidak Diketahui";
    }

    void processSale() {
        string code;
        int quantity;
        cout << "Masukkan kode barang: ";
        cin >> code;
        cout << "Masukkan jumlah: ";
        cin >> quantity;

        for (int i = 0; i < itemCount; ++i) {
            if (items[i].code == code) {
                if (items[i].stock >= quantity) {
                    double total = items[i].sellPrice * quantity;
                    items[i].stock -= quantity;
                    if (dailySales.find(code) == dailySales.end()) {
                        dailySales[code] = 0;
                    }
                    dailySales[code] += quantity; // Increment sales count
                    cout << "Total: " << total << endl;

                    int paymentChoice;
                    cout << "Pilih metode pembayaran (1 for Cash, 2 for QRIS): ";
                    cin >> paymentChoice;
                    PaymentMethod paymentMethod = (paymentChoice == 1) ? PaymentMethod::CASH : PaymentMethod::QRIS;

                    if (paymentMethodCount < MAX_ITEMS) {
                        paymentMethods[paymentMethodCount++] = make_pair(code, paymentMethod);
                    } else {
                        cout << "Tidak bisa menyimpan metode pembayaran lagi." << endl;
                    }

                    cout << "Nota:\n";
                    cout << "Nomor Transaksi: " << rand() % 10000 << endl;
                    cout << "Barang: " << items[i].name << ", Jumlah: " << quantity << ", Harga: " << items[i].sellPrice << " x " << quantity << " = " << total << endl;
                    cout << "Metode Pembayaran: " << ((paymentMethod == PaymentMethod::CASH) ? "Cash" : "QRIS") << endl;
                    cout << "Total Bayar: " << total << endl;
                } else {
                    cout << "Stok tidak mencukupi." << endl;
                }
                return;
            }
        }
        cout << "Barang tidak ditemukan." << endl;
    }

    void checkPrice() {
        string code;
        cout << "Masukkan kode barang: ";
        cin >> code;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].code == code) {
                cout << "Harga barang " << items[i].name << " adalah: " << items[i].sellPrice << endl;
                return;
            }
        }
        cout << "Barang tidak ditemukan." << endl;
    }

    void shiftReport() {
        int totalTransactions = dailySales.size();
        double totalIncome = 0;
        int cashPayments = 0, QRISPayments = 0;

        for (const auto& sale : dailySales) {
            for (int i = 0; i < itemCount; ++i) {
                if (items[i].code == sale.first) {
                    totalIncome += items[i].sellPrice * sale.second;
                    break;
                }
            }
        }

        for (int i = 0; i < paymentMethodCount; ++i) {
            if (paymentMethods[i].second == PaymentMethod::CASH) cashPayments++;
            else if (paymentMethods[i].second == PaymentMethod::QRIS) QRISPayments++;
        }

        cout << "--- Laporan Shift ---" << endl;
        cout << "Total Transaksi: " << totalTransactions << endl;
        cout << "Total Pendapatan: " << totalIncome << endl;
        cout << "Detail Pembayaran:\n" << "Cash: " << cashPayments << "\nQRIS: " << QRISPayments << endl;
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\nAdmin Menu:\n"
                 << "1. Input Barang\n"
                 << "2. Lihat Stok\n"
                 << "3. Update Stok\n"
                 << "4. Laporan Penjualan Harian\n"
                 << "5. Keuntungan per Item\n"
                 << "6. Barang Terlaris\n"
                 << "7. Kembali\n"
                 << "Pilih: ";
            cin >> choice;
            switch (choice) {
                case 1: addItem(); break;
                case 2: viewStock(); break;
                case 3: updateStock(); break;
                case 4: dailySalesReport(); break;
                case 5: profitPerItem(); break;
                case 6: topSellingItems(); break;
                case 7: break;
                default: cout << "Pilihan tidak valid." << endl;
            }
        } while (choice != 7);
    }

    void cashierMenu() {
        int choice;
        do {
            cout << "\nKasir Menu:\n"
                 << "1. Proses Penjualan\n"
                 << "2. Cek Harga Barang\n"
                 << "3. Buat Laporan Shift\n"
                 << "4. Kembali\n"
                 << "Pilih: ";
            cin >> choice;
            switch (choice) {
                case 1: processSale(); break;
                case 2: checkPrice(); break;
                case 3: shiftReport(); break;
                case 4: break;
                default: cout << "Pilihan tidak valid." << endl;
            }
        } while (choice != 4);
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
            store.cashierMenu();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}