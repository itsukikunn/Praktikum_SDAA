#include <iostream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

struct Pemain {
    string nama;
    string posisi;
    int NoPunggung;
    Pemain* next;
};

struct Tim {
    Pemain* head;

    Tim() {
        head = nullptr;
    }

    void TambahPemain() {
        Pemain* PemainBaru = new Pemain;
        cout << "Masukkan nama pemain: ";
        getline(cin, PemainBaru->nama);

        if (PemainBaru->nama.empty()) {
            cout << "Nama pemain tidak boleh kosong." << endl;
            delete PemainBaru;
            return;
        }

        cout << "Masukkan posisi pemain (pivot, kiper, anchor, flank): ";
        getline(cin, PemainBaru->posisi);

        if (PemainBaru->posisi != "pivot" && PemainBaru->posisi != "kiper" && PemainBaru->posisi != "anchor" && PemainBaru->posisi != "flank") {
            cout << "Posisi pemain tidak valid." << endl;
            delete PemainBaru;
            return;
        }

        string NomorPunggung;
        cout << "Masukkan nomor pemain: ";
        getline(cin, NomorPunggung);

        stringstream ss(NomorPunggung);
        int nomorPunggung;
        if (!(ss >> nomorPunggung) || nomorPunggung <= 0) {
            cout << "Nomor punggung tidak valid." << endl;
            delete PemainBaru;
            return;
        }

        Pemain* current = head;
        while (current != nullptr) {
            if (current->NoPunggung == nomorPunggung) {
                cout << "Nomor punggung sudah digunakan." << endl;
                delete PemainBaru;
                return;
            }
            current = current->next;
        }

        PemainBaru->NoPunggung = nomorPunggung;
        PemainBaru->next = head;
        head = PemainBaru;

        cout << "Pemain berhasil ditambahkan." << endl;
    }

    void LihatPemain() {
        if (head == nullptr) {
            cout << "Belum ada pemain yang ditambahkan." << endl;
            return;
        }

        Pemain* current = head;
        cout << "Daftar Pemain Futsal: " << endl;
        while (current != nullptr) {
            cout << "Nama: " << current->nama << ", Posisi: " << current->posisi << ", Nomor Punggung: " << current->NoPunggung << endl;
            current = current->next;
        }
    }

    void UpdatePemain() {
        string namaPemain;
        cout << "Masukkan nama pemain yang ingin diupdate: ";
        getline(cin, namaPemain);

        Pemain* current = head;
        bool pemainDitemukan = false;

        while (current != nullptr) {
            if (current->nama == namaPemain) {
                string NomorPunggung;
                cout << "Masukkan nomor punggung baru: ";
                getline(cin, NomorPunggung);

                stringstream ss(NomorPunggung);
                int nomorPunggung;
                if (!(ss >> nomorPunggung) || nomorPunggung <= 0) {
                    cout << "Nomor punggung tidak valid." << endl;
                    return;
                }

                Pemain* temp = head;
                while (temp != nullptr) {
                    if (temp->NoPunggung == nomorPunggung && temp != current) {
                        cout << "Nomor punggung sudah digunakan oleh pemain lain." << endl;
                        return;
                    }
                    temp = temp->next;
                }

                current->NoPunggung = nomorPunggung;

                cout << "Masukkan posisi pemain baru (pivot, kiper, anchor, flank): ";
                getline(cin, current->posisi);

                if (current->posisi != "pivot" && current->posisi != "kiper" && current->posisi != "anchor" && current->posisi != "flank") {
                    cout << "Posisi pemain tidak valid." << endl;
                    return;
                }

                cout << "Data pemain berhasil diupdate." << endl;
                pemainDitemukan = true;
                break;
            }
            current = current->next;
        }

        if (!pemainDitemukan) {
            cout << "Pemain dengan nama " << namaPemain << " tidak ditemukan." << endl;
        }
    }

    void HapusPemain() {
        string namaPemain;
        cout << "Masukkan nama pemain yang ingin dihapus: ";
        getline(cin, namaPemain);

        Pemain* current = head;
        Pemain* prev = nullptr;

        while (current != nullptr) {
            if (current->nama == namaPemain) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Pemain " << namaPemain << " berhasil dihapus." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Pemain dengan nama " << namaPemain << " tidak ditemukan." << endl;
    }
};

int main() {
    string username, password;
    int percobaan = 0;
    Tim tim;

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
            tim.HapusPemain();
        } else if (pilihan == 5) {
            cout << "Program selesai." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
