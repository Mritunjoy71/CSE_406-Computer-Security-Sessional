#include<bits/stdc++.h>
using namespace std;


int main()
{

    map<char, char> mp;
    mp['A']=' ';
    mp['B']=' ';
    mp['C']=' ';
    mp['D']=' ';
    mp['E']=' ';
    mp['F']=' ';
    mp['G']=' ';
    mp['H']=' ';
    mp['I']=' ';
    mp['J']=' ';
    mp['K']=' ';
    mp['L']=' ';
    mp['M']=' ';
    mp['N']=' ';
    mp['O']=' ';
    mp['P']=' ';
    mp['Q']=' ';
    mp['R']=' ';
    mp['S']=' ';
    mp['T']=' ';
    mp['U']=' ';
    mp['V']=' ';
    mp['W']=' ';
    mp['X']=' ';
    mp['Y']=' ';
    mp['Z']=' ';

    string ciph;
    int lcount[26];
    int spacecount=0;

    fstream file;
    string line, filename,str[3];
    filename = "file.txt";
    file.open(filename.c_str());
    int i=0;
    while (file)
    {
        getline(file,line);
        if(line!="" && i<3)
        {
            str[i]=line;
            cout << str[i] << endl;
            line="";
            i++;

        }
    }
    ciph=str[0];
    int l=ciph.length();
    cout<<"length :"<<l<<endl;

    vector <string> letter;
    vector<string> word;
    for(i=1; i<3; i++)
    {
        stringstream check(str[i]);
        string intermediate;
        int j=0;
        while(getline(check, intermediate, ','))
        {
            if(j!=0)
            {
                intermediate=intermediate.substr(1,intermediate.length());

            }
            j++;
            if(i==1)
            {
                letter.push_back(intermediate);
            }
            else
            {
                word.push_back(intermediate);
            }
        }
    }
    /*for(int i = 0; i < word.size(); i++)
        cout << word[i] << '\n';
        */
    for(int i=0; i<26; i++)
    {
        lcount[i]=0;
    }

    for (int i = 0; i <l; i++)
    {
        if(ciph[i]!=' ')
        {
            int val=(int)ciph[i]-65;
            if(val>=0 && val<=26)
            {
                lcount[val]++;
                //cout<<"ok"<<endl;
            }
            else
            {
                spacecount++;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        cout<<char(i+65)<<" : "<<lcount[i]<<endl;
    }
    int max_freq[letter.size()];
    int index ;
    for(int i=0; i<letter.size(); i++)
    {
        int largest = lcount[0];
        for(int k = 1; k < 26; k++)
        {
            if(largest < lcount[k])
            {
                largest = lcount[k];
                index=k;
                lcount[k]=0;
            }
        }
        max_freq[i]=index;
        mp[index+65]=letter[i][0];
        //cout<<"Largest element in array is: "<<max_freq[i]<<endl;
    }
    for(int j=0; j<letter.size(); j++)
    {
        // string s=letter[j];
        for(int i=0; i<ciph.length(); i++)
        {
            if(ciph[i]==max_freq[j]+65)
            {
                ciph[i]=mp[ciph[i]];
                cout<<"ok\n";
            }
        }
    }
    cout<<"Intial replacement\n";
    cout<<ciph<<endl;

    for(int i=0; i<word.size(); i++)
    {
        for(int j=0; j<ciph.length()-word[i].length(); j++)
        {


        }
    }

    return 0;
}
