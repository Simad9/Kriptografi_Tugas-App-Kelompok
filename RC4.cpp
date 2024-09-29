#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

// Fungsi untuk inisialisasi state RC4
void rc4_init(vector<int>& S, const string& key) {
    int j = 0;
    int key_len = key.size();

    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        swap(S[i], S[j]);
    }
}

// Fungsi untuk mengenkripsi atau mendekripsi
string rc4_crypt(const string& data, const string& key) {
    vector<int> S(256);
    rc4_init(S, key);

    int i = 0, j = 0;
    string result = data;

    for (size_t k = 0; k < data.size(); k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);

        int rnd = S[(S[i] + S[j]) % 256];
        result[k] ^= rnd;
    }

    return result;
}

// Fungsi untuk konversi string ke hexadecimal
string rc4_to_hex(const string& str) {
    stringstream ss;
    for (unsigned char c : str) {
        ss << hex << setw(2) << setfill('0') << (int)c;
    }
    return ss.str();
}

// Fungsi untuk konversi hexadecimal ke string
string rc4_from_hex(const string& hex_str) {
    stringstream ss;
    for (size_t i = 0; i < hex_str.length(); i += 2) {
        string byte = hex_str.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        ss << chr;
    }
    return ss.str();
}

// Fungsi menu utama
void menu() {
    int pilihan;
    string key, input;

    while (true) {
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 3) {
            break;
        }

        cout << "Masukkan kunci: ";
        cin >> key;

        if (pilihan == 1) {
            cout << "Masukkan plain text: ";
            cin.ignore();
            getline(cin, input);

            string encrypted = rc4_crypt(input, key);
            string encrypted_hex = rc4_to_hex(encrypted);
            cout << "Hasil enkripsi (hex): " << encrypted_hex << endl;
        } else if (pilihan == 2) {
            cout << "Masukkan cipher text (hex): ";
            cin.ignore();
            getline(cin, input);

            string decrypted = rc4_crypt(rc4_from_hex(input), key);
            cout << "Hasil dekripsi: " << decrypted << endl;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
