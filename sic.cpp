#include <bits/stdc++.h>

using namespace std;

#define mk make_pair
#define ll long long

vector<string> location;
vector<string> object;

unordered_map<string, string> h;

int hextodec(string s)
{
    int x;
    stringstream str;
    str << s;
    str >> hex >> x;
    return x;
}

string dectohex(int number)
{
    stringstream str;
    str << hex << number;
    return str.str();
}

string get_opcode(string str)
{
    map<string, string> opcode;
    opcode.insert(pair<string, string>("LDA", "00"));
    opcode.insert(pair<string, string>("AND", "40"));
    opcode.insert(pair<string, string>("DIV", "24"));
    opcode.insert(pair<string, string>("SUB", "1C"));
    opcode.insert(pair<string, string>("ADD", "18"));
    opcode.insert(pair<string, string>("LDL", "08"));
    opcode.insert(pair<string, string>("RD", "D8"));
    opcode.insert(pair<string, string>("WD", "DC"));
    opcode.insert(pair<string, string>("LDCH", "50"));
    opcode.insert(pair<string, string>("STX", "10"));
    opcode.insert(pair<string, string>("JLT", "38"));
    opcode.insert(pair<string, string>("TIX", "2C"));
    opcode.insert(pair<string, string>("TD", "E0"));
    opcode.insert(pair<string, string>("STCH", "54"));
    opcode.insert(pair<string, string>("STL", "14"));
    opcode.insert(pair<string, string>("LDX", "04"));
    opcode.insert(pair<string, string>("RSUB", "4C"));
    opcode.insert(pair<string, string>("STA", "0C"));
    opcode.insert(pair<string, string>("J", "3C"));
    opcode.insert(pair<string, string>("JEQ", "30"));
    opcode.insert(pair<string, string>("COMP", "26"));
    opcode.insert(pair<string, string>("COMP", "14"));
    opcode.insert(pair<string, string>("JSUB", "48"));
    opcode.insert(pair<string, string>("JGT", "34"));
    opcode.insert(pair<string, string>("MUL", "20"));
    opcode.insert(pair<string, string>("OR", "44"));
    opcode.insert(pair<string, string>("STSW", "E8"));

    if (opcode.find(str) == opcode.end())
        return "-1";

    return opcode[str];
}

