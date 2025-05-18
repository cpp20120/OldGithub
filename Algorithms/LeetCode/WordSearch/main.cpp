class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> p(board.size(),vector<bool>(board[0].size(),false));
        int count=0;
        for(int i=1; i<word.size();i++)
        {
            if(word[i]==word[i-1])
                count++;
            else break;
        }
        int th=word.length()/2;
        if(count > th)
        reverse(word.begin(),word.end());


        for(int i=0; i<board.size();i++)
        {
            for(int j=0; j<board[0].size();j++)
            {
                if(backtrack(board, p, word, -1, i, j))
                return true;
            }
        }
        return false;
    }

    bool backtrack(vector<vector<char>>& board, vector<vector<bool>> &p, string word, int c, int x, int y)
    {
        c=c+1;
        if(c==word.size())
            return true;
        else if(board[x][y]==word[c])
        {
            if(c==word.size()-1)
                return true;

            p[x][y]=true;
            vector<vector<int>> nbrs = {{x-1,y},{x+1,y},{x,y+1},{x,y-1}};
            for(vector<int> nbr:nbrs)
            {
                if(nbr[0]>=0 && nbr[0]<board.size() && nbr[1]>=0 && nbr[1]<board[0].size())
                {
                    if(!p[nbr[0]][nbr[1]])
                        if(backtrack(board, p, word, c, nbr[0], nbr[1]))
                            return true;
                }
            }
            p[x][y] = false;
        }
        return false;
    }

};
