class ATM {
public:
    ATM() {}
    
    void deposit(vector<int> banknotesCount) 
    {
        for ( int i = 0; i < banknotesCount.size(); ++i )
            banknotes.at( i ) += banknotesCount.at( i );
    }
    
    vector<int> withdraw(int amount) 
    {
        std::vector<int> take( 5, 0 );
        for ( int i = 4; i >= 0; --i )
        {
            take.at( i ) = std::min( banknotes.at( i ), amount / values.at( i ) );
            amount -= take.at( i ) * values.at( i );
        }

        if ( amount != 0 )
            return { -1 };

        for ( int i = 0; i < 5; ++i )
            banknotes.at( i ) -= take.at( i );

        return take;
    }

private:

    std::array<int, 5> values = { 20, 50, 100, 200, 500 };

    std::array<int, 5> banknotes = { 0, 0, 0, 0, 0 };

};
