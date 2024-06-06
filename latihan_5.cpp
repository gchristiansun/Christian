#include <iostream>

using namespace std;

int main()
{
    const int baris = 2;
    const int kolom = 2;

    int arr1[baris][kolom];

    cout << "Masukan array pertama:" << endl;

    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j)
        {
            cout << "Masukan nilai array [" << i << "][" << j << "]: ";
            cin >> arr1[i][j];
        }
    }

    int arr2[baris][kolom];

    cout << "\nMasukan array kedua:" << endl;

    for (int i = 0; i < baris; ++i) {
        for (int j = 0; j < kolom; ++j)
        {
            cout << "Masukan nilai array [" << i << "][" << j << "]: ";
            cin >> arr2[i][j];
        }
    } 

    int hasil[baris][kolom];

    for (int i = 0; i < baris; ++i)
    {
        for (int j = 0; j < kolom; ++j)
        {
            hasil[i][j] = 0;
            for (int p = 0; p < kolom; ++p)
            {
                hasil[i][j] += arr1[i][p] * arr2[p][j];
            }
            
        }
    }

    cout << "\nHasil Perkalian:\n";
    for (int i = 0; i < baris; ++i)
    {
        for (int j = 0; j < kolom; ++j)
        {
            cout << hasil[i][j] << " ";
        }
        cout << endl;
    }

}