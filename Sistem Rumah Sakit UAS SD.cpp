#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Pasien {
    int nomor;
    string nama;
    string keluhan;
    stack<string> riwayatLokasi;
};

struct NodePasien {
    Pasien data;
    NodePasien* next;

    NodePasien(Pasien p) {
        data = p;
        next = NULL;
    }
};

// BST : Arsip Pasien Selesai (Hanya untuk yang sudah lewat Apotek)
struct TreeNode {
    Pasien data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Pasien p) {
        data = p;
        left = NULL;
        right = NULL;
    }
};

// CLASS UTAMA
class RumahSakit {
private:
    NodePasien* front;
    NodePasien* rear;
    int nomorOtomatis = 1;
    TreeNode* root;

public:
    RumahSakit() {
        front = rear = NULL;
        root = NULL;
    }
    
    // 1. TAMBAH PASIEN (QUEUE)
    void tambahPasien() {
        Pasien p;
        p.nomor = nomorOtomatis++;
        
        cin.ignore();
        cout << "Nama Pasien : ";
        getline(cin, p.nama);
        cout << "Keluhan     : ";
        getline(cin, p.keluhan);

        // lokasi awal
        p.riwayatLokasi.push("Administrasi");
        NodePasien* baru = new NodePasien(p);
        if (front == NULL) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
        cout << "\nPasien berhasil ditambahkan di Administrasi!\n";
    }
    
    // 2. TAMPILKAN SEMUA ANTREAN
    void tampilPasien() {
        if (front == NULL) {
            cout << "Antrean kosong!\n";
            return;
        }

        NodePasien* bantu = front;
        cout << "\n=== SEMUA PASIEN AKTIF ===\n";
        while (bantu != NULL) {
            cout << "Nomor   : " << bantu->data.nomor << endl;
            cout << "Nama    : " << bantu->data.nama << endl;
            cout << "Lokasi  : " << bantu->data.riwayatLokasi.top() << endl;
            cout << "----------------------\n";
            bantu = bantu->next;
        }
    }

    // 3. PINDAH RUANGAN (DENGAN PANDUAN NAVIGASI)
    void pindahRuangan(Pasien &p) {
        // Menampilkan gambar navigasi dalam bentuk teks sebagai patokan
        cout << "\n=== PANDUAN NAVIGASI ANTAR POLI ===\n";
        cout << "1. Administrasi\n   Tujuan:\n   - Poli Umum\n\n";
        cout << "2. Poli Umum\n   Tujuan:\n   - Apotek\n   - Laboratorium\n\n";
        cout << "3. Laboratorium\n   Tujuan:\n   - Apotek\n";
        cout << "===================================\n";

        cout << "Posisi pasien saat ini: [" << p.riwayatLokasi.top() << "]\n";
        cout << "--- PILIH RUANGAN TUJUAN ---\n";
        cout << "1. Poli Umum\n";
        cout << "2. Laboratorium\n";
        cout << "3. Apotek\n";
        cout << "Pilih Ruangan (1-3): ";
        int pilihanRuang; cin >> pilihanRuang;

        string ruangan;
        switch (pilihanRuang) {
            case 1: ruangan = "Poli Umum"; break;
            case 2: ruangan = "Laboratorium"; break;
            case 3: ruangan = "Apotek"; break;
            default: cout << "Pilihan ruangan tidak valid!\n"; return;
        }

        p.riwayatLokasi.push(ruangan);
        cout << "Pasien berhasil dipindahkan ke " << ruangan << endl;
    }

    // 4. PANGGIL PASIEN (HANYA PENGUMUMAN)
    void panggilPasien() {
        if (front == NULL) {
            cout << "Antrean kosong!\n";
            return;
        }
        int nomor;
        cout << "Masukkan nomor pasien yang ingin dipanggil: ";
        cin >> nomor;

        NodePasien* p = cariPasien(nomor);
        if (p == NULL) {
            cout << "Pasien tidak ditemukan!\n";
            return;
        }

        // Pengumuman ini akan otomatis memanggil lokasi yang di-set di Menu 3
        cout << "\n>>> PENGUMUMAN: Panggilan untuk pasien atas nama " << p->data.nama 
             << " (No. " << p->data.nomor << "), silakan menuju " 
             << p->data.riwayatLokasi.top() << " <<<\n";
    }

    // 5. TAMPILKAN PASIEN PER RUANGAN (FILTER)
    void tampilPerRuangan() {
        if (front == NULL) {
            cout << "Antrean kosong!\n";
            return;
        }

        cout << "\n--- FILTER RUANGAN ---\n";
        cout << "1. Administrasi\n2. Poli Umum\n3. Laboratorium\n4. Apotek\n";
        cout << "Pilih Ruangan (1-4): ";
        int pil; cin >> pil;
        
        string target = "";
        if (pil == 1) target = "Administrasi";
        else if (pil == 2) target = "Poli Umum";
        else if (pil == 3) target = "Laboratorium";
        else if (pil == 4) target = "Apotek";
        else { cout << "Pilihan tidak valid!\n"; return; }

        NodePasien* bantu = front;
        bool ada = false;
        cout << "\n=== PASIEN DI RUANG " << target << " ===\n";
        while (bantu != NULL) {
            if (bantu->data.riwayatLokasi.top() == target) {
                cout << "- No: " << bantu->data.nomor << " | Nama: " << bantu->data.nama << "\n";
                ada = true;
            }
            bantu = bantu->next;
        }
        if (!ada) cout << "Tidak ada pasien di ruangan ini.\n";
    }

