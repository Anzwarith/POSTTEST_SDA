#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Penerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    Penerbangan* next;
    Penerbangan* prev;
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
    newNode->prev = nullptr;
    return newNode;
}

// Menambah Jadwal Penerbangan diakhir
void tambahJadwal(Penerbangan** head, Penerbangan** tail, string tujuan, string status) {
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
        *tail = newNode;
        return;
    }
    
    (*tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;
}

// Menyisipkan Jadwal Spesifik
void sisipkanJadwal(Penerbangan** head, Penerbangan** tail, string tujuan, string status, int posisi) {
    if (posisi < 1) {
        cout << "Posisi tidak valid!" << endl;
        return;
    }
    
    string kode = "JT-" + nimTerakhir + "-" + to_string(counterPenerbangan);
    counterPenerbangan++;
    
    Penerbangan* newNode = buatNode(kode, tujuan, status);
    
    if (posisi == 1) {
        if (*head == nullptr) {
            *head = newNode;
            *tail = newNode;
        } else {
            newNode->next = *head;
            (*head)->prev = newNode;
            *head = newNode;
        }
        return;
    }
    
    Penerbangan* temp = *head;
    int currentPos = 1;
    
    while (temp != nullptr && currentPos < posisi - 1) {
        temp = temp->next;
        currentPos++;
    }
    
    if (temp == nullptr) {
        cout << "Posisi melebihi panjang linked list!" << endl;
        delete newNode;
        return;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != nullptr) {
        temp->next->prev = newNode;
    } else {
        *tail = newNode;
    }
    
    temp->next = newNode;
}

// Menghapus Jadwal Paling Awal
void hapusAwal(Penerbangan** head, Penerbangan** tail) {
    if (*head == nullptr) {
        cout << "Tidak ada jadwal untuk dihapus!" << endl;
        return;
    }
    
    Penerbangan* temp = *head;
    *head = (*head)->next;
    
    if (*head != nullptr) {
        (*head)->prev = nullptr;
    } else {
        *tail = nullptr;
    }
    
    cout << "Jadwal " << temp->kodePenerbangan << " telah dihapus." << endl;
    delete temp;
}

// Menghapus Jadwal Berdasarkan Kode
void hapusBerdasarkanKode(Penerbangan** head, Penerbangan** tail, string kode) {
    if (*head == nullptr) {
        cout << "Tidak ada jadwal untuk dihapus!" << endl;
        return;
    }
    
    Penerbangan* temp = *head;
    
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kode) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            } else {
                *tail = temp->prev;
            }
            
            cout << "Jadwal " << temp->kodePenerbangan << " telah dihapus." << endl;
            delete temp;
            return;
        }
        temp = temp->next;
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

// Menampilkan detail jadwal berdasarkan kode
void tampilkanDetailJadwal(Penerbangan* head, string kode) {
    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kode) {
            cout << "\n+=================================================+" << endl;
            cout << "|              DETAIL JADWAL PENERBANGAN         |" << endl;
            cout << "+=================================================+" << endl;
            cout << "| Kode Penerbangan : " << left << setw(28) << temp->kodePenerbangan << "|" << endl;
            cout << "| Tujuan           : " << left << setw(28) << temp->tujuan << "|" << endl;
            cout << "| Status           : " << left << setw(28) << temp->status << "|" << endl;
            cout << "+=================================================+" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Kode penerbangan " << kode << " tidak ditemukan!" << endl;
}

// Menampilkan semua jadwal dari depan 
void tampilkanJadwalMaju(Penerbangan* head) {
    if (head == nullptr) {
        cout << "Belum ada jadwal penerbangan!" << endl;
        return;
    }
    
    cout << "\n+=================================================================+" << endl;
    cout << "|                   DAFTAR JADWAL PENERBANGAN (DEPANs->BELAKANG)  |" << endl;
    cout << "+=================================================================+" << endl;
    cout << "| " << left << setw(15) << "Kode" << " | " << setw(20) << "Tujuan" << " | " << setw(15) << "Status" << " |" << endl;
    cout << "+=================================================================+" << endl;
    
    Penerbangan* temp = head;
    while (temp != nullptr) {
        cout << "| " << setw(15) << temp->kodePenerbangan << " | " 
             << setw(20) << temp->tujuan << " | " 
             << setw(15) << temp->status << " |" << endl;
        temp = temp->next;
    }
    cout << "+=================================================================+" << endl;
}

