#include <bits/stdc++.h>
using namespace std;

set<int> prime; // A set to hold prime numbers
int public_key;
int private_key;
int n;

// Function to fill the set of prime numbers using the Sieve of Eratosthenes
void primefiller() {
    vector<bool> seive(250, true);
    seive[0] = false;
    seive[1] = false;
    for (int i = 2; i < 250; i++) {
        for (int j = i * 2; j < 250; j += i) {
            seive[j] = false;
        }
    }
    for (int i = 0; i < seive.size(); i++) {
        if (seive[i])
            prime.insert(i);
    }
}

// Function to pick a random prime number and remove it from the set
int pickrandomprime() {
    int k = rand() % prime.size();
    auto it = prime.begin();
    while (k--)
        it++;
    int ret = *it;
    prime.erase(it);
    return ret;
}

// Function to set the public and private keys
void setkeys() {
    int prime1 = pickrandomprime(); // First prime number
    int prime2 = pickrandomprime(); // Second prime number
    n = prime1 * prime2;
    int fi = (prime1 - 1) * (prime2 - 1);
    int e = 2;
    while (1) {
        if (__gcd(e, fi) == 1)
            break;
        e++;
    }
    public_key = e;
    int d = 2;
    while (1) {
        if ((d * e) % fi == 1)
            break;
        d++;
    }
    private_key = d;
}

// Function to encrypt a given number
long long int encrypt(int message) {
    int e = public_key;
    long long int encrypted_text = 1;
    while (e--) {
        encrypted_text *= message;
        encrypted_text %= n;
    }
    return encrypted_text;
}

// Function to decrypt a given number
long long int decrypt(int encrypted_text) {
    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrypted_text;
        decrypted %= n;
    }
    return decrypted;
}

// Function to encode a string message
vector<int> encoder(string message) {
    vector<int> form;
    for (auto& letter : message)
        form.push_back(encrypt((int)letter));
    return form;
}

// Function to decode a vector of integers back into a string
string decoder(vector<int> encoded) {
    string s;
    for (auto& num : encoded)
        s += decrypt(num);
    return s;
}

int main() {
    primefiller();
    setkeys();
    string message;
    
    cout << "Enter the message: ";
    getline(cin, message);
    
    // Calling the encoding function
    vector<int> coded = encoder(message);
    
    cout << "Initial message:\n" << message;
    cout << "\n\nThe encoded message (encrypted by public key):\n";
    for (auto& p : coded)
        cout << p << " ";
    
    cout << "\n\nThe decoded message (decrypted by private key):\n";
    cout << decoder(coded) << endl;
    
    return 0;
}
