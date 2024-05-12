#include <iostream>
#include "catering.h"
using namespace std;

void createListAcara(listAcara &L){
    first(L) = NULL;
    last(L) = NULL;
}

void createListMenu(listMenu &L){
    first(L) = NULL;
}

void createListRelasi(listRelasi &L){
    first(L) = NULL;
    last(L) = NULL;
}

adrAcara alokasiAcara(infotypeAcara x){
    adrAcara P = new elmAcara;
    info(P) = x;
    info(P).totalHarga = 0;
    next(P) = NULL;
    prev(P) = NULL;

    listRelasi LRelasi;
    createListRelasi(LRelasi);
    menuAcara(P) = LRelasi;

    return P;
}

adrMenu alokasiMenu(infotypeMenu x){
    adrMenu P = new elmMenu;
    info(P) = x;
    next(P) = NULL;

    return P;
}

adrRelasi alokasiRelasi(adrMenu x){
    adrRelasi P = new elmRelasi;
    nextMenu(P) = x;
    next(P) = NULL;

    return P;
}

void dealokasiAcara(adrAcara &P){
    delete(P);
}

void dealokasiMenu(adrMenu &P){
    delete(P);
}

void dealokasiRelasi(adrRelasi &P){
    delete(P);
}

void insertAcara(listAcara &L, adrAcara P){
    if((first(L) == NULL) && (last(L) == NULL)){
        first(L) = P;
        last(L) = P;
    }else{
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    }
}

void insertMenu(listMenu &L, adrMenu P){
    if(first(L) == NULL){
        first(L) = P;
    }else{
        next(P) = first(L);
        first(L) = P;
    }
}

void insertRelasi(listAcara &LAcara, listMenu LMenu, string namaAcara, string namaMenu){
    adrAcara P;
    adrMenu Q;
    adrRelasi R, S;
    bool found = false;

    P = findAcara(LAcara, namaAcara);
    Q = findMenu(LMenu, namaMenu);

    if((P != NULL) && (Q != NULL)){
        S = first(menuAcara(P));
        while(S != NULL){
            if(info(nextMenu(S)).namaMenu == info(Q).namaMenu){
                found = true;
            }
            S = next(S);
        }

        if(found == false){
            R = alokasiRelasi(Q);
            info(P).totalHarga = info(P).totalHarga + (info(P).porsiDipesan * info(nextMenu(R)).hargaMenu);
            if((first(menuAcara(P)) == NULL) && (last(menuAcara(P)) == NULL)){
                first(menuAcara(P)) = R;
                last(menuAcara(P)) = R;
            }else{
                next(R) = first(menuAcara(P));
                prev(first(menuAcara(P))) = R;
                first(menuAcara(P)) = R;
            }
        }else{
            cout << "Menu " << namaMenu << " sudah ada pada acara " << namaAcara << "!" << endl;
        }

    }else{
        cout << "Acara atau Menu tidak ditemukan!" << endl;
    }
}

void deleteAcara(listAcara &L, string namaAcara){
    adrAcara P, R;
    adrRelasi Q;

    P = findAcara(L, namaAcara);

    if(P != NULL){
        while(first(menuAcara(P)) != NULL){
            Q = first(menuAcara(P));
            if(first(menuAcara(P)) != last(menuAcara(P))){
                first(menuAcara(P)) = next(Q);
                next(Q) = NULL;
                prev(first(menuAcara(P))) = NULL;
            }else{
                first(menuAcara(P)) = NULL;
                last(menuAcara(P)) = NULL;
            }
            dealokasiRelasi(Q);
            Q = next(Q);
        }

        if(first(L) != last(L)){
            if(P == first(L)){
                first(L) = next(P);
                prev(first(L)) = NULL;
                next(P) = NULL;
            }else if(P == last(L)){
                last(L) = prev(P);
                next(last(L)) = NULL;
                prev(P) = NULL;
            }else{
                R = prev(P);
                next(R) = next(P);
                prev(next(P)) = R;
                next(P) = NULL;
                prev(P) = NULL;
            }
        }else{
            first(L) = NULL;
            last(L) = NULL;
        }

        dealokasiAcara(P);
        cout << "Acara " << namaAcara << " berhasil dihapus!" << endl;
    }else{
        cout << "Acara " << namaAcara << " tidak ditemukan!" << endl;
    }
}

