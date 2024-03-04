#include <iostream>
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
    return key;
}

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