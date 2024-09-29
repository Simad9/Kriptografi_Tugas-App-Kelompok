#include <iostream>
#include <string>

using namespace std;

void prepareKeyVigenere(string &key){
    string keyReady;
    for(int i = 0; i < key.size(); ++i){
        if(key[i] != ' '){
          keyReady += toupper(key[i]); 
        }
    }
    key = keyReady;
}

bool validasiKunci(string key){
    if(key.empty()){
        cout << "Kunci tidak boleh kosong!" << endl;
        return false;
    }
    
    for(int i = 0; i < key.length(); ++i){
        if(!isalpha(key[i]) && key[i] != ' '){
            cout << "Kunci hanya boleh berisi huruf alfabet! Silahkan masukkan kembali. \n" << endl;
            return false;
        }
    }
    return true;
}

string inputKunciVigenere(){
  string key;
  do{
    cout << "Masukkan kunci: ";
    getline(cin, key);
  } while(!validasiKunci(key));
  return key;
}

void enkripsiVigenere(string message, string key){
    string resultEnkripsi;
    int indeksKey = 0;

    for(int i = 0; i < message.length(); ++i){
        char plainteks = message[i];

        if(plainteks >= 'a' && plainteks <= 'z'){
            plainteks = toupper(plainteks);
        } else if(plainteks <  'A' || plainteks > 'Z'){
            resultEnkripsi += plainteks;
            continue;
        }

        resultEnkripsi += ((plainteks - 'A') + (key[indeksKey] - 'A')) % 26 + 'A';
        indeksKey = (indeksKey + 1) % key.length();
    }
    system("cls"); 
    cout << "\nPlainteks: " << message << endl;
    cout << "Kunci: " << key << endl;
    cout << "Pesan Terenkripsi: " << resultEnkripsi << endl;
}

void dekripsiVigenere(string message, string key){
    string resultDekripsi;
    int indeksKey = 0;

    for(int i = 0; i < message.length(); ++i){
        char chiperteks = message[i];

        if(chiperteks >= 'a' && chiperteks <= 'z'){
            chiperteks = toupper(chiperteks);
        } else if(chiperteks < 'A' || chiperteks > 'Z'){
            resultDekripsi += chiperteks;
            continue;
        }

        resultDekripsi += (chiperteks - key[indeksKey] + 26) % 26 + 'A';
        indeksKey = (indeksKey + 1) % key.length();
    }
    system("cls");
    cout << "\nChiperteks: " << message << endl;
    cout << "Kunci: " << key << endl;
    cout << "Pesan Terenkripsi: " << resultDekripsi << endl;
}

int main(){
    int pilihan;
    string key, massage;

    do{
        cout << "Menu: \n";
        cout << "====== \n";
        cout << "1. Enkripsi \n";
        cout << "2. Deskripsi \n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        switch (pilihan)
        {
        case 1:
            system("cls");
            cout << "Enkripsi" << endl;
            cout << "========" << endl;
            cout << "Masukkan pesan yang ingin dienkripsi: ";
            getline(cin, massage);
            key = inputKunciVigenere();

            prepareKeyVigenere(key);
            enkripsiVigenere(massage, key);
            break;

        case 2:
            system("cls");
            cout << "Dekripsi" << endl;
            cout << "========" << endl;
            cout << "Masukkan pesan yang ingin dideskripsi: ";
            getline(cin, massage);
            key = inputKunciVigenere();

            prepareKeyVigenere(key);
            dekripsiVigenere(massage, key);
            break;
            
        default:
            cout << "Pilihan tidak valid." << endl; 
            break;
        }
    } while (pilihan == 1 || pilihan == 2);
}