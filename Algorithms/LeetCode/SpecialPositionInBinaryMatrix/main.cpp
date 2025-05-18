class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int cnt=0;
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat[i].size();j++){
                if(mat[i][j]==1){
                    bool s=true;
                    for(int z=0;z<mat[i].size();z++){
                        if(mat[i][z]==1 && z!=j){
                            s=false;
                            break;
                        }
                    }
                    for(int a=0;a<mat.size();a++){
                        if(mat[a][j]==1 && a!=i){
                            s=false;
                            break;
                        }
                    }
                    if(s==true){
                    cnt+=mat[i][j];
                    }
                }
            }
        }
        return cnt;
    }
};
