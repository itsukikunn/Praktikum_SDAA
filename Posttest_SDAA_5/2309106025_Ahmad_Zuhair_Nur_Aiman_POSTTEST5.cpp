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

    // merge sort ascending
    Pemain* merge(Pemain* kiri, Pemain* kanan) {
        if (!kiri) return kanan;
        if (!kanan) return kiri;

        if (kiri->NoPunggung < kanan->NoPunggung) {
            kiri->next = merge(kiri->next, kanan);
            return kiri;
        } else {
            kanan->next = merge(kiri, kanan->next);
            return kanan;
        }
    }

    Pemain* tukar(Pemain* head) {
        Pemain* fast = head->next;
        Pemain* slow = head;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        Pemain* temp = slow->next;
        slow->next = nullptr;
        return temp;
    }

    void mergeSort() {
        head = mergeSortUtil(head);
    }

    Pemain* mergeSortUtil(Pemain* head) {
        if (!head || !head->next) return head;

        Pemain* second = tukar(head);
        head = mergeSortUtil(head);
        second = mergeSortUtil(second);

        return merge(head, second);
    }

    // quick sort descending
    Pemain* kondisi(Pemain* low, Pemain* high) {
    int pivot = high->NoPunggung;
    Pemain* i = low;

    for (Pemain* j = low; j != high; j = j->next) {
        if (j->NoPunggung >= pivot) {
            swap(i->NoPunggung, j->NoPunggung); 
            swap(i->nama, j->nama);
            swap(i->posisi, j->posisi);
            i = i->next;                        
        }
    }

    swap(i->NoPunggung, high->NoPunggung);
    swap(i->nama, high->nama);
    swap(i->posisi, high->posisi);
    return i; 
    }

    void quickSort(Pemain* low, Pemain* high) {
        if (low != nullptr && high != nullptr && low != high && low != high->next) {
            Pemain* pivot = kondisi(low, high); 
            quickSort(low, pivot->next);
            quickSort(pivot->next, high);
        }
    }


    void sortAscending() {
        mergeSort();
    }

   void sortDescending() {
        if (head == nullptr) return;

        Pemain* last = head;
        while (last->next) last = last->next;
        quickSort(head, last);
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
        cout << "6. Urutkan Pemain Ascending (Merge Sort) " << endl;
        cout << "7. Urutkan Pemain Descending (Quick Sort) " << endl;
        cout << "8. Hentikan Program " << endl;
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
            tim.sortAscending();
            cout << "Pemain berhasil diurutkan secara ascending." << endl;
        } else if (pilihan == 7) {
            tim.sortDescending();
            cout << "Pemain berhasil diurutkan secara descending." << endl;
        } else if (pilihan == 8) {
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
