class Solution {
public:
    int compress(vector<char>& chars) 
    {
        int i = 0 , n = chars.size();
        int ansIndex = 0;
        while(i<n)
        {
            int sameCnt = 1;
            int next = i+1;
            while(next<n && chars[i] == chars[next])
            {
              sameCnt++;  
              next++; 
            }

            if(sameCnt>1)
            {
                chars[ansIndex] = chars[i]; ansIndex++;

                string num = to_string(sameCnt);
                for(char ch : num)
                {
                    chars[ansIndex] = ch;
                    ansIndex++;
                }
                i = next;
            }
            else
            {
                 chars[ansIndex] = chars[i]; ansIndex++;
                i++;
            }
        }   

        return ansIndex;

    }
};
