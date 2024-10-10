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

struct StackNode {
    Pemain* pemain;
    StackNode* next;
};

struct Stack {
    StackNode* top;

    Stack() {
        top = nullptr;
    }

    void push(Pemain* pemain) {
        StackNode* Nodebaru = new StackNode;
        Nodebaru->pemain = pemain;
        Nodebaru->next = top;
        top = Nodebaru;
        cout << "Pemain " << pemain->nama << " dimasukkan ke stack." << endl;
    }

    Pemain* pop() {
        if (top == nullptr) {
            cout << "Stack kosong, tidak ada pemain yang dapat diambil." << endl;
            return nullptr;
        }
        Pemain* pemain = top->pemain;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return pemain;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

struct QueueNode {
    Pemain* pemain;
    QueueNode* next;
};

struct Queue {
    QueueNode* awal;
    QueueNode* akhir;

    Queue() {
        awal = nullptr;
        akhir = nullptr;
    }

    void queue(Pemain* pemain) {
        QueueNode* Nodebaru = new QueueNode;
        Nodebaru->pemain = pemain;
        Nodebaru->next = nullptr;
        if (akhir == nullptr) {
            awal = akhir = Nodebaru;
        } else {
            akhir->next = Nodebaru;
            akhir = Nodebaru;
        }
        cout << "Pemain " << pemain->nama << " dimasukkan ke queue." << endl;
    }

    Pemain* dequeue() {
        if (awal == nullptr) {
            cout << "Queue kosong, tidak ada pemain yang dapat diambil." << endl;
            return nullptr;
        }
        Pemain* pemain = awal->pemain;
        QueueNode* temp = awal;
        awal = awal->next;
        if (awal == nullptr) {
            akhir = nullptr;
        }
        delete temp;
        return pemain;
    }

    bool isEmpty() {
        return awal == nullptr;
    }
};

struct Tim {
    Pemain* head;
    Stack stackPemain;
    Queue queuePemain;

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

        // Masukkan pemain ke dalam queue
        queuePemain.queue(PemainBaru);

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

                // Masukkan pemain yang dihapus ke stack
                stackPemain.push(current);

                cout << "Pemain " << namaPemain << " berhasil dihapus." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Pemain dengan nama " << namaPemain << " tidak ditemukan." << endl;
    }

    void LihatStack() {
        if (stackPemain.isEmpty()) {
            cout << "Stack kosong." << endl;
        } else {
            StackNode* current = stackPemain.top;
            cout << "Daftar Pemain di Stack (yang dihapus): " << endl;
            while (current != nullptr) {
                cout << "Nama: " << current->pemain->nama << ", Posisi: " << current->pemain->posisi << ", Nomor Punggung: " << current->pemain->NoPunggung << endl;
                current = current->next;
            }
        }
    }

    void LihatQueue() {
        if (queuePemain.isEmpty()) {
            cout << "Queue kosong." << endl;
        } else {
            QueueNode* current = queuePemain.awal;
            cout << "Daftar Pemain di Queue (yang ditambahkan): " << endl;
            while (current != nullptr) {
                cout << "Nama: " << current->pemain->nama << ", Posisi: " << current->pemain->posisi << ", Nomor Punggung: " << current->pemain->NoPunggung << endl;
                current = current->next;
            }
        }
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
        cout << "3. Hapus Data Pemain " << endl;
        cout << "4. Lihat Stack Pemain Dihapus " << endl;
        cout << "5. Lihat Queue Pemain Ditambahkan " << endl;
        cout << "6. Hentikan Program " << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tim.TambahPemain();
        } else if (pilihan == 2) {
            tim.LihatPemain();
        } else if (pilihan == 3) {
            tim.HapusPemain();
        } else if (pilihan == 4) {
            tim.LihatStack();
        } else if (pilihan == 5) {
            tim.LihatQueue();
        } else if (pilihan == 6) {
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
