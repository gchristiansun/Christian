#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;


std::vector<string> vertex;

void tambahTempat(const string& v)
{
    for (const string&i : vertex)
    {
        if (i == v)
        {
            cout << " --> Lokasi " << v << " sudah ada" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "\033[2K"; // Menghapus baris saat ini
            cout << "\033[1A";
            cout << "                                                            " << endl;
            cout << "\033[2K"; // Menghapus baris saat ini
            cout << "\033[1A";
            return;
        }
    }
    vertex.push_back(v);
    // cout << "Vertex " << v << " ditambahkan" << endl;
}

int main()
{
    // int count = 5;
    string tempat;
    string konfirmasi;
    cout << "===========================================================================" << endl;
    cout << "                                 Isi Form                                  " << endl;
    cout << "===========================================================================" << endl;
    cout << "Ketik '<' untuk kembali atau tekan enter untuk mengakhiri input" << endl;
    while (true)
    {
        cout << "- Masukan tempat: ";
        getline(cin, tempat);

        if (tempat.empty())
        {
            cout << "\033[2K"; // Menghapus baris saat ini
            cout << "\033[1A";
            cout << "- Akhiri inputan? (y/n): ";
            getline(cin, konfirmasi);

            if (konfirmasi.empty())
            {
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
                cout << "                                                            " << endl;
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
                cout << "--> Masukan y/n" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
            }
            else if (konfirmasi == "y")
            {
                break;
            }
            else if (konfirmasi == "n")
            {
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
                cout << "                                                            " << endl;
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
            }
            else if (konfirmasi != "y" && konfirmasi != "n")
            {
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
                cout << "                                                            " << endl;
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
                cout << "--> Masukan y/n" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                cout << "\033[2K"; // Menghapus baris saat ini
                cout << "\033[1A";
            }
            
        }
        else if (tempat != "<")
        {
            tambahTempat(tempat);
        }
        else if (tempat == "<")
        {
            break;
        }
    }
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Lokasi "; 
    for (size_t i = 0; i < vertex.size(); ++i)
    {
        cout << vertex[i];
        if (i < vertex.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " telah ditambahkan ke vertex" << endl;

    cout << endl;

    cout << "===========================================================================" << endl;
    cout << "                           Tempat yang ditambahkan:                        " << endl;
    cout << "===========================================================================" << endl;
    for (const string&i : vertex) {
        cout << "- " << i << endl;
    }

    return 0;
}
