#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to encrypt a file using DES
void encryptFile(const char* inputFile, const char* outputFile, const char* key) {
    FILE* in = fopen(inputFile, "rb");
    FILE* out = fopen(outputFile, "wb");
    DES_cblock desKey;
    DES_key_schedule desKeySchedule;

    // Initialize DES key from the provided key
    DES_string_to_key(key, &desKey);

    // Set up encryption context
    DES_set_key(&desKey, &desKeySchedule);

    // Read and encrypt file contents
    unsigned char inputBuffer[8];
    unsigned char outputBuffer[8];
    size_t bytesRead;

    while ((bytesRead = fread(inputBuffer, 1, 8, in)) > 0) {
        DES_ecb_encrypt(inputBuffer, outputBuffer, &desKeySchedule, DES_ENCRYPT);
        fwrite(outputBuffer, 1, bytesRead, out);
    }

    fclose(in);
    fclose(out);
}

// Function to decrypt a file using DES
void decryptFile(const char* inputFile, const char* key) {
    FILE* in = fopen(inputFile, "rb");
    DES_cblock desKey;
    DES_key_schedule desKeySchedule;

    // Initialize DES key from the provided key
    DES_string_to_key(key, &desKey);

    // Set up decryption context
    DES_set_key(&desKey, &desKeySchedule);

    // Read and decrypt file contents
    unsigned char inputBuffer[8];
    unsigned char outputBuffer[8];
    size_t bytesRead;

    while ((bytesRead = fread(inputBuffer, 1, 8, in)) > 0) {
        DES_ecb_encrypt(inputBuffer, outputBuffer, &desKeySchedule, DES_DECRYPT);
        fwrite(outputBuffer, 1, bytesRead, stdout); // Display decrypted content on console
    }

    fclose(in);
}

int main() {
    const char* key = "MySecretKey"; // Replace with your own key
    const char* inputFile = "plaintext.txt"; // Replace with your input file
    const char* encryptedFile = "encrypted.dat";
    const char* decryptedFile = "decrypted.txt";

    // Encrypt the input file
    encryptFile(inputFile, encryptedFile, key);
    printf("File encrypted successfully.\n");

    // Decrypt and display the encrypted file
    printf("Decrypted content:\n");
    decryptFile(encryptedFile, key);

    return 0;
}

