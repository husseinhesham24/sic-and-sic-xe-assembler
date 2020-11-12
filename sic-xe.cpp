#include <bits/stdc++.h>

using namespace std;

#define mk make_pair
#define ll long long

vector<string> location;
vector<string> object;

unordered_map<string, string> h;
string base = "-1";

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
    map<string, string> r;
    r["ADD"] = "18";
    r["ADDF"] = "58";
    r["ADDR"] = "90";
    r["AND"] = "40";
    r["CLEAR"] = "B4";
    r["COMP"] = "28";
    r["COMPF"] = "88";
    r["COMPR"] = "A0";
    r["DIV"] = "24";
    r["DIVF"] = "64";
    r["DIVR"] = "9C";
    r["FIX"] = "C4";
    r["FLOAT"] = "C0";
    r["HIO"] = "F4";
    r["J"] = "3C";
    r["JEQ"] = "30";
    r["JGT"] = "34";
    r["JLT"] = "38";
    r["JSUB"] = "48";
    r["LDA"] = "00";
    r["LDB"] = "68";
    r["LDCH"] = "50";
    r["LDF"] = "70";
    r["LDL"] = "08";
    r["LDS"] = "6C";
    r["LDT"] = "74";
    r["LDX"] = "04";
    r["LPS"] = "D0";
    r["MUL"] = "20";
    r["MULF"] = "60";
    r["MULR"] = "98";
    r["NORM"] = "C8";
    r["OR"] = "44";
    r["RD"] = "D8";
    r["RMO"] = "AC";
    r["RSUB"] = "4C";
    r["SHIFTL"] = "A4";
    r["SHIFTR"] = "A8";
    r["SIO"] = "F0";
    r["SSK"] = "EC";
    r["STA"] = "0C";
    r["STB"] = "78";
    r["STCH"] = "54";
    r["STF"] = "80";
    r["STI"] = "D4";
    r["STL"] = "14";
    r["STS"] = "7C";
    r["STSW"] = "E8";
    r["STT"] = "84";
    r["STX"] = "10";
    r["SUB"] = "1C";
    r["SUBF"] = "5C";
    r["SUBR"] = "94";
    r["SVC"] = "B0";
    r["TD"] = "E0";
    r["TIO"] = "F8";
    r["TIX"] = "2C";
    r["TIXR"] = "B8";
    r["WD"] = "DC";
    string opcode;

    opcode = r[str];
    return opcode;
}

