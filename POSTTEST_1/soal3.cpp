#include <iostream>
#include <string>
#include <iomanip>
#include <cctype> 
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

// Fungsi validasi nama 
bool isValidNama(const string &nama) {
    if (nama.empty()) return false;
    for (char c : nama) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// Fungsi validasi NIM (hanya angka)
bool isValidNIM(const string &nim) {
    if (nim.empty()) return false;
    for (char c : nim) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Fungsi validasi IPK (0.0 - 4.0)
bool isValidIPK(float ipk) {
    return (ipk >= 0.0 && ipk <= 4.0);
}

int main() {
    Mahasiswa mhs[4];
    
    cout << "Input data 4 mahasiswa:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "\nMahasiswa " << i+1 << ":" << endl;
        
        
        do {
            cout << "Nama: ";
            getline(cin, mhs[i].nama);
            if (!isValidNama(mhs[i].nama)) {
                cout << "Error: Nama hanya boleh berisi huruf dan spasi!" << endl;
            }
        } while (!isValidNama(mhs[i].nama));
        
        
        do {
            cout << "NIM: ";
            getline(cin, mhs[i].nim);
            if (!isValidNIM(mhs[i].nim)) {
                cout << "Error: NIM hanya boleh berisi angka!" << endl;
            }
        } while (!isValidNIM(mhs[i].nim));
        
        
        do {
            cout << "IPK: ";
            cin >> mhs[i].ipk;
            if (!isValidIPK(mhs[i].ipk)) {
                cout << "Error: IPK harus antara 0.0 - 4.0!" << endl;
            }
            cin.ignore(1000, '\n'); 
        } while (!isValidIPK(mhs[i].ipk));
    }
    
    // Urutkan berdasarkan IPK ascending (bubble sort)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3-i; j++) {
            if (mhs[j].ipk > mhs[j+1].ipk) {
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j+1];
                mhs[j+1] = temp;
            }
        }
    }
    
    cout << "\nData mahasiswa setelah diurutkan berdasarkan IPK:" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Nama" << setw(15) << "NIM" << "IPK" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << left << setw(20) << mhs[i].nama 
             << setw(15) << mhs[i].nim 
             << fixed << setprecision(2) << mhs[i].ipk << endl;
    }
    
    return 0;
}