    // 6. UNDO LOKASI
    void undoRuangan(Pasien &p) {
        if (p.riwayatLokasi.size() <= 1) {
            cout << "Tidak bisa undo lagi! Pasien sudah berada di lokasi awal.\n";
            return;
        }
        p.riwayatLokasi.pop();
        cout << "Kembali ke lokasi : " << p.riwayatLokasi.top() << endl;
    }

    NodePasien* cariPasien(int nomor) {
        NodePasien* bantu = front;
        while (bantu != NULL) {
            if (bantu->data.nomor == nomor) return bantu;
            bantu = bantu->next;
        }
        return NULL;
    }

    // 7. EDIT DATA PASIEN
    void editPasien() {
        if (front == NULL) {
            cout << "Antrean kosong! Tidak ada data yang bisa diedit.\n";
            return;
        }
        int nomor;
        cout << "Masukkan nomor pasien yang ingin diedit: "; cin >> nomor;

        NodePasien* pasien = cariPasien(nomor);
        if (pasien == NULL) { cout << "Pasien tidak ditemukan!\n"; return; }

        cin.ignore();
        cout << "\n--- EDIT DATA PASIEN (ID: " << nomor << ") ---\n";
        cout << "Nama Baru (Lama: " << pasien->data.nama << ") : ";
        string namaBaru; getline(cin, namaBaru);
        if (!namaBaru.empty()) pasien->data.nama = namaBaru;

        cout << "Keluhan Baru (Lama: " << pasien->data.keluhan << ") : ";
        string keluhanBaru; getline(cin, keluhanBaru);
        if (!keluhanBaru.empty()) pasien->data.keluhan = keluhanBaru;

        cout << "Data pasien berhasil diperbarui!\n";
    }

    TreeNode* insertBST(TreeNode* node, Pasien p) {
        if (node == NULL) return new TreeNode(p);
        if (p.nomor < node->data.nomor) node->left = insertBST(node->left, p);
        else node->right = insertBST(node->right, p);
        return node;
    }
    
    // 8. SELESAI & MASUK ARSIP (VALIDASI APOTEK)
    void selesaiMasukArsip() {
        if (front == NULL) { cout << "Antrean kosong!\n"; return; }
        
        int nomor;
        cout << "Masukkan nomor pasien yang akan diarsipkan (Selesai Berobat): ";
        cin >> nomor;

        NodePasien* temp = front;
        NodePasien* prev = NULL;

        // Cari posisi node pasien
        while (temp != NULL && temp->data.nomor != nomor) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Pasien tidak ditemukan!\n"; return;
        }

        // VALIDASI: Pasien hanya boleh masuk arsip jika sudah di Apotek
        if (temp->data.riwayatLokasi.top() != "Apotek") {
            cout << "GAGAL: Pasien belum sampai di Apotek! Selesaikan alur terlebih dahulu.\n";
            return;
        }

        // Masukkan ke Arsip BST
        root = insertBST(root, temp->data);

        // Hapus dari Linked List (Antrean Aktif)
        if (prev == NULL) front = front->next; // Jika di awal
        else prev->next = temp->next;          // Bypass node di tengah/akhir
        
        if (temp == rear) rear = prev;         // Update tail jika perlu

        cout << "Pasien " << temp->data.nama << " telah selesai menebus obat dan datanya dipindah ke Arsip.\n";
        delete temp;
    }

    void inorder(TreeNode* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << "ID : " << node->data.nomor << " | Nama : " << node->data.nama << endl;
        inorder(node->right);
    }

    // 9. TAMPILKAN ARSIP
    void tampilArsip() {
        cout << "\n=== ARSIP PASIEN SELESAI ===\n";
        if (root == NULL) { cout << "Arsip masih kosong.\n"; return; }
        inorder(root);
    }

    void menuPindahRuangan() {
        int nomor;
        cout << "Masukkan nomor pasien : "; cin >> nomor;
        NodePasien* pasien = cariPasien(nomor);
        if (pasien == NULL) { cout << "Pasien tidak ditemukan!\n"; return; }
        pindahRuangan(pasien->data);
    }

    void menuUndo() {
        int nomor;
        cout << "Masukkan nomor pasien : "; cin >> nomor;
        NodePasien* pasien = cariPasien(nomor);
        if (pasien == NULL) { cout << "Pasien tidak ditemukan!\n"; return; }
        undoRuangan(pasien->data);
    }
};

// MAIN
int main() {
    RumahSakit rs;
    int pilih;

    do {
        cout << "\n=== SISTEM RUMAH SAKIT ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Tampilkan Semua Antrean\n";
        cout << "3. Pindah Ruangan\n";
        cout << "4. Panggil Pasien \n";
        cout << "5. Tampilkan Pasien Per Ruangan\n";
        cout << "6. Undo Ruangan\n";
        cout << "7. Edit Data Pasien\n";
        cout << "8. Selesai Berobat & Masuk Arsip\n";
        cout << "9. Tampilkan Arsip\n";
        cout << "0. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;

        switch (pilih) {
            case 1: rs.tambahPasien(); break;
            case 2: rs.tampilPasien(); break;
            case 3: rs.menuPindahRuangan(); break;
            case 4: rs.panggilPasien(); break;
            case 5: rs.tampilPerRuangan(); break;
            case 6: rs.menuUndo(); break;
            case 7: rs.editPasien(); break;
            case 8: rs.selesaiMasukArsip(); break;
            case 9: rs.tampilArsip(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Menu tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}