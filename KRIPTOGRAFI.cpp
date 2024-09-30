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
void prepareKeyVigenere(string &key);
string inputKunciVigenere();
void enkripsiVigenere(string message, string key);
void dekripsiVigenere(string message, string key);
void vigenere();

// == RC4 CIPHER ==
void RC4();
void rc4_init(vector<int> &S, const string &key);
string rc4_crypt(const string &data, const string &key);
string rc4_to_hex(const string &str);
string rc4_from_hex(const string &hex_str);

// == RSA CHIPER ==
void judul();                                                                  // tampilan judul atas
int isPrima(int number);                                                       // mengecek bilangan prima
int gcd(int a, int b);                                                         // menghitung gcd(Great Common Divisor) / Faktor Persekutuan Terbesar menggunakan Algoritam Euclid
int gcdExtended(int a, int b, int &x, int &y);                                 // ini yang diperpanjang
int modInverse(int e, int phi);                                                // mencari modular dari totint (φ(n))
void generateKunci();                                                          // Untuk generate kunci
long long modExp(long long base, long long exponent, long long modulus);       // Untuk menghitung base^eksponen mod modulus secara efisien, rumus RSA
vector<long long> encrypt(const string &plaintext, long long e, long long n);  // Untuk enkripsi
string decrypt(const vector<long long> &ciphertext, long long d, long long n); // Untuk dekripsi
vector<long long> parseInputToVector(const string &input);                     // mengubah String menjadi Vector
void enkripsiRSA();                                                            // Tampilan Enrkipsi RSA
void dekripsiRSA();                                                            // Tampilan Dekripsi RSA
void rsa();                                                                    // Tampilan secara keseurugahn

// == SUPER Chiper ==
void superEnkripsi(){
  string plaintext;
  int kunciCaesar;
  string kunciVigenere;
  string kunciRC4;
  int kunciPublik, modulus;

  // Caesar Chipper
  cout << endl;
  cout << "--------------------------" << endl;
  cout << "  Enkripsi dengan Caesar  " << endl;
  cout << "--------------------------" << endl;
  cout << "  Masukkan plaintext  : ";
  getline(cin >> ws, plaintext);
  cout << "  Masukkan kunci      : ";
  cin >> kunciCaesar;
  cout << endl;

  string plaintextInput = plaintext;

  for (int i = 0; i < plaintext.length(); i++)
  {
    if (isalpha(plaintext[i]))
    {                                                 // Cek apakah karakter adalah huruf
      char base = isupper(plaintext[i]) ? 'A' : 'a';       // Huruf besar atau kecil
      plaintext[i] = (plaintext[i] - base + kunciCaesar) % 26 + base; // Geser huruf
    }
    else if (isdigit(plaintext[i]))
    {                                               // Cek apakah karakter adalah angka
      plaintext[i] = (plaintext[i] - '0' + kunciCaesar) % 10 + '0'; // Geser angka
    }
    else if (plaintext[i] == ' ')
    { // Abaikan spasi
      continue;
    }
    else
    {
      cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
      return; // Berhenti jika ditemukan karakter non-huruf/angka selain spasi
    }
  }
  cout << "  Plaintext    : " << plaintextInput << endl;
  cout << "  Kunci        : " << kunciCaesar << endl;
  cout << "  Chipertext   : " << plaintext << endl;
  cout << endl;

  // Vigenere
  cout << "-----------------------------" << endl;
  cout << "  Enkripsi dengan Vigenere   " << endl;
  cout << "-----------------------------" << endl;
  cout << "  Masukan kunci Vigenere : ";
  getline(cin >> ws, kunciVigenere);
  // kunciVigenere = inputKunciVigenere();
  prepareKeyVigenere(kunciVigenere); // di uppercase

  string resultEnkripsi;
  int indeksKey = 0;

  for(int i = 0; i < plaintext.length(); ++i){
    char plainteks = plaintext[i];
    if(plainteks >= 'a' && plainteks <= 'z'){
      plainteks = toupper(plainteks);
    } else if(plainteks < 'A' || plainteks > 'Z'){
      resultEnkripsi += plainteks;
      continue;
    }

    resultEnkripsi += ((plainteks - 'A') + (kunciVigenere[indeksKey] - 'A')) % 26 + 'A';
    indeksKey = (indeksKey + 1) % kunciVigenere.length();
  } 
  cout << endl;
  cout << "  Plaintext   : " << plaintext << endl;
  cout << "  Kunci       : " << kunciVigenere << endl;
  cout << "  Chipertext  : " << resultEnkripsi << endl;

  // biar cuman satu
  plaintext = resultEnkripsi;
  cout << endl;

  // RC4
  cout << "-------------------------" << endl;
  cout << "  Enkripsi dengan RC4    " << endl;
  cout << "-------------------------" << endl;

  cout << "  Masukkan kunci: ";
  getline(cin >> ws, kunciRC4);
  cout << endl;

  string encrypted = rc4_crypt(plaintext, kunciRC4);
  string encrypted_hex = rc4_to_hex(encrypted);

  cout << "  Plaintext         : " << plaintext << endl;
  cout << "  Kunci             : " << kunciRC4 << endl;
  cout << "  Chipertext (hex)  : " << encrypted_hex << endl;

  // biar cuman satu
  plaintext = encrypted_hex;
  cout << endl;
  // RSA
  cout << "-------------------------" << endl;
  cout << "  Enkripsi dengan RSA    " << endl;
  cout << "-------------------------" << endl;

  cout << "  Masukkan Kunci Publik : ";
  cin >> kunciPublik;
  cout << "  Masukkan Modulus : ";
  cin >> modulus;
  cout << endl;
  // CODE BERKERJA

  // 1. Plaintext ubah jadi ASCII
  int plaintextASCI[plaintext.length()];
  vector<long long> ciphertext = encrypt(plaintext, kunciPublik, modulus);

  // konversi plaintext
  for (int i = 0; i < plaintext.length(); i++)
  {
    plaintextASCI[i] = (int)plaintext[i]; 
  }

  cout << "  Plaintext         : " << plaintext << endl;
  cout << "  Kunci Publik      : " << kunciPublik << endl;
  cout << "  Modulus           : " << modulus << endl;
  cout << "  Ciphertext        : ";
  for (long long value : ciphertext)
  {
    cout << value << " ";
  }
  cout << endl;
}

