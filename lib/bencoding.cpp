//bencoding.cpp
#include "../include/bencoding.h"

#include <string>
#include <iostream>

void bencode_hello(){
    printf("Hello from bencode\n");
}

Decode::Decode(const std::string& inputByteSequence) 
    : byteSequence(inputByteSequence) {}

void Decode::decode() const {
    std::cout << "Processing byte sequence: " << byteSequence << std::endl;
    if (byteSequence[0] == 'i'){
        std::string int_string = "";
        int index = 1;
        while (byteSequence[index] != 'e'){
            int_string += byteSequence[index];
            index +=1;

        }
        std::cout << "integer found: " << int_string << std::endl;
    }
}


