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

    std::vector<int> voteCounts(numChoices+1); // holds the vote counts
    
    int max;
    std::deque<int> maxNames;
    
    int min;
    std::deque<int> minNames;
    map<int, int> mapOfIllegalNames;
    
    std::deque<std::deque<int> >::iterator it;
    it = ballotContainer.begin();
    
    while(it != ballotContainer.end())
    {   
        voteCounts[(*it).front()]++;
        ++it;
    }
    
    
   std::vector<int>::iterator voteCountsIt;
   voteCountsIt = voteCounts.begin();
   ++voteCountsIt;


    int name = 1;

    max = (*voteCountsIt);
    maxNames.push_back(name);

    min = (*voteCountsIt);
    minNames.push_back(name);

    ++name;
    ++voteCountsIt;
    int temp;
    while(voteCountsIt != voteCounts.end())
    {
        temp = (*voteCountsIt);
        if(temp > max)
        {
            cout << "temp > max" << endl;
            max = temp;
            maxNames.clear();
            maxNames.push_back(name);
            tie = false;
        }
        
        else if (temp == max) {
            cout << "temp = max" << endl;
            tie = true;
            maxNames.push_back(name);

        }
        
        else if(temp < min)
        {
            cout << "temp < min" << endl;
            min = temp;
            minNames.clear();
            minNames.push_back(name);
            mapOfIllegalNames.clear();
            mapOfIllegalNames[name] = name;
        }
        
        else if (temp == min) {
            cout << "temp = min" << endl;
            minNames.push_back(name);
            mapOfIllegalNames[name] = name;
        }

        ++voteCountsIt;
        ++name;
    }

   bool overHalf = false;
   bool foundWinner;
   //cout << "max: " << max << endl;
   //cout <<  "numOfBallots: " << numOfBallots << endl;
   //cout << "numOfBallots/2: " << numOfBallots/2 << endl;
   if( max > (numOfBallots/2) ) {
      overHalf = true;
   }

  // cout << "maxNamesSize: " << (int) maxNames.size() << endl;

   // if there is a tie between all the candidates
   if(maxNames.size() == numChoices) {
      maxNames.clear();
      overHalf = true;
   }


      // if maxNames has more than one value, must be a tie
      if( maxNames.size() > 1 || !overHalf  ) {
         //cout << "minNames size: " << (int) minNames.size() << endl;

        // so need to delete the minName from ballot
        // need to grab the people that voted for the min name
        multimap<int, std::deque<int> >::iterator mapIt;
        pair<multimap<int, std::deque<int> >::iterator, multimap<int, std::deque<int> >::iterator> ret;
        std::deque<int>::iterator minNamesIt;

        minNamesIt = minNames.begin();

         while(minNamesIt != minNames.end()) {

           //cout << "minNamesIt: " << *minNamesIt << endl;
         ret = ballotsSortedByVotes.equal_range(*minNamesIt);  // grabs all the ballots who voted for minName

            for (mapIt=ret.first; mapIt!=ret.second; ++mapIt) {
 
               bool valid = false;

         // will run until finds a valid vote
         // still need to check if never a valid vote
            while( !valid ) {
               int newVote;
               //cout << "about to pop: " << (*mapIt).second.front() << endl;
               (*mapIt).second.pop_front();
            
               // if the deque isn't empty check the next vote
               if(!(*mapIt).second.empty()) {
                  newVote = (*mapIt).second.front();
                  //cout << "newVote: " << newVote << endl;
                  map<int, int>::iterator illegalNamesIt = mapOfIllegalNames.find(newVote);

                  // if next vote on ballot is legal, increment vote
                  if (illegalNamesIt == mapOfIllegalNames.end() && newVote != 0) {
                  //if (mapOfIllegalNames.count(newVote) <= 0) {
                     //cout << "incrementing vote: " << newVote << endl;
                     voteCounts[newVote]++;
                     valid = true;
                  }
               }

               // reached end of deque
               else {
                 // cout << "deque is empty" << endl;
                  valid = true;
               }  
             }  // while not valid

          }  // end of for loop
       minNamesIt++;
       }

   //cout << "elements in map with minNames: " << mapIt->second << endl; 

      // go through new vote counts to see if we have a winner, if not, must repeat
      std::vector<int>::iterator countIt;
      countIt = voteCounts.begin();
      ++countIt;
      int newMax = 0;
      while(countIt != voteCounts.end()) {
         if((*countIt) > newMax) {
            newMax = *countIt;
         }
         countIt++;
      }   

   }


   return voteCounts; //change this!
}


/**
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
*/


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

   string line;
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

   //cout << "final max: " << max << endl;

   while(resultIt != result.end()) {

      //cout << "results: " << *resultIt << endl;

      if(*resultIt == max)
         w << names[resultIt-result.begin()] << endl;

      resultIt++;
   }
        
}
