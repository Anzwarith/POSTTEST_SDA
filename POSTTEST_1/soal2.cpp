#include <iostream>
using namespace std;

int main() {
    int matrix[3][3];
    int sum = 0;
    
    cout << "Masukkan matriks 3x3:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Matrix[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    
    for (int i = 0; i < 3; i += 2) {
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
    }
    
    cout << "\nMatriks:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    cout << "\nJumlah elemen baris genap: " << sum << endl;
    
    return 0;
}