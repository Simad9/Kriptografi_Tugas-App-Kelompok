#include <iostream>
#include <vector>
#include <cmath>

// Fungsi untuk menghitung (base^exponent) mod modulus
long long modExp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    
    while (exponent > 0) {
        // Jika exponent adalah bilangan ganjil, kalikan dengan base
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        // Pembagian exponent dengan 2
        exponent = exponent >> 1; // Sama dengan exponent /= 2
        base = (base * base) % modulus; // Square base
    }
    
    return result;
}

// Fungsi untuk melakukan enkripsi
std::vector<long long> encrypt(const std::string &plaintext, long long e, long long n) {
    std::vector<long long> ciphertext;
    for (char ch : plaintext) {
        long long encryptedChar = modExp(static_cast<long long>(ch), e, n);
        ciphertext.push_back(encryptedChar);
    }
    return ciphertext;
}

// Fungsi untuk melakukan dekripsi
std::string decrypt(const std::vector<long long> &ciphertext, long long d, long long n) {
    std::string plaintext;
    for (long long encryptedChar : ciphertext) {
        char decryptedChar = static_cast<char>(modExp(encryptedChar, d, n));
        plaintext += decryptedChar;
    }
    return plaintext;
}

int main() {
    std::string plaintext = "Halo";
    long long e = 17;
    long long n = 3233;
    long long d = 2753;

    // Enkripsi
    std::vector<long long> ciphertext = encrypt(plaintext, e, n);
    
    std::cout << "Ciphertext: ";
    for (long long value : ciphertext) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Dekripsi
    std::string decryptedText = decrypt(ciphertext, d, n);
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
