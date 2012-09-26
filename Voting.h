// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <vector>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <map>
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
bool voting_readBallot (std::istream& r, int numChoices, std::deque<int>& ballot)
{
    
    for(int i = 0; i < numChoices; ++i)
    {
        r >> ballot[i]; //this reads one number at a time and assigns it to a spot in the deque (>> operator is delimited by whitespace)

        //cout << "ballot at i: " << i << " " << ballot[i] << endl;
    }
    if(!r) //"if there wasn't anything left to be read" (I don't think this should ever be reached because we know the number of candidates)
        return false;
    return true;
}

void read_first_vote(std::deque<int>& ballot) {
  

}

// ------------
// voting_eval
// ------------

/**
 * -- Put documentation here! --
*/
std::vector<int> voting_eval (std::deque<std::deque<int> > ballotContainer, int numChoices, int numOfBallots, multimap<int, std::deque<int> > ballotsSortedByVotes)
{
    bool tie = false;
    std::vector<std::vector<int> > counts(numChoices + 1, vector<int> (numOfBallots, 0));

    std::vector<int> voteCounts(numChoices+1); // holds the vote counts
    
    int max;
    std::deque<int> maxNames;
    
    int min;
    std::deque<int> minNames;
    map<int, int> mapOfIllegalNames;
    
    std::deque<std::deque<int> >::iterator it;
    it = ballotContainer.begin();
    
    int ballot = 1;
    while(it != ballotContainer.end())
    {   
        voteCounts[(*it).front()]++;
        counts[(*it).front()][0]++;
        counts[(*it).front()].push_back(ballot);
        ++ballot;
        ++it;
    }
    
    std::vector<std::vector<int> >::iterator countIt;
    countIt = counts.begin();
    ++countIt;
    


    //voteCounts.push_back((*countIt)[0]);

    int name = 1;

    max = (*countIt)[0];
    maxNames.push_back(name);

    min = (*countIt)[0];
    minNames.push_back(name);

    ++name;
    ++countIt;
    int temp;
    while(countIt != counts.end())
    {
        temp = (*countIt)[0];
        if(temp > max)
        {
            //cout << "temp > max" << endl;
            max = temp;
            maxNames.clear();
            maxNames.push_back(name);
            tie = false;
        }
        
        else if (temp == max) {
            //cout << "temp = max" << endl;
            tie = true;
            maxNames.push_back(name);
            mapOfIllegalNames[name] = name;
        }
        
        else if(temp < min)
        {
            //cout << "temp < min" << endl;
            min = temp;
            minNames.clear();
            minNames.push_back(name);
            mapOfIllegalNames.clear();
            mapOfIllegalNames[name] = name;
        }
        
        else if (temp == min) {
            //cout << "temp = min" << endl;
            minNames.push_back(name);
        }
        //voteCounts.push_back(temp);
        ++countIt;
        ++name;
    }
    
//    std::deque<int> result(0);
//    result.push_front(-1);

   bool overHalf = false;

   if( max >= (numChoices/2) ) {
      overHalf = true;
   }

   // if maxNames has more than one value, must be a tie
   if( maxNames.size() > 1 || !overHalf  ) {
      //cout << "maxNames size: " << (int) maxNames.size() << endl;

     // so need to delete the minName from ballot
     // need to grab the people that voted for the min name
     multimap<int, std::deque<int> >::iterator mapIt;
     pair<multimap<int, std::deque<int> >::iterator, multimap<int, std::deque<int> >::iterator> ret;
     std::deque<int>::iterator minNamesIt;


     minNamesIt = minNames.begin();

     //cout << *minNamesIt << endl;
     ret = ballotsSortedByVotes.equal_range(*minNamesIt);  // grabs all the ballots who voted for minName

    for (mapIt=ret.first; mapIt!=ret.second; ++mapIt) {
      //cout << "original front: " << (*mapIt).second.front() << endl;
      (*mapIt).second.pop_front();
      //cout << "popped front, new front is: " << (*mapIt).second.front() << endl;

      int newVote;
      newVote = (*mapIt).second.front();

      // if next vote on ballot is legal, increment vote
      map<int, int>::iterator illegalNamesIt = mapOfIllegalNames.find(newVote);
      if ( illegalNamesIt == mapOfIllegalNames.end() ) {
          voteCounts[newVote]++;
      }
      
    }

    // cout << "elements in map with minNames: " << mapIt->second << endl;

 
    

  }
   


    while(!maxNames.empty())
    {
        cout << "MaxNames: " << endl;
        cout << maxNames.front() << endl; //prints the first element of the results container (which holds at least one winner)
        maxNames.pop_front(); //remove the winner that we just printed (note that pop_front DOES NOT return anything
    }

    while(!minNames.empty())
    {
       cout << "MinNames: " << endl;
       cout << minNames.front() << endl; //prints the first element of the results container (which holds at least one winner)
        minNames.pop_front(); //remove the winner that we just printed (note that pop_front DOES NOT return anything
    }



    return voteCounts; //change this!
}



