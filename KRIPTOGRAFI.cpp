#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

// == INIT FUNCTION PER ALGORITMA ==

// == CAESAR CIHPER ==
void caesar();

// == VIGENERE CIPHER ==

// == AES CIPHER ==

// == RSA CHIPER ==
int isPrima(int number);
int gcd(int a, int b);
long long modExp(long long base, long long exponent, long long modulus);
vector<long long> encrypt(const string &plaintext, long long e, long long n);
string decrypt(const vector<long long> &ciphertext, long long d, long long n);
vector<long long> parseInputToVector(const string &input);
void generateKunci();
void enkripsiRSA();
void dekripsiRSA();
void rsa();

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
        rsa();
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


// == CAESAR CHIPER ==
void caesar(){

    system ("cls");
    cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;
    cout << left << setw (10) <<setfill (' ') << " "<<setw(34)<< " >> CAESAR CHIPER << "<<" " << endl;
    cout << " " <<setw (41) <<setfill ('-')<< " "<<endl;


    int milih, shift;
    string text;

    cout << "  Pilih mode yang di inginkan   : " << endl;
    cout << "    1. Enkripsi" << endl;
    cout << "    2. Deskripsi" << endl;
    cout << "  Masukkan mode yang diinginkan : ";
    cin >> milih;
    cin.ignore();

    if (milih == 1) {
        system("cls");
        cout << " " << setw(41) << setfill('-') << " " << endl;
        cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
        cout << " " << setw(41) << setfill('-') << " " << endl;

        cout << "  Enkripsi menggunakan Caesar Chipper" << endl << endl;
        cout << "  Masukkan teks  : ";
        getline(cin, text);
        cout << "  Masukkan kunci : ";
        cin >> shift;
        cout << endl;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) { // Cek apakah karakter adalah huruf
                char base = isupper(text[i]) ? 'A' : 'a'; // Huruf besar atau kecil
                text[i] = (text[i] - base + shift) % 26 + base; // Geser huruf
            } else if (isdigit(text[i])) { // Cek apakah karakter adalah angka
                text[i] = (text[i] - '0' + shift) % 10 + '0'; // Geser angka
            } else if (text[i] == ' ') { // Abaikan spasi
                continue;
            } else {
                cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
                return; // Berhenti jika ditemukan karakter non-huruf/angka selain spasi
            }
        }
        cout << "  Hasil Enkripsi : " << text << endl;

    } else if (milih == 2) {
        system("cls");
        cout << " " << setw(41) << setfill('-') << " " << endl;
        cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
        cout << " " << setw(41) << setfill('-') << " " << endl;

        cout << "  Deskripsi menggunakan Caesar Chipper" << endl << endl;

        cout << "  Masukkan teks  : ";
        getline(cin, text);
        cout << "  Masukkan kunci : ";
        cin >> shift;
        cout << endl;

        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) { // Cek apakah karakter adalah huruf
                char base = isupper(text[i]) ? 'A' : 'a'; // Huruf besar atau kecil
                text[i] = (text[i] - base - shift + 26) % 26 + base; // Geser huruf ke belakang
            } else if (isdigit(text[i])) { // Cek apakah karakter adalah angka
                text[i] = (text[i] - '0' - shift + 10) % 10 + '0'; // Geser angka ke belakang
            } else if (text[i] == ' ') { // Abaikan spasi
                continue;
            } else {
                cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
                return; // Berhenti jika ditemukan karakter non-huruf/angka selain spasi
            }
        }
        cout << "  Hasil Dekripsi : " << text << endl;

    } else {
        cout << "  Input salah atau tidak tersedia." << endl;
    }
}

// == VIGENERE CHIPER ==

// == AES CHIPER ==

// == RSA CHIPER ==
// ** KUMPULAN FUNGSI **

// Fungsi untuk mengecek apakah sebuah bilangan prima
int isPrima(int number) {
  // init
  int i;
  // kode
  for (i = 2; i < number; i++) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}

