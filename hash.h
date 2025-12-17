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

        // max 26 characters 
        unsigned long long w[5];

        for(int i =0; i<5; i++){
            w[i]=0;
        }

        int group=4;
        int pos = k.length() -1;

        // want to decrement indexes becasue we are searchign from right to left
        //not left to right
        while(pos >= 0){
            if (group < 0){
                break;
            }
            unsigned long long value =0;
            unsigned long long base =1;

            for (int j =0; j < 6; j++){
                if ( pos < 0){
                    break;
                }
                unsigned long long digitValue = letterDigitToNumber(k[pos]);
                value += digitValue * base;
                base *= 36;
                pos--;
            }
            w[group] = value;
            group--;
        }

        unsigned long long hash =0;
        for (int i =0; i< 5; i++){
            hash += (unsigned long long )rValues[i] * w[i];
        }

        return hash;



        


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
    
        //vector<int> values;
        //vector<char> letters_lower;
        //vector<char> letters_upper;

        // for (size_t i=0, i <= 25 ; i++){
        //     // want it to be the letters
        //     values[i]= i
        // }

        // for (size_t i =0; i <= 9; i++){
        //     values[26+i]= i;
        // }

        // for(size_t i=0; i <= 36; i++){
        //     if (letter == values[i]){
        //         letter = values[i];// possibly
        //     }
        // }
        // value assigned to the numbers
        if (letter >= '0' && letter <= '9'){
            return (letter -'0') +26;
        }

        // value assigned to the uppercase
        //must change to lower case first
        if(letter >- 'A' && letter <= 'Z'){
            letter = tolower(letter);
        }
        //value assigned to the lowercase
        if (letter >= 'a' && letter <= 'z'){
            return letter-'a';
        }

        return 0;
        

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
