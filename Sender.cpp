#include <iostream>
#include <fstream>
using namespace std;

// Function to check if a number is prime
bool isPrime(long long n)
{
    if (n < 2)
    {
        return false;
    }

    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

// Function to calculate GCD
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

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

int main()
{
    long long p, q;

    cout << "Enter two prime numbers (p and q): ";
    cin >> p >> q;

    if (isPrime(p) == false || isPrime(q) == false)
    {
        cout << "Error: Both numbers must be prime." << endl;
        return 0;
    }

    // Step 1: Compute n and phi

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);


    // Step 2: Find public exponent e
    long long e = 2;
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
        {
            break; // Found e
        }
        else
        {
            e++;
        }
    }

    cout << "\nPublic Key (n, e): (" << n << ", " << e << ")" << endl;

    // Step 3: Input message
    long long msg;
    cout << "Enter integer message (less than n): ";
    cin >> msg;

    if (msg >= n)
    {
        cout << "Error: Message must be smaller than n." << endl;
        return 0;
    }

    // Step 4: Encrypt the message
    long long cipher = modExp(msg, e, n);
    cout << "Encrypted Message (cipher): " << cipher << endl;

    // Step 5: Save to file
    ofstream fout("cipher.txt");
    fout << n << " " << e << endl;
    fout << cipher << endl;
    fout.close();

    cout << "\nSaved encrypted message to 'cipher.txt'." << endl;
    cout << "Share (n, e) publicly, keep p and q secret." << endl;

    return 0;
}
