#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

// Returns gcd of a and b
int gcd(int a, int h)
{
    while (1) {
        int temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}

// Function to compute (base^exponent) % modulus using modular exponentiation
long long mod_exp(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to generate a list of prime numbers using the Sieve of Eratosthenes
vector<int> generate_primes(int limit)
{
    vector<bool> sieve(limit + 1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (sieve[i]) {
            for (int j = i * i; j <= limit; j += i) {
                sieve[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to pick a random prime number from a list of primes
int pick_random_prime(const vector<int>& primes)
{
    int index = rand() % primes.size();
    return primes[index];
}


// Function to find modular inverse of a under modulo m using Extended Euclidean Algorithm
long long mod_inverse(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}


// Code to demonstrate RSA algorithm
int main()
{
    srand(time(0));

    // Generate prime numbers up to a certain limit
    int prime_limit = 100;
    vector<int> primes = generate_primes(prime_limit);

    // Pick two random prime numbers
    int p = pick_random_prime(primes);
    int q;
    do {
        q = pick_random_prime(primes);
    } while (q == p); // Ensure p and q are different

    // First part of public key:
    long long n = (long long) p * q;

    // Finding other part of public key.
    // e stands for encrypt
    long long e = 2;
    long long phi = (long long)(p - 1) * (q - 1);
    while (e < phi) {
        // e must be co-prime to phi and smaller than phi.
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    long long d = mod_inverse(e, phi);



    // Message to be encrypted
    long long msg;
    cout << "Enter message data: ";
    cin >> msg;

    cout << "Message data = " << msg << endl;
    cout << "Prime numbers p = " << p << ", q = " << q << endl;
    cout << "Public key (n, e) = (" << n << ", " << e << ")" << endl;
    cout << "Private key (d) = " << d << endl;

    // Encryption c = (msg ^ e) % n
    long long c = mod_exp(msg, e, n);
    cout << "Encrypted data = " << c << endl;

    // Decryption m = (c ^ d) % n
    long long m = mod_exp(c, d, n);
    cout << "Decrypted data = " << m << endl;

    return 0;
}
