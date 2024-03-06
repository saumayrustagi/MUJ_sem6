#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <bitset>
using namespace std;

using ll = long long;

int main()
{
    string str = strdup("Saumay Rustagi");
    string conv_str;
    for (char &c : str)
    {
        std::string binary = bitset<8>((int)c).to_string();
        conv_str = conv_str + binary;
    }

    int diff = conv_str.size() % 64;

    while (diff != 0){
        conv_str+='0';
        --diff;
    }

    cout << conv_str << '\n';

    const int n = conv_str.size();

    string l = conv_str.substr(0, n/2);
    string r = conv_str.substr((n/2), n);

    cout << l.size() << ' ' << r.size() << '\n';

    return 0;
}