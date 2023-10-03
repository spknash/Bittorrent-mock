#include <iostream>
#include "../include/bencoding.h"

int main(){
    // test 1
    std::cout << "Processing byte sequence: " << "i123e" << std::endl;
    Decode decoder("i123e");
    std::shared_ptr<piece> sample_piece = std::make_shared<piece>();
    //std::shared_ptr<piece> sample_piece;
    decoder.decode(0, sample_piece);
    std::cout << "value of code is(should be 123): " << sample_piece->bint.int_val << std::endl;
    
    // Encode encoder;
    // std::string encoded_val = encoder.encode(&sample_piece);
    // std::cout << "msg after encoding again is " << encoded_val << std::endl;
    // test 2
    std::cout << "Processing byte sequence: " << "5:hello" << std::endl;
    Decode decoder2("5:hello");
    std::shared_ptr<piece> sample_piece2 = std::make_shared<piece>();
    decoder2.decode(0, sample_piece2);
    std::cout << "value of code is(should be hello): " << sample_piece2->bstr.string_val << std::endl;
    // test 3
    std::cout << "Processing byte sequence: " << "l5:hello4:dogs3:abce" << std::endl;
    Decode decoder3("l5:hello4:dogs3:abce");
    std::shared_ptr<piece> sample_piece3 = std::make_shared<piece>();
    decoder3.decode(0, sample_piece3);
    std::cout << "value of code is(should be dogs): " << sample_piece3->blist.pieces[1]->bstr.string_val << std::endl;
    // test 4
    std::cout << "Processing byte sequence: " << "d3:cow3:moo4:spam4:eggse" << std::endl;
    Decode decoder4("d3:cow3:moo4:spam4:eggse");
    std::shared_ptr<piece> sample_piece4 = std::make_shared<piece>();
    ben_str first_key = {"cow"};
    ben_str second_key = {"spam"};
    std::cout << "before decode" << std::endl;
    decoder4.decode(0, sample_piece4);
    std::cout << "after decode dict" << std::endl;
    std::cout << "value of code is(should be eggs): " << sample_piece4->bdict.dict[second_key]->bstr.string_val << std::endl;


}