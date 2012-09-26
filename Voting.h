// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <vector>
#include <deque>
using namespace std;

// ------------
// voting_read
// ------------

/**
 */
bool voting_read (std::istream& r, string & x)
{
    getline(r, x); //reads a single line from the input stream 'r' and assigns it as the value for the string 'x'
    if(!r) //"if there wasn't a line to be read..."
        return false;
    return true;
}

/**
 * @param r a std::istream
 * @param num an int representing the number of candidates
 * @param ballot a reference to the deque to which the votes will be assigned
 */
bool voting_readBallot (std::istream& r, int num, std::deque<int>& ballot)
{
    
    for(int i = 0; i < num; ++i)
    {
        r >> ballot[i]; //this reads one number at a time and assigns it to a spot in the deque (>> operator is delimited by whitespace)
    }
    if(!r) //"if there wasn't anything left to be read" (I don't think this should ever be reached because we know the number of candidates)
        return false;
    return true;
}

// ------------
// voting_eval
// ------------

/**
 * -- Put documentation here! --
 */
std::deque<int> voting_eval (std::deque<std::deque<int> > ballotContainer, int n, int b)
{
    bool tie = false;
    std::vector<std::vector<int> > counts(n + 1, vector<int> (b, 0));
    int max;
    std::deque<int> maxNames;
    int min;
    std::deque<int> minNames;
    
    std::deque<std::deque<int> >::iterator it;
    it = ballotContainer.begin();
    int ballot = 1;
    while(it != ballotContainer.end())
    {    
        counts[(*it).front()][0]++;
        counts[(*it).front()].push_back(ballot);
        ++ballot;
        ++it;
    }
    
    std::vector<std::vector<int> >::iterator countIt;
    countIt = counts.begin();
    ++countIt;
    int name = 1;
    ++name;
    max = (*countIt)[0];
    maxNames.push_back(name);
    min = (*countIt)[0];
    maxNames.push_back(min);
    ++countIt;
    int temp;
    while(countIt != counts.end())
    {
        temp = (*countIt)[0];
        if(temp > max)
        {
            max = temp;
            maxNames.clear();
            maxNames.push_back(name);
            tie = false;
        }
        
        else if (temp == max) {
            tie = true;
            maxNames.push_back(name);
        }
        
        else if(temp < min)
        {
            min = temp;
            minNames.clear();
            minNames.push_back(name);
        }
        
        else if (temp == min) {
            minNames.push_back(name);
        }
        ++countIt;
        ++name;
    }
    
//    std::deque<int> result(0);
//    result.push_front(-1);
    return maxNames; //change this!
}

//checkWinner checks to see if there is a winner yet by checking both for ties (in which case EVERY remaining candidate must be tied with each other)
//or the case where one candidate has > 50% of all the votes
bool checkWinner(std::vector<std::vector<int> >& counts, int total)
{
    bool tie = true;
    int temp = 0;
    std::vector<std::vector<int> >::iterator it;
    it = counts.begin();
    while(it != counts.end()) //loop through the whole thing
    {
        if((*it)[0] > (total/2)) //if the value has more than 50% of the votes, return true
            return true;
            
        if(temp == 0 && (*it)[0] > 0) //if we haven't seen a non-zero value yet, assign it to our temp variable
            temp = (*it)[0];
        
        else if(temp == (*it)[0] && (*it)[0] > 0) //if we HAVE seen a nonzero value before and just saw another, DIFFERENT nonzero value, then there cannot be a winner by tie
            tie = false;
            
        ++it;
    }
    if(tie) //if we got to this point, then that mean nobody had >50% of the vote, so the only way there can be a winner is if there's a tie
        return true;
        
    return false; //if we got here, then neither requirement has been met - return false
}

//evalHelper assumes that there is a winner, and finds and returns the deque containing either the lone winner or all that tied
std::deque<int> evalHelper(std::deque<std::deque<int> >& ballotContainer, int n, int b, std::vector<std::vector<int> >& counts)
{
        std::deque<int> result;
        std::vector<std::vector<int> >::iterator it;
        it = counts.begin();
        while(it != counts.end())
        {
            if((*it)[0] != 0)
                result.push_back((*it)[0]);
            ++it;
        }
        return result;
}

//this is a function I made that prints out a 2-D deque - not required
void tempPrint(std::deque<std::deque<int> > ballotContainer)
{
    for(int i = 0; i < ballotContainer.size(); ++i)
    {
        cout << "{ ";
        for(int j = 0; j < ballotContainer[i].size(); ++j)
        {
            cout << ballotContainer[i][j] << " ";
        }
        cout << "}" << endl;
    }
}

// -------------
// voting_solve
// -------------

/**
 * -- Put documentation here! --
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve (std::istream& r, std::ostream& w) {
    string x;
    voting_read(r, x); //Read 1st line (it says how many candidates there are)
    int num = atoi(x.c_str()); //Store first line as number of candidates
    
    //Read second block of information: ordered names of candidates and store them in a vector
    //Note: We tried to use an array but it wasn't working because we were trying to assign it
    //a variable size.
    std::vector<string> names(num + 1);
    for(int i = 0; i < num; ++i)
    {
        voting_read(r, x);
        names[i + 1] = x;
    }
    
    //Container for all ballots: Deque (only b/c we don't know the number of ballots, if we
    //did, then we'd use a Vector)
    //NOTE: I think the first parameter is setting the initial size, so 0 might be inefficient
    std::deque<std::deque<int> > ballotContainer(0, deque<int> (num));   
    
    //Container for each ballot: Vector
    std::deque<int> tempBallot(num);
    int ballotNums = 0;
    //read the ballots one by one, store them in their own deque, then add that deque to the ballotContainer
    while (voting_readBallot(r, num, tempBallot))
    {
        ballotContainer.push_back(tempBallot);
        ++ballotNums;
    }
        
    std::deque<int> result = voting_eval(ballotContainer, num, ballotNums);
    while(!result.empty())
    {
        w << result.front() << endl; //prints the first element of the results container (which holds at least one winner)
        result.pop_front(); //remove the winner that we just printed (note that pop_front DOES NOT return anything
    }
    //tempPrint(ballotContainer); //this prints the processed ballot matrix
}