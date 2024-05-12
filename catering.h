#ifndef CATERING_H_INCLUDED
#define CATERING_H_INCLUDED
#include <iostream>
#define first(L) (L).first
#define last(L) (L).last
#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define menuAcara(P) (P)->menuAcara
#define nextMenu(P) (P)->nextMenu
using namespace std;

struct infotypeAcara{
    string namaAcara;
    string tanggalAcara;
    int porsiDipesan;
    int totalHarga;
};

struct infotypeMenu{
    string namaMenu;
    string jenisMenu;
    int hargaMenu;
};

typedef struct elmAcara *adrAcara;
typedef struct elmMenu *adrMenu;
typedef struct elmRelasi *adrRelasi;

struct listRelasi{
    adrRelasi first;
    adrRelasi last;
};

struct elmAcara{
    infotypeAcara info;
    adrAcara next;
    adrAcara prev;
    listRelasi menuAcara;
};

struct elmMenu{
    infotypeMenu info;
    adrMenu next;
};

struct elmRelasi{
    adrMenu nextMenu;
    adrRelasi next;
    adrRelasi prev;
};

struct listAcara{
    adrAcara first;
    adrAcara last;
};

struct listMenu{
    adrMenu first;
};

void createListAcara(listAcara &L);
void createListMenu(listMenu &L);
void createListRelasi(listRelasi &L);
adrAcara alokasiAcara(infotypeAcara x);
adrMenu alokasiMenu(infotypeMenu x);
adrRelasi alokasiRelasi(adrMenu x);
void dealokasiAcara(adrAcara &P);
void dealokasiMenu(adrMenu &P);
void dealokasiRelasi(adrRelasi &P);
void insertAcara(listAcara &L, adrAcara P);
void insertMenu(listMenu &L, adrMenu P);
void insertRelasi(listAcara &LAcara, listMenu LMenu, string namaAcara, string namaMenu);
void deleteAcara(listAcara &L, string namaAcara);
void deleteMenu(listAcara &LAcara, listMenu &LMenu, string namaMenu);
void deleteRelasi(listAcara &L, string namaAcara, string namaMenu);
adrAcara findAcara(listAcara L, string namaAcara);
adrMenu findMenu(listMenu L, string namaMenu);
adrRelasi findRelasi(listAcara L, string namaAcara, string namaMenu);
void showAcara(listAcara L);
void showMenu(listMenu L);
void showAllAcaraMenu(listAcara L);
adrMenu mostSoldMenu(listAcara LAcara, listMenu LMenu);
int countRelasi(listAcara L, string namaAcara);
int fitur();

#endif // CATERING_H_INCLUDED
