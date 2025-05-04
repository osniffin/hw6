#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //keep track of position 
        // divide string into substrings of 6
        // make lowercase
        //compute to number (helper fn)
        //store each value -- 0s added if needed
        //calc final hash
      int length = k.length();

      unsigned long long w[5] = {0};

      int pos = length-1;

      for(int i=4; i>=0; i--){
        unsigned long long value = 0;
        
        unsigned long long power = 1;

        for(int j=0;j<6 && pos>=0;j++, pos--){
          char temp = std::tolower(k[pos]);
          value+= letterDigitToNumber(temp)*power;
          power*=36;
        }
        w[i]=value;
      }

      unsigned long long hash =0;
      for(int i=0; i<5; i++){
        hash += static_cast<unsigned long long>(rValues[i] * w[i]);
      }
      return static_cast<HASH_INDEX_T>(hash); 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      // Add code here or delete this helper function if you do not want it
    
      if(letter >= 'a' && letter<= 'z'){
          return letter-'a'; 
      }else if(letter>='0'&& letter<='9'){
        return 26+ (letter-'0'); 
      }return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
