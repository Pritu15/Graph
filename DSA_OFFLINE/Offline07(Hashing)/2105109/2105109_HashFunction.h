#ifndef HashFunction_H
#define HashFunction_H

#include <iostream>
#include <cstdint>
#include<math.h>
using namespace std;
long long HashFunction1(string s)
{
    int key = 0;
    for (int i = 0; i < s.length(); i++)
    {
        // key += pow(27, i) * s[i];
        key = 37 * key + s[i];
    }
    return abs(key);
}

long long HashFunction2(string s) {
    /* // Calculate the square of the length of the key
    long long squaredLength = key.length() * key.length();
    
    // Convert squared length to string to find its length
    string squaredLengthStr = to_string(squaredLength);
    long long length = squaredLengthStr.length();
    
    // Calculate the middle portion of the squared length
    long long mid = length / 2;
    
    // Extract the middle portion
    string midStr = squaredLengthStr.substr(mid - 1, 2); // Adjusted for zero-based index
    
    // Convert the middle portion back to integer
    long long hash = stoi(midStr);
    
    // Apply modulo to fit into the table size
    return abs(hash);
    */
    unsigned long hash = 5381;
    for (char c : s)
    {
        hash = hash * 33 + c; /* hash * 33 + c */
    }
    return hash;
   
}


// uint32_t HashFunction2(string& str) {
//     uint32_t hash = 2166136261u;  // FNV offset basis

//     for (char c : str) {
//         hash ^= static_cast<uint32_t>(c);
//         hash *= 16777619u;  // FNV prime
//     }

//     return hash;
// }
long long auxHash(string key)
{
    long long sum;
    for (long long i = 0, sum = 0; i < key.length(); i++)
        sum += key[i];
    return sum;
}
bool CheckPrime(long long x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x != i)
        {
            if (x % i == 0)
            {
                return false;
            }
        }
    }
    return true;
}
long long nearestPrime(long long num)
{
    while (true)
    {
        if (CheckPrime(num))
        {
            return num;
        }
        num++;
    }
}

#endif // HashFunction_H