#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const int Nb = 4;  // AES block size is 4 words
const int Nk = 4;  // Key length (4 words for AES-128)
const int Nr = 10; // Number of rounds (10 for AES-128)

// S-box
unsigned char s_box[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

// Inverse S-box
unsigned char inv_s_box[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

// Rcon table for Key Expansion
unsigned char Rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb};

void KeyExpansion(unsigned char *key, unsigned char *w)
{
    unsigned char temp[4];
    int i = 0;

    while (i < 4 * Nk)
    {
        w[i] = key[i];
        i++;
    }

    i = Nk;
    while (i < Nb * (Nr + 1))
    {
        for (int j = 0; j < 4; j++)
        {
            temp[j] = w[(i - 1) * 4 + j];
        }

        if (i % Nk == 0)
        {
            // Rotate word and apply S-box
            unsigned char tmp = temp[0];
            temp[0] = s_box[temp[1]];
            temp[1] = s_box[temp[2]];
            temp[2] = s_box[temp[3]];
            temp[3] = s_box[tmp];

            temp[0] ^= Rcon[i / Nk];
        }

        for (int j = 0; j < 4; j++)
        {
            w[i * 4 + j] = w[(i - Nk) * 4 + j] ^ temp[j];
        }
        i++;
    }
}

void AddRoundKey(unsigned char state[][4], unsigned char *roundKey)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] ^= roundKey[i * Nb + j];
        }
    }
}
void SubBytes(unsigned char state[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = s_box[state[i][j]];
        }
    }
}

void InvSubBytes(unsigned char state[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = inv_s_box[state[i][j]];
        }
    }
}

void ShiftRows(unsigned char state[][4])
{
    unsigned char temp;

    // Row 1 shift
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Row 2 shift
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Row 3 shift
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

void InvShiftRows(unsigned char state[][4])
{
    unsigned char temp;

    // Row 1 inverse shift
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;

    // Row 2 inverse shift
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Row 3 inverse shift
    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

void MixColumns(unsigned char state[][4])
{
    unsigned char temp[4];

    for (int i = 0; i < 4; i++)
    {
        temp[0] = (unsigned char)(0x02 * state[0][i] ^ 0x03 * state[1][i] ^ state[2][i] ^ state[3][i]);
        temp[1] = (unsigned char)(state[0][i] ^ 0x02 * state[1][i] ^ 0x03 * state[2][i] ^ state[3][i]);
        temp[2] = (unsigned char)(state[0][i] ^ state[1][i] ^ 0x02 * state[2][i] ^ 0x03 * state[3][i]);
        temp[3] = (unsigned char)(0x03 * state[0][i] ^ state[1][i] ^ state[2][i] ^ 0x02 * state[3][i]);

        for (int j = 0; j < 4; j++)
        {
            state[j][i] = temp[j];
        }
    }
}

void InvMixColumns(unsigned char state[][4])
{
    unsigned char temp[4];

    for (int i = 0; i < 4; i++)
    {
        temp[0] = (unsigned char)(0x0e * state[0][i] ^ 0x0b * state[1][i] ^ 0x0d * state[2][i] ^ 0x09 * state[3][i]);
        temp[1] = (unsigned char)(0x09 * state[0][i] ^ 0x0e * state[1][i] ^ 0x0b * state[2][i] ^ 0x0d * state[3][i]);
        temp[2] = (unsigned char)(0x0d * state[0][i] ^ 0x09 * state[1][i] ^ 0x0e * state[2][i] ^ 0x0b * state[3][i]);
        temp[3] = (unsigned char)(0x0b * state[0][i] ^ 0x0d * state[1][i] ^ 0x09 * state[2][i] ^ 0x0e * state[3][i]);

        for (int j = 0; j < 4; j++)
        {
            state[j][i] = temp[j];
        }
    }
}

void AES_Encrypt_Block(unsigned char *input, unsigned char *output, unsigned char *key)
{
    unsigned char state[4][4];

    // Copy input to state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = input[i * 4 + j];
        }
    }

    unsigned char expandedKey[Nb * (Nr + 1) * 4];
    KeyExpansion(key, expandedKey);

    AddRoundKey(state, expandedKey);

    for (int round = 1; round < Nr; round++)
    {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey + round * Nb * 4);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey + Nr * Nb * 4);

    // Copy state to output
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[i * 4 + j] = state[j][i];
        }
    }
}