void superDekripsi(){
  
}

void super(){
  int pilihan;
  char ulang;

   do {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "        >> Menu Super Enkripsi <<      " << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih mode yang diinginkan   :" << endl;
        cout << "  1. Enkripsi \n";
        cout << "  2. Deskripsi \n";
        cout << "  3. Keluar \n";
        cout << "Masukkan Mode yang diinginkan: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        switch (pilihan) {
        case 1:
            superEnkripsi();
            break;
        case 2:
           superDekripsi();
            break;
        case 3 :
            cout << "Keluar dari Menu Super Enkripsi" << endl;
            return;
            break;

        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
        cout << "\nKembali Ke Menu Super Enkripsi (y/t): ";
        cin >> ulang;
    } 
    while (toupper(ulang) == 'Y');
    system("cls");
}

int main()
{

  int pilih;
  char ulang = 'Y';

  do
  {
    system("cls");
    cout << " " << setw(41) << setfill('-') << " " << endl;
    cout << left << setw(1) << setfill(' ') << " " << setw(34) << "  >> PROGRAM ALGORITMA KRIPTOGRAFI <<" << " " << endl;
    cout << right << " " << setw(41) << setfill('-') << " " << endl;

    cout << left << setw(16) << setfill('=') << " " << setw(25) << " PILIHAN " << "" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 1. Caesar Chiper" << "|" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 2. Vigenere Chiper" << "|" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 3. RC4 Chiper" << "|" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 4. RSA Chiper" << "|" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 5. Super " << "|" << endl;
    cout << left << setw(4) << setfill(' ') << " |" << setw(36) << " 6. Keluar dari Program" << "|" << endl;
    cout << right << " " << setw(41) << setfill('=') << " " << endl;
    cout << left << setw(2) << setfill(' ') << " " << setw(23) << "Silahkan pilih menu yang tersedia = ";
    cin >> pilih;

    if (pilih == 1)
    {
      caesar();
    }
    else if (pilih == 2)
    {
      vigenere();
    }
    else if (pilih == 3)
    {
      RC4();
    }
    else if (pilih == 4)
    {
      rsa();
    }
    else if (pilih == 5)
    {
      super();
    }
    else if (pilih == 6)
    {
      cout << endl;
      cout << "  Program Selesai" << endl;
      exit(0);
    }
    else if (pilih > 5)
    {
      cout << endl;
      cout << "  Input salah";
      cout << endl;
    }
    cout << endl;
    cout << "  Kembali Ke Menu (y/t) : ";
    cin >> ulang;
  } while (toupper(ulang) == 'Y');
  cout << endl;
  cout << "  Program Selesai" << endl;

  return 0;
}

