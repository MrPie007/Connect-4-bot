#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
char grid[10][10];
//7 col and 6 rows
int no_in_col[10];
const long long mod = 1e7+19;
int sol[10000020];
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};
unordered_map<pair<long long,long long>, int, hash_pair> um;
long long xx,oo;
void print_mask(long long xto_output)
{
    vector<int>v[6];
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            v[i].push_back(xto_output%2);
            //cout<<xto_output%2<<" ";
            xto_output/=2;
        }
        //cout<<endl;
    }
    for(int i=5;i>=0;i--)
    {
        for(int j=0;j<7;j++)
        {

            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool is_legal(int i)
{
    if(no_in_col[i] < 6)
        return 1;
    return 0;
}
/*
35 36 37 38 39 40 41
28 29 30 31 32 33 34
21 22 23 24 25 26 27
14 15 16 17 18 19 20
7  8  9  10 11 12 13
0  1  2  3  4  5  6
*/
void put_in(bool turn,int col)
{
    no_in_col[col]++;
    int idx = (col-1) + 7*(no_in_col[col]-1);
    if(turn)xx|=(1ll<<idx);
    else oo|=(1ll<<idx);
    if(turn)
    {
        grid[no_in_col[col]][col] = 'X';
    }
    else
    {
        grid[no_in_col[col]][col] = 'O';
    }
}
int is_win(int col)
{
    int row = no_in_col[col];
    int c=0;
    for(int i=col;i>=max(1,col-3);i--)
    {
        if(grid[row][i] == 'X')c++;
        else break;
    }
    for(int i=col;i<=min(7,col+3);i++)
    {
        if(grid[row][i] == 'X')c++;
        else break;
    }
    if(c>=5)return 1;
    c=0;
    for(int i=row;i>=max(1,row-3);i--)
    {
        if(grid[i][col] == 'X')c++;
        else break;
    }
    for(int i=row;i<=min(6,row+3);i++)
    {
        if(grid[i][col] == 'X')c++;
        else break;
    }
    if(c>=5)return 1;
    c=0;
    for(int i=col;i>=max(1,col-3);i--)
    {
        if(grid[row][i] == 'O')c++;
        else break;
    }
    for(int i=col;i<=min(7,col+3);i++)
    {
        if(grid[row][i] == 'O')c++;
        else break;
    }
    if(c>=5)return -1;
    c=0;
    for(int i=row;i>=max(1,row-3);i--)
    {
        if(grid[i][col] == 'O')c++;
        else break;
    }
    for(int i=row;i<=min(6,row+3);i++)
    {
        if(grid[i][col] == 'O')c++;
        else break;
    }
    if(c>=5)return -1;

    for(int i=0;i<4;i++)
    {
        if(row+i>6 || col+i>7)break;
        if(grid[row+i][col+i] == 'X')c++;
        else break;
    }
    for(int i=0;i<4;i++)
    {
        if(row-i<=0 || col-i<=0)break;
        if(grid[row-i][col-i] == 'X')c++;
        else break;
    }
    if(c>=5)return 1;
    c=0;
    for(int i=0;i<4;i++)
    {
        if(row-i<=0 || col+i>7)break;
        if(grid[row-i][col+i] == 'X')c++;
        else break;
    }
    for(int i=0;i<4;i++)
    {
        if(row+i>6 || col-i<=0)break;
        if(grid[row+i][col-i] == 'X')c++;
        else break;
    }
    if(c>=5)return 1;

    c=0;
    for(int i=0;i<4;i++)
    {
        if(row+i>6 || col+i>7)break;
        if(grid[row+i][col+i] == 'O')c++;
        else break;
    }
    for(int i=0;i<4;i++)
    {
        if(row-i<=0 || col-i<=0)break;
        if(grid[row-i][col-i] == 'O')c++;
        else break;
    }
    if(c>=5)return -1;
    c=0;
    for(int i=0;i<4;i++)
    {
        if(row-i<=0 || col+i>7)break;
        if(grid[row-i][col+i] == 'O')c++;
        else break;
    }
    for(int i=0;i<4;i++)
    {
        if(row+i>6 || col-i<=0)break;
        if(grid[row+i][col-i] == 'O')c++;
        else break;
    }
    if(c>=5)return -1;
    return 0;
}
//-1 player 2 won
//1 player 1 won
//0 its a tie
int best_move;
int lst_best_move=-1;
int max_depth;
int start_move;
int ct;
bool fail=0;
int solve(bool turn,int depth,int alpha,int beta,int current_move)
{
    if(depth == 0)return 0;
    if(um.count({xx,oo}))return um[{xx,oo}];
    if(GetTickCount() - ct > 5000)
    {
        fail=1;
        return 0;
    }
    int best_eval=0;
    if(turn)
    {
        best_eval=-500000;
        bool play=0;
        vector<int>moves;
        if(lst_best_move!=-1)
        {
            moves.push_back(lst_best_move);
        }
        if(lst_best_move!=4)
        moves.push_back(4);
        for(int i=1;i<=3;i++)
        {
            if(lst_best_move!=4-i)
            moves.push_back(4-i);
            if(lst_best_move!=4+i)
            moves.push_back(4+i);
        }

        //random_shuffle(moves.begin(),moves.end());
        for(int jj=0;jj<7;jj++)
        {
            int i=moves[jj];
            if(is_legal(i))
            {
                play=1;
                put_in(turn,i);
                int won = is_win(i)*(42 - (current_move - start_move));
                if(won == 0)
                {
                    int x = solve(!turn,depth-1,alpha,beta,current_move+1);
                    if(x>best_eval)
                    {
                        best_eval = x;
                        if(depth == max_depth)
                        {
                            best_move = i;
                        }
                    }
                }
                else
                {
                    if(won>best_eval)
                    {
                        best_eval = won;
                        if(depth == max_depth)
                        {

                            best_move = i;
                        }
                    }
                }
                int idx = (i-1) + 7*(no_in_col[i]-1);
                xx^=(1ll<<idx);
                grid[no_in_col[i]][i]='.';
                no_in_col[i]--;
                if(best_eval>=beta)break;
                    alpha=max(alpha,best_eval);


            }
        }
        if(!play)return 0;
        if(best_eval!=0 && um.size()<1e8)um[{xx,oo}]=best_eval;

        return best_eval;
    }
    else
    {
        best_eval=500000;
        bool play=0;
        vector<int>moves;
        moves.push_back(4);
        for(int i=1;i<=3;i++)
        {
            moves.push_back(4-i);
            moves.push_back(4+i);
        }
        //random_shuffle(moves.begin(),moves.end());
        for(int jj=0;jj<7;jj++)
        {
            int i=moves[jj];
            if(is_legal(i))
            {
                play=1;
                put_in(turn,i);
                int won = is_win(i)*(42 - (current_move - start_move));
                if(won == 0)
                {
                    int x = solve(!turn,depth-1,alpha,beta,current_move+1);
                    if(x<best_eval)
                    {
                        best_eval = x;
                        if(depth == max_depth)
                        {

                            best_move = i;
                        }
                    }
                }
                else
                {
                    if(won<best_eval)
                    {
                        best_eval = won;
                        if(depth == max_depth)
                        {

                            best_move = i;
                        }
                    }
                }

                grid[no_in_col[i]][i]='.';
                int idx = (i-1) + 7*(no_in_col[i]-1);
                oo^=(1ll<<idx);
                no_in_col[i]--;
                if(best_eval<=alpha)break;
                beta=min(beta,best_eval);
            }
        }
        if(!play)return 0;
        if(best_eval!=0 && um.size()<1e8)um[{xx,oo}]=best_eval;
        return best_eval;
    }

}
int main()
{
    srand(time(0)^clock());
    for(int i=1;i<=6;i++)for(int j=1;j<=7;j++)grid[i][j]='.';
   // grid[1][1]=grid[1][2] = grid[1][3] = 'X';
    //no_in_col[1] = no_in_col[2] = no_in_col[3] = 1;
    for(int i=6;i>=1;i--)
    {
        for(int j=1;j<=7;j++)
        {
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    max_depth =12;
    bool turn=1;
    bool f=0;
    auto startTime = std::chrono::high_resolution_clock::now();
    for(int c=0;c<42;c++)
    {
        um.clear();
        int evl=0;
        if(0)
        {

            int x;
            cin>>x;
            put_in(turn,x);
            turn=!turn;
            if(is_win(x))f=1;
        }
        else
        {
            ct = GetTickCount();
            lst_best_move = -1;
            fail = 0;
            for(max_depth=7;GetTickCount() - ct < 5000 && max_depth<50;max_depth++)
            {
                start_move = c;
                evl=solve(turn,max_depth,-500000,500000,c);
                if(fail)
                {
                    max_depth--;
                    break;
                }
                lst_best_move = best_move;
            }
            best_move = lst_best_move;
            put_in(turn,best_move);
            if(is_win(best_move))f=1;
            turn=!turn;
        }
        //auto endTime = std::chrono::high_resolution_clock::now();
        system("CLS");
        //int time_spent = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        //if(time_spent < 1000)max_depth++;
        //if(time_spent > 5000)max_depth--;
        cout<<"1 2 3 4 5 6 7"<<endl;
        for(int i=6;i>=1;i--)
        {
            for(int j=1;j<=7;j++)
            {
                cout<<grid[i][j]<<" ";
            }
            cout<<endl;
        }
        print_mask(oo);
        if(evl<0)cout<<"player 2 wins in: ";
        else if(evl > 0 )cout<<"Player 1 wins in: ";
        else cout<<"I can't see a win rn, here is a 42: ";
        cout<<42-abs(evl)<<endl;
        cout<<"moves: "<<c<<endl;
        cout<<"best move: "<<best_move<<endl;
        std::cout << "Time Elapsed: " <<GetTickCount()-ct << "ms\n";
        cout<<"in_depth: "<<max_depth<<endl;
        if(f)
        {
            break;
        }

    }

    //put_in(turn,best_move)
    return 0;
}
