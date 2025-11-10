// A5
// A message is to be transmitted using network resources from one machine to another.
// Calculate and demonstrate the use of a Hash value equivalent to SHA-1.
// Program in C++ using Eclipse.

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <sstream>

using namespace std;

// Left rotation (circular shift)
uint32_t leftrotate(uint32_t x, unsigned n)
{
    return (x << n) | (x >> (32 - n));
}

// Function to compute SHA-1 hash
string sha1(const string &message)
{
    // Convert message to bytes
    vector<uint8_t> data(message.begin(), message.end());

    // Message length in bits
    uint64_t ml = static_cast<uint64_t>(data.size()) * 8ULL;

    // Append bit '1' (0x80)
    data.push_back(0x80);

    // Append zeros until message length ≡ 56 mod 64
    while ((data.size() % 64) != 56)
        data.push_back(0x00);

    // Append original length (in bits) as 64-bit big-endian
    for (int i = 7; i >= 0; --i)
        data.push_back(static_cast<uint8_t>((ml >> (8 * i)) & 0xFF));

    // Initial hash values
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Process each 512-bit chunk
    for (size_t offset = 0; offset < data.size(); offset += 64)
    {
        uint32_t w[80];

        // Break chunk into sixteen 32-bit big-endian words
        for (int t = 0; t < 16; ++t)
        {
            size_t idx = offset + t * 4;
            w[t] = (static_cast<uint32_t>(data[idx]) << 24) |
                   (static_cast<uint32_t>(data[idx + 1]) << 16) |
                   (static_cast<uint32_t>(data[idx + 2]) << 8) |
                   (static_cast<uint32_t>(data[idx + 3]));
        }

        // Extend the first 16 words into the remaining 64 words
        for (int t = 16; t < 80; ++t)
            w[t] = leftrotate(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);

        // Initialize working variables
        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

        // Main loop
        for (int t = 0; t < 80; ++t)
        {
            uint32_t f, k;
            if (t < 20)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (t < 40)
            {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (t < 60)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else
            {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = leftrotate(a, 5) + f + e + k + w[t];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }

        // Add this chunk's hash to result so far
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Produce the final hash (20 bytes)
    ostringstream digest_stream;
    digest_stream << uppercase << hex << setfill('0');

    auto append_be = [&](uint32_t v)
    {
        digest_stream << setw(2) << ((v >> 24) & 0xFF);
        digest_stream << setw(2) << ((v >> 16) & 0xFF);
        digest_stream << setw(2) << ((v >> 8) & 0xFF);
        digest_stream << setw(2) << (v & 0xFF);
    };

    append_be(h0);
    append_be(h1);
    append_be(h2);
    append_be(h3);
    append_be(h4);

    return digest_stream.str();
}

int main()
{
    string message;
    cout << "Enter the message to be hashed: ";
    getline(cin, message);

    string hash = sha1(message);

    cout << "\nSHA-1 Hash of the message is: " << hash << endl;
    cout << "First 8 characters of the hash are: " << hash.substr(0, 8) << endl;

    return 0;
}
