// Kode Algoritma Kriptografi RSA
// sumber informasi : https://www.geeksforgeeks.org/rsa-algorithm-cryptography/

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Fungsi - Generate Kunci
int isPrima(int number);
int gcd(int a, int b);
void generateKunci();

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
// Fungsi untuk melakukan enkripsi
vector<long long> encrypt(const std::string &plaintext, long long e,
                          long long n) {
  vector<long long> ciphertext;
  for (char ch : plaintext) {
    long long encryptedChar = modExp(static_cast<long long>(ch), e, n);
    ciphertext.push_back(encryptedChar);
  }
  return ciphertext;
}

// Fungsi - Dekripsi
// Fungsi untuk melakukan dekripsi
string decrypt(const std::vector<long long> &ciphertext, long long d,
               long long n) {
  string plaintext;
  for (long long encryptedChar : ciphertext) {
    char decryptedChar = static_cast<char>(modExp(encryptedChar, d, n));
    plaintext += decryptedChar;
  }
  return plaintext;
}

// Fungsi Tampilan
void tampilan();

// Try dan Error
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
  cout << std::endl;
}

// DEKRIPSI
// Fungsi untuk mengubah input string menjadi vector
std::vector<long long> parseInputToVector(const std::string &input) {
  std::vector<long long> vec;
  std::stringstream ss(input);
  long long number;
  while (ss >> number) {
    vec.push_back(number);
  }
  return vec;
}

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
  cout << std::endl;

  // 2. Dekripsi + Tampilkan
  string decryptedText = decrypt(ciphertext, kunciPrivat, modulus);
  cout << "Decrypted Text: " << decryptedText << endl;
}

int main() {
  tampilan();
  return 0;
}

// KUMPULAN FUNGSI

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

void tampilan() {
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
