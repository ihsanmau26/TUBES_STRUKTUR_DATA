#include <iostream>
#include "catering.h"
using namespace std;

int main()
{
    listAcara LAcara;
    createListAcara(LAcara);

    listMenu LMenu;
    createListMenu(LMenu);

    int i, N, pilihan;
    infotypeAcara x1;
    infotypeMenu x2;
    adrAcara P;
    adrMenu Q;
    adrRelasi R;
    string acara, menu;

    pilihan = fitur();
    while(pilihan != 0){
        switch(pilihan){
            case 1:
                cout << "Berapa banyak acara yang ingin dimasukkan? : ";
                cin >> N;
                for(i = 0; i < N; i++){
                    cout << "Nama Acara : ";
                    cin >> x1.namaAcara;
                    cout << "Tanggal Acara : ";
                    cin >> x1.tanggalAcara;
                    cout << "Porsi Dipesan : ";
                    cin >> x1.porsiDipesan;

                    P = alokasiAcara(x1);
                    insertAcara(LAcara, P);
                }

                pilihan = fitur();
            break;

            case 2:
                cout << "Berapa banyak menu yang ingin dimasukkan? : ";
                cin >> N;
                for(i = 0; i < N; i++){
                    cout << "Nama Menu : ";
                    cin >> x2.namaMenu;
                    cout << "Jenis Menu : ";
                    cin >> x2.jenisMenu;
                    cout << "Harga Menu : ";
                    cin >> x2.hargaMenu;

                    Q = alokasiMenu(x2);
                    insertMenu(LMenu, Q);
                }

                pilihan = fitur();
            break;

            case 3:
                cout << "Nama acara yang ingin diinputkan menu? : ";
                cin >> acara;
                cout << "Berapa menu yang ingin diinputkan? : ";
                cin >> N;
                for(i = 0; i < N; i++){
                    cout << "Menu yang ingin diinputkan keacara " << acara << " : ";
                    cin >> menu;

                    insertRelasi(LAcara, LMenu, acara, menu);
                }

                pilihan = fitur();
            break;

            case 4:
                cout << "Nama acara yang ingin dihapus? : ";
                cin >> acara;
                deleteAcara(LAcara, acara);

                pilihan = fitur();
            break;

            case 5:
                cout << "Nama menu yang ingin dihapus? : ";
                cin >> menu;
                deleteMenu(LAcara, LMenu, menu);

                pilihan = fitur();
            break;

            case 6:
                cout << "Nama acara yang ingin dihapus menunya? : ";
                cin >> acara;
                cout << "Nama menu yang ingin dihapus dari acara " << acara << "? : ";
                cin >> menu;
                deleteRelasi(LAcara, acara, menu);

                pilihan = fitur();
            break;

            case 7:
                cout << "Nama acara yang ingin dicari? : ";
                cin >> acara;
                P = findAcara(LAcara, acara);
                if(P != NULL){
                    cout << "Nama Acara : " << info(P).namaAcara << endl;
                    cout << "Tanggal Acara : " << info(P).tanggalAcara << endl;
                    cout << "Porsi Dipesan : " << info(P).porsiDipesan << endl;
                    cout << "Total Harga : " << info(P).totalHarga << endl;
                }else{
                    cout << "Acara " << acara << " tidak ditemukan!" << endl;
                }

                pilihan = fitur();
            break;

            case 8:
                cout << "Nama menu yang ingin dicari? : ";
                cin >> menu;
                Q = findMenu(LMenu, menu);
                if(Q != NULL){
                    cout << "Nama Menu : " << info(Q).namaMenu << endl;
                    cout << "Jenis Menu : " << info(Q).jenisMenu << endl;
                    cout << "Harga Menu : " << info(Q).hargaMenu << endl;
                }else{
                    cout << "Menu " << menu << " tidak ditemukan!" << endl;
                }

                pilihan = fitur();
            break;

            case 9:
                cout << "Nama acara yang ingin dicari? : ";
                cin >> acara;
                cout << "Nama menu yang ingin dicari? : ";
                cin >> menu;
                P = findAcara(LAcara, acara);
                R = findRelasi(LAcara, acara, menu);
                if((P != NULL) && (R != NULL)){
                    cout << "Nama Acara : " << info(P).namaAcara << endl;
                    cout << "Tanggal Acara : " << info(P).tanggalAcara << endl;
                    cout << "Porsi Dipesan : " << info(P).porsiDipesan << endl;
                    cout << "Total Harga : " << info(P).totalHarga << endl;
                    cout << "Nama Menu : " << info(nextMenu(R)).namaMenu << endl;
                    cout << "Jenis Menu : " << info(nextMenu(R)).jenisMenu << endl;
                    cout << "Harga Menu : " << info(nextMenu(R)).hargaMenu << endl << endl;
                }else if((P == NULL) && (R == NULL)){
                    cout << "Acara " << acara << " dan menu " << menu << " tidak ditemukan!" << endl << endl;
                }else if(P == NULL){
                    cout << "Acara " << acara << " tidak ditemukan!" << endl << endl;
                }else if(R == NULL){
                    cout << "Menu " << menu << " pada acara " << acara << " tidak ditemukan!" << endl << endl;
                }

                pilihan = fitur();
            break;

            case 10:
                showAcara(LAcara);
                pilihan = fitur();
            break;

            case 11:
                showMenu(LMenu);
                pilihan = fitur();
            break;

            case 12:
                showAllAcaraMenu(LAcara);
                pilihan = fitur();
            break;

            case 13:
                Q = mostSoldMenu(LAcara, LMenu);
                cout << "Menu yang paling banyak terjual adalah " << info(Q).namaMenu << "!" << endl;
                pilihan = fitur();
            break;

            case 14:
                cout << "Acara apa yang ingin dihitung menunya? : ";
                cin >> acara;
                N = countRelasi(LAcara, acara);
                if(N != -1){
                    cout << "Terdapat " << N << " menu diacara " << acara << endl << endl;
                }else{
                    cout << "Acara " << acara << " tidak ditemukan!" << endl << endl;
                }

                pilihan = fitur();
            break;
        }
    }

    cout << "===== ANDA TELAH KELUAR DARI APLIKASI =====" << endl;
    return 0;
}
