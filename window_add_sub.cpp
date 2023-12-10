#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using namespace std;

set<long long> Small_Window(long long a, long long k)
{

    set<long long> alpha = {1, 2, 3}; // initialize alpha
    while (*alpha.rbegin() < pow(2, k) - 1)
    {
        alpha.insert(*alpha.rbegin() + 2);
    }

    long long n = log2(a) + 1;
    long long i = n - 1;
    long long p = 0;
    vector<long long> w;
    // vector<bool> sub;

    while (i >= 0)
    {
        w.push_back(0);
        for (long long j = 0; j < k; j++)
        {
            if ((a >> (i - j)) & 1)
            {
                w.back() |= 1 << (k - j - 1);
            }
        }
        i -= k;
        // sub.push_back(false);
        while ((i > -1) && !((a >> i) & 1))
        {
            w.back() <<= 1;
            i--;
        }
        p++;
    }
    vector<long long> s;
    for (long long i = 0; i < w.size(); i++)
    {
        s.push_back(log2(w[i]) + 1);
    }
    long long wp = w.front();

    while (wp > pow(2, k))
    {
        wp /= 2;
    }

    if (wp % 2 == 0)
    {
        alpha.insert(wp - 1);
    }
    for (long long i = 0; i <= s[0] - k; i++)
    {
        alpha.insert(pow(2, i) * wp);
    }

    long long ac = pow(2, s[0] - k) * wp;

    for (long long i = 1; i < w.size(); i++)
    {

        wp = w[i];

        while (wp % 2 == 0)
        {
            wp /= 2;
        }

        for (long long j = 1; j <= log2(wp) + 1; j++)
        {
            alpha.insert(pow(2, j) * ac);
        }

        ac = pow(2, (long long)(log2(wp) + 1)) * ac + wp;

        for (long long j = 0; j <= s[i] - (long long)(log2(wp)) - 1; j++)
        {
            alpha.insert(pow(2, j) * ac);
        }

        ac = pow(2, s[i] - (long long)(log2(wp)) - 1) * ac;
    }

    return alpha;
}


set<long long> Proposed(long long a, long long k)
{

    set<long long> alpha = {1, 2, 3}; // initialize alpha
    while (*alpha.rbegin() < pow(2, k) - 1)
    {
        alpha.insert(*alpha.rbegin() + 2);
    }

    long long n = log2(a) + 1;
    long long i = n - 1;
    long long p = 0;
    vector<long long> w;
    vector<bool> sub;

    while (i >= 0)
    {
        w.push_back(0);
        for (long long j = 0; j < k; j++)
        {
            if ((a >> (i - j)) & 1)
            {
                w.back() |= 1 << (k - j - 1);
            }
        }
        i -= k;
        sub.push_back(false);
        if ((i > -1) && (a >> i) & 1)
        {
            w.back()++;
            if (w.back() <= pow(2, k - 1))
            {
                w.back() = pow(2, k) - w.back(); // 2's complement
                sub.back() = true;               // subtraction
            }
            while ((i > -1) && (a >> i) & 1)
            {
                w.back() <<= 1;
                i--;
            }
        }
        else
        {
            if (w.back() <= pow(2, k - 1))
            {
                w.back() = pow(2, k) - w.back(); // 2's complement
                sub.back() = true;               // subtraction
            }
            while ((i > -1) && !((a >> i) & 1))
            {
                w.back() <<= 1;
                i--;
            }
        }
        p++;
    }
    // return w;
    // cout << "window size is " << w.size() << endl;

    vector<long long> s;
    for (long long i = 0; i < w.size(); i++)
    {
        s.push_back(log2(w[i]) + 1);
    }
    long long wp = w.front();

    while (wp > pow(2, k))
    {
        wp /= 2;
    }

    if (wp % 2 == 0)
    {
        alpha.insert(wp - 1);
    }
    for (long long i = 0; i <= s[0] - k; i++)
    {
        alpha.insert(pow(2, i) * wp);
    }

    long long ac = pow(2, s[0] - k) * wp;

    for (long long i = 1; i < w.size(); i++)
    {

        wp = w[i];

        while (wp % 2 == 0)
        {
            wp /= 2;
        }

        for (long long j = 1; j <= log2(wp) + 1; j++)
        {
            alpha.insert(pow(2, j) * ac);
        }

        ac = pow(2, (long long)(log2(wp) + 1)) * ac;

        if (sub[i])
        {
            ac -= wp;
        }
        else
        {
            ac += wp;
        }

        for (long long j = 0; j <= s[i] - (long long)(log2(wp)) - 1; j++)
        {
            alpha.insert(pow(2, j) * ac);
        }

        ac = pow(2, s[i] - (long long)(log2(wp)) - 1) * ac;
    }

    return alpha;
}

int main()
{
    long long a = 0b10101101011;
    a = 0b11010101101011100011101001110011;
    a = 0b1111110001; // 1009 not working for this case
    // a = 0b1011000;        // 88 not working for this case
    long long k = 5;
    int valid = 0;
    int testcases = 10000;
    cout << "Enter window size: ";
    cin >> k;
    cout << "Enter number of testcases: ";
    cin >> testcases;
    map <long long, long long> mp ;
    long long improvement = 0;
    for (int i = 256; i < testcases+256; i++)
    {
        cout << i << endl;
        a = i;
        set<long long> w = Proposed(a, k);
        set<long long> sw = Small_Window(a, k);
        if (w.find(a) != w.end())
        {
            // cout << "found" << endl;
            valid++;
            if(sw.find(a) == w.end())
                return 0;
            improvement += sw.size() - w.size(); 
            // cout << sw.size() << " " << w.size() << "\n";
            // cout << improvement << '\n';
        }
    }
    cout << "window size is " << k << endl;
    cout << "valid " << valid  << " total " << testcases  << " percent valid " << (((float)valid * 100) / (testcases-64)) << endl;
    cout << "improvement " << (float)improvement / testcases << endl;
    return 0;
}