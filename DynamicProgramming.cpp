#include <iostream>
#include <string>
#include <cstdio>

#define INSERTION_COST 1
#define DELETION_COST 1
#define SUBSTITUTION_COST 1

using namespace std;

void printTable(int**tab, int n, int m);

int lcs (string str1, string str2);

void print_LCS (int **b,string str1,int i,int j);

void print_edit (int **b,string str1,string str2,int i,int j);
int editDistance (string str1, string str2, int ci, int cd, int cr);

int main()
{
    string str1 = " ABCBDAB", str2 = " BDCABA";
    ///cin>>str1>>str2;

    cout<<lcs(str1, str2);
getchar();
    str1 = " SUNDAY", str2 = " SATURDAY";
    cout<<editDistance(str1,str2,INSERTION_COST,DELETION_COST,SUBSTITUTION_COST);

    return 0;
}

int lcs (string str1, string str2){
    int n = str1.length();
    int m = str2.length();
    int** c = new int* [n]; /// numbers
    int** b = new int* [n]; /// arrows, lewa 0, skos 1, gora 2
    for (int i = 0; i < n; ++i){
        c[i] = new int [m];
        b[i] = new int [m];
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            c[i][j] = -1;
        }
    }
    for (int i = 0; i < n; ++i){
        c[i][0] = 0;
    }
    for (int j = 0; j < m; ++j){
        c[0][j] = 0;
    }

    for (int i = 1; i < n; ++i){
        for (int j = 1; j < m; ++j){
            if (str1[i] == str2[j]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 1;
            }else {
                if (c[i-1][j] >= c[i][j-1]){
                    c[i][j] = c[i-1][j];
                    b[i][j] = 2;
                }else{
                    c[i][j] = c[i][j-1];
                    b[i][j] = 0;
                }
            }
            //printTable(c, n, m);
            //getchar();
        }
    }
    cout<<"Solution: "<<endl;
    print_LCS(b,str1,n-1,m-1);
    cout<<endl;
    cout<<"Length: "<<endl;
    return c[n-1][m-1];
}

void print_LCS (int **b,string str1,int i,int j){
    if (i == 0 || j == 0 ) return;

    if(b[i][j] == 1){
        print_LCS(b,str1,i-1,j-1);
        cout<<str1[i];
    }else if (b[i][j] == 2){
        print_LCS(b,str1,i-1,j);
    }else{
        print_LCS(b,str1,i,j-1);
    }
}

void printTable(int**tab, int n, int m){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }
}

int editDistance (string str1, string str2, int ci, int cd, int cr){
    int n = str1.length();
    int m = str2.length();
    int** c = new int* [n]; /// numbers
    int** b = new int* [n]; /// arrows, lewa 0, skos 1, gora 2
    for (int i = 0; i < n; ++i){
        c[i] = new int [m];
        b[i] = new int [m];
    }
    for (int i = 0; i < n; ++i){
        c[i][0] = i * cd;
        b[i][0] = 2;
    }
    for (int j = 0; j < m; ++j){
        c[0][j] = j * ci;
        b[0][j] = 0;
    }
    int ic, dc, rc;
    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++){
            ic = c[i][j-1] + ci;
            dc = c[i-1][j] + cd;
            if (str1[i] == str2[j]) rc = c[i-1][j-1];
            else rc = c[i-1][j-1] + cr;

            c[i][j] = ic;
            b[i][j] = 0;
            if (c[i][j] > dc){
                c[i][j] = dc;
                b[i][j] = 2;
            }
            if (c[i][j] > rc){
                c[i][j] = rc;
                b[i][j] = 1;
            }
        }
    }
    cout<<endl<<"Edit: "<<endl;
    print_edit(b,str1,str2,n-1,m-1);
    cout<<endl<<"Cost:"<<endl;
    return c[n-1][m-1];

}

void print_edit (int **b,string str1,string str2,int i,int j){
    if (i == 0 || j == 0 ) return;

    if(b[i][j] == 1){
        print_edit(b,str1,str2,i-1,j-1);
        if (str1[i]!=str2[j]) cout<<"sub("<<str1[i]<<","<<str2[j]<<") ";
        else cout<<str1[i]<<" ";
    }else if (b[i][j] == 2){
        print_edit(b,str1,str2,i-1,j);
        cout<<"del("<<str1[i]<<") ";
    }else{
        print_edit(b,str1,str2,i,j-1);
        cout<<"ins("<<str2[j]<<") ";
    }
}