void deleteMenu(listAcara &LAcara, listMenu &LMenu, string namaMenu){
    adrAcara P;
    adrMenu Q, S;
    adrRelasi R;

    Q = findMenu(LMenu, namaMenu);

    if(Q != NULL){
        P = first(LAcara);
        while(P != NULL){
            cout << info(P).namaAcara << endl;
            R = findRelasi(LAcara, info(P).namaAcara, info(Q).namaMenu);
            if(R != NULL){
                deleteRelasi(LAcara, info(P).namaAcara, info(Q).namaMenu);
            }
            P = next(P);
        }

        if(next(first(LMenu)) == NULL){
            first(LMenu) = NULL;
        }else if(Q == first(LMenu)){
            first(LMenu) = next(Q);
            next(Q) = NULL;
        }else if(next(Q) == NULL){
            S = first(LMenu);
            while(next(next(S)) != NULL){
                S = next(S);
            }
            next(S) = NULL;
        }else{
            S = first(LMenu);
            while(info(next(S)).namaMenu != info(Q).namaMenu){
                S = next(S);
            }
            next(S) = next(Q);
            next(Q) = NULL;
        }

        dealokasiMenu(Q);
        cout << "Menu " << namaMenu << " berhasil dihapus!" << endl;

    }else{
        cout << "Menu " << namaMenu << " tidak ditemukan!" << endl;
    }
}

void deleteRelasi(listAcara &L, string namaAcara, string namaMenu){
    adrAcara P;
    adrRelasi Q, R;

    P = findAcara(L, namaAcara);
    Q = findRelasi(L, namaAcara, namaMenu);

    if((P != NULL) && (Q != NULL)){
        info(P).totalHarga = info(P).totalHarga - (info(P).porsiDipesan * info(nextMenu(Q)).hargaMenu);
        nextMenu(Q) = NULL;
        if(first(menuAcara(P)) != last(menuAcara(P))){
            if(Q == first(menuAcara(P))){
                first(menuAcara(P)) = next(Q);
                next(Q) = NULL;
                prev(first(menuAcara(P))) = NULL;
            }else if(Q == last(menuAcara(P))){
                last(menuAcara(P)) = prev(Q);
                next(last(menuAcara(P))) = NULL;
                prev(Q) = NULL;
            }else{
                R = prev(Q);
                next(R) = next(Q);
                prev(next(Q)) = R;
                next(Q) = NULL;
                prev(Q) = NULL;
            }
        }
        dealokasiRelasi(Q);

        cout << "Menu " << namaMenu << " pada acara " << namaAcara << " berhasil dihapus!" << endl;
    }else if((P == NULL) && (Q == NULL)){
        cout << "Acara " << namaAcara << " dan menu " << namaMenu << " tidak ditemukan!" << endl << endl;
    }else if(P == NULL){
        cout << "Acara " << namaAcara << " tidak ditemukan!" << endl << endl;
    }else if(Q == NULL){
        cout << "Menu " << namaMenu << " pada acara " << namaAcara << " tidak ditemukan!" << endl << endl;
    }
}

adrAcara findAcara(listAcara L, string namaAcara){
    adrAcara Q = first(L);
    while(Q != NULL){
        if(info(Q).namaAcara == namaAcara){
            return Q;
        }else{
            Q = next(Q);
        }
    }
}

adrMenu findMenu(listMenu L, string namaMenu){
    adrMenu P, Q;
    Q = first(L);
    while(Q != NULL){
        if(info(Q).namaMenu == namaMenu){
            return Q;
        }else{
            Q = next(Q);
        }
    }
}

adrRelasi findRelasi(listAcara L, string namaAcara, string namaMenu){
    adrRelasi Q;
    adrAcara P = findAcara(L, namaAcara);

    if(P != NULL){
        if(first(menuAcara(P)) != NULL){
            Q = first(menuAcara(P));
            while(Q != NULL){
                if(info(nextMenu(Q)).namaMenu == namaMenu){
                    return Q;
                }else{
                    Q = next(Q);
                }
            }
        }
    }else{
        return NULL;
    }

}