string stringtohex(const string &input)
{
    static const char *const lut = "0123456789ABCDEF";
    size_t len = input.length();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

int main()
{
    /////////////////Scan data/////////////////////
    //////////////////////////////////////////////
    string line;
    ifstream ss("inSIC.txt");
    vector<string> v;
    vector<pair<string, pair<string, string>>> x;
    string start;
    string progname;
    int idx = 0;
    ll cnt1 = 0;
    while (getline(ss, line))
    {
        stringstream iss(line);
        if (isspace(line[0]))
        {
            string p1 = "#", p2, p3;
            ll cnt = 2;
            string word;
            while (iss >> word)
            {
                if (cnt == 2)
                {
                    p2 = word;
                    cnt++;
                }
                else
                {
                    p3 = word;
                }
            }
            x.push_back(mk(p1, mk(p2, p3)));
        }
        else
        {
            string p1, p2, p3;
            ll cnt = 1;
            string word;
            while (iss >> word)
            {
                if (cnt == 1)
                {
                    p1 = word;
                    cnt++;
                }
                else if (cnt == 2)
                {
                    p2 = word;
                    cnt++;
                }
                else
                {
                    p3 = word;
                }
            }

            if (p2 == "Start")
            {
                start = p3;
                idx = cnt1;
                progname = p1;
            }
            x.push_back(mk(p1, mk(p2, p3)));
        }
        cnt1++;
    }

    x.pop_back();
    /*for(int i=0;i<x.size();i++)
    {
        cout<<x[i].first<<" "<<x[i].second.first<<" "<<x[i].second.second<<endl;
    }*/

    //////////////////////////////////////////////////

    //////////////Location address////////////////////
    /////////////////////////////////////////////////
    location.push_back(start);
    location.push_back(start);

    for (int i = idx + 1; i < x.size() - 1; i++)
    {
        if (x[i].first == "#" || x[i].first == "LOOP")
        {
            location.push_back(dectohex(hextodec(location[i]) + 3));
            if (x[i].first == "LOOP")
            {
                h[x[i].first] = location[i];
            }
        }
        else
        {
            if (x[i].second.first == "WORD")
            {
                location.push_back(dectohex(hextodec(location[i]) + 3));
            }
            else if (x[i].second.first == "RESW")
            {
                int a = stoi(x[i].second.second);
                a *= 3;
                location.push_back(dectohex(hextodec(location[i]) + a));
            }
            else if (x[i].second.first == "BYTE")
            {
                string lol = x[i].second.second;
                if (lol[0] == 'X')
                {
                    ll a = lol.size() - 3;
                    a /= 2;
                    location.push_back(dectohex(hextodec(location[i]) + a));
                }
                else
                {
                    ll a = lol.size() - 3;
                    location.push_back(dectohex(hextodec(location[i]) + a));
                }
            }
            else
            {
                int a = stoi(x[i].second.second);
                location.push_back(dectohex(hextodec(location[i]) + a));
            }

            h[x[i].first] = location[i];

            //symbol table
            //cout << x[i].first << " " << h[x[i].first] << endl;
        }
    }
    //cout<<h["LOOP"]<<endl;
    /*for(int i=0;i<location.size();i++)
    {
        cout<<location[i]<<" "<<x[i].first<<" "<<x[i].second.first<<" "<<x[i].second.second<<endl;
    }*/

    //////////////////////////////////////////////////////
    

    ///////////////////object code/////////////////////////
    //////////////////////////////////////////////////////

    object.push_back("#");
    for (int i = idx + 1; i < x.size(); i++)
    {
        if (x[i].first == "#" || x[i].first == "LOOP")
        { 
            string lol = x[i].second.second;
            if (lol[lol.size() - 1] == 'X' && lol[lol.size() - 2] == ',')
            {
                string a = get_opcode(x[i].second.first);
                lol.pop_back();
                lol.pop_back();
                string b = dectohex(hextodec(h[lol]) + 32768);
                object.push_back(a + b);
            }
            else
            {
                string a = get_opcode(x[i].second.first);
                object.push_back(a + h[x[i].second.second]);
            }
        }
        else
        {
            if (x[i].second.first == "WORD")
            {
                int a = stoi(x[i].second.second);
                object.push_back("00" + dectohex(a));
            }
            else if (x[i].second.first == "RESW")
            {
                object.push_back("#");
            }
            else if (x[i].second.first == "BYTE")
            {
                string lol = x[i].second.second;
                if (lol[0] == 'X')
                {
                    string a = "";
                    for (int i = 2; i < lol.size() - 1; i++)
                    {
                        a += lol[i];
                    }
                    object.push_back(a);
                }
                else
                {
                    string a = "";
                    for (int i = 2; i < lol.size() - 1; i++)
                    {
                        a += lol[i];
                    }
                    object.push_back(stringtohex(a));
                }
            }
            else
            {
                object.push_back("#");
            }
        }
    }

    /*for (int i = 0; i < object.size(); i++)
    {
        cout << location[i] << " " << x[i].first << " " << x[i].second.first << " " << x[i].second.second << " " << object[i] << endl;
    }*/

    /////////////////////////////////////////////////////////////////////



    ///////////////////////////HTE RECORD///////////////////////////////
    ////////////////////////////////////////////////////////////////////
    
    /*cout<<"\n"<<endl;
    cout<<"H "<<progname<<" "<<start<<" "<<dectohex(hextodec(location[location.size()-1]) - hextodec(start))<<endl;
    ll i=idx+1;
    ll cnt5=1;
    vector<string>t;
    string start_location;
    bool f = true;
    for(int i=1;i<x.size();i++)
    {
        if(x[i].second.first=="RESW" || x[i].second.first=="RESB" || x[i].first=="End")
        {
            if(t.size()>0)
            {
                cout<<"t"<<cnt5<<" "<<start_location<<" "<<dectohex(hextodec(location[i]) - hextodec(start_location))<<" ";
                f = true;
                cnt5++;
                for(int j=0;j<t.size();j++)
                {
                    cout<<t[j]<<" ";
                }
                t.clear();
                cout<<endl;
            }
        }
        else
        {
            if(f)
            {
                start_location = location[i];
                f = false;
            }
            t.push_back(object[i]);
        }
    }
    cout<<"E "<<start<<endl;*/

    return 0;
}