void AES_Decrypt_Block(unsigned char *input, unsigned char *output, unsigned char *key)
{
    unsigned char state[4][4];

    // Copy input to state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = input[i * 4 + j];
        }
    }

    unsigned char expandedKey[Nb * (Nr + 1) * 4];
    KeyExpansion(key, expandedKey);

    AddRoundKey(state, expandedKey + Nr * Nb * 4);

    for (int round = Nr - 1; round > 0; round--)
    {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, expandedKey + round * Nb * 4);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, expandedKey);

    // Copy state to output
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[i * 4 + j] = state[j][i];
        }
    }
}

void AES_Encrypt(vector<unsigned char> &input, vector<unsigned char> &output, unsigned char *key)
{
    // Pad input if necessary
    int paddingLength = 16 - (input.size() % 16);
    input.insert(input.end(), paddingLength, paddingLength); // PKCS7 padding

    for (size_t i = 0; i < input.size(); i += 16)
    {
        unsigned char block[16];
        unsigned char encryptedBlock[16];

        // Copy input block
        for (int j = 0; j < 16; j++)
        {
            block[j] = input[i + j];
        }

        AES_Encrypt_Block(block, encryptedBlock, key);

        // Append encrypted block to output
        for (int j = 0; j < 16; j++)
        {
            output.push_back(encryptedBlock[j]);
        }
    }
}

void AES_Decrypt(vector<unsigned char> &input, vector<unsigned char> &output, unsigned char *key) {
    // Pastikan input adalah kelipatan dari 16 byte
    if (input.size() % 16 != 0) {
        throw std::length_error("Encrypted data length must be a multiple of 16 bytes.");
    }

    for (size_t i = 0; i < input.size(); i += 16) {
        unsigned char block[16];
        unsigned char decryptedBlock[16];

        // Copy input block
        for (int j = 0; j < 16; j++) {
            block[j] = input[i + j];
        }

        AES_Decrypt_Block(block, decryptedBlock, key);

        // Append decrypted block to output
        for (int j = 0; j < 16; j++) {
            output.push_back(decryptedBlock[j]);
        }
    }

    // Remove padding (PKCS#7)
    if (!output.empty()) {
        int paddingLength = output.back();
        
        // Cek validitas padding
        if (paddingLength > 0 && paddingLength <= 16) {
            // Pastikan padding benar
            bool validPadding = true;
            for (int i = 0; i < paddingLength; i++) {
                if (output[output.size() - 1 - i] != paddingLength) {
                    validPadding = false;
                    break;
                }
            }

            if (validPadding) {
                output.resize(output.size() - paddingLength);  // Hapus padding
            }
        }
    }
}

int main()
{
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0xcf, 0x9f, 0x2f, 0x3c, 0xd4, 0x9a};

    // Convert plaintext to a vector of unsigned char
    vector<unsigned char> input(plaintext.begin(), plaintext.end());
    vector<unsigned char> encryptedOutput;
    vector<unsigned char> decryptedOutput;

    // Encrypt the input
    AES_Encrypt(input, encryptedOutput, key);

    cout << "Encrypted output (hex): ";
    for (unsigned char byte : encryptedOutput)
    {
        cout << hex << setw(2) << setfill('0') << (int)byte;
    }
    cout << endl;

    // Decrypt the encrypted data
    AES_Decrypt(encryptedOutput, decryptedOutput, key);

    cout << "Decrypted output: ";
    for (unsigned char byte : decryptedOutput)
    {
        cout << byte;
    }
    cout << endl;

    return 0;
}
