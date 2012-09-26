import java.io.*;
import java.util.*;

class generate_tests {
    public static void main(String[] args) throws IOException {
        
        FileWriter fWriter = null;
        BufferedWriter writer = null; 
        try {
          fWriter = new FileWriter("RunVoting.in");
          writer = new BufferedWriter(fWriter); //WRITES 1 LINE TO FILE AND CHANGES LINE
        
        //Set number of candidates, n, where 1 <= n <= 20
        Random rand = new Random();
        int min = 1;
        int max = 20;
//        int num_candidates = rand.nextInt(max - min + 1) + min;
        int num_candidates = 20;
        ArrayList<String> candidates = new ArrayList<String>();
        writer.write(num_candidates + "");
        writer.newLine();
        
        //32-126
        //Generate and write candidates line by line
        while(candidates.size() < num_candidates)
        {
            String candidate = makeCandidate();
            if(!candidates.contains(candidate))
            {
                writer.write(candidate);
                writer.newLine();
                candidates.add(candidate);
            }
        }
        
        //creates array {1, 2, 3, ..., n}
        int[] baseBallot = new int[num_candidates];
        for(int i = 0; i < num_candidates; ++i)
        {
            baseBallot[i] = i + 1;
        }
        
        int num_ballots = 1000;
        for(int i = 0; i < num_ballots; i++)
        {
            String temp = generator(num_candidates, baseBallot);
            writer.write(temp);
            if(i < num_ballots - 1)
                writer.newLine();
        }
           writer.close();
        } catch (Exception e) {
        }
        
    }
    
        public static String generator(int n, int[] baseBallot)
        {
            String result = "";
            ArrayList<Integer> tempResult = new ArrayList<Integer>();
            for(int i = 0; i < n; ++i)
            {
                tempResult.add(baseBallot[i]);
            }
            Collections.shuffle(tempResult);
            for(int i = 0; i < n - 1; ++i)
            {
                result = result + tempResult.get(i) + " ";
            }
            result = result + tempResult.get(n - 1);
            return result;
        }
        
        public static String makeCandidate()
        {
            String result = "";
            Random rand = new Random();
            int min = 1;
            int max = 80;
            max = rand.nextInt(max - min + 1) + min;
            int temp;
            while(min < max)
            {
                temp = rand.nextInt(126 - 32 + 1) + 32;
                result = result + (char) temp + "";
                ++min;
            }
            return result;
        }
}