/**
int voting_eval (std::deque<std::deque<int> > ballotContainer, int numChoices, int numOfBallots)
{
   int numVotes[21];

   std::deque<std::deque<int> >::iterator it;
   it = ballotContainer.begin();

   while(it != ballotContainer.end())
    {
      std::deque<int> currentBallot;
      currentBallot = (*it).front();   
      std::deque<int>::iterator ballotIt;
      ballotIt = currentBallot.begin();
      numVotes[ballotIt]++;
      ++it;
    }

   return numVotes;
    
}

*/

//c++ map example
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
    string elections;
    voting_read(r, elections);
    int loopNum = atoi(elections.c_str());
    for(int k = 0; k < loopNum; ++k)
    {
	    string line;
            voting_read(r, line);
	    voting_read(r, line); //Read 1st line (it says how many candidates there are)
	    int numChoices = atoi(line.c_str()); //Store first line as number of candidates
	    
	    //Read second block of information: ordered names of candidates and store them in a vector
	    //Note: We tried to use an array but it wasn't working because we were trying to assign it
	    //a variable size.
	    std::vector<string> names(numChoices + 1);
	    for(int i = 0; i < numChoices; ++i)
	    {
		voting_read(r, line);
		names[i + 1] = line;
	    }
	    
	    //Container for all ballots: Deque (only b/c we don't know the number of ballots, if we
	    //did, then we'd use a Vector)
	    //NOTE: I think the first parameter is setting the initial size, so 0 might be inefficient
	    std::deque<std::deque<int> > ballotContainer(0, deque<int> (numChoices));


	    multimap<int, std::deque<int> > ballotsSortedByVotes;


	    
	    //Container for each ballot: Vector
	    std::deque<int> tempBallot(numChoices);
	    int ballotNums = 0;
	    //read the ballots one by one, store them in their own deque, then add that deque to the ballotContainer
	    while (voting_readBallot(r, numChoices, tempBallot))
	    {
		ballotContainer.push_back(tempBallot);

		std::deque<int>::iterator it;
		it = tempBallot.begin();
		
		ballotsSortedByVotes.insert(pair<int, std::deque<int> >(tempBallot[0], tempBallot));      
	    
		++ballotNums;
	    }

	    //tempPrint(ballotContainer);



		
	    std::vector<int> result = voting_eval(ballotContainer, numChoices, ballotNums, ballotsSortedByVotes);


	    std::vector<int>::iterator resultIt;
	    resultIt = result.begin();

	    int max = *resultIt;

	    while(resultIt != result.end())
	    {

		if(*resultIt >= max)
		    max = *resultIt;

	 //prints the first element of the results container (which holds at least one winner)
		//result.pop_front(); //remove the winner that we just printed (note that pop_front DOES NOT return anything
	     
	     resultIt++;
	    }

	    resultIt = result.begin();

	    while(resultIt != result.end()) {

	       if(*resultIt == max) 
		  w << names[resultIt-result.begin()] << endl;
	    //tempPrint(ballotContainer); //this prints the processed ballot matrix
		resultIt++;
	    }
        }
}
