// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <vector>
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

// ------------
// voting_eval
// ------------

/**
 * -- Put documentation here! --
 */
int collatz_eval (int i, int j)
{
    
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
    
    while (voting_read(r, x))
    {
        cout << x << endl;
    }
}