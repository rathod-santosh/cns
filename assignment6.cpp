#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Check if number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// Compute GCD
int gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

// Compute modular inverse (for finding d)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Fast modular exponentiation (for encryption/decryption)
long long powerMod(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        exp /= 2;
        base = (base * base) % mod;
    }
    return res;
}

// Simple numeric hash function
long long simpleHash(string msg) {
    long long hash = 0;
    for (char c : msg)
        hash = (hash * 31 + (c - '0')) % 100000; // numeric hash
    return hash;
}

// RSA encryption
long long rsaEncrypt(long long msg, int e, int n) {
    return powerMod(msg, e, n);
}

// RSA decryption
long long rsaDecrypt(long long cipher, int d, int n) {
    return powerMod(cipher, d, n);
}

int main() {
    srand(time(0));

    cout << "Generating RSA key pair..." << endl;

    int p = 1, q = 1;
    // pick random primes between 50–149
    while (!isPrime(p)) p = rand() % 100 + 50;
    while (!isPrime(q) || p == q) q = rand() % 100 + 50;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // choose e such that gcd(e, phi) == 1
    int e = rand() % (phi - 2) + 2;
    while (gcd(e, phi) != 1)
        e = rand() % (phi - 2) + 2;

    int d = modInverse(e, phi);

    cout << "\nRSA Key Pair Generated Successfully" << endl;
    cout << "Prime Numbers: p = " << p << ", q = " << q << endl;
    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // Input numeric message
    string msgStr;
    cout << "\nEnter a numeric message (digits only): ";
    cin >> msgStr;

    long long message = stoll(msgStr);

    if (message >= n) {
        cout << "\nError: Message must be smaller than n (" << n << ")." << endl;
        return 0;
    }

    // Step 1: Encrypt message
    long long encrypted = rsaEncrypt(message, e, n);

    // Step 2: Create hash and sign it with private key
    long long hashVal = simpleHash(msgStr);
    long long signature = rsaEncrypt(hashVal, d, n);

    cout << "\nEncrypted Message: " << encrypted << endl;
    cout << "Digital Signature: " << signature << endl;

    // Step 3: Receiver decrypts message
    long long decrypted = rsaDecrypt(encrypted, d, n);

    // Step 4: Receiver verifies signature
    long long decryptedHash = rsaDecrypt(signature, e, n);
    long long receiverHash = simpleHash(to_string(decrypted));

    cout << "\nDecrypted Message: " << decrypted << endl;
    cout << "Hash from Signature: " << decryptedHash << endl;
    cout << "Receiver's Hash: " << receiverHash << endl;

    if (decryptedHash == receiverHash)
        cout << "\nSignature is VALID — Message integrity verified." << endl;
    else
        cout << "\nInvalid Signature — Message may have been tampered." << endl;

    return 0;
}
