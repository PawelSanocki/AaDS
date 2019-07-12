#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>

using namespace std;

bool substringFind(int length, char text[], int dictPos, int look, int j){
    if (length == 0) return true;
    if (length < 3) return false;
    switch(length){
case 4:
    if (text[dictPos - j + 4] != text[dictPos + 4]){
        return false;
    }
case 3:
    if (text[dictPos - j + 3] != text[dictPos + 3]){
        return false;
    }
case 2:
    if (text[dictPos - j + 2] != text[dictPos + 2]){
        return false;
    }
case 1:
    if (text[dictPos - j + 1] != text[dictPos + 1]){
        return false;
    }
    }
    return true;
}

void printDictLook(char text[], int start, int stop){
    for (int i = start; i <= stop; i++){
        cout << text[i];
    }
    cout<<endl;
}

string intToString(int i){
    stringstream ss;
    string str;
    ss << i;
    str = ss.str();
    //cout <<"str:"<< str<<endl;
    return str;
}

int findShift(char text[], int dictPos, int look, int &offset){
    int shift = 0;
    bool flag = 0;
    for (int length = look; length > 0; --length){
        if (flag == 1) break;
        for(int j = length; j < 8; ++j){
            if (substringFind(length, text, dictPos, look, j)){
                shift = length;
                offset = j - 1;
                flag = 1;
                break;
            }
        }
    }
    return shift;
}

string compress(char text[], int dictPos, int look, int n){
    string result = "";
    int offset;
    int shift;
    while (dictPos < n){
        look = min(4, n - dictPos);
        shift = findShift(text, dictPos, look, offset);
        /// printing
        //printDictLook(text, dictPos - 7, dictPos + look);

        if (!shift){
            result.append("1");
            result+=text[dictPos + 1];
            shift = 1;
        }
        else {
            result.append("0").append(intToString(offset)).append(intToString(shift));
        }
        ///result += " "; ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ czytelnosc kompresji
        //cout << "result: "<< result << endl;
        //getchar();
        dictPos+=shift;
    }
    cout << result;
    return result;
}

string decompress(string code){
    string text = "AAAAAAAA";
    int shift = 0;
    char c;
    char c2;
    cout<<endl;
    int l;

    for (unsigned int i = 0; i < code.length(); i+=shift){
        c = code[i];
        if ((int)c - 48 == 1){
            text += (char)code[i+1];
            shift = 2;
        }else if ((int)c - 48 == 0){
            c = code[i+2];
            c2 = (char)code[i+1];
            l = text.length();
            for (int it = 0; it < (int)c - 48; ++it){
                text += text[l - 1 - ((int)c2 - 48) + it]; // place we are - offset + position
            }
            shift = 3;
        }
        cout<<endl<<text<<endl;
        getchar();
    }

    return text;
}

void shiftText(char text[], int shift){
    for (int i = 0; i < 12-shift ; ++i){
        text[i] = text[i+shift];
    }
}

string compress(int dictPos, int look, int n){
    n = 8;
    char text[12] = "AAAAAAAA";
    ifstream ifile("text.txt");
    ofstream ofile("output.txt", ios::trunc);
    for (int i = 12 - 4; i < 12; ++i){
        ifile >> noskipws >> text[i];
        n++;
    }
    string result = "";
    int offset;
    int shift = 0;
int dictPos1 = 7;
    while (dictPos < n){
        cout << "result: "<< result << endl;
        look = min(4, n - dictPos);
        shift = findShift(text, dictPos1, look, offset);
        /// printing
        //printDictLook(text, dictPos - 7, dictPos + look);

        if (!shift){
            result.append("1");
            result+=text[dictPos1 + 1];
            shift = 1;
        }
        else {
            result.append("0").append(intToString(offset)).append(intToString(shift));
        }

        //result += " "; ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ czytelnosc kompresji

        //getchar();
        //cout<<endl<<text<<endl;
        getchar();
        dictPos+=shift;
        shiftText(text, shift);
        for (int i = 12 - shift; i < 12; ++i){
            if(ifile.bad()) break;
            ifile >> noskipws >> text[i];
            n++;
        }
        //ofile << result << endl;
    }
    cout << result;
    ofile << result;
    return result;
}

int main()
{
    char text[] = "AAAAAAAAABABCDABCABCDCADABCA";
    int n = 27;
    int dictPos = 7;
    int look = 4;
    cout << decompress(compress(text, dictPos, look, n)) << endl << endl;

    cout << "From file:" << endl;
    cout << decompress(compress(dictPos, look, n)) << endl << endl;
}