// == CAESAR CHIPER ==
void caesar()
{

  system("cls");
  cout << " " << setw(41) << setfill('-') << " " << endl;
  cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
  cout << " " << setw(41) << setfill('-') << " " << endl;

  int milih, shift;
  string text;

  cout << "  Pilih mode yang di inginkan   : " << endl;
  cout << "    1. Enkripsi" << endl;
  cout << "    2. Deskripsi" << endl;
  cout << "  Masukkan mode yang diinginkan : ";
  cin >> milih;
  cin.ignore();

  if (milih == 1)
  {
    system("cls");
    cout << " " << setw(41) << setfill('-') << " " << endl;
    cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
    cout << " " << setw(41) << setfill('-') << " " << endl;

    cout << "  Enkripsi menggunakan Caesar Chipper" << endl
         << endl;
    cout << "  Masukkan teks  : ";
    getline(cin, text);
    cout << "  Masukkan kunci : ";
    cin >> shift;
    cout << endl;

    for (int i = 0; i < text.length(); i++)
    {
      if (isalpha(text[i]))
      {                                                 // Cek apakah karakter adalah huruf
        char base = isupper(text[i]) ? 'A' : 'a';       // Huruf besar atau kecil
        text[i] = (text[i] - base + shift) % 26 + base; // Geser huruf
      }
      else if (isdigit(text[i]))
      {                                               // Cek apakah karakter adalah angka
        text[i] = (text[i] - '0' + shift) % 10 + '0'; // Geser angka
      }
      else if (text[i] == ' ')
      { // Abaikan spasi
        continue;
      }
      else
      {
        cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
        return; // Berhenti jika ditemukan karakter non-huruf/angka selain spasi
      }
    }
    cout << "  Hasil Enkripsi : " << text << endl;
  }
  else if (milih == 2)
  {
    system("cls");
    cout << " " << setw(41) << setfill('-') << " " << endl;
    cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
    cout << " " << setw(41) << setfill('-') << " " << endl;

    cout << "  Deskripsi menggunakan Caesar Chipper" << endl
         << endl;

    cout << "  Masukkan teks  : ";
    getline(cin, text);
    cout << "  Masukkan kunci : ";
    cin >> shift;
    cout << endl;

    for (int i = 0; i < text.length(); i++)
    {
      if (isalpha(text[i]))
      {                                                      // Cek apakah karakter adalah huruf
        char base = isupper(text[i]) ? 'A' : 'a';            // Huruf besar atau kecil
        text[i] = (text[i] - base - shift + 26) % 26 + base; // Geser huruf ke belakang
      }
      else if (isdigit(text[i]))
      {                                                    // Cek apakah karakter adalah angka
        text[i] = (text[i] - '0' - shift + 10) % 10 + '0'; // Geser angka ke belakang
      }
      else if (text[i] == ' ')
      { // Abaikan spasi
        continue;
      }
      else
      {
        cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
        return; // Berhenti jika ditemukan karakter non-huruf/angka selain spasi
      }
    }
    cout << "  Hasil Dekripsi : " << text << endl;
  }
  else
  {
    cout << "  Input salah atau tidak tersedia." << endl;
  }
}

// == VIGENERE CHIPER ==
// Mempersiapkan kunci Vigenere (Menjadi Kapital dan mengabaikan spasi)
void prepareKeyVigenere(string &key){
    string keyReady;
    for(int i = 0; i < key.size(); ++i){
        if(key[i] != ' '){
            keyReady += toupper(key[i]); 
        }
    }
    key = keyReady;
}

// Fungsi untuk validasi kunci (tidak boleh kosong dan hanya boleh alfabet)
bool validasiKunci(string key){
    if(key.empty()){
        cout << "Kunci tidak boleh kosong!" << endl;
        return false;
    }
    for(int i = 0; i < key.length(); ++i){
        if(!isalpha(key[i]) && key[i] != ' '){
            cout << "Kunci hanya boleh berisi huruf alfabet! Silahkan masukkan kembali." << endl;
            return false;
        }
    }
    return true;
}

