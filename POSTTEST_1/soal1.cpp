#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n/2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void reverseArray(int *arr, int size) {
    int temp;
    for (int i = 0; i < size/2; i++) {
        temp = arr[i];
        arr[i] = arr[size-1-i];
        arr[size-1-i] = temp;
    }
}

int main() {
    int arr[7];
    int num = 2;
    int count = 0;
    
   
    while (count < 7) {
        if (isPrime(num)) {
            arr[count] = num;
            count++;
        }
        num++;
    }
    
    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    reverseArray(arr, 7);
    
    cout << "Array setelah dibalik: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}