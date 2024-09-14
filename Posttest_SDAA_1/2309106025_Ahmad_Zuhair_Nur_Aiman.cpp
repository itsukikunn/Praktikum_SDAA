#include <iostream>
#include <string>
using namespace std;

void hanoi(int i, string asal, string tujuan, string sementara) {
    if (i == 1) {
        cout << "Pindahkan piringan 1 dari menara " << asal << " ke menara " << tujuan << endl;
        return;
    }
    
    hanoi(i - 1, asal, sementara, tujuan);
    cout << "Pindahkan piringan " << i << " dari menara " << asal << " ke menara " << tujuan << endl;
    hanoi(i - 1, sementara, tujuan, asal);
}

int main() {
    int jumlah_piringan = 3;
    string menara[] = {"Asal", "Sementara", "Tujuan"};
    hanoi(jumlah_piringan, menara[0], menara[2], menara[1]);
    
    return 0;
}