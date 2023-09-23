//bencoding.cpp
#include "../include/bencoding.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <stack>

enum Data_Type {
    NONE,
    INT,    
    STRING,  
    LIST,
    DICT    
};

Decode::Decode(const std::string& inputByteSequence) 
    : byteSequence(inputByteSequence) {}

void Decode::decode() const {
    std::cout << "Processing byte sequence: " << byteSequence << std::endl;
    if (byteSequence.size() <2){
        printf("not valid bencode");
    }
    std::stack<int> bit_stack;
    Data_Type curr_type = NONE;
    char first_char = byteSequence[0];
    if (std::isdigit(first_char)){
        bit_stack.push(STRING);
    }else if (first_char == 'i'){
        bit_stack.push(INT);
    }else if (first_char == 'l'){
        bit_stack.push(LIST);
    }else if (first_char == 'd'){
        bit_stack.push(DICT);
    }else{
        printf("not valid bencode");
    }
    int index = 0;
    //piece popped_piece;
    std::string int_builder = "";
    int str_len;
    std::string str_len_builder = "";
    bool colon_found = false;
    std::string str_builder = "";
    while (!bit_stack.empty()){
        if (bit_stack.top()==STRING){
            // handle STRING here
        }else if (bit_stack.top()==INT){
            // handle INT here
            if (std::isdigit(byteSequence[index])){
                int_builder += byteSequence[index];
            }else if(byteSequence[index]=='e'){
                int num = std::stoi(int_builder);
                int_builder = "";
                bit_stack.pop();

            }
        }else if (bit_stack.top()==LIST){
            // handle LIST here

        }else{
            // handle DICT here
        }

    }
    if (byteSequence[0] == 'i'){
        bit_stack.push(1);

        std::string int_string = "";
        int index = 1;
        while (byteSequence[index] != 'e'){
            int_string += byteSequence[index];
            index +=1;

        }
        int num = std::stoi(int_string);
        std::cout << "integer found: " << int_string << std::endl;
    }
}