// Fungsi untuk menghitung GCD menggunakan Algoritma Euclid
int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Function to calculate gcd using the Extended Euclidean Algorithm
int gcdExtended(int a, int b, int &x, int &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }

  int x1, y1;
  int gcd = gcdExtended(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

// Function to find the modular inverse of e modulo phi(n)
int modInverse(int e, int phi) {
  int x, y;
  int gcd = gcdExtended(e, phi, x, y);
  if (gcd != 1) {
    cout << "Inverse does not exist!" << endl;  // e and phi are not coprime
    return -1;
  } else {
    // Make x positive
    int d = (x % phi + phi) % phi;
    return d;
  }
}

// Fungsi generate kunci
void generateKunci() {
  // INIT
  int p, q, n_modulus, fi_totint, e_kunciPublik, d_kunciPrivat;
  // KODE BEKERJA
  cout << "=======================\n";
  cout << "Generate Kunci \n\n";
  // Input p harus prima
  cout << "Masukkan p : ";
  cin >> p;
  while (isPrima(p) == 0) {
    cout << "Masukkan p : ";
    cin >> p;
  }
  // Input q harus prima
  cout << "Masukkan q : ";
  cin >> q;
  while (isPrima(q) == 0) {
    cout << "Masukkan q : ";
    cin >> q;
  }
  // Pengecekan p tidak boleh sama dan q
  while (p == q) {
    cout << "Masukkan q : ";
    cin >> q;
  }
  // Menghitung n - modulus dan fi - totint
  n_modulus = p * q;
  fi_totint = (p - 1) * (q - 1);
  // Input e - kunci publik
  cout << "Masukkan e : ";
  cin >> e_kunciPublik;
  while ((e_kunciPublik > 1 || e_kunciPublik < fi_totint) &&
         !(gcd(e_kunciPublik, fi_totint) == 1)) {
    cout << "Masukkan e : ";
    cin >> e_kunciPublik;
  }

  // Menghitung d - kunci privat
  d_kunciPrivat = modInverse(e_kunciPublik, fi_totint);

  // Output
  cout << "\nKunci Publik : " << e_kunciPublik << endl;
  cout << "Kunci Privat : " << d_kunciPrivat << endl;
  cout << "Modulus : " << n_modulus << endl;
  cout << endl;
};

// Fungsi - Pengendalian e - n dan d - n
long long modExp(long long base, long long exponent, long long modulus) {
  long long result = 1;
  base = base % modulus;

  while (exponent > 0) {
    // Jika exponent adalah bilangan ganjil, kalikan dengan base
    if (exponent % 2 == 1) {
      result = (result * base) % modulus;
    }
    // Pembagian exponent dengan 2
    exponent = exponent >> 1;        // Sama dengan exponent /= 2
    base = (base * base) % modulus;  // Square base
  }

  return result;
}

// Fungsi - Enkripsi
vector<long long> encrypt(const string &plaintext, long long e, long long n) {
  vector<long long> ciphertext;
  for (char ch : plaintext) {
    long long encryptedChar = modExp(static_cast<long long>(ch), e, n);
    ciphertext.push_back(encryptedChar);
  }
  return ciphertext;
}

// Fungsi - Dekripsi
string decrypt(const vector<long long> &ciphertext, long long d, long long n) {
  string plaintext;
  for (long long encryptedChar : ciphertext) {
    char decryptedChar = static_cast<char>(modExp(encryptedChar, d, n));
    plaintext += decryptedChar;
  }
  return plaintext;
}

// Fungsi untuk mengubah input string menjadi vector
vector<long long> parseInputToVector(const string &input) {
  vector<long long> vec;
  stringstream ss(input);
  long long number;
  while (ss >> number) {
    vec.push_back(number);
  }
  return vec;
}

// ENKRIPSI
void enkripsiRSA() {
  // INIT
  string plaintextInput;
  int kunciPublik, modulus;

  // TAMPILAN
  cout << "Enkripsi Metode RSA \n\n";
  cout << "Masukkan Plaintext : ";
  getline(cin >> ws, plaintextInput);
  cout << "Masukkan Kunci Publik : ";
  cin >> kunciPublik;
  cout << "Masukkan Modulus : ";
  cin >> modulus;
  cout << endl;
  // CODE BERKERJA
  // 1. Plaintext ubah jadi ASCII
  int plaintextASCI[plaintextInput.length()];

  // konversi plaintext
  for (int i = 0; i < plaintextInput.length(); i++) {
    plaintextASCI[i] = (int)plaintextInput[i];
    cout << plaintextASCI[i] << " ";
  }
  cout << endl;

  // 2. Enkripsi
  vector<long long> ciphertext = encrypt(plaintextInput, kunciPublik, modulus);
  cout << "Ciphertext: ";
  for (long long value : ciphertext) {
    cout << value << " ";
  }
  cout << endl;
}

// DEKRIPSI
void dekripsiRSA() {
  // INIT
  string ciphertextInput;
  int kunciPrivat, modulus;
  // TAMPILAN
  cout << "Dekripsi Metode RSA \n\n";
  cout << "Masukkan Ciphertext : ";
  getline(cin >> ws, ciphertextInput);
  cout << "Masukkan Kunci Privat : ";
  cin >> kunciPrivat;
  cout << "Masukkan Modulus : ";
  cin >> modulus;
  cout << endl;
  // CODE BERKERJA

  // 1. Ubah input string menjadi vector
  vector<long long> ciphertext = parseInputToVector(ciphertextInput);
  cout << "Ciphertext: ";
  for (long long value : ciphertext) {
    cout << value << " ";
  }
  cout << endl;

  // 2. Dekripsi + Tampilkan
  string decryptedText = decrypt(ciphertext, kunciPrivat, modulus);
  cout << "Decrypted Text: " << decryptedText << endl;
}

void rsa() {
  // Init
  char menu;
  // Tampilan
  cout << "Kode Algoritma Kriptografi RSA \n";
  cout << endl;
  do {
    cout << "Menu : \n";
    cout << "====== \n";
    cout << "0. Generate Kunci \n";
    cout << "1. Enkripsi \n";
    cout << "2. Dekripsi \n";
    cout << "Pilihan : ";
    cin >> menu;
    cout << endl;
    if (menu == '0') {
      generateKunci();
    } else if (menu == '1') {
      enkripsiRSA();
      cout << endl;
    } else if (menu == '2') {
      dekripsiRSA();
      cout << endl;
    }
    cout << "kembali ke menu (y/n) : ";
    cin >> menu;
  } while (menu == 'y' || menu == 'Y');
}

