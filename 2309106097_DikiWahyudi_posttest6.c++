#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm> // Tambahkan header ini untuk menggunakan fungsi sort

using namespace std;

// Struktur data untuk menyimpan informasi beras
struct BerasInfo {
    string jenisNama;
    double hargaBeras;
    int stokBeras;
};

// Fungsi untuk membandingkan dua objek BerasInfo berdasarkan jenisNama
bool compareBerasNama(const BerasInfo& a, const BerasInfo& b) {
    return a.jenisNama < b.jenisNama;
}

// Vektor untuk menyimpan data beras
vector<BerasInfo> daftarBeras;

// Fungsi untuk login
bool prosesLogin() {
    string user, pw;
    int percobaan = 0;
    const string userBenar = "diki";
    const string pwBenar = "097";

    while (percobaan < 3) {
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pw;

        if (user == userBenar && pw == pwBenar) {
            return true;
        } else {
            percobaan++;
            cout << "Username atau password salah. Sisa percobaan: " << 3 - percobaan << endl;
        }
    }

    cout << "Login gagal. Program akan keluar." << endl;
    return false;
}
// Fungsi untuk menampilkan menu
void tampilMenu() {
    cout << "=== Toko Beras Diki Walla ===" << endl;
    cout << "1. Lihat Daftar Beras" << endl;
    cout << "2. Tambah Jenis Beras" << endl;
    cout << "3. Jual Beras" << endl;
    cout << "4. Hapus Jenis Beras" << endl;
    cout << "5. Ubah Jenis Beras" << endl;
    cout << "6. Cari Jenis Beras" << endl;
    cout << "7. Urutkan Daftar Beras (Ascending)" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilihan: ";
}

// Fungsi menambah jenis beras baru
void tambahBerasData() {
    BerasInfo berasInput;
    cout << "Jenis Beras: ";
    cin.ignore();
    getline(cin, berasInput.jenisNama);
    cout << "Harga per Kg: ";
    cin >> berasInput.hargaBeras;
    cin.clear(); // Membersihkan status error dari cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    while (true) {
        cout << "Stok (Kg): ";
        if (cin >> berasInput.stokBeras && berasInput.stokBeras >= 0) {
            break; // Keluar dari loop jika input valid
        } else {
            cout << "Input tidak valid. Masukkan angka positif." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }

    daftarBeras.push_back(berasInput);
    cout << "Jenis beras berhasil ditambahkan!" << endl;
}

