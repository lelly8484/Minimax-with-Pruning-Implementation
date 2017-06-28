bool istied(int *board)
{
    for (int i=0; i<9; i++)
    {
        if (board[i]==0)
        {
            return false;
        }
    }
    return true;
}

int minmaxhelper(int *board, int turn)
{
    char status = game_status(board);
    if (status==X)
    {
        
        return 1;
    }
    
    else if (status==O)
    {
        return -1;
    }
    
    else if (istied(board))
    {
        return NONE;
    }
    else
    {
        if (turn==X)
        {
            int maximizer=-999;
            int checkmax;
            
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=X;
                    
                    checkmax=minmaxhelper(tempboard,O);
                    if (checkmax>maximizer)
                    {
                        maximizer=checkmax;
                    }
                    
                }
            }
            
            return maximizer;
            
        }
        else
        {
            int minimizer=999;
            int checkmin;
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=O;
                    
                    checkmin=minmaxhelper(tempboard,X);
                    if (checkmin<minimizer)
                    {
                        minimizer=checkmin;
                    }
                    
                }
            }
            
            return minimizer;
            
            
        }
    }
    
}

int minmax_tictactoe(int *board, int turn)
{
    //put your code here:
    //it must return X(1), O(2) or NONE(0) for tie.
    //use the function game_status(board), to evaluate a board
    //it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
    //the program will keep track of the number of boards evaluated
    //int result = game_status(board);
    
    int winner=minmaxhelper(board, turn);
    
    if (winner==-1)
    {
        return O;
    }
    else if (winner==1)
    {
        return X;
    }
    return NONE;
    }

int abprunehelper(int *board, int turn, int alpha, int beta)
{
    char status = game_status(board);
    if (status==X)
    {
        return 1;
    }
    else if (status==O)
    {
        return -1;
    }
    else if (istied(board))
    {
        return NONE;
    }
    else
    {
        if (turn==X)
        {
            int maximizer=-999;
            int checkmax;
            
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=X;
                    checkmax=abprunehelper(tempboard,O,alpha,beta);
                    
                    if (checkmax>maximizer)
                    {
                        maximizer=checkmax;
                    }
                    if (maximizer>=beta)
                    {
                        return maximizer;
                    }
                    if (maximizer>alpha)
                    {
                        alpha=maximizer;
                    }
                }
            }
            return maximizer;
        }
        else
        {
            int minimizer=999;
            int checkmin;
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=O;
                    checkmin=abprunehelper(tempboard,X,alpha,beta);
                    
                    if (checkmin<minimizer)
                    {
                        minimizer=checkmin;
                    }
                    if (minimizer<=alpha)
                    {
                        return minimizer;
                    }
                    if (minimizer<beta)
                    {
                        beta=minimizer;
                    }
                    
                }
            }
            return minimizer;
        }
    }
}


int abprun_tictactoe(int *board, int turn)
{ 
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
    
    int winner=abprunehelper(board,turn,-1,1);
    
    if (winner==-1)
    {
        return O;
    }
    else if (winner==1)
    {
        return X;
    }
    return NONE;
}

float stochastic(int *board, int turn)
{
    int status = game_status(board);
    int counter=0;
    for (int j=0; j<9; j++)
    {
        if (board[j]==0)
        {
            counter++;
        }
    }
    
    if (status==X)
    {
        
        return 1.0;
    }
    
    else if (status==O)
    {
        return 0.0;
    }
    
    else if (istied(board))
    {
        return 0.0;
    }
    else
    {
        if (turn==X)
        {
            float maximizer=0.0;
            float result=0.0;
            float temp=0;
            
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=X;
                    
                    temp=stochastic(tempboard,O);
                    result+=(temp*1.0/9);
                    if(temp>maximizer)
                    {
                        maximizer=temp;
                    }
                }
            }
            
            result+=(maximizer*(9-counter)/9);
            return result;
            
        }
        else
        {
            float minimizer=1.0;
            float result=0.0;
            float temp=0;
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=O;
                    temp=stochastic(tempboard,X);
                    result+=(temp*1.0/9);
                    if(temp<minimizer)
                    {
                        minimizer=temp;
                    }
                    
                }
            }
            
            result+=(minimizer*(9-counter)/9);
            return result;
            
            
        }
    }
    
}


    
float st_tictactoe_win(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
    float results=stochastic(board,turn);
    
	return results;
}

float stochastic1(int *board, int turn)
{
    int status = game_status(board);
    int counter=0;
    for (int j=0; j<9; j++)
    {
        if (board[j]==0)
        {
            counter++;
        }
    }
    
    if (status==X)
    {
        
        return 1.0;
    }
    
    else if (status==O)
    {
        return 0.0;
    }
    
    else if (istied(board))
    {
        return 1.0;
    }
    else
    {
        if (turn==X)
        {
            float maximizer=0.0;
            float result=0.0;
            float temp=0;
            
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=X;
                    
                    temp=stochastic1(tempboard,O);
                    result+=(temp*1.0/9);
                    if(temp>maximizer)
                    {
                        maximizer=temp;
                    }
                }
            }
            
            result+=(maximizer*(9-counter)/9);
            return result;
            
        }
        else
        {
            float minimizer=1.0;
            float result=0.0;
            float temp=0;
            for (int i=0; i<9; i++)
            {
                if (board[i]==0)
                {
                    int tempboard[9];
                    for (int j=0; j<9; j++)
                    {
                        tempboard[j]=board[j];
                    }
                    tempboard[i]=O;
                    temp=stochastic1(tempboard,X);
                    result+=(temp*1.0/9);
                    if(temp<minimizer)
                    {
                        minimizer=temp;
                    }
                    
                }
            }
            
            result+=(minimizer*(9-counter)/9);
            return result;
            
            
        }
    }
    
}

float st_tictactoe_winortie(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
    float results=stochastic1(board,turn);
    
	return results;
}



















