// bencode.h
#pragma once
#include <string>


void bencode_hello();

class Decode {
private:
    std::string byteSequence;

public:
    // Constructor that takes a byte sequence
    Decode(const std::string& inputByteSequence);

    void decode() const;
};

class Encode {
private:
    std::string byteSequence;

public:
    // Constructor that takes a byte sequence
    Encode(const std::string& inputByteSequence);

    void encode() const;
};