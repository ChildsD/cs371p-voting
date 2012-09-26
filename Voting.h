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
 * reads two ints into i and j
 * @param r an  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool voting_read (std::istream& r, string & x)
{
    //I chose 80 because I don't think the input file can have lines any longer than that
    getline(r, x);
    if(!r)
        return false;
    return true;
}

bool voting_readBallot (std::istream& r, int num, std::vector<int>& ballot)
{
    for(int i = 0; i < num; ++i)
    {
        r >> ballot[i];
    }
    if(!r)
        return false;
    return true;
}

// ------------
// voting_eval
// ------------

/**
 * -- Put documentation here! --
 */
std::deque<int> voting_eval (std::deque<std::vector<int> > ballotContainer)
{
    std::deque<int> result(0);
    result.push_front(-1);
    return result; //change this!
}

void tempPrint(std::deque<std::vector<int> > ballotContainer)
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
    std::deque<std::vector<int> > ballotContainer(0, vector<int> (num));   
    
    //Container for each ballot: Vector
    std::vector<int> tempBallot(num);
    while (voting_readBallot(r, num, tempBallot))
    {
        ballotContainer.push_back(tempBallot);
    }
    
    std::deque<int> result = voting_eval(ballotContainer); //returns the # of the winner
    while(!result.empty())
    {
        cout << result.front() << endl;
        result.pop_front();
    }
//    for(int i = 0; i < sizeof(result); ++i)
//    {
//        if(result[i] == 0)
//            break;
//        w << i << endl;
////        w << names[i] << endl;
//    }
    //tempPrint(ballotContainer); //this prints the processed ballot matrix
}