// Fungsi untuk meminta input kunci
string inputKunciVigenere(){
    string key;
    while(!validasiKunci(key)){
        cout << "Masukkan kunci: ";
        getline(cin, key);
    };
    return key;
}

// Fungsi enkripsi Vigenere
void enkripsiVigenere(string message, string key){
    string resultEnkripsi;
    int indeksKey = 0;

    for(int i = 0; i < message.length(); ++i){
        char plainteks = message[i];

        if(plainteks >= 'a' && plainteks <= 'z'){
            plainteks = toupper(plainteks);
        } else if(plainteks < 'A' || plainteks > 'Z'){
            resultEnkripsi += plainteks;
            continue;
        }

        resultEnkripsi += ((plainteks - 'A') + (key[indeksKey] - 'A')) % 26 + 'A';
        indeksKey = (indeksKey + 1) % key.length();
    }
    system("cls");
    cout << "HASIL" << endl;
    cout << "=================================" << endl;
    cout << "   Plain teks\t\t\t: " << message << endl;
    cout << "   Kunci\t\t\t: " << key << endl;
    cout << "   Pesan TerEnkripsi\t\t: " << resultEnkripsi << endl;
}

// Fungsi dekripsi Vigenere
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
    cout << "HASIL" << endl;
    cout << "=================================" << endl;
    cout << "   Chiper teks\t\t\t: " << message << endl;
    cout << "   Kunci\t\t\t: " << key << endl;
    cout << "   Pesan TerDekripsi\t\t: " << resultDekripsi << endl;
}

// Fungsi menu Vigenere
void vigenere() {
    int pilihan;
    string key, message;
    char ulang;

    do {
        system("cls");
        cout << "---------------------------------------" << endl;
        cout << "         >> Menu Vigenere << "         << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih mode yang diinginkan   :" << endl;
        cout << "  1. Enkripsi \n";
        cout << "  2. Deskripsi \n";
        cout << "  0. Keluar \n";
        cout << "Masukkan Mode yang diinginkan: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        switch (pilihan) {
        case 1:
            system("cls");
            cout << "Enkripsi Vigenere" << endl;
            cout << "====================================" << endl <<endl;
            cout << "Masukkan pesan yang ingin dienkripsi: ";
            getline(cin, message);
            key = inputKunciVigenere();

            prepareKeyVigenere(key);
            enkripsiVigenere(message, key);
            break;

        case 2:
            system("cls");
            cout << "Dekripsi Vigenere" << endl;
            cout << "====================================" << endl <<endl;;
            cout << "Masukkan pesan yang ingin didekripsi: ";
            getline(cin, message);
            key = inputKunciVigenere();

            prepareKeyVigenere(key);
            dekripsiVigenere(message, key);
            break;

        case 0 :
            cout << "Keluar dari Menu Vigenere Chiper" << endl;
            return;
            break;

        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
        cout << "\nKembali Ke Menu Vigenere (y/t): ";
        cin >> ulang;
    } 
    while (toupper(ulang) == 'Y');
    system("cls");
}

// == RC4 CHIPER ==
void rc4_init(vector<int> &S, const string &key)
{
  int j = 0;
  int key_len = key.size();

  for (int i = 0; i < 256; i++)
  {
    S[i] = i;
  }

  for (int i = 0; i < 256; i++)
  {
    j = (j + S[i] + key[i % key_len]) % 256;
    swap(S[i], S[j]);
  }
}

// Fungsi untuk mengenkripsi atau mendekripsi
string rc4_crypt(const string &data, const string &key)
{
  vector<int> S(256);
  rc4_init(S, key);

  int i = 0, j = 0;
  string result = data;

  for (size_t k = 0; k < data.size(); k++)
  {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    swap(S[i], S[j]);

    int rnd = S[(S[i] + S[j]) % 256];
    result[k] ^= rnd;
  }

  return result;
}

// Fungsi untuk konversi string ke hexadecimal
string rc4_to_hex(const string &str)
{
  stringstream ss;
  for (unsigned char c : str)
  {
    ss << hex << setw(2) << setfill('0') << (int)c;
  }
  return ss.str();
}

// Fungsi untuk konversi hexadecimal ke string
string rc4_from_hex(const string &hex_str)
{
  stringstream ss;
  for (size_t i = 0; i < hex_str.length(); i += 2)
  {
    string byte = hex_str.substr(i, 2);
    char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
    ss << chr;
  }
  return ss.str();
}

