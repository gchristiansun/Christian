#include <iostream>
#include <string>

using namespace std;

int main() 
{
    const int baris = 2;
    const int kolom = 3;

    string arr[baris][kolom];

    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j)
        {
            cout << "Masukan nilai array: [" << i << "][" << j << "]: ";
            cin >> arr[i][j];
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

    return 0;
}
