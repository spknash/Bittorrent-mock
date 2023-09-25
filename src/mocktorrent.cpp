#include <iostream>
#include "../include/bencoding.h"

int main(){
    // test 1
    std::cout << "Processing byte sequence: " << "i123e" << std::endl;
    Decode decoder("i123e");
    piece sample_piece;
    decoder.decode(0, sample_piece);
    std::cout << "value of code is(should be 123): " << sample_piece.bint.int_val << std::endl;
    // test 2
    std::cout << "Processing byte sequence: " << "5:hello" << std::endl;
    Decode decoder2("5:hello");
    piece sample_piece2;
    decoder2.decode(0, sample_piece2);
    std::cout << "value of code is(should be hello): " << sample_piece2.bstr.string_val << std::endl;
    // test 3
    std::cout << "Processing byte sequence: " << "l5:hello4:dogs3:abce" << std::endl;
    Decode decoder3("l5:hello4:dogs3:abce");
    piece sample_piece3;
    decoder3.decode(0, sample_piece3);
    std::cout << "value of code is(should be abc): " << sample_piece3.blist.pieces[2]->bstr.string_val << std::endl;
    // test 4
    std::cout << "Processing byte sequence: " << "d3:cow3:moo4:spam4:eggse" << std::endl;
    Decode decoder4("d3:cow3:moo4:spam4:eggse");
    piece sample_piece4;
    ben_str first_key = {"cow"};
    ben_str second_key = {"spam"};
    decoder4.decode(0, sample_piece4);
    std::cout << "value of code is(should be eggs): " << sample_piece4.bdict.dict[second_key]->bstr.string_val << std::endl;


}