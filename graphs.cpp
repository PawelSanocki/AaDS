#include <iostream>
#include <fstream>
#include <queue>
#include <list>

#define INF 10000

using namespace std;

void printTable(int**tab, int n, int m){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cout<<tab[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void fw_alg(string fileName){
    int nodes, edges;
    int from, to, weigth;
    ifstream file(fileName);
    file>>nodes>>edges;
    int ** d = new int*[nodes];
    int ** p = new int*[nodes];
    for (int i = 0; i < nodes; ++i){
        d[i] = new int[nodes];
        p[i] = new int[nodes];
        for (int j = 0; j < nodes; ++j){
            d[i][j] = INF;
            p[i][j] = -1;
            if(i==j){
                d[i][j] = 0;
                p[i][j] = j;
            }
        }
    }
    while(file.good()){
        file>>from>>to>>weigth;
        d[from][to] = weigth;
        p[from][to] = to;
    }

    for (int k = 0; k < nodes; ++k){
        for (int i = 0; i < nodes; ++i){
            if (d[i][k] != INF)
            for (int j = 0; j < nodes; ++j){
                if (d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[i][k];
                }
            }
        }
    }/*
    cout<<"DISTANCES:"<<endl;
    printTable(d,nodes,nodes);
    cout<<"Predecessors"<<endl;
    printTable(p,nodes,nodes);
    cout<<endl<<"Result: "<<endl;*/
    int temp;
    for(int i = 1; i < nodes; ++i){
        for (int j = 1; j < nodes; ++j){
            if (d[i][j] > INF/10 || i==j) continue;
            cout << "d("<<i<<", "<<j<<") = "<<d[i][j];
            cout<<" Path: ";
            temp = i;
            while (temp != j){
                cout<<temp<<" - ";
                temp = p[temp][j];
            }
            cout<<temp<<endl;
        }
    }

}

//tutaj kolejny program :/ jak to zrobiæ? kto to wie? lel

class Connection{
public:
    unsigned int dest;
    unsigned int src;
    Connection(int s, int d): dest(d), src(s){}
};
class Node{
public:
    int state; /// 0 - unvisited, 1 - visited, 2 - analysed
    int distance;
    int predecessor;
    int id;
    Node(int ID, int d = 0):id(ID){
        state = 0;
        distance = d;
    }
};
void bfs(int from, int to, string fileName){
    int u;
    int t1, t2;
    int nodes, edges;
    ifstream file(fileName);
    file>>nodes>>edges;

    list<Connection> con;
    list<Connection>::iterator it;
    while(file.good()){
        file>>t1>>t2;
        con.push_back(Connection(t1,t2));
    }
    vector <Node> allNodes;
    for (int i = 0; i < nodes; ++i){
        allNodes.push_back(Node(i));
    }
    queue <int> qNodes;
    qNodes.push(from);
    while(!qNodes.empty()){
        u = qNodes.front();
        qNodes.pop();
        it = con.begin();
        while (it != con.end()){
            if (it->src == u && allNodes[it->dest].state == 0){
                allNodes[it->dest].state = 1;
                allNodes[it->dest].distance = allNodes[u].distance+1;
                allNodes[it->dest].predecessor = u;
                qNodes.push(it->dest);
            }
            ++it;
        }
        allNodes[u].state = 2;
    }

    ///printing
    int curr = to;
    cout<<"Path from "<<from<<" to "<< to <<" is: "<<endl;
    while (curr!=from){
        cout<<curr<<" - ";
        curr = allNodes[curr].predecessor;
    }
    cout<<curr<<endl;
}

void maze(){
    ifstream file("maze.txt");
    int maxx, maxy;
    int counter = 1;
    file>>maxx>>maxy;
    char ** tab = new char*[maxy];
    int ** t = new int * [maxy];
    for (int i = 0; i < maxy; i++){
        tab[i] = new char[maxx];
        t[i] = new int[maxx];
        for (int j = 0; j < maxx; j++){
            file>>tab[i][j];
            if (tab[i][j] == 'x'){
                t[i][j] = -1;
            } else if (tab[i][j] == '.'){
                t[i][j] = counter;
                counter++;
            } else if (tab[i][j] == 'I'){
                t[i][j] = 0;
            }else t[i][j] = 1;
            cout<<tab[i][j];
        }
        cout<<endl;
    }
    for (int i = 0; i < maxy; i++){
        for (int j = 0; j < maxx; j++){
            if (tab[i][j] == 'O'){
                t[i][j] = counter;
            }
            cout<<t[i][j]<<"\t";
        }
        cout<<endl;
    }
    file.close();
    ofstream file2("temp.txt");
    file2<<counter<<" "<<10<<endl;;
    for (int i = 0; i < maxy; i++){
        for (int j = 0; j < maxx; j++){
            if(t[i][j] == 0 || t[i][j] == counter){
                if (i==0){
                    if(t[i+1][j]>=0) file2<<t[i][j]<<" "<<t[i+1][j]<<endl;
                    if(t[i][j-1]>=0) file2<<t[i][j]<<" "<<t[i][j-1]<<endl;
                    if(t[i][j+1]>=0) file2<<t[i][j]<<" "<<t[i][j+1]<<endl;
                }
                if (i==maxy-1){
                    if(t[i-1][j]>=0) file2<<t[i][j]<<" "<<t[i-1][j]<<endl;
                    if(t[i][j-1]>=0) file2<<t[i][j]<<" "<<t[i][j-1]<<endl;
                    if(t[i][j+1]>=0) file2<<t[i][j]<<" "<<t[i][j+1]<<endl;
                }
                if (j==0){
                    if(t[i-1][j]>=0) file2<<t[i][j]<<" "<<t[i-1][j]<<endl;
                    if(t[i+1][j]>=0) file2<<t[i][j]<<" "<<t[i+1][j]<<endl;
                    if(t[i][j+1]>=0) file2<<t[i][j]<<" "<<t[i][j+1]<<endl;
                }
                if (j==maxx-1){
                    if(t[i-1][j]>=0) file2<<t[i][j]<<" "<<t[i-1][j]<<endl;
                    if(t[i+1][j]>=0) file2<<t[i][j]<<" "<<t[i+1][j]<<endl;
                    if(t[i][j-1]>=0) file2<<t[i][j]<<" "<<t[i][j-1]<<endl;
                }
            }else if(t[i][j]>0 ){
                if(t[i-1][j]>=0) file2<<t[i][j]<<" "<<t[i-1][j]<<endl;
                if(t[i+1][j]>=0) file2<<t[i][j]<<" "<<t[i+1][j]<<endl;
                if(t[i][j-1]>=0) file2<<t[i][j]<<" "<<t[i][j-1]<<endl;
                if(t[i][j+1]>=0) file2<<t[i][j]<<" "<<t[i][j+1]<<endl;
            }
        }
    }

    file2.close();

    bfs(0,counter,"temp.txt");

}

int main()
{
    fw_alg("floyd1.txt");
    cout<<endl<<"----------------------------------------------------------------------"<<endl;
    bfs(1,2,"graph1.txt");
    cout<<endl<<"----------------------------------------------------------------------"<<endl;
    maze();
    return 0;
}
