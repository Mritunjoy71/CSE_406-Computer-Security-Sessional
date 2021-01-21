#include<bits/stdc++.h>
#include <bitset>
using namespace std;
/*Initial permut matrix for the datas
data[] is 64 bit. PI[] is also 64bits. For example, 58th bit in data (data[57]) will be the first bit of transposed_data (transposed_data[0]), In the same way, transposed_data[1] = data[49]
*/
int PI[64] =
{
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};
//to get 56 but key
/*Initial permut made on the key
Remember, your key is 64 bit long. But you need only 56 bits. How will you shorten the key.
Use CP_1 array. It means, 57th bit (key[56] will be the first bit of modified_key: modified_key[0] = key[56], modified_key[1] = key[48])
*/
int CP_1[56]=
{
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};
//to get 48 bit key
/* Permut applied on shifted key to get Ki+1
For each round, you will need, 48 bit key. But currently you have 56bit keys. Use CP_2 (48 len) arrays.
Key_in_round_i[0] = modified_key[13], ....*/
int CP_2[48]=
{
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

/*Expand matrix to get a 48bits matrix of datas to apply the xor with Ki
You need to expand your leftmost 32 bits to 48 bits. Use E array.
expanded_bits [0] = leftmost_bit[31], expanded_bits[1] = leftmost_bit[0]*/

int E[48] = {32, 1, 2, 3, 4, 5,
             4, 5, 6, 7, 8, 9,
             8, 9, 10, 11, 12, 13,
             12, 13, 14, 15, 16, 17,
             16, 17, 18, 19, 20, 21,
             20, 21, 22, 23, 24, 25,
             24, 25, 26, 27, 28, 29,
             28, 29, 30, 31, 32, 1
            };

/*Permut made after each SBox substitution for each round
The P box is 8*4 size. So there will be 32 inputs and 32 outputs. The internal wiring is given.
It menas input 1 is connected to 16
input 2 is connected to 7........
*/
int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
             1, 15, 23, 26, 5, 18, 31, 10,
             2, 8, 24, 14, 32, 27, 3, 9,
             19, 13, 30, 6, 22, 11, 4, 25
            };

/*PI_2 is used to shorten the result of xoring leftmost extended 48 bits and 48 bits of key for that round
shorten_result [0] = result_xor [34], ......
*/
int PI_2[32] =
{
    35, 38, 46, 6, 43, 40, 14, 45,
    33, 19, 26, 15, 23, 8, 22, 10,
    12, 11, 5, 25, 27, 21, 16, 31,
    28, 32, 34, 24, 9, 37, 2, 1
} ;


/*
Final permut for datas after the 16 rounds
After all rounds end, use this matrix to permute the data again.
*/
int PI_1[64] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

/*Matrix that determine the shift for each round of keys
AT first round of encryption, left shift by 1 bit, 2nd round: 1 bit, 3rd round: 2 bit......*/
int SHIFT [16]=
{
    1,1,2,2,
    2,2,2,2,
    1,2,2,2,
    2,2,2,1
};

string TextToBinary(string s)
{
    int n = s.length();

    string     b_str="";
    for (int i = 0; i <= n; i++)
    {
        int val = int(s[i]);
        string bin = "";
        while (val > 0)
        {
            if(val % 2)
                bin.push_back('1');
            else
                bin.push_back('0');
            val /= 2;

        }
        reverse(bin.begin(), bin.end());
        if(bin.length()==7)
            bin="0"+bin;
        b_str+=bin;
    }
    return b_str;
}

string permutation(string str, int* array, int n)
{
    string permut="";
    for(int i=0; i<n ; i++)
    {
        permut=permut + str[array[i]-1];
    }
    return permut;
}

string leftrotate(string key, int shifts)
{
    reverse(key.begin(), key.begin()+shifts);
    reverse(key.begin()+shifts, key.end());
    reverse(key.begin(), key.end());
    return key;
}

string bin2hex(string s)
{
    // binary to hexadecimal conversion
    map<string, char> mp;
    mp["0000"]= '0';
    mp["0001"]= '1';
    mp["0010"]= '2';
    mp["0011"]= '3';
    mp["0100"]= '4';
    mp["0101"]= '5';
    mp["0110"]= '6';
    mp["0111"]= '7';
    mp["1000"]= '8';
    mp["1001"]= '9';
    mp["1010"]= 'A';
    mp["1011"]= 'B';
    mp["1100"]= 'C';
    mp["1101"]= 'D';
    mp["1110"]= 'E';
    mp["1111"]= 'F';
    string hex="";
    for(int i=0; i<s.length(); i+=4)
    {
        string ch="";
        ch+= s[i];
        ch+= s[i+1];
        ch+= s[i+2];
        ch+= s[i+3];
        hex+= mp[ch];
    }
    return hex;
}

string bin2Text(string s)
{
    string data =s;
    stringstream sstream(data);
    string text="";
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        text += c;
    }

    return text;
}

string X_OR(string e, string k)
{
    string x_or= "";
    for(int i=0; i<e.size(); i++)
    {
        if(e[i]==k[i])
        {
            x_or+= "0";
        }
        else
        {
            x_or+= "1";
        }
    }
    return x_or;
}
string hex2bin(string s)
{
    // hexadecimal to binary conversion
    map <char, string> mp;
    mp['0']= "0000";
    mp['1']= "0001";
    mp['2']= "0010";
    mp['3']= "0011";
    mp['4']= "0100";
    mp['5']= "0101";
    mp['6']= "0110";
    mp['7']= "0111";
    mp['8']= "1000";
    mp['9']= "1001";
    mp['A']= "1010";
    mp['B']= "1011";
    mp['C']= "1100";
    mp['D']= "1101";
    mp['E']= "1110";
    mp['F']= "1111";
    string bin="";
    for(int i=0; i<s.size(); i++)
    {
        bin+= mp[s[i]];
    }
    return bin;
}