int get_format(string str)
{
    map<string, int> r;
    r["ADD"] = 3;
    r["ADDF"] = 3;
    r["ADDR"] = 2;
    r["AND"] = 3;
    r["CLEAR"] = 2;
    r["COMP"] = 3;
    r["COMPF"] = 3;
    r["COMPR"] = 2;
    r["DIV"] = 3;
    r["DIVF"] = 3;
    r["DIVR"] = 2;
    r["FIX"] = 1;
    r["FLOAT"] = 1;
    r["HIO"] = 1;
    r["J"] = 3;
    r["JEQ"] = 3;
    r["JGT"] = 3;
    r["JLT"] = 3;
    r["JSUB"] = 3;
    r["LDA"] = 3;
    r["LDB"] = 3;
    r["LDCH"] = 3;
    r["LDF"] = 3;
    r["LDS"] = 3;
    r["LDL"] = 3;
    r["LDT"] = 3;
    r["LDX"] = 3;
    r["LPS"] = 3;
    r["MUL"] = 3;
    r["MULF"] = 3;
    r["MULR"] = 2;
    r["NORM"] = 1;
    r["OR"] = 3;
    r["RD"] = 3;
    r["RMO"] = 2;
    r["RSUB"] = 3;
    r["SHIFTL"] = 2;
    r["SHIFTR"] = 2;
    r["SIO"] = 1;
    r["SSK"] = 3;
    r["STA"] = 3;
    r["STB"] = 3;
    r["STCH"] = 3;
    r["STF"] = 3;
    r["STI"] = 3;
    r["STL"] = 3;
    r["STS"] = 3;
    r["STSW"] = 3;
    r["STT"] = 3;
    r["STX"] = 3;
    r["SUB"] = 3;
    r["SUBF"] = 3;
    r["SUBR"] = 2;
    r["SVC"] = 2;
    r["TD"] = 3;
    r["TIO"] = 1;
    r["TIX"] = 3;
    r["TIXR"] = 2;
    r["WD"] = 3;
    int format;

    format = r[str];
    return format;
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

string corr(string x)
{
    ll n = x.length();
    for (int i = n; i < 4; i++)
    {
        x = '0' + x;
    }
    return x;
}

string get_op(char x)
{
    string lol = "";
    if (x == '0')
    {
        lol += '0';
        lol += '0';
    }
    else if (x == '4')
    {
        lol += '0';
        lol += '1';
    }
    else if (x == '8')
    {
        lol += '1';
        lol += '0';
    }
    else
    {
        lol += '1';
        lol += '1';
    }

    return lol;
}

string bintohex(string x)
{
    int sum = 0;
    for (int i = 3, j = 0; i >= 0; i--, j++)
    {
        if (x[i] == '1')
        {
            sum += pow(2, j);
        }
    }

    return dectohex(sum);
}

string get_object(string ins, string y, string loc)
{
    string ans = "";
    char n = '0', i = '0', x = '0', b = '0', p = '0', e = '0';
    if (ins[0] == '+')
    {
        e = '1';
        ins.erase(ins.begin());
    }
    else
    {
        e = '0';
    }

    ll l = y.length();
    if (y[l - 1] == 'X' && y[l - 2] == ',')
    {
        x = '1';
        y.pop_back();
        y.pop_back();
    }
    else
    {
        x = '0';
    }

    string op = get_opcode(ins);
    ans += op[0];
    string lol = "";
    lol += get_op(op[1]);

    if (ins == "RSUB")
    {
        lol += n;
        lol += i;
        ans += bintohex(lol);
        lol = "";
        lol += x;
        lol += b;
        lol += p;
        lol += e;
        ans += bintohex(lol);
        ans += "000";
        return ans;
    }
    else if (e == '1' || y[0] == '#')
    {
        if (y[0] == '#')
        {
            y.erase(y.begin());
            n = '0';
            i = '1';
        }
        else if (y[0] == '@')
        {
            y.erase(y.begin());
            n = '1';
            i = '0';
        }
        else
        {
            n = '1';
            i = '1';
        }

        b = '0';
        p = '0';

        lol += n;
        lol += i;
        ans += bintohex(lol);
        lol = "";
        lol += x;
        lol += b;
        lol += p;
        lol += e;
        ans += bintohex(lol);

        if (h.count(y))
        {
            ans += '0' + h[y];
            return ans;
        }
        else
        {
            string temp = dectohex(stoi(y));
            l = temp.length();
            if (l < 3)
            {
                for (int j = l; j < 3; j++)
                {
                    temp = '0' + temp;
                }
            }
            else if (l > 3 && l < 5)
            {
                for (int j = l; j < 5; j++)
                {
                    temp = '0' + temp;
                }
            }

            ans += temp;
            return ans;
        }
    }
    else
    {
        if (y[0] == '@')
        {
            y.erase(y.begin());
            n = '1';
            i = '0';
        }
        else
        {
            n = '1';
            i = '1';
        }

        b = '0';
        p = '0';

        lol += n;
        lol += i;
        ans += bintohex(lol);

        ll aa = hextodec(h[y]);
        ll bb = hextodec(loc);
        ll zz = aa - bb;
        if (zz >= -2048 && zz <= 2047)
        {
            p = '1';
            b = '0';
        }
        else
        {
            zz = aa - hextodec(h[base]);
            p = '0';
            b = '1';
        }

        string temp = dectohex(zz);
        l = temp.length();
        if (l < 3)
        {
            for (int j = l; j < 3; j++)
            {
                temp = '0' + temp;
            }
        }
        else if (l > 3 && l < 5)
        {
            for (int j = l; j < 5; j++)
            {
                temp = '0' + temp;
            }
        }
        else
        {
            while (temp.length() > 3)
            {
                temp.erase(temp.begin());
            }
        }

        lol = "";
        lol += x;
        lol += b;
        lol += p;
        lol += e;
        ans += bintohex(lol);
        ans += temp;
        return ans;
    }
}

int main()
{
    /////////////////Scan data/////////////////////4C
    //////////////////////////////////////////////
    string line;
    ifstream ss("inSICXE.txt");
    vector<string> v;
    vector<pair<string, pair<string, string>>> x;
    string start;
    string progname;
    int idx = 0;
    ll cnt1 = 0;
    while (getline(ss, line))
    {
        stringstream iss(line);

        string p1, p2, p3;
        ll cnt = 0;
        string word;
        while (iss >> word)
        {
            cnt++;
        }

        stringstream isss(line);
        word = "";
        if (cnt == 3)
        {
            cnt = 1;
            while (isss >> word)
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
        }
        else
        {
            cnt = 1;
            p1 = "#";
            while (isss >> word)
            {
                if (cnt == 1)
                {
                    p2 = word;
                    cnt++;
                }
                else
                {
                    p3 = word;
                }
            }
        }

        if (p2 == "START")
        {
            start = p3;
            idx = cnt1;
            progname = p1;
        }
        else if (p2 == "BASE")
        {
            base = p3;
        }
        x.push_back(mk(p1, mk(p2, p3)));
    }
    cnt1++;

    /*for(int i=0;i<x.size();i++)
    {
        cout<<x[i].first<<" "<<x[i].second.first<<" "<<x[i].second.second<<endl;
    }*/

    //////////////////////////////////////////////////

    //////////////Location address////////////////////
    /////////////////////////////////////////////////
    location.push_back(corr(start));
    location.push_back(corr(start));

    for (int i = idx + 1; i < x.size() - 1; i++)
    {
        if (x[i].second.first == "WORD" || x[i].second.first == "RESW" || x[i].second.first == "BYTE" || x[i].second.first == "RESB")
        {
            if (x[i].second.first == "WORD")
            {
                string lol = x[i].second.second;
                int cntcor = 0;
                for (int j = 0; j < lol.size(); j++)
                {
                    if (lol[j] == ',')
                    {
                        cntcor++;
                    }
                }
                if (cntcor == 0)
                {
                    location.push_back(corr(dectohex(hextodec(location[i]) + 3)));
                }
                else
                {
                    location.push_back(corr(dectohex(hextodec(location[i]) + ((cntcor + 1) * 3))));
                }
            }
            else if (x[i].second.first == "RESW")
            {
                int a = stoi(x[i].second.second);
                a *= 3;
                location.push_back(corr(dectohex(hextodec(location[i]) + a)));
            }
            else if (x[i].second.first == "BYTE")
            {
                string lol = x[i].second.second;
                if (lol[0] == 'X')
                {
                    ll a = lol.size() - 3;
                    a /= 2;
                    location.push_back(corr(dectohex(hextodec(location[i]) + a)));
                }
                else
                {
                    ll a = lol.size() - 3;
                    location.push_back(corr(dectohex(hextodec(location[i]) + a)));
                }
            }
            else
            {
                int a = stoi(x[i].second.second);
                location.push_back(corr(dectohex(hextodec(location[i]) + a)));
            }

            h[x[i].first] = location[i];

            //symbol table
            //cout << x[i].first << " " << h[x[i].first] << endl;
        }
        else if (x[i].second.first[0] == '+')
        {
            location.push_back(corr(dectohex(hextodec(location[i]) + 4)));
            if (x[i].first != "#")
            {
                h[x[i].first] = location[i];
                //symbol table
                //cout << x[i].first << " " << h[x[i].first] << endl;
            }
        }
        else
        {
            location.push_back(corr(dectohex(hextodec(location[i]) + get_format(x[i].second.first))));
            if (x[i].first != "#")
            {
                h[x[i].first] = location[i];
                //symbol table
                //cout << x[i].first << " " << h[x[i].first] << endl;
            }
        }
    }

    /*for(int i=0;i<location.size();i++)
    {
        cout<<location[i]<<" "<<x[i].first<<" "<<x[i].second.first<<" "<<x[i].second.second<<endl;
    }*/

    //////////////////////////////////////////////////////

    ///////////////////object code/////////////////////////
    //////////////////////////////////////////////////////

    object.push_back("#");
    for (int i = idx + 1; i < x.size() - 1; i++)
    {
        if (x[i].second.first == "WORD" || x[i].second.first == "RESW" || x[i].second.first == "BYTE" || x[i].second.first == "RESB")
        {
            if (x[i].second.first == "WORD")
            {
                string lol = x[i].second.second;
                string str = "";
                string ans = "";
                for (int j = 0; j < lol.size(); j++)
                {
                    if (lol[j] == ',')
                    {
                        int a = stoi(str);
                        string temp = dectohex(a);

                        ll l = temp.length();
                        for (int k = l; k < 6; k++)
                        {
                            temp = '0' + temp;
                        }
                        ans += temp;
                        str = "";
                    }
                    else
                    {
                        str += lol[j];
                    }
                }

                int a = stoi(str);
                string temp = dectohex(a);

                ll l = temp.length();
                for (int k = l; k < 6; k++)
                {
                    temp = '0' + temp;
                }
                ans += temp;
                object.push_back(ans);
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

                    ll l = a.length();
                    for (int k = l; k < 6; k++)
                    {
                        a = '0' + a;
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

                    string temp = stringtohex(a);

                    ll l = temp.length();
                    for (int k = l; k < 6; k++)
                    {
                        temp = '0' + temp;
                    }
                    
                    object.push_back(temp);
                }
            }
            else
            {
                object.push_back("#");
            }
        }
        else if (x[i].second.first == "BASE")
        {
            object.push_back("#");
        }
        else
        {
            object.push_back(get_object(x[i].second.first, x[i].second.second, location[i + 1]));
        }
    }
    object.push_back("#");

    for (int i = 0; i < object.size(); i++)
    {
        cout << location[i] << " " << x[i].first << " " << x[i].second.first << " " << x[i].second.second << " " << object[i] << endl;
    }

    /////////////////////////////////////////////////////////////////////

    ///////////////////////////HTE RECORD///////////////////////////////
    ////////////////////////////////////////////////////////////////////

    cout << "\n" << endl;
    cout << "H " << progname << " " << start << " " << dectohex(hextodec(location[location.size() - 1]) - hextodec(start)) << endl;
    ll i = idx + 1;
    ll cnt5 = 1;
    vector<string> t;
    string start_location;
    bool f = true;
    for (int i = 1; i < x.size(); i++)
    {
        if (x[i].second.first == "RESW" || x[i].second.first == "RESB" || x[i].second.first == "END")
        {
            if (t.size() > 0)
            {
                cout << "t" << cnt5 << " " << start_location << " " << dectohex(hextodec(location[i]) - hextodec(start_location)) << " ";
                f = true;
                cnt5++;
                for (int j = 0; j < t.size(); j++)
                {
                    cout << t[j] << " ";
                }
                t.clear();
                cout <<"\n"<<endl;
            }
        }
        else
        {
            if (f)
            {
                start_location = location[i];
                f = false;
            }

            if(object[i]!="#")
                t.push_back(object[i]);
        }
    }
    
    for (int i = 1; i < x.size(); i++)
    {
        if(x[i].second.first[0]=='+' && x[i].second.second[0]!='#')
        {
            cout <<"M "<<corr(dectohex(hextodec(location[i]) + 1))<<" 05"<<endl; 
        }
    }

    cout<<endl;

    cout << "E " << corr(start) << endl;

    return 0;
}
