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
int s[8][4][16]=
{
    {
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },


    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }
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

string encryption(string p_text, vector<string> key_b, vector<string> key_h)
{
    p_text=TextToBinary(p_text);
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
            <<bin2hex(R)<<" "<<key_h[j]<<endl;

        ciph=L+R;
        ciph=permutation(ciph,PI_1, 64);
    }



    return ciph;
}


int main()
{
    string p_text,key;
    int i;
    cout<<"Enter plain text: ";
    getline(cin,p_text);
    cout<<"Enter key(8 characters): ";
    getline(cin,key);
    //cout<<p_text<<endl;
    //cout<<key<<endl;
    key=TextToBinary(key);
    //cout<<key<<endl<<key.length();
    key= permutation(key, CP_1, 56);
    string lpt= key.substr(0, 28);
    string rpt= key.substr(28, 28);


    vector<string> key_roundb;//rkb for RoundKeys in binary
    vector<string> key_roundh;//rk for RoundKeys in hexadecimal

    for(i=0; i<16; i++)
    {

        lpt= leftrotate(lpt, SHIFT[i]);
        rpt= leftrotate(rpt, SHIFT[i]);
        string key_shifted=lpt+rpt;
        //cout<<key_shifted<<endl;
        string Key_comp= permutation(key_shifted,CP_2, 48);
        key_roundb.push_back(Key_comp);
        key_roundh.push_back(bin2hex(Key_comp));

    }
    cout<<"\n"<<bin2hex(TextToBinary(p_text))<<endl;
    cout<<"\nEncryption:\n\n";
    string encrypted=encryption(p_text,key_roundb,key_roundh);
    cout<<"\nCipher Text: "<<bin2hex(encrypted)<<endl;
    //cout<<encrypted<<endl;

    cout<<"\nDecryption\n\n";
	reverse(key_roundb.begin(), key_roundb.end());
	reverse(key_roundh.begin(), key_roundh.end());
	string text= encryption(encrypted,key_roundb, key_roundh);
	cout<<"\nPlain Text: "<<bin2hex(text)<<endl;

    return 0;
}