void showAcara(listAcara L){
    adrAcara P = first(L);

    if(first(L) != NULL){
        cout << "========== LIST ACARA ===========" << endl;
        while(P != NULL){
            cout << "Nama Acara : " << info(P).namaAcara << endl;
            cout << "Tanggal Acara : " << info(P).tanggalAcara << endl;
            cout << "Porsi Dipesan : " << info(P).porsiDipesan << endl;
            cout << "Total Harga : " << info(P).totalHarga << endl;

            P = next(P);
        }
        cout << endl;
    }else{
        cout << "List Kosong!" << endl;
    }
}

void showMenu(listMenu L){
    adrMenu P = first(L);

    if(first(L) != NULL){
        cout << "========== LIST MENU ===========" << endl;
        while(P != NULL){
            cout << "Nama Menu : " << info(P).namaMenu << endl;
            cout << "Jenis Menu : " << info(P).jenisMenu << endl;
            cout << "Harga Menu : " << info(P).hargaMenu << endl;

            P = next(P);
        }
        cout << endl;
    }else{
        cout << "List Kosong!" << endl;
    }

}

void showAllAcaraMenu(listAcara L){
    adrAcara P = first(L);
    adrRelasi Q;

    if(first(L) != NULL){
        cout << "========== LIST MENU PADA ACARA ===========" << endl;
        while(P != NULL){
            cout << "Nama Acara : " << info(P).namaAcara << endl;
            cout << "Tanggal Acara : " << info(P).tanggalAcara << endl;
            cout << "Porsi Dipesan : " << info(P).porsiDipesan << endl;
            cout << "Total Harga : " << info(P).totalHarga << endl << endl;
            if(first(menuAcara(P)) != NULL){
                Q = first(menuAcara(P));
                while(Q != NULL){
                    cout << "Nama Menu : " << info(nextMenu(Q)).namaMenu << endl;
                    cout << "Jenis Menu : " << info(nextMenu(Q)).jenisMenu << endl;
                    cout << "Harga Menu : " << info(nextMenu(Q)).hargaMenu << endl;

                    Q = next(Q);
                }
                cout << endl;
            }else{
                cout << "Parent ini tidak memiliki child" << endl;
            }
            cout << endl;

            P = next(P);
        }
    }else{
        cout << "List Kosong!" << endl;
    }

}

adrMenu mostSoldMenu(listAcara LAcara, listMenu LMenu){
    adrAcara P;
    adrMenu Q, mostMenu;
    adrRelasi R;
    int temp, mostCount;

    mostCount = 0;
    Q = first(LMenu);
    while(Q != NULL){
        temp = 0;
        P = first(LAcara);
        while(P != NULL){
            R = first(menuAcara(P));
            while(R != NULL){
                if(info(nextMenu(R)).namaMenu == info(Q).namaMenu){
                    temp = temp + 1;
                }
                R = next(R);
            }
            P = next(P);
        }
        if(temp > mostCount){
            mostCount = temp;
            mostMenu = Q;
        }
        Q = next(Q);
    }

    return mostMenu;

}

int countRelasi(listAcara L, string namaAcara){
    adrAcara P;
    adrRelasi Q;
    int jumlah = 0;

    P = findAcara(L, namaAcara);
    if(P != NULL){
        if(first(menuAcara(P)) != NULL){
            Q = first(menuAcara(P));
            while(Q != NULL){
                jumlah = jumlah + 1;
                Q = next(Q);
            }
        }

        return jumlah;
    }else{
        return -1;
    }

}

int fitur(){
    int input;

    cout << endl << "=============== APLIKASI CATERING-U ===============" << endl;
    cout << "1. Tambah Acara" << endl;
    cout << "2. Tambah Menu" << endl;
    cout << "3. Tambah Menu ke Acara" << endl;
    cout << "4. Hapus Acara" << endl;
    cout << "5. Hapus Menu" << endl;
    cout << "6. Hapus Menu dari Acara" << endl;
    cout << "7. Cari Acara" << endl;
    cout << "8. Cari Menu" << endl;
    cout << "9. Cari Menu di Acara" << endl;
    cout << "10. Tampilkan Acara" << endl;
    cout << "11. Tampilkan Menu" << endl;
    cout << "12. Tampilkan Menu dari Acara" << endl;
    cout << "13. Tampilkan Menu yang paling banyak dipesan" << endl;
    cout << "14. Hitung Menu di Acara" << endl;
    cout << "0. Keluar" << endl;
    cout << "===================================================" << endl;

    cout << "Masukan pilihan : ";
    cin >> input;
    cout << endl;

    return input;
}
