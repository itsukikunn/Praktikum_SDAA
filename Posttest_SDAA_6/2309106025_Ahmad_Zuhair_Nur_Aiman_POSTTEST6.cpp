#include <iostream>
#include <string>
#include <limits>
#include <cmath>
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
        Pemain* high = head;
        if (!high) return;

        while (high->next) {
            high = high->next;
        }

        quickSort(head, high);
    }

   int fibonacciSearch(Pemain* head, int NoPunggung) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    int n = 0;
    Pemain* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        Pemain* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        if (temp->NoPunggung < NoPunggung) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->NoPunggung > NoPunggung) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            return i;
        }
    }
    Pemain* lastNode = head;
    for (int j = 0; j < offset + 1; j++) {
        lastNode = lastNode->next;
    }

    if (fibMMm1 == 1 && lastNode != nullptr && lastNode->NoPunggung == NoPunggung) {
        return offset + 1;
    }
        return -1;
    }
    
int jumpSearch(Pemain* head, int NoPunggung) {
    int n = 0;
    Pemain* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }
    int step = sqrt(n);
    Pemain* prev = nullptr;
    current = head;
    int count = 0;
    while (current != nullptr && current->NoPunggung < NoPunggung) {
        prev = current;
        for (int i = 0; i < step && current != nullptr; i++) {
            current = current->next;
            count++;
        }
    }
    while (prev != nullptr && prev->NoPunggung < NoPunggung) {
        prev = prev->next;
        count++;
    }
    if (prev != nullptr && prev->NoPunggung == NoPunggung) {
        return count - 1;
    }
        return -1;
    }

   void badCharHeuristic(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
    }

    int boyerMooreSearch(string txt, string pat) {
        int m = pat.size();
        int n = txt.size();

        int badchar[256];

        badCharHeuristic(pat, m, badchar);

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pat[j] == txt[s + j])
                j--;

            if (j < 0) {
                return s;
                s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            } else {
                s += max(1, j - badchar[txt[s + j]]);
            }
        }

        return -1;
    }

    void cariNoPunggungFibonacci(int nomor) {
    int result = fibonacciSearch(head, nomor);
    if (result != -1) {
        cout << "Pemain dengan nomor punggung " << nomor << " ditemukan." << endl;
    } else {
        cout << "Pemain dengan nomor punggung " << nomor << " tidak ditemukan." << endl;
        }
    }

    void cariNoPunggungJump(int nomor) {
        int result = jumpSearch(head, nomor);
        if (result != -1) {
            cout << "Pemain dengan nomor punggung " << nomor << " ditemukan." << endl;
        } else {
            cout << "Pemain dengan nomor punggung " << nomor << " tidak ditemukan." << endl;
        }
    }

    void cariNama(string nama) {
        Pemain* current = head;
        while (current != nullptr) {
            if (boyerMooreSearch(current->nama, nama) != -1) {
                cout << "Pemain dengan nama " << nama << " ditemukan." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Pemain dengan nama " << nama << " tidak ditemukan." << endl;
    }

    void Sorting() {
        int pilihan;
        cout << "Pilih metode pengurutan: \n1. Merge Sort\n2. Quick Sort\nPilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            mergeSort();
            cout << "Pemain diurutkan secara ascending berdasarkan nomor punggung." << endl;
        } else if (pilihan == 2) {
            if (head == nullptr) {
                cout << "Tidak ada pemain untuk diurutkan." << endl;
                return;
            }
            Pemain* high = head;
            while (high->next) {
                high = high->next;
            }
            quickSort(head, high);
            cout << "Pemain diurutkan secara descending berdasarkan nomor punggung." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    void Searching() {
    int pilihan;
    cout << "Pilih metode pencarian: \n1. Fibonacci Search (Nomor Punggung)\n2. Jump Search (Nomor Punggung)\n3. Boyer-Moore Search (Nama Pemain)\nPilihan: ";
    cin >> pilihan;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilihan) {
        case 1: {
            int noPunggung;
            cout << "Masukkan nomor punggung pemain yang ingin dicari: ";
            cin >> noPunggung;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cariNoPunggungFibonacci(noPunggung);
            break;
        }
        case 2: {
            int noPunggung;
            cout << "Masukkan nomor punggung pemain yang ingin dicari: ";
            cin >> noPunggung;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cariNoPunggungJump(noPunggung);
            break;
        }
        case 3: {
            string name;
            cout << "Masukkan nama pemain yang ingin dicari: ";
            getline(cin, name);
            cariNama(name);
            break;
        }
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
    }
    }       
};

int main() {
    Tim tim;
    int pilihan;

    do {
        cout << "Menu: " << endl;
        cout << "1. Tambah Pemain" << endl;
        cout << "2. Lihat Pemain" << endl;
        cout << "3. Hapus Pemain" << endl;
        cout << "4. Lihat Stack" << endl;
        cout << "5. Lihat Queue" << endl;
        cout << "6. Urutkan Data Pemain" << endl;
        cout << "7. Cari Pemain" << endl;
        cout << "8. Keluar" << endl;

        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                tim.TambahPemain();
                break;
            case 2:
                tim.LihatPemain();
                break;
            case 3:
                tim.HapusPemain();
                break;
            case 4:
                tim.LihatStack();
                break;
            case 5:
                tim.LihatQueue();
                break;
            case 6:
                tim.Sorting();
                break;
            case 7:
                tim.Searching();
                break;
            case 8:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (pilihan != 8);

    return 0;
};