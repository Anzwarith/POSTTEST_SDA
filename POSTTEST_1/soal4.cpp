#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x, y;
    
    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;
    
    cout << "\nSebelum ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    
    swap(x, y);
    
    cout << "\nSetelah ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    
    return 0;
}