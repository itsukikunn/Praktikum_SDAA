#include <iostream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

const int MAX_PEMAIN = 100;

struct Tim {
    struct Pemain {
        string nama;
        string posisi;
        int NoPunggung;
    };

    Pemain DataPemain[MAX_PEMAIN];
    int jumlahPemain;

    void TambahPemain() {
        if (jumlahPemain >= MAX_PEMAIN) {
            cout << "Jumlah pemain sudah mencapai batas maksimum." << endl;
            return;
        }

        Pemain PemainBaru;
        cout << "Masukkan nama pemain: ";
        getline(cin, PemainBaru.nama);

        if (PemainBaru.nama.empty()) {
            cout << "Nama pemain tidak boleh kosong." << endl;
            return;
        }

        cout << "Masukkan posisi pemain (pivot, kiper, anchor, flank): ";
        getline(cin, PemainBaru.posisi);

        if (PemainBaru.posisi != "pivot" && PemainBaru.posisi != "kiper" && PemainBaru.posisi != "anchor" && PemainBaru.posisi != "flank") {
            cout << "Posisi pemain tidak valid." << endl;
            return;
        }

        string NomorPunggung;
        cout << "Masukkan nomor pemain: ";
        getline(cin, NomorPunggung);

        stringstream ss(NomorPunggung);
        int nomorPunggung;
        if (!(ss >> nomorPunggung) || nomorPunggung <= 0) {
            cout << "Nomor punggung tidak valid." << endl;
            return;
        }
        PemainBaru.NoPunggung = nomorPunggung;

        for (int i = 0; i < jumlahPemain; ++i) {
            if (DataPemain[i].NoPunggung == PemainBaru.NoPunggung) {
                cout << "Nomor punggung tidak valid." << endl;
                return;
            }
        }

        DataPemain[jumlahPemain++] = PemainBaru;
        cout << "Pemain berhasil ditambahkan." << endl;
    }

    void LihatPemain() {
        cout << "Daftar Pemain Futsal: " << endl;
        for (int i = 0; i < jumlahPemain; ++i) {
            cout << "Nama: " << DataPemain[i].nama << ", Posisi: " << DataPemain[i].posisi << ", Nomor Punggung: " << DataPemain[i].NoPunggung << endl;
        }
    }

    void UpdatePemain() {
        string namaPemain;
        cout << "Masukkan nama pemain yang ingin diupdate: ";
        getline(cin, namaPemain);

        bool pemainDitemukan = false;
        for (int i = 0; i < jumlahPemain; ++i) {
            if (DataPemain[i].nama == namaPemain) {
                string NomorPunggung;
                cout << "Masukkan nomor punggung baru: ";
                getline(cin, NomorPunggung);

                stringstream ss(NomorPunggung);
                int nomorPunggung;
                if (!(ss >> nomorPunggung) || nomorPunggung <= 0) {
                    cout << "Nomor punggung tidak valid. Silahkan masukkan angka ." << endl;
                    return;
                }

                for (int j = 0; j < jumlahPemain; ++j) {
                    if (DataPemain[j].NoPunggung == nomorPunggung && i != j) {
                        cout << "Nomor punggung sudah digunakan oleh pemain lain. Silakan coba lagi." << endl;
                        return;
                    }
                }

                DataPemain[i].NoPunggung = nomorPunggung;

                cout << "Masukkan posisi pemain baru (pivot, kiper, anchor, flank): ";
                getline(cin, DataPemain[i].posisi);

                if (DataPemain[i].posisi != "pivot" && DataPemain[i].posisi != "kiper" && DataPemain[i].posisi != "anchor" && DataPemain[i].posisi != "flank") {
                    cout << "Posisi pemain tidak valid." << endl;
                    return;
                }

                cout << "Data pemain berhasil diupdate." << endl;
                pemainDitemukan = true;
                break;
            }
        }

        if (!pemainDitemukan) {
            cout << "Pemain dengan nama " << namaPemain << " tidak ditemukan." << endl;
        }
    }

    void HapusPemain(Pemain* pemain) { 
        bool pemainDitemukan = false;
        for (int i = 0; i < jumlahPemain; ++i) {
            if (&DataPemain[i] == pemain) {
                pemainDitemukan = true;
                for (int j = i; j < jumlahPemain - 1; ++j) {
                    DataPemain[j] = DataPemain[j + 1];
                }
                jumlahPemain--;
                cout << "Pemain " << (*pemain).nama << " berhasil dihapus." << endl; // mengakses nama pemain dengan menggunakan operator dereference
                break;
            }
        }

        if (!pemainDitemukan) {
            cout << "Pemain tidak ditemukan." << endl;
        }
    }
};

int main() {
    string username, password;
    int percobaan = 0;
    Tim tim;
    tim.jumlahPemain = 0;

    while (percobaan < 3) {
        cout << "Masukkan username anda: ";
        getline(cin, username);
        cout << "Masukkan password anda: ";
        getline(cin, password);

        if (username == "ahmad zuhair nur aiman" && password == "2309106025") {
            cout << "Anda berhasil login" << endl;
            break;
        } else {
            cout << "username atau password anda salah, silahkan coba lagi" << endl;
            percobaan++;
        }
    }

    if (percobaan == 3) {
        cout << "Terlalu banyak mencoba, program dihentikan" << endl;
        return 0;
    }
    
    int pilihan;
    while (true) {
        cout << "\nMenu CRUD Pemain:" << endl;
        cout << "1. Tambah Data Pemain " << endl;
        cout << "2. Tampilkan Data Pemain " << endl;
        cout << "3. Update Data Pemain " << endl;
        cout << "4. Hapus Data Pemain " << endl;
        cout << "5. Hentikan Program " << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tim.TambahPemain();
        } else if (pilihan == 2) {
            tim.LihatPemain();
        } else if (pilihan == 3) {
            tim.UpdatePemain();
        } else if (pilihan == 4) {
            string namaPemain;
            cout << "Masukkan nama pemain yang ingin dihapus: ";
            getline(cin, namaPemain);
            for (int i = 0; i < tim.jumlahPemain; ++i) {
                if (tim.DataPemain[i].nama == namaPemain) { 
                    tim.HapusPemain(&tim.DataPemain[i]);
                    break;
                }
        } 
        }else if (pilihan == 5) {
            cout << "Program selesai. Gacorr Ngabb " << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        }
    }
    return 0;
}