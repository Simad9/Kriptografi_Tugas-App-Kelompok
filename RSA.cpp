// Kode Algoritma Kriptografi RSA
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Fungsi - Generate Kunci

void judul();

int isPrima(int number);
int gcd(int a, int b);
void generateKunci();

long long modExp(long long base, long long exponent, long long modulus);
vector<long long> encrypt(const string &plaintext, long long e, long long n);
string decrypt(const vector<long long> &ciphertext, long long d, long long n);
vector<long long> parseInputToVector(const string &input);

void enkripsiRSA();
void dekripsiRSA();

void rsa();

int main() {
  rsa();
  return 0;
}

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
  judul();
  cout << "Generate Kunci untuk RSA \n\n";
  // Input p harus prima
  cout << "Note = p harus bilangain prima \nMasukkan p : ";
  cin >> p;
  while (isPrima(p) == 0) {
    cout << "p tidak prima masukan lagi digit lagi !!!" << endl;
    cout << "Masukkan p : ";
    cin >> p;
  }
  // Input q harus prima
  cout << "\nNote = q harus bilangain prima dan tidak boleh sama dengan p \n"
          "Masukkan q : ";
  cin >> q;
  while (isPrima(q) == 0 && p == q) {
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
         !(gcd(e_kunciPublik, fi_totint) == 1)) {
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
  for (int i = 0; i < plaintextInput.length(); i++) {
    plaintextASCI[i] = (int)plaintextInput[i];
    // cout << plaintextASCI[i] << " ";
  }
  cout << endl;
  cout << "Plaintext  : " << plaintextInput << endl;

  // 2. Enkripsi
  vector<long long> ciphertext = encrypt(plaintextInput, kunciPublik, modulus);
  cout << "Ciphertext : ";
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
  for (long long value : ciphertext) {
    cout << value << " ";
  }
  cout << endl;

  // 2. Dekripsi + Tampilkan
  string decryptedText = decrypt(ciphertext, kunciPrivat, modulus);
  cout << "Plaintext  : " << decryptedText << endl;
}

// FUNGSI TAMPILAN
void judul() {
  cout << "----------------------------------------" << endl;
  cout << "   >> RSA - (Rivest-Shamir-Adleman) <<  " << endl;
  cout << "----------------------------------------" << endl;
}

void rsa() {
  // Init
  char menu;
  // Tampilan
  do {
    judul();
    cout << "Pilih mode yang akan di inginkan : \n";
    cout << "0. Generate Kunci \n";
    cout << "1. Enkripsi \n";
    cout << "2. Dekripsi \n";
    cout << "Masukan mode yang diinginkan : ";
    cin >> menu;
    cout << endl;
    if (menu == '0') {
      system("cls");
      generateKunci();
    } else if (menu == '1') {
      system("cls");
      enkripsiRSA();
      cout << endl;
    } else if (menu == '2') {
      system("cls");
      dekripsiRSA();
      cout << endl;
    }
    cout << "kembali ke menu (y/n) : ";
    cin >> menu;
    system("cls");
  } while (menu == 'y' || menu == 'Y');
}