// Fungsi menu utama
void RC4()
{
  int pilihan;
  string key, input;

  while (true)
  {
    cout << " " << setw(41) << setfill('-') << " " << endl;
    cout << "  >> PROGRAM ALGORITMA KRIPTOGRAFI <<" << endl;
    cout << " " << setw(41) << setfill('-') << " " << endl;

    cout << "Menu:\n";
    cout << "1. Enkripsi\n";
    cout << "2. Dekripsi\n";
    cout << "3. Keluar\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

    if (pilihan == 3)
    {
      break;
    }
    system("cls");
    cout << "Masukkan kunci: ";
    cin >> key;

    if (pilihan == 1)
    {
      cout << "Masukkan plain text: ";
      cin.ignore();
      getline(cin, input);

      string encrypted = rc4_crypt(input, key);
      string encrypted_hex = rc4_to_hex(encrypted);
      cout << "Hasil enkripsi (hex): " << encrypted_hex << endl;
    }
    else if (pilihan == 2)
    {
      cout << "Masukkan cipher text (hex): ";
      cin.ignore();
      getline(cin, input);

      string decrypted = rc4_crypt(rc4_from_hex(input), key);
      cout << "Hasil dekripsi: " << decrypted << endl;
    }
    else
    {
      cout << "Pilihan tidak valid.\n";
    }
  }
}

