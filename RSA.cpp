// Kode Algoritma Kriptografi RSA
// sumber informasi : https://www.geeksforgeeks.org/rsa-algorithm-cryptography/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Fungsi - Generate Kunci
int isPrima(int number);
int gcd(int a, int b);
void generateKunci();

// Fungsi - Enkripsi

// Fungsi - Dekripsi

// Fungsi Tampilan
void tampilan();

// Try dan Error
void enkripsiRSA() {
  // INIT
  string plaintext;
  int kunciPublik, modulus;

  // TAMPILAN
  cout << "Enkripsi Metode RSA \n\n";
  cout << "Masukkan Plaintext : ";
  cin >> plaintext;
  cout << "Masukkan Kunci Publik : ";
  cin >> kunciPublik;
  cout << "Masukkan Modulus : ";
  cin >> modulus;
  cout << endl;
  // CODE BERKERJA
  // 1. Plaintext ubah jadi ASCII
  int plaintextASCI[plaintext.length()];

  // konversi plaintext
  for (int i = 0; i < plaintext.length(); i++) {
    plaintextASCI[i] = (int)plaintext[i];
  }
  cout << endl;
  // Tampilkan arci
  for (int i = 0; i < plaintext.length(); i++) {
    cout << plaintextASCI[i] << " ";
  }

  // 2. Enkripsi
  int chipertext[plaintext.length()];
  for (int i = 0; i < plaintext.length(); i++) {
    chipertext[i] = (plaintextASCI[i] * kunciPublik) % modulus;
  }

  // 3. Tampilakan Chipertext
  for (int i = 0; i < plaintext.length(); i++) {
    cout << chipertext[i] << " ";
  }
}

void dekripsiRSA() {
  // INIT
  string ciphertext;
  int kunciPrivat, modulus;
  // TAMPILAN
  cout << "Dekripsi Metode RSA \n\n";
  cout << "Masukkan Ciphertext : ";
  getline(cin >> ws, ciphertext);
  cout << "Masukkan Kunci Privat : ";
  cin >> kunciPrivat;
  cout << "Masukkan Modulus : ";
  cin >> modulus;
  cout << endl;
  // CODE BERKERJA
  std::istringstream iss(ciphertext);
  std::vector<int> numbers;
  int number;

  // Memecah string menjadi angka dan memasukkannya ke dalam array
  while (iss >> number) {
    numbers.push_back(number);
  }

  for (size_t i = 0; i < numbers.size(); ++i) {
    int result = (numbers[i] * kunciPrivat) % modulus;
    std::cout << result << " ";
  }

  // 1. Ciphertext ubah jadi array dulu

  // 2. Dekripsi

  // 3. Tampilkan
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
  while ((e_kunciPublik < 2 || e_kunciPublik > fi_totint) &&
         (gcd(e_kunciPublik, fi_totint) != 1)) {
    cout << "Masukkan e : ";
    cin >> e_kunciPublik;
  }

  // Menghitung d - kunci privat
  e_kunciPublik = e_kunciPublik % fi_totint;
  for (int x = 1; x < fi_totint; x++) {
    if ((e_kunciPublik * x) % fi_totint == 1) {
      d_kunciPrivat = x;
    }
  }

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