// Fungsi menjual beras
void jualBerasData() {
    string jenisNama;
    int jumlahJual;
    cout << "Jenis Beras: ";
    cin.ignore();
    getline(cin, jenisNama);

    while (true) {
        cout << "Jumlah Jual (Kg): ";
        if (cin >> jumlahJual && jumlahJual >= 0) {
            break; // Keluar dari loop jika input valid
        } else {
            cout << "Input tidak valid. Masukkan angka positif." << endl;
            cin.clear(); // Membersihkan status error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }

    for (auto& beras : daftarBeras) {
        if (beras.jenisNama == jenisNama) {
            if (beras.stokBeras >= jumlahJual) {
                beras.stokBeras -= jumlahJual;
                double totalHarga = beras.hargaBeras * jumlahJual;
                cout << "Total Harga: " << totalHarga << endl;
                cout << "Transaksi berhasil!" << endl;
            } else {
                cout << "Stok tidak mencukupi!" << endl;
            }
            return;
        }
    }

    cout << "Jenis beras tidak ditemukan!" << endl;
}

// Fungsi menghapus jenis beras
void hapusBerasData() {
    string jenisNama;
    cout << "Jenis Beras yang Akan Dihapus: ";
    cin.ignore();
    getline(cin, jenisNama);

    for (auto it = daftarBeras.begin(); it != daftarBeras.end(); ++it) {
        if (it->jenisNama == jenisNama) {
            daftarBeras.erase(it);
            cout << "Jenis beras berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "Jenis beras tidak ditemukan!" << endl;
}

// Fungsi mengubah jenis beras
void ubahBerasData() {
    string jenisNama;
    cout << "Jenis Beras yang Akan Diubah: ";
    cin.ignore();
    getline(cin, jenisNama);

    for (auto& beras : daftarBeras) {
        if (beras.jenisNama == jenisNama) {
            BerasInfo berasUbah;
            cout << "Jenis Beras Baru: ";
            getline(cin, berasUbah.jenisNama);
            cout << "Harga per Kg: ";
            cin >> berasUbah.hargaBeras;
            cin.clear(); // Membersihkan status error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Stok (Kg): ";
                if (cin >> berasUbah.stokBeras && berasUbah.stokBeras >= 0) {
                    break; // Keluar dari loop jika input valid
                } else {
                    cout << "Input tidak valid. Masukkan angka positif." << endl;
                    cin.clear(); // Membersihkan status error dari cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            beras = berasUbah;
            cout << "Jenis beras berhasil diubah!" << endl;
            return;
        }
    }

    cout << "Jenis beras tidak ditemukan!" << endl;
}

// Fungsi dengan parameter dereference
void tambahStokBeras(BerasInfo* beras, int tambahanStok) {
    if (beras != nullptr) {
        beras->stokBeras += tambahanStok;
        cout << "Stok beras berhasil ditambahkan!" << endl;
    } else {
        cout << "Jenis beras tidak ditemukan!" << endl;
    }
}
// Fungsi mencari jenis beras
void cariBerasData() {
    string jenisNama;
    cout << "Jenis Beras yang Akan Dicari: ";
    cin.ignore();
    getline(cin, jenisNama);

    for (const auto& beras : daftarBeras) {
        if (beras.jenisNama == jenisNama) {
            cout << "Jenis Beras: " << beras.jenisNama << endl;
            cout << "Harga per Kg: " << beras.hargaBeras << endl;
            cout << "Stok: " << beras.stokBeras << " Kg" << endl;
            return;
        }
    }

    cout << "Jenis beras tidak ditemukan!" << endl;
}
// Fungsi mencari jenis beras dan mengembalikan pointer ke objek beras
BerasInfo* cariBerasData(const string& jenisNama) {
    for (auto& beras : daftarBeras) {
        if (beras.jenisNama == jenisNama) {
            return &beras;
        }
    }
    return nullptr;
}

// Fungsi menampilkan menu utama secara rekursif
void tampilMenuUtama() {
    tampilMenu();
    int pilihan;
    cin >> pilihan;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    try {
        if (pilihan < 1 || pilihan > 8) {
            throw invalid_argument("pilihan tidak valid masukan angka 1-8!");
        }

        switch (pilihan) {
            case 1:
                cout << "=== Daftar Beras ===" << endl;
                if (daftarBeras.empty()) {
                    cout << "Tidak ada jenis beras!" << endl;
                } else {
                    for (const auto& beras : daftarBeras) {
                        cout << "Jenis Beras: " << beras.jenisNama << endl;
                        cout << "Harga per Kg: " << beras.hargaBeras << endl;
                        cout << "Stok: " << beras.stokBeras << " Kg" << endl;
                        cout << "-------------------" << endl;
                    }
                }
                tampilMenuUtama();
                break;
            case 2:
                tambahBerasData();
                tampilMenuUtama();
                break;
            case 3:
                jualBerasData();
                tampilMenuUtama();
                break;
            case 4:
                hapusBerasData();
                tampilMenuUtama();
                break;
            case 5:
                ubahBerasData();
                tampilMenuUtama();
                break;
            case 6:
                cariBerasData();
                tampilMenuUtama();
                break;
            case 7: // Kasus untuk sorting ascending
                cout << "=== Daftar Beras Setelah Diurutkan (Ascending) ===" << endl;
                if (daftarBeras.empty()) {
                    cout << "Tidak ada jenis beras!" << endl;
                } else {
                    // Mengurutkan daftar beras berdasarkan jenis nama (ascending)
                    sort(daftarBeras.begin(), daftarBeras.end(), compareBerasNama);

                    for (const auto& beras : daftarBeras) {
                        cout << "Jenis Beras: " << beras.jenisNama << endl;
                        cout << "Harga per Kg: " << beras.hargaBeras << endl;
                        cout << "Stok: " << beras.stokBeras << " Kg" << endl;
                        cout << "-------------------" << endl;
                    }
                }
                tampilMenuUtama();
                break;
            case 8:
                cout << "Terima kasih telah belanja di toko kami!" << endl;
                break;
        }
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tampilMenuUtama();
    }
}

int main() {
    // Login
    if (!prosesLogin()) {
        return 0; // Keluar dari program jika login gagal
    }

    tampilMenuUtama();

    return 0;
}