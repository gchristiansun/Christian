#include <iostream>
using namespace std;

int main()
{
    int arr[2][2];

    int a[2][2] ={{1,2},{3,4}};
    int b[2][2] ={{1,2},{3,4}};
    int c[2][2]; 

    for (int i= 0; i < 2; i++){
        for (int j= 0; j < 2; j++){
            c[i][j] = a[i][j] + b[i][j];
            cout << c[i][j] << " "; 
        }
        cout << "\n";
    }

return 0;
}