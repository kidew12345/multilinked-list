#include <iostream>
#include <string>

using namespace std;

// Definisi tipe data
struct elm_jual {
    int info;
    elm_jual* Next;
};

struct sales {
    string nama;
    string gol;
};

struct elm_sales {
    sales info;
    elm_sales* Next;
    elm_jual* nextJual;
};

struct mll {
    elm_sales* First;
};

typedef elm_jual* adr_jual;
typedef elm_sales* adr_sales;

// Fungsi mencari sales berdasarkan nama
adr_sales Search_Sales(mll List_Sales, string nama_Sales) {
    adr_sales P = List_Sales.First;
    while (P != nullptr && P->info.nama != nama_Sales) {
        P = P->Next;
    }
    return P;
}

// Prosedur untuk menambahkan sales pada bagian akhir list
void insert_last_Sales(mll& List_Sales, adr_sales S) {
    if (List_Sales.First == nullptr) {
        List_Sales.First = S;
    } else {
        adr_sales P = List_Sales.First;
        while (P->Next != nullptr) {
            P = P->Next;
        }
        P->Next = S;
    }
}

// Prosedur untuk menghapus penjualan kurang dari 3
void deletePenjualanKurangDariTiga(adr_jual& First) {
    adr_jual P = First;
    adr_jual Prec = nullptr;

    while (P != nullptr) {
        if (P->info < 3) {
            if (Prec == nullptr) {
                // Pada elemen pertama
                First = P->Next;
            } else {
                Prec->Next = P->Next;
            }

            delete P;
            P = Prec->Next;
        } else {
            Prec = P;
            P = P->Next;
        }
    }
}

int main() {
    // Contoh penggunaan
    mll List_Sales;
    List_Sales.First = nullptr;

    // Menambahkan sales A ke dalam list
    adr_sales SA = new elm_sales;
    SA->info.nama = "Siska";
    SA->info.gol = "Golongan A";
    SA->Next = nullptr;
    SA->nextJual = nullptr;

    // Menambahkan informasi penjualan untuk Sales A
    adr_jual JA1 = new elm_jual;
    JA1->info = 5;  // Penjualan bulan 1
    JA1->Next = nullptr;
    SA->nextJual = JA1;

    adr_jual JA2 = new elm_jual;
    JA2->info = 3;  // Penjualan bulan 2
    JA2->Next = nullptr;
    JA1->Next = JA2;

    adr_jual JA3 = new elm_jual;
    JA3->info = 4;  // Penjualan bulan 3
    JA3->Next = nullptr;
    JA2->Next = JA3;

    adr_jual JA4 = new elm_jual;
    JA4->info = 2;  // Penjualan bulan 4
    JA4->Next = nullptr;
    JA3->Next = JA4;

    deletePenjualanKurangDariTiga(SA->nextJual);

    insert_last_Sales(List_Sales, SA);

    // Menambahkan sales B ke dalam list
    adr_sales SB = new elm_sales;
    SB->info.nama = "Affan";
    SB->info.gol = "Golongan C";
    SB->Next = nullptr;
    SB->nextJual = nullptr;

    // Menambahkan informasi penjualan untuk Sales B
    adr_jual JB1 = new elm_jual;
    JB1->info = 4;  // Penjualan bulan 1
    JB1->Next = nullptr;
    SB->nextJual = JB1;

    adr_jual JB2 = new elm_jual;
    JB2->info = 3;  // Penjualan bulan 2
    JB2->Next = nullptr;
    JB1->Next = JB2;

    // Tidak ada informasi penjualan untuk bulan 3 pada Sales B dalam contoh ini

    deletePenjualanKurangDariTiga(SB->nextJual);

    insert_last_Sales(List_Sales, SB);

    // Menampilkan list sales beserta informasi penjualan
    adr_sales P = List_Sales.First;
    while (P != nullptr) {
        cout << "Nama Sales: " << P->info.nama << ", Gol: " << P->info.gol;
        cout << ", Penjualan: {";
        adr_jual J = P->nextJual;
        while (J != nullptr) {
            cout << J->info;
            if (J->Next != nullptr) {
                cout << ", ";
            }
            J = J->Next;
        }
        cout << "}" << endl;

        P = P->Next;
    }

    // Hapus semua node untuk menghindari memory leak
    P = List_Sales.First;
    while (P != nullptr) {
        adr_sales tempS = P;
        P = P->Next;

        adr_jual tempJ = tempS->nextJual;
        while (tempJ != nullptr) {
            adr_jual delJ = tempJ;
            tempJ = tempJ->Next;
            delete delJ;
        }

        delete tempS;
    }

    return 0;
}
