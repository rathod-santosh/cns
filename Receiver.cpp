#include <iostream>
#include <fstream>
using namespace std;

// Function for modular exponentiation: base^exp % mod
long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;

    while (exp > 0)
    {
        if ((exp % 2) == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

// Extended Euclidean Algorithm to compute modular inverse
// Compute modular inverse (for finding d)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}


int main()
{
    // Step 1: Read cipher and public key from file
    ifstream fin("cipher.txt");
    if (!fin.is_open())
    {
        cout << "Error: 'cipher.txt' not found." << endl;
        return 0;
    }

    long long n, e, cipher;
    fin >> n >> e;
    fin >> cipher;
    fin.close();

    cout << "Received Public Key (n, e): (" << n << ", " << e << ")" << endl;
    cout << "Cipher: " << cipher << endl;

    // Step 2: Input private primes
    long long p, q;
    cout << "Enter the private primes p and q (used by sender): ";
    cin >> p >> q;

    if (p * q != n)
    {
        cout << "Error: Product of p and q must equal n." << endl;
        return 0;
    }

    // Step 3: Compute phi
    long long phi = (p - 1) * (q - 1);

    // Step 4: Compute private key d
    long long d = modInverse(e, phi);
    if (d == -1)
    {
        cout << "Error: Modular inverse does not exist." << endl;
        return 0;
    }

    cout << "Private Key (d): " << d << endl;

    // Step 5: Decrypt the message
    long long message = modExp(cipher, d, n);
    cout << "Decrypted Message: " << message << endl;

    return 0;
}
