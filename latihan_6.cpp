#include <iostream>
#include <string>
using namespace std;

int main() {
    const int baris = 2;
    const int kolom = 3;

    string arr[baris][kolom];
    string nilai_maksimum;

    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j) {
            cout << "Masukkan nilai array [" << i << "][" << j << "]: ";
            cin >> arr[i][j];

            // Membandingkan dengan nilai maksimum yang telah ditemukan
            if (nilai_maksimum.empty() || arr[i][j] > nilai_maksimum) {
                nilai_maksimum = arr[i][j];
            }
        }
    }

    // Mencetak array dengan nama yang dimasukkan
    cout << "\nNilai array 2 × 3 adalah:\n";
    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Nilai maksimum yang dimasukkan adalah: " << nilai_maksimum << endl;

    return 0;
}
