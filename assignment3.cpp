#include <iostream>
#include <string>
using namespace std;

// Encryption: Shifts ASCII values and applies XOR with the key
string encrypt(string text, int key) {
    string cipher = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        // XOR with key, then add key value
        ch = (ch ^ key) + key;
        cipher += ch;
    }
    return cipher;
}

// Decryption: Reverses the encryption process
string decrypt(string cipher, int key) {
    string plain = "";
    for (int i = 0; i < cipher.length(); i++) {
        char ch = cipher[i];
        // Reverse the process: subtract key, then XOR again
        ch = (ch - key) ^ key;
        plain += ch;
    }
    return plain;
}

int main() {
    string text;
    int key;
    
    cout << "Enter text: ";
    getline(cin, text);
    cout << "Enter key (integer): ";
    cin >> key;
    
    string encrypted = encrypt(text, key);
    string decrypted = decrypt(encrypted, key);
    
    cout << "\nOriginal Text: " << text;
    cout << "\nEncrypted Text: " << encrypted;
    cout << "\nDecrypted Text: " << decrypted << endl;
    
    return 0;
}