string encryption(string p_text, vector<string> key_b, vector<string> key_h)
{
    p_text=hex2bin(p_text);
    p_text= permutation(p_text,PI, 64);
    // string s=bin2Text(p_text);
    cout<<"After initial permutation:"<<bin2hex(p_text)<<endl;
    string L= p_text.substr(0, 32);
    string R= p_text.substr(32, 32);
    cout<<"After splitting: L0="<<bin2hex(L)<<" R0="<<bin2hex(R)<<endl;
    string ciph="";
    for(int j=0; j<16; j++)
    {
        string e= permutation(R,E, 48);
        string x_or= X_OR(e,key_b[j]);
        string f="";

        f= permutation(x_or,PI_2, 32);
        f=permutation(f,P,32);
        x_or= X_OR(f, L);
        L= x_or;
        if(j!= 15)
        {
            swap(L, R);
        }
        cout<<"Round "<<j+1<<" "<<bin2hex(L)<<" "
            <<bin2hex(R)<<endl;

        ciph=L+R;
        ciph=bin2hex(permutation(ciph,PI_1, 64));
    }



    return ciph;
}
string tohex(string& s, bool upper=false)
{
    ostringstream ret;

    unsigned int c;
    for (string::size_type i = 0; i < s.length(); ++i)
    {
        c = (unsigned int)(unsigned char)s[i];
        ret << hex << setfill('0') <<
            setw(2) << (upper ? uppercase : nouppercase) << c;
    }
    return ret.str();
}
void hex2string(string s)
{
    std::string str(s);
    std::string res;
    res.reserve(str.size() / 2);
    for (int i = 0; i < str.size(); i += 2)
    {
        std::istringstream iss(str.substr(i, 2));
        int temp;
        iss >> std::hex >> temp;
        res += static_cast<char>(temp);
    }
    std::cout << res;



}


int main()
{
    string plain_text,key;
    int i;
    cout<<"Enter plain text: ";
    getline(cin,plain_text);
    cout<<"Enter key(8 characters): ";
    getline(cin,key);
    //cout<<p_text<<endl;
    //cout<<key<<endl;
    int l=plain_text.length();
    if(l%8!=0)
    {
        for(int i=0; i<l%8; i++)
        {
            plain_text+="~";
        }
    }
    l=plain_text.length();
    string encrypted="";
    cout<<"\n"<<"plain text in hexa: "<<tohex(plain_text)<<endl;
    cout<<"\nEncryption:\n\n";

    vector<string> key_roundb[l/8];//rkb for RoundKeys in binary
    vector<string> key_roundh[l/8];//rk for RoundKeys in hexadecimal
    int k;

    for( k=0; k <plain_text.length(); k+=8)
    {
        string p_text=plain_text.substr(k,8);
        string p=p_text;
        p_text=tohex(p_text);
        key=tohex(key);
        key=hex2bin(key);
        //cout<<key<<endl<<key.length();
        key= permutation(key, CP_1, 56);
        string lpt= key.substr(0, 28);
        string rpt= key.substr(28, 28);

        for(i=0; i<16; i++)
        {

            lpt= leftrotate(lpt, SHIFT[i]);
            rpt= leftrotate(rpt, SHIFT[i]);
            string key_shifted=lpt+rpt;
            //cout<<key_shifted<<endl;
            string Key_comp= permutation(key_shifted,CP_2, 48);
            key_roundb[k/8].push_back(Key_comp);
            key_roundh[k/8].push_back(bin2hex(Key_comp));

        }
        cout<<"\n\n"<<"number of block: "<<k/8+1<<endl;
        cout<<"string block: "<<p<<endl;
        string en=encryption(p_text,key_roundb[k/8],key_roundh[k/8]);
        encrypted+=en;
        cout<<"\nCipher Text in hexa: "<<en<<endl;
        cout<<"Cipher Text in string: ";
        hex2string(en);
        cout<<endl;
        //cout<<encrypted<<endl;

    }

    cout<<"\n\nfinal encripted text in hexa: "<<encrypted<<endl;
    cout<<"final encripted text in char: ";
    hex2string(encrypted);
    cout<<endl;

    cout<<"\nDecryption\n\n";
    string decr="";
    for(k=0; k <2*l; k+=16)
    {
        cout<<"\n\n"<<"number of block: "<<k/16+1<<endl;
        string d=encrypted.substr(k,16);
        reverse(key_roundb[k/16].begin(), key_roundb[k/16].end());
        reverse(key_roundh[k/16].begin(), key_roundh[k/16].end());
        string text= encryption(d,key_roundb[k/16], key_roundh[k/16]);
        decr+=text;
        cout<<"\ndecripted Text in hexa: "<<text<<endl;
        cout<<"decripted Text in string: ";
        hex2string(text);
        cout<<endl;
    }
    cout<<"\n\nfinal decripted text in hexa: "<<decr<<endl;
    cout<<"final decripted text in char: ";
    hex2string(decr);
    cout<<endl;




    return 0;
}
