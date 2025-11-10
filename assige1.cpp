#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;

// ------------------------------------
// 1️⃣ Caesar Cipher Encryption
// ------------------------------------
string caesarEncrypt(string text, int key)
{
    string result = "";

    for (char c : text)
    {
        if (isalpha(c))
        {
            char base;
            if (isupper(c))
                base = 'A';
            else
                base = 'a';

            int position = c - base;
            int newPosition = (position + key) % 26;
            char newChar = base + newPosition;

            result += newChar;
        }
        else
        {
            result += c;
        }
    }
    return result;
}

// ------------------------------------
// 2️⃣ Poly Cipher (Vigenère logic)
// ------------------------------------
string polyEncrypt(string text, string key)
{
    string result = "";
    int j = 0;

    for (char c : text)
    {
        if (isalpha(c))
        {
            char base;
            if (isupper(c))
                base = 'A';
            else
                base = 'a';

            int textPos = c - base;
            int keyPos = tolower(key[j % key.size()]) - 'a';

            int newPos = (textPos + keyPos) % 26;
            char newChar = base + newPos;

            result += newChar;
            j++;
        }
        else
        {
            result += c;
        }
    }

    return result;
}

// ------------------------------------
// 3️⃣ Rail Fence Cipher Encryption
// ------------------------------------
string railFenceEncrypt(string text, int rails)
{
    if (rails <= 1)
        return text;

    vector<string> rail(rails);
    int dir = 1;
    int row = 0;

    for (char c : text)
    {
        rail[row] += c;

        if (row == 0)
            dir = 1;
        else if (row == rails - 1)
            dir = -1;

        row += dir;
    }

    string result = "";
    for (int i = 0; i < rails; i++)
        result += rail[i];

    return result;
}

// ------------------------------------
// 4️⃣ Vernam Cipher Encryption
// ------------------------------------
string vernamEncrypt(string text, string key)
{
    string result = "";

    for (int i = 0; i < text.size(); i++)
    {
        unsigned char c = text[i];
        unsigned char k = key[i % key.size()];
        unsigned char enc = c ^ k;

        stringstream ss;
        ss << hex << setw(2) << setfill('0') << (int)enc;
        result += ss.str();
    }

    return result;
}

// ------------------------------------
// 5️⃣ Vigenère Cipher Encryption
// ------------------------------------
string vigenereEncrypt(string text, string key)
{
    string result = "";
    int keyIndex = 0;
    int keyLength = key.length();

    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            char base;
            if (isupper(c))
                base = 'A';
            else
                base = 'a';

            char keyChar = key[keyIndex % keyLength];
            if (isupper(keyChar))
                keyChar = tolower(keyChar);

            int keyShift = keyChar - 'a';
            int position = c - base;
            int newPosition = (position + keyShift) % 26;
            char newChar = base + newPosition;

            result += newChar;
            keyIndex++;
        }
        else
        {
            result += c;
        }
    }

    return result;
}

// ------------------------------------
// 6️⃣ One-Time Pad Cipher Encryption
// ------------------------------------
string oneTimePadEncrypt(string text, string key)
{
    string result = "";

    for (int i = 0; i < text.size(); i++)
    {
        unsigned char c = text[i];
        unsigned char k = key[i];
        unsigned char enc = c ^ k;

        stringstream ss;
        ss << hex << setw(2) << setfill('0') << (int)enc;
        result += ss.str();
    }
    return result;
}

// ------------------------------------
// MAIN FUNCTION WITH SWITCH MENU
// ------------------------------------
int main()
{
    int choice;
    string text, key;
    int keyNum, rails;

    cout << "==============================" << endl;
    cout << " 🔐 MULTI CIPHER ENCRYPTION " << endl;
    cout << "==============================" << endl;
    cout << "1. Caesar Cipher" << endl;
    cout << "2. Poly Cipher (Vigenere logic)" << endl;
    cout << "3. Rail Fence Cipher" << endl;
    cout << "4. Vernam Cipher" << endl;
    cout << "5. Vigenere Cipher" << endl;
    cout << "6. One-Time Pad Cipher" << endl;
    cout << "Enter your choice (1–6): ";
    cin >> choice;
    cin.ignore();

    cout << "\nEnter text to encrypt: ";
    getline(cin, text);

    switch (choice)
    {
    case 1:
        cout << "Enter key (number): ";
        cin >> keyNum;
        cout << "\nEncrypted Text: " << caesarEncrypt(text, keyNum) << endl;
        break;

    case 2:
        cout << "Enter key (word): ";
        cin >> key;
        cout << "\nEncrypted Text: " << polyEncrypt(text, key) << endl;
        break;

    case 3:
        cout << "Enter number of rails: ";
        cin >> rails;
        cout << "\nEncrypted Text: " << railFenceEncrypt(text, rails) << endl;
        break;

    case 4:
        cout << "Enter key (word): ";
        cin >> key;
        cout << "\nEncrypted (Hex): " << vernamEncrypt(text, key) << endl;
        break;

    case 5:
        cout << "Enter key (word): ";
        cin >> key;
        cout << "\nEncrypted Text: " << vigenereEncrypt(text, key) << endl;
        break;

    case 6:
        cout << "Enter key (same length as text): ";
        cin >> key;
        if (key.size() != text.size())
        {
            cout << "❌ Error: Key length must match text length!" << endl;
        }
        else
        {
            cout << "\nEncrypted (Hex): " << oneTimePadEncrypt(text, key) << endl;
        }
        break;

    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
