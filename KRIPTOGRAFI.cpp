#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

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