// == RSA CHIPER ==
// Fungsi untuk mengecek apakah sebuah bilangan prima
int isPrima(int number)
{
  // init
  int i;
  // kode
  for (i = 2; i < number; i++)
  {
    if (number % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

// Fungsi untuk menghitung GCD menggunakan Algoritma Euclid
int gcd(int a, int b)
{
  while (b != 0)
  {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// Fungsi untuk menghitung GCD menggunakan Algoritma Euclid
int gcdExtended(int a, int b, int &x, int &y)
{
  if (a == 0)
  {
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

// Berfungsi untuk mencari invers modular dari e modulo phi(n) / totint
int modInverse(int e, int phi)
{
  int x, y;
  int gcd = gcdExtended(e, phi, x, y);
  if (gcd != 1)
  {
    cout << "Invers tidak ada!" << endl;
    return -1;
  }
  else
  {
    // Make x positive
    int d = (x % phi + phi) % phi;
    return d;
  }
}

// Fungsi generate kunci
void generateKunci()
{
  // INIT
  int p, q, n_modulus, fi_totint, e_kunciPublik, d_kunciPrivat;
  // KODE BEKERJA
  judul();
  cout << "Generate Kunci untuk RSA \n\n";
  // Input p harus prima
  cout << "Note = p harus bilangain prima \nMasukkan p : ";
  cin >> p;
  while (isPrima(p) == 0)
  {
    cout << "p tidak prima masukan lagi digit lagi !!!" << endl;
    cout << "Masukkan p : ";
    cin >> p;
  }
  // Input q harus prima
  cout << "\nNote = q harus bilangain prima dan tidak boleh sama dengan p \n"
          "Masukkan q : ";
  cin >> q;
  while (isPrima(q) == 0 && p == q)
  {
    cout << "p tidak prima masukan lagi digit lagi !!!" << endl;
    cout << "Masukkan q : ";
    cin >> q;
  }

  // Menghitung n - modulus dan fi - totint
  n_modulus = p * q;
  fi_totint = (p - 1) * (q - 1);
  // Input e - kunci publik
  cout << "\nNote = e adalah Kunci Publik \n";
  cout << "Masukkan e : ";
  cin >> e_kunciPublik;
  while ((e_kunciPublik >= 1 || e_kunciPublik < fi_totint) &&
         !(gcd(e_kunciPublik, fi_totint) == 1))
  {
    cout << "e tidak sesuai dengan aturan ... \n";
    cout << "Masukkan e : ";
    cin >> e_kunciPublik;
  }

  // Menghitung d - kunci privat
  d_kunciPrivat = modInverse(e_kunciPublik, fi_totint);

  // Output
  cout << "\nIni adalah Kunci Publik, Kunci Privat, dan Modulus untuk "
          "digunakan dalam RSA \n";
  cout << "Kunci Publik : " << e_kunciPublik << endl;
  cout << "Kunci Privat : " << d_kunciPrivat << endl;
  cout << "Modulus : " << n_modulus << endl;
  cout << endl;
};

// Fungsi untuk menghitung base^eksponen mod modulus secara efisien, rumus RSA
long long modExp(long long base, long long exponent, long long modulus)
{
  long long result = 1;
  base = base % modulus;

  while (exponent > 0)
  {
    // Jika exponent adalah bilangan ganjil, kalikan dengan base
    if (exponent % 2 == 1)
    {
      result = (result * base) % modulus;
    }
    // Pembagian exponent dengan 2
    // menggunakan `>>` Operator bitwise digunakan untuk menggeser bit suatu bilangan biner ke kanan
    exponent = exponent >> 1;       // Sama dengan exponent /= 2
    base = (base * base) % modulus; // Square base
  }

  return result;
}

// Fungsi - Enkripsi
vector<long long> encrypt(const string &plaintext, long long e, long long n)
{
  vector<long long> ciphertext;
  for (char ch : plaintext)
  {
    long long encryptedChar = modExp(static_cast<long long>(ch), e, n);
    ciphertext.push_back(encryptedChar);
  }
  return ciphertext;
}

// Fungsi - Dekripsi
string decrypt(const vector<long long> &ciphertext, long long d, long long n)
{
  string plaintext;
  for (long long encryptedChar : ciphertext)
  {
    char decryptedChar = static_cast<char>(modExp(encryptedChar, d, n));
    plaintext += decryptedChar;
  }
  return plaintext;
}

// Fungsi untuk mengubah input string menjadi vector
vector<long long> parseInputToVector(const string &input)
{
  vector<long long> vec;
  stringstream ss(input);
  long long number;
  while (ss >> number)
  {
    vec.push_back(number);
  }
  return vec;
}

// ENKRIPSI
void enkripsiRSA()
{
  // INIT
  string plaintextInput;
  int kunciPublik, modulus;

  // TAMPILAN
  judul();
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
  for (int i = 0; i < plaintextInput.length(); i++)
  {
    plaintextASCI[i] = (int)plaintextInput[i]; //(int)plaintextInput[i] diconvert ke integer
    // cout << plaintextASCI[i] << " ";
  }
  cout << endl;
  cout << "Plaintext  : " << plaintextInput << endl;

  // 2. Enkripsi
  vector<long long> ciphertext = encrypt(plaintextInput, kunciPublik, modulus);
  cout << "Ciphertext : ";
  for (long long value : ciphertext)
  {
    cout << value << " ";
  }
  cout << endl;
}

// DEKRIPSI
void dekripsiRSA()
{
  // INIT
  string ciphertextInput;
  int kunciPrivat, modulus;
  // TAMPILAN
  judul();
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
  cout << "Ciphertext : ";
  for (long long value : ciphertext)
  {
    cout << value << " ";
  }
  cout << endl;

  // 2. Dekripsi + Tampilkan
  string decryptedText = decrypt(ciphertext, kunciPrivat, modulus);
  cout << "Plaintext  : " << decryptedText << endl;
}

// FUNGSI TAMPILAN
void judul()
{
  cout << "----------------------------------------" << endl;
  cout << "   >> RSA - (Rivest-Shamir-Adleman) <<  " << endl;
  cout << "----------------------------------------" << endl;
}

void rsa()
{
  // Init
  char menu;
  // Tampilan
  do
  {
    cout << endl;
    judul();
    cout << "Pilih mode yang akan di inginkan : \n";
    cout << "0. Generate Kunci \n";
    cout << "1. Enkripsi \n";
    cout << "2. Dekripsi \n";
    cout << "3. Keluar \n";
    cout << "Masukan mode yang diinginkan : ";
    cin >> menu;
    cout << endl;
    if (menu == '0')
    {
      system("cls");
      generateKunci();
    }
    else if (menu == '1')
    {
      system("cls");
      enkripsiRSA();
      cout << endl;
    }
    else if (menu == '2')
    {
      system("cls");
      dekripsiRSA();
      cout << endl;
    }
    else if (menu == '3'){
      cout << "Keluar dari Menu RSA" << endl;
      return;
      break;
    }
    cout << "kembali ke menu (y/n) : ";
    cin >> menu;
    system("cls");
  } while (menu == 'y' || menu == 'Y');
}
