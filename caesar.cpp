#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <conio.h>

using namespace std;

void caesar();

int main()
{
    caesar();
}

void caesar()
{
  int milih, shift;
  string text;
  char ulang;

  do
  {
    system("cls");
    cout << " " << setw(41) << setfill('-') << " " << endl;
    cout << left << setw(10) << setfill(' ') << " " << setw(34) << " >> CAESAR CHIPER << " << " " << endl;
    cout << " " << setw(41) << setfill('-') << " " << endl;

    cout << "  Pilih mode yang di inginkan   : " << endl;
    cout << "    1. Enkripsi" << endl;
    cout << "    2. Deskripsi" << endl;
    cout << "    3. Keluar" << endl;
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
        if (isalpha(text[i])) // Cek apakah karakter adalah huruf
        {
          char base = isupper(text[i]) ? 'A' : 'a'; // Huruf besar atau kecil
          text[i] = (text[i] - base + shift) % 26 + base; // Geser huruf
        }
        else if (isdigit(text[i]))  // Cek apakah karakter adalah angka
        {
          text[i] = (text[i] - '0' + shift) % 10 + '0'; // Geser angka
        }
        else if (text[i] == ' ')  // Abaikan spasi
        {
          continue;
        }
        else
        {
          cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
          return;
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
        {
          char base = isupper(text[i]) ? 'A' : 'a';
          text[i] = (text[i] - base - shift + 26) % 26 + base;
        }
        else if (isdigit(text[i]))
        {
          text[i] = (text[i] - '0' - shift + 10) % 10 + '0';
        }
        else if (text[i] == ' ')
        {
          continue;
        }
        else
        {
          cout << "  Error: Teks mengandung karakter non-huruf/non-angka pada posisi " << i + 1 << "!" << endl;
          return;
        }
      }
      cout << "  Hasil Dekripsi : " << text << endl;
    }
    else if (milih == 3)
    {
      return; // Kembali ke menu utama
    }
    else
    {
      cout << "  Input salah atau tidak tersedia." << endl;
    }

    cout << endl;
    cout << "  Kembali ke Menu Caesar (y/t) : ";
    cin >> ulang;
  } while (toupper(ulang) == 'Y');
}