// Menampilkan semua jadwal dari belakang 
void tampilkanJadwalMundur(Penerbangan* tail) {
    if (tail == nullptr) {
        cout << "Belum ada jadwal penerbangan!" << endl;
        return;
    }
    
    cout << "\n+=================================================================+" << endl;
    cout << "|                   DAFTAR JADWAL PENERBANGAN (BELAKANG->DEPAN)  |" << endl;
    cout << "+=================================================================+" << endl;
    cout << "| " << left << setw(15) << "Kode" << " | " << setw(20) << "Tujuan" << " | " << setw(15) << "Status" << " |" << endl;
    cout << "+=================================================================+" << endl;
    
    Penerbangan* temp = tail;
    while (temp != nullptr) {
        cout << "| " << setw(15) << temp->kodePenerbangan << " | " 
             << setw(20) << temp->tujuan << " | " 
             << setw(15) << temp->status << " |" << endl;
        temp = temp->prev;
    }
    cout << "+=================================================================+" << endl;
}

// Membersihkan memori
void bersihkanMemori(Penerbangan** head, Penerbangan** tail) {
    Penerbangan* temp;
    while (*head != nullptr) {
        temp = *head;
        *head = (*head)->next;
        delete temp;
    }
    *tail = nullptr;
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
    Penerbangan* tail = nullptr;
    int pilihan, posisiSisip;
    string tujuan, status, kode;
    
    cout << "Masukkan 3 digit terakhir NIM Anda: ";
    getline(cin, nimTerakhir);
    if (nimTerakhir.length() != 3) {
        cout << "NIM harus 3 digit! Masukkan ulang: ";
        getline(cin, nimTerakhir);
    }
    
    char digitTerakhirChar = nimTerakhir.empty() ? '0' : nimTerakhir.back();
    int digitTerakhir = digitTerakhirChar - '0';
    if (digitTerakhir == 0) {
        posisiSisip = 2;
    } else {
        posisiSisip = digitTerakhir + 1;
    }
    
    do {
        cout << "\n";
        cout << "+=============================================================+" << endl;
        cout << "|                FLIGHT SCHEDULE SYSTEM                      |" << endl;
        cout << "|           [Danendra Hazzel PW - " << nimTerakhir << " - GENAP]               |" << endl;
        cout << "+=============================================================+" << endl;
        cout << "| 1. Tambah Jadwal Penerbangan                               |" << endl;
        cout << "| 2. Sisipkan Jadwal Penerbangan (posisi: " << setw(2) << posisiSisip << ")                |" << endl;
        cout << "| 3. Hapus Jadwal Paling Awal                                |" << endl;
        cout << "| 4. Update Status Penerbangan                               |" << endl;
        cout << "| 5. Tampilkan Semua Jadwal (Depan->Belakang)                |" << endl;
        cout << "| 6. Tampilkan Semua Jadwal (Belakang->Depan)                |" << endl;
        cout << "| 7. Tampilkan Detail Jadwal Berdasarkan Kode                |" << endl;
        cout << "| 8. Hapus Jadwal Berdasarkan Kode                           |" << endl;
        cout << "| 0. Keluar                                                  |" << endl;
        cout << "+=============================================================+" << endl;
        
        pilihan = inputAngka("Pilih menu: ");
        
        switch (pilihan) {
            case 1:
                cout << "Masukkan tujuan penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan status penerbangan: ";
                getline(cin, status);
                tambahJadwal(&head, &tail, tujuan, status);
                cout << "✓ Jadwal berhasil ditambahkan!" << endl;
                break;
                
            case 2:
                cout << "Masukkan tujuan penerbangan: ";
                getline(cin, tujuan);
                cout << "Masukkan status penerbangan: ";
                getline(cin, status);
                sisipkanJadwal(&head, &tail, tujuan, status, posisiSisip);
                cout << "✓ Jadwal berhasil disisipkan di posisi " << posisiSisip << "!" << endl;
                break;
                
            case 3:
                hapusAwal(&head, &tail);
                break;
                
            case 4:
                cout << "Masukkan kode penerbangan: ";
                getline(cin, kode);
                updateStatus(head, kode);
                break;
                
            case 5:
                tampilkanJadwalMaju(head);
                break;
                
            case 6:
                tampilkanJadwalMundur(tail);
                break;
                
            case 7:
                cout << "Masukkan kode penerbangan: ";
                getline(cin, kode);
                tampilkanDetailJadwal(head, kode);
                break;
                
            case 8:
                cout << "Masukkan kode penerbangan: ";
                getline(cin, kode);
                hapusBerdasarkanKode(&head, &tail, kode);
                break;
                
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                break;
                
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
        
    } while (pilihan != 0);
    
    // Membersihkan memori sebelum keluar
    bersihkanMemori(&head, &tail);
    
    return 0;
}