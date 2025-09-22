#include <iostream>
#include <string>
using namespace std;

struct Penerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    Penerbangan* next;
};


int counterPenerbangan = 1;
string nimTerakhir = ""; 

// Membuat Node Baru
Penerbangan* buatNode(string kode, string tujuan, string status) {
    Penerbangan* newNode = new Penerbangan;
    newNode->kodePenerbangan = kode;
    newNode->tujuan = tujuan;
    newNode->status = status;
    newNode->next = nullptr;
    return newNode;
}

// Menambah Jadwal Penerbangan diakhir
void tambahJadwal(Penerbangan** head, string tujuan, string status) {
    string kode;
    if (counterPenerbangan == 1) {
        kode = "JT-" + nimTerakhir;
    } else {
        kode = "JT-" + nimTerakhir + "-" + to_string(counterPenerbangan);
    }
    
    Penerbangan* newNode = buatNode(kode, tujuan, status);
    counterPenerbangan++;
    
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    
    Penerbangan* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Menyisipkan Jadwal Spesifik
void sisipkanJadwal(Penerbangan** head, string tujuan, string status, int posisi) {
    string kode = "JT-" + nimTerakhir + "-" + to_string(counterPenerbangan);
    counterPenerbangan++;
    
    Penerbangan* newNode = buatNode(kode, tujuan, status);
    
    if (posisi == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    
    Penerbangan* temp = *head;
    for (int i = 1; i < posisi - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }
    
    if (temp == nullptr) {
        cout << "Posisi melebihi panjang linked list!" << endl;
        delete newNode;
        return;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
}

// Menghapus Jadwal
void hapusAwal(Penerbangan** head) {
    if (*head == nullptr) {
        cout << "Tidak ada jadwal untuk dihapus!" << endl;
        return;
    }
    
    Penerbangan* temp = *head;
    *head = (*head)->next;
    cout << "Jadwal " << temp->kodePenerbangan << " telah dihapus." << endl;
    delete temp;
}


void hapusBerdasarkanKode(Penerbangan** head, string kode) {
    if (*head == nullptr) {
        cout << "Tidak ada jadwal untuk dihapus!" << endl;
        return;
    }
    
    
    if ((*head)->kodePenerbangan == kode) {
        Penerbangan* temp = *head;
        *head = (*head)->next;
        cout << "Jadwal " << temp->kodePenerbangan << " telah dihapus." << endl;
        delete temp;
        return;
    }
    
    
    Penerbangan* prev = *head;
    Penerbangan* curr = (*head)->next;
    
    while (curr != nullptr) {
        if (curr->kodePenerbangan == kode) {
            prev->next = curr->next;
            cout << "Jadwal " << curr->kodePenerbangan << " telah dihapus." << endl;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    
    cout << "Kode penerbangan " << kode << " tidak ditemukan!" << endl;
}

// Update status Penerbangan
void updateStatus(Penerbangan* head, string kode) {
    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kode) {
            cout << "Status saat ini: " << temp->status << endl;
            cout << "Masukkan status baru: ";
            getline(cin, temp->status);
            cout << "Status berhasil diupdate!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Kode penerbangan " << kode << " tidak ditemukan!" << endl;
}


void tampilkanJadwal(Penerbangan* head) {
    if (head == nullptr) {
        cout << "Belum ada jadwal penerbangan!" << endl;
        return;
    }
    
    cout << "\n+-----------------------------------------------------------------+" << endl;
    cout << "|                   DAFTAR JADWAL PENERBANGAN                   |" << endl;
    cout << "+-----------------------------------------------------------------+" << endl;
    cout << "| " << "Kode           | " << "Tujuan               | " << "Status         |" << endl;
    cout << "+-----------------------------------------------------------------+" << endl;
    
    Penerbangan* temp = head;
    while (temp != nullptr) {
        cout << "| " << temp->kodePenerbangan;
        
        for (int i = temp->kodePenerbangan.length(); i < 15; i++) cout << " ";
        cout << "| " << temp->tujuan;
        for (int i = temp->tujuan.length(); i < 20; i++) cout << " ";
        cout << "| " << temp->status;
        for (int i = temp->status.length(); i < 15; i++) cout << " ";
        cout << "|" << endl;
        
        temp = temp->next;
    }
    cout << "+-----------------------------------------------------------------+" << endl;
}


void bersihkanMemori(Penerbangan** head) {
    Penerbangan* temp;
    while (*head != nullptr) {
        temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}


int inputAngka(string pesan) {
    int nilai;
    while (true) {
        cout << pesan;
        if (cin >> nilai) {
            cin.ignore();
            return nilai;
        } else {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Fungsi utama
int main() {
    Penerbangan* head = nullptr;
    int pilihan, posisiSisip;
    string tujuan, status, kode;
    
    
    cout << "Masukkan 3 digit terakhir NIM Anda: ";
    getline(cin, nimTerakhir);
    if (nimTerakhir.length() != 3) {
    cout << "NIM harus 3 digit! Masukkan ulang: ";
    getline(cin, nimTerakhir);
}
    
    // Menentukan posisi sisip berdasarkan digit terakhir NIM(096)
    char digitTerakhirChar = nimTerakhir.empty() ? '0' : nimTerakhir.back();
    int digitTerakhir = digitTerakhirChar - '0';
    if (digitTerakhir == 0) {
        posisiSisip = 2;
    } else {
        posisiSisip = digitTerakhir + 1;
    }
    
    do {
        cout << "\n";
        cout << "+------------------------------------------------------------+" << endl;
        cout << "|                  FLIGHT SCHEDULE SYSTEM                    |" << endl;
        cout << "|           [Danendra Hazzel PW - " << nimTerakhir << " - GENAP]               |" << endl;
        cout << "+------------------------------------------------------------+" << endl;
        cout << "| 1. Tambah Jadwal Penerbangan                               |" << endl;
        cout << "| 2. Sisipkan Jadwal Penerbangan (posisi: " << posisiSisip << ")                 |" << endl;
        cout << "| 3. Hapus Jadwal Paling Awal                                |" << endl;
        cout << "| 4. Update Status Penerbangan                               |" << endl;
        cout << "| 5. Tampilkan Semua Jadwal                                  |" << endl;
        cout << "| 6. Hapus Jadwal Berdasarkan Kode                           |" << endl;
        cout << "| 0. Keluar                                                  |" << endl;
        cout << "+------------------------------------------------------------+" << endl;
        
        pilihan = inputAngka("Pilih menu: ");
        
        switch (pilihan) {
            case 1:
                cout << "Masukkan tujuan penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan status penerbangan: ";
                getline(cin, status);
                tambahJadwal(&head, tujuan, status);
                cout << "Jadwal berhasil ditambahkan!" << endl;
                break;
                
            case 2:
                cout << "Masukkan tujuan penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan status penerbangan: ";
                getline(cin, status);
                sisipkanJadwal(&head, tujuan, status, posisiSisip);
                cout << "Jadwal berhasil disisipkan di posisi " << posisiSisip << "!" << endl;
                break;
                
            case 3:
                hapusAwal(&head);
                break;
                
            case 4:
                cout << "Masukkan kode penerbangan: ";
                getline(cin, kode);
                updateStatus(head, kode);
                break;
                
            case 5:
                tampilkanJadwal(head);
                break;
                
            case 6:
                cout << "Masukkan kode penerbangan: ";
                getline(cin, kode);
                hapusBerdasarkanKode(&head, kode);
                break;
                
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                break;
                
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
        
    } while (pilihan != 0);
    
    // Membersihkan memori sebelum keluar
    bersihkanMemori(&head);
    
    return 0;
}