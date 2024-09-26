#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

void caesar();

int main (){

    int pilih;
    char ulang = 'Y';

    do{
    system("cls");
    cout << " " << setw (41) << setfill ('-')<< " "<< endl;
    cout << left << setw (1) << setfill (' ') << " "<< setw(34) << "  >> PROGRAM ALGORITMA KRIPTOGRAFI <<"<<" " << endl;
    cout << right <<" " <<setw (41) << setfill ('-') << " " << endl;

    cout << left << setw (16) << setfill ('=') << " "<< setw(25) << " PILIHAN "<< "" << endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 1. Caesar Chiper"<< "|" << endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 2. Vigenere Chiper" << "|" <<endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 3. AES Chiper" << "|" << endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 4. RSA Chiper" << "|" << endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 5. Super "<< "|" << endl;
    cout << left << setw (4) << setfill (' ') << " |"<< setw(36) << " 6. Keluar dari Program" << "|" << endl;
    cout << right <<" " <<setw (41)<< setfill ('=') << " " << endl;
    cout << left << setw (2) <<setfill (' ') << " "<< setw(23) << "Silahkan pilih menu yang tersedia = ";
	cin >> pilih;

    if(pilih == 1){
        caesar();
    }
	else if(pilih == 2){

    }
    else if(pilih == 3){

    }
    else if(pilih == 4){

    }
    else if(pilih == 5){

    }
    else if (pilih == 6){
        cout<<endl;
		cout<<"  Program Selesai"<<endl;
		exit(0);
    }
    else if (pilih > 5){
        cout<<endl;
        cout << "  Input salah";
        cout<<endl;
    }
    cout<<endl;
    cout << "  Kembali Ke Menu (y/t) : "; cin >> ulang;
    } while (toupper(ulang)=='Y');
    cout<<endl;
	cout<<"  Program Selesai"<<endl;

    return 0;
}


void caesar(){

    system ("cls");
    cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;
    cout << left << setw (10) <<setfill (' ') << " "<<setw(34)<< " >> CAESAR CHIPER << "<<" " << endl;
    cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;

    int milih, shift;
    string text;

    cout << "  Pilih mode yang di inginkan   : "<<endl;
    cout << "    1. Enrkipsi"<<endl;
    cout << "    2. Deskripsi"<<endl;
    cout << "  Masukkan mode yang diinginkan : ";
    cin >> milih;
    cin.ignore();

    if (milih == 1){
        system ("cls");
        cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;
        cout << left << setw (10) <<setfill (' ') << " "<<setw(34)<< " >> CAESAR CHIPER << "<<" " << endl;
        cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;

        cout << "  Enkripsi menggunakan Caesar Chipper"<<endl<<endl;
        cout << "  Masukkan teks  : ";
        getline(cin, text);
        cout << "  Masukkan kunci : ";
        cin >> shift;
        cout<<endl;

         for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) { // Cek apakah karakter adalah huruf
                char base = isupper(text[i]) ? 'A' : 'a'; // Huruf besar atau kecil
                text[i] = (text[i] - base + shift) % 26 + base; // Geser huruf
            } else if (text[i] == ' ') { // Abaikan spasi
                continue;
            } else {
                cout << "  Error: Teks mengandung karakter non-huruf pada posisi " << i+1 << "!" << endl;
                return; // Berhenti jika ditemukan karakter non-huruf selain spasi
            }
        }
        cout << "  Hasil Enkripsi : " << text << endl;

    }else if (milih == 2){
        system ("cls");
        cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;
        cout << left << setw (10) <<setfill (' ') << " "<<setw(34)<< " >> CAESAR CHIPER << "<<" " << endl;
        cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;

        cout << "  Deskripsi menggunakan Caesar Chipper"<<endl<<endl;

        cout << "  Masukkan teks  : ";
        getline(cin, text);
        cout << "  Masukkan kunci : ";
        cin >> shift;
        cout<<endl;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) { // Cek apakah karakter adalah huruf
                char base = isupper(text[i]) ? 'A' : 'a'; // Huruf besar atau kecil
                text[i] = (text[i] - base - shift + 26) % 26 + base; // Geser huruf ke belakang
            } else if (text[i] == ' ') { // Abaikan spasi
                continue;
            } else {
                cout << "  Error: Teks mengandung karakter non-huruf pada posisi " << i+1 << "!" << endl;
                return; // Berhenti jika ditemukan karakter non-huruf selain spasi
            }
        }
        cout << "  Hasil Dekripsi : " << text << endl;

    }else {
        cout << "  Input salah atau tidak tersedia."<<endl;
    }

}
