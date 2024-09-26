#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Fungsi untuk menghitung gcd
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// Fungsi untuk menghitung modulo invers
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1; // tidak ditemukan
}

// Fungsi untuk mengenkripsi plaintext
int encrypt(int m, int e, int n) {
    int c = 1;
    for (int i = 0; i < e; i++) {
        c = (c * m) % n;
    }
    return c;
}

// Fungsi untuk mendekripsi ciphertext
int decrypt(int c, int d, int n) {
    int m = 1;
    for (int i = 0; i < d; i++) {
        m = (m * c) % n;
    }
    return m;
}

// Fungsi untuk mengubah string ke integer
int stringToInt(const string &s) {
    int num = 0;
    for (char ch : s) {
        num = num * 256 + ch; // Menggunakan 256 untuk representasi karakter
    }
    return num;
}

// Fungsi untuk mengubah integer ke string
string intToString(int num) {
    string s;
    while (num > 0) {
        s = char(num % 256) + s; // Menggunakan 256 untuk representasi karakter
        num /= 256;
    }
    return s;
}

int main() {
    // Nilai kunci RSA
    int p = 61, q = 53;
    int n = p * q; // n
    int phi = (p - 1) * (q - 1); // φ(n)
    int e = 17; // Eksponen publik
    int d = modInverse(e, phi); // Eksponen privat

    // Pesan yang akan dienkripsi
    string plaintext = "Halo";
    int m = stringToInt(plaintext); // Ubah plaintext ke integer

    // Enkripsi
    int c = encrypt(m, e, n);
    cout << "Ciphertext: " << c << endl;

    // Dekripsi
    int decrypted = decrypt(c, d, n);
    string decryptedText = intToString(decrypted); // Ubah integer kembali ke string

    // Menampilkan hasil
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
