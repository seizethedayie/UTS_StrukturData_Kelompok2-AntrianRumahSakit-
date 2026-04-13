#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

// Struct data pasien
struct Pasien {
    int nomor;
    string nama;
    string keluhan;
};

// Class sistem antrian rumah sakit
class AntrianRumahSakit {
private:
    Pasien data[MAX];
    int jumlah = 0;
    int nomorOtomatis = 1;

public:

    bool kosong() {
        return jumlah == 0;
    }

    bool penuh() {
        return jumlah == MAX;
    }

    void sorting() {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - i - 1; j++) {
                if (data[j].nomor > data[j + 1].nomor) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void tambah() {
        if (penuh()) {
            cout << "Data penuh!\n";
            return;
        }

        data[jumlah].nomor = nomorOtomatis++;
        cout << "\nNomor Antrian : " << data[jumlah].nomor << endl;
        cin.ignore();

        do {
            cout << "Nama Pasien : ";
            getline(cin, data[jumlah].nama);
        } while (data[jumlah].nama.empty());

        do {
            cout << "Keluhan : ";
            getline(cin, data[jumlah].keluhan);
        } while (data[jumlah].keluhan.empty());

        jumlah++;
        sorting();

        cout << "Data berhasil ditambahkan\n";
    }

    void tampil() {
        if (kosong()) {
            cout << "\nData kosong!\n";
            return;
        }

        cout << "\n=== DATA ANTRIAN PASIEN ===\n";
        for (int i = 0; i < jumlah; i++) {
            cout << "Nomor   : " << data[i].nomor << endl;
            cout << "Nama    : " << data[i].nama << endl;
            cout << "Keluhan : " << data[i].keluhan << endl;
            cout << "-------------------------\n";
        }
    }

    void update() {
        if (kosong()) {
            cout << "Data kosong!\n";
            return;
        }

        int cari;
        cout << "Masukkan nomor antrian: ";
        cin >> cari;
        cin.ignore();

        for (int i = 0; i < jumlah; i++) {
            if (data[i].nomor == cari) {
                cout << "Nama baru: ";
                getline(cin, data[i].nama);

                cout << "Keluhan baru: ";
                getline(cin, data[i].keluhan);

                cout << "Data berhasil diupdate\n";
                return;
            }
        }

        cout << "Data tidak ditemukan\n";
    }

    void hapus() {
        if (kosong()) {
            cout << "Data kosong!\n";
            return;
        }

        int cari;
        cout << "Masukkan nomor antrian: ";
        cin >> cari;

        for (int i = 0; i < jumlah; i++) {
            if (data[i].nomor == cari) {

                // Geser data ke kiri
                for (int j = i; j < jumlah - 1; j++) {
                    data[j] = data[j + 1];
                }

                jumlah--;

                // ?? Atur ulang nomor supaya berurutan lagi
                for (int k = 0; k < jumlah; k++) {
                    data[k].nomor = k + 1;
                }

                // Sinkronkan nomor otomatis
                nomorOtomatis = jumlah + 1;

                cout << "Data berhasil dihapus\n";
                return;
            }
        }

        cout << "Data tidak ditemukan\n";
    }

    void cari() {
        if (kosong()) {
            cout << "Data kosong!\n";
            return;
        }

        int nomor;
        cout << "Masukkan nomor antrian: ";
        cin >> nomor;

        for (int i = 0; i < jumlah; i++) {
            if (data[i].nomor == nomor) {
                cout << "\nData ditemukan:\n";
                cout << "Nomor   : " << data[i].nomor << endl;
                cout << "Nama    : " << data[i].nama << endl;
                cout << "Keluhan : " << data[i].keluhan << endl;
                return;
            }
        }

        cout << "Data tidak ditemukan\n";
    }

    void jumlahData() {
        cout << "Total pasien: " << jumlah << endl;
    }

    void panggil() {
        if (kosong()) {
            cout << "Tidak ada antrian!\n";
            return;
        }

        int cari;
        cout << "Masukkan nomor antrian yang dipanggil: ";
        cin >> cari;

        for (int i = 0; i < jumlah; i++) {
            if (data[i].nomor == cari) {

                cout << "\nMemanggil pasien:\n";
                cout << "Nomor   : " << data[i].nomor << endl;
                cout << "Nama    : " << data[i].nama << endl;
                cout << "Keluhan : " << data[i].keluhan << endl;

                for (int j = i; j < jumlah - 1; j++) {
                    data[j] = data[j + 1];
                }

                jumlah--;

                // ?? Atur ulang nomor setelah dipanggil
                for (int k = 0; k < jumlah; k++) {
                    data[k].nomor = k + 1;
                }

                nomorOtomatis = jumlah + 1;

                return;
            }
        }

        cout << "Nomor antrian tidak ditemukan!\n";
    }
};

int main() {
    AntrianRumahSakit rs;
    int pilih;

    do {
        cout << "\n=== SISTEM ANTRIAN RUMAH SAKIT ===\n";
        cout << "1. Tambah Data Pasien\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Update Data\n";
        cout << "4. Hapus Data\n";
        cout << "5. Cari Data\n";
        cout << "6. Jumlah Data\n";
        cout << "7. Panggil Pasien\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu : ";
        cin >> pilih;

        switch (pilih) {
            case 1: rs.tambah(); break;
            case 2: rs.tampil(); break;
            case 3: rs.update(); break;
            case 4: rs.hapus(); break;
            case 5: rs.cari(); break;
            case 6: rs.jumlahData(); break;
            case 7: rs.panggil(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}