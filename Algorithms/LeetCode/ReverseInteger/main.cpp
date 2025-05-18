class Solution {                      
public:
    int reverse(int x) {
        long ans = 0;
        while(x){
            int rem = x%10;
            ans = ans*10+rem;
            x=x/10;
        }  

        if(ans>INT_MAX || ans<INT_MIN){
            return 0;
        }
        else{
            return int(ans);
        }
       
         
    }
}; 
