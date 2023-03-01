#include<iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

bool word_diff(std:: string word1, std:: string word2){
    if(word1.length() != word2.length()) return false;

    int pointer1 = 0;
    int pointer2 = 0;

    while(pointer1 < word1.length() && pointer2 < word2.length()){ 
        if(word1[pointer1] != word2[pointer2]){ //if at any point the words dont match, return false
            return false;
        }
        //Increment pointers
        pointer1++;
        pointer2++;
    }

    return true; 
}

bool classical_file_diff(std::string file1, std::string file2){
    std::ifstream firstFile; //initialize input stream to read file contents
    firstFile.open(file1,std::ios::in); //open the file

    std::ifstream secondFile;
    secondFile.open(file2,std::ios::in);

    std::string firstString = ""; //string to have contents of file

    std::string secondString = "";

    while(firstFile){
        firstString.push_back(firstFile.get()); //keep pushing characters of firstFile until we get to the end
    }

    while(secondFile){
        secondString.push_back(secondFile.get());
    }

    firstFile.close(); //finally, close all the files
    secondFile.close();

    return word_diff(firstString,secondString); //call word diff on firsString and secondString, which have been fed the contents of the files
}

std::size_t hash_it(std::string someString){
    std::hash<std::string> hasher; //simply return hash of someString
    return hasher(someString);
    // std::hash<std::string>()("foo");
}

bool enhanced_file_diff(std::string file1, std::string file2){
    std::ifstream firstFile; 
    firstFile.open(file1,std::ios::in);

    std::ifstream secondFile;
    secondFile.open(file2,std::ios::in);

    std::string line1;
    std::string line2;

    while(std::getline(firstFile,line1)){
        std::cout << "in while enhanced" << std::endl;
        std::getline(secondFile, line2);

        if(hash_it(line1) != hash_it(line2)){ //if hash of any lines not the same, close the files and return false
            firstFile.close();
            secondFile.close();
            return false;
        }
    }

    firstFile.close();
    secondFile.close();

    return true;

}

void mismatch_helper(std::string file1, std::string file2, int count){ //recursive helper function for list_mismatched_lines
    std::ifstream firstFile(file1,std::ios::in);
    // firstFile.open(file1);

    std::ifstream secondFile(file2,std::ios::in);
    // secondFile.open(file2);

    std::string line1;
    std::string line2;

    int track = count; //keep track of original value of count to be used later

    while(count > 0){ //count refers to the line number that we want to read 
        std::getline(firstFile,line1);
        std::getline(secondFile,line2);
        count--;
    }

    if(!enhanced_file_diff(file1,file2)){ //if they're different, find the hash of the lines and print them out

        if(hash_it(line1) != hash_it(line2)){
            std::cout<<"file1: "<< line1 <<std::endl;
            std::cout<<"file2: "<< line2 <<std::endl;
        }
        
    }

    if(firstFile.eof() || secondFile.eof() || !std::getline(firstFile, line1) || !std::getline(secondFile, line2)) return; //base case: if end of file is reached, return
    std::cout << firstFile.eof();


    track = track+1;
    mismatch_helper(file1,file2,track); //else, increment track (so increment line number to read) and recursively call the function

    firstFile.close();
    secondFile.close();
}

void list_mismatched_lines(std::string file1, std::string file2){
    mismatch_helper(file1,file2,1); //call recursive mismatch helper function with starting value 1
}

std::vector<std::string> findWords(std::string s){
    std::string word = ""; //word to append to 
    std::vector<std::string> result; //to be returned

    for(int i = 0; i < s.length(); i++){
        char c = s.at(i);
        
        if(isspace(s.at(i))){ //if s.at(i) is whitespace, append word, reset it, then continue 
            result.push_back(word);
            word = "";
            continue;
        } 
        word += c; 

    }

    return result;

}

void mismatch_words_helper(std::string file1, std::string file2, int count){ //recursive helper function for list_mismatched_words
    std::ifstream firstFile;
    firstFile.open(file1);

    std::ifstream secondFile;
    secondFile.open(file2);

    std::string line1;
    std::string line2;

    int track = count; //keep track of original value of count to be used later

    while(count > 0){ //count refers to the line number that we want to read 
        std::getline(firstFile,line1);
        std::getline(secondFile,line2);
        count--;
    }

    if(!enhanced_file_diff(file1,file2)){ //if they're different, find the hash of the lines and print them out

        std::vector<std::string> line1V = findWords(line1);
        std::vector<std::string> line2V = findWords(line2);

        for(int i = 0; i < line1V.size(); i++){
            //std::cout<< line1V[i] <<std::endl;
            if(hash_it(line1V[i]) != hash_it(line2V[i])){ //iterate through vector to find mismatched words
                std::cout<<"file1: "<< line1V[i] << " (line " + std::to_string(track) + ")" <<std::endl;
                std::cout<<"file2: "<< line2V[i] << " (line " + std::to_string(track) + ")" <<std::endl;
            }

        }
        
    }

    if(firstFile.eof() || secondFile.eof()) return; //base case: if end of file is reached, return

    track = track+1;
    mismatch_words_helper(file1,file2,track); //else, increment track (so increment line number to read) and recursively call the function

    firstFile.close();
    secondFile.close();
}

void list_mismatched_words(std::string file1, std::string file2){
    mismatch_words_helper(file1, file2, 1);
}

// int main(){
//     //Q1
//     std::string str1 = "Hello World";
//     std::string str2 = "hEllO World";
//     std::string str3 = "World";
//     std::string str4 = "Hello World";
//     bool result1 = word_diff(str1, str2); // False
//     std::cout << result1 << std::endl;
//     bool result2 = word_diff(str1, str3); // False
//     bool result3 = word_diff(str1, str4); // True

//     // // Q2
//     std::string file1 = "./txt_folder/file1.txt";
//     std::string file2 = "./txt_folder/file2.txt";
//     bool result4 = classical_file_diff(file1, file2); // False

//     // // Q3
//     std::string mystr = "I love this assignment";
//     std::size_t h1 = hash_it (mystr);
//     std::cout << h1 << std::endl;

//     // // Q4
//     bool result5 = enhanced_file_diff(file1, file2); // False

//     // // Q5
//     list_mismatched_lines(file1, file2); // This should print to the screen the mismatched lines

//     // Q6
//     list_mismatched_words(file1, file2); // This should print to the screen the mismatched words
// }
