//bencoding.cpp
#include "../include/bencoding.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <stack>



void changeType(piece &p, Data_Type newType) {
    // First, destroy the current type
    switch (p.type) {
        case Type::ben_int:
            p.bint.~ben_int();
            break;
        case Type::ben_str:
            p.bstr.~ben_str();
            break;
        case Type::ben_list:
            p.blist.~ben_list();
            break;
        case Type::ben_dict:
            p.bdict.~ben_dict();
            break;
    }

    // Now, based on the newType, initialize the correct member
    switch (newType) {
        case Data_Type::INT:
            new (&p.bint) ben_int();  // Default initialize ben_int
            p.type = Type::ben_int;
            break;
        case Data_Type::STRING:
            new (&p.bstr) ben_str();  // Default initialize ben_str
            p.type = Type::ben_str;
            break;
        case Data_Type::LIST:
            new (&p.blist) ben_list();  // Default initialize ben_list
            p.type = Type::ben_list;
            break;
        case Data_Type::DICT:
            new (&p.bdict) ben_dict();  // Default initialize ben_dict
            p.type = Type::ben_dict;
            break;
        case Data_Type::NONE:
            throw ParseError("Something went wrong");
            break;
    }
}

Decode::Decode(const std::string& inputByteSequence) 
    : byteSequence(inputByteSequence) {}

int Decode::decode_int(int start_index, ben_int& result) const{
    std::string int_builder = "";
    int curr_index = start_index;
    while (isdigit(byteSequence[curr_index])){
        int_builder += byteSequence[curr_index];
        curr_index += 1;
    }
    if (byteSequence[curr_index]=='e'){
        int result_num = std::stoi(int_builder);
        result.int_val = result_num;
        return curr_index + 1;
    }else{
        throw ParseError("Invalid Bencode: int");
    }    
}

int Decode::decode_str(int start_index, ben_str& result) const{
    std::string str_len_builder = "";
    int curr_index = start_index;
    while(isdigit(byteSequence[curr_index])){
        str_len_builder += byteSequence[curr_index];
        curr_index += 1;
    }
    int str_len = std::stoi(str_len_builder);
    std::string str_builder = "";
    if (byteSequence[curr_index]==':'){
        curr_index += 1;
        int limit = curr_index + str_len;
        while ((curr_index < limit) and (curr_index < byteSequence.size())) {
            str_builder += byteSequence[curr_index];
            curr_index += 1;
        }
        result.string_val = str_builder;
        //std::cout << str_builder << std::endl;
        return curr_index;
    }else{
        throw ParseError("Invalid Bencode: in string");
    }
    throw ParseError("Invalid Bencode: in string");

}

int Decode::decode_list(int start_index, ben_list& result) const{
    std::vector<std::shared_ptr<piece>> list_elements;
    int curr_index = start_index;
    while (byteSequence[curr_index] != 'e'){
        auto input_piece = std::make_shared<piece>();
        int next_index = decode(curr_index, *input_piece);
        list_elements.push_back(input_piece);
        curr_index = next_index;
    }
    result.pieces = list_elements;
    return curr_index + 1;
}

int Decode::decode_dict(int start_index, ben_dict& result) const{
    std::unordered_map<ben_str, std::shared_ptr<piece>> dict_elements;
    int curr_index = start_index;
    while (byteSequence[curr_index] != 'e'){
        ben_str res_str;
        
        int next_index = decode_str(curr_index,res_str);
        auto input_piece = std::make_shared<piece>();
        int next_next_index = decode(next_index, *input_piece);
        dict_elements[res_str] = input_piece;
        curr_index = next_next_index;
        //std::cout << "value of curr_index is : " << curr_index << std::endl;
    }
    result.dict = dict_elements;
    return curr_index+1;
}

int Decode::decode(int start_index, piece& result_piece) const {
    if (byteSequence.size() <2){
        throw ParseError("Invalid Bencode: too short");
    }
    char first_char = byteSequence[start_index];
    if (isdigit(first_char)){
        //std::cout << "found digit, so string" << std::endl;
        ben_str res;
        int next_index = decode_str(start_index,res);
        changeType(result_piece, STRING);
        result_piece.bstr = res;
        //std::cout << "value returned by decode_str is: " << next_index << std::endl;
        return next_index;
    }else if(first_char == 'i'){
        ben_int res;
        int next_index = decode_int(start_index+1, res);
        changeType(result_piece, INT);
        result_piece.bint = res;
        return next_index;
    }else if(first_char == 'l'){
        ben_list res;
        int next_index = decode_list(start_index+1,res);
        changeType(result_piece, LIST);
        result_piece.blist = res;
        return next_index;
    }else if(first_char == 'd'){
        ben_dict res;
        int next_index = decode_dict(start_index+1,res);
        changeType(result_piece, DICT);
        result_piece.bdict = res;
        return next_index;
    }else{
        throw ParseError("Invalid Bencode: no valid start");
    }
    
}

Encode::Encode(const std::shared_ptr<piece> input_piece) 
    : decoded_piece(input_piece) {}


std::string Encode::encode() const{
    std::string code_builder = "";
    switch(decoded_piece->type){
        case Type::ben_int:
            code_builder += 'i';
            code_builder += std::to_string(decoded_piece->bint.int_val);
            code_builder += 'e';
            break;
        case Type::ben_str:
            
            break;
        case Type::ben_list:
            code_builder += 'e';
            break;
        case Type::ben_dict:
            code_builder += 'e';
            break;

    };
    return code_builder;
}


