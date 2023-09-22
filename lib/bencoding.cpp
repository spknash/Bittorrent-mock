//bencoding.cpp
#include "../include/bencoding.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <stack>



Decode::Decode(const std::string& inputByteSequence) 
    : byteSequence(inputByteSequence) {}

void Decode::decode() const {
    std::cout << "Processing byte sequence: " << byteSequence << std::endl;
    std::stack<int> bit_stack;
    while (!bit_stack.empty()){
        
    }
    if (byteSequence[0] == 'i'){
        bit_stack.push(1);

        std::string int_string = "";
        int index = 1;
        while (byteSequence[index] != 'e'){
            int_string += byteSequence[index];
            index +=1;

        }
        std::cout << "integer found: " << int_string << std::endl;
    }
}


