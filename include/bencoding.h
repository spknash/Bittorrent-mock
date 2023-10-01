// bencode.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <stdexcept>

class ParseError : public std::runtime_error {
public:
    // Use the constructor of std::runtime_error to initialize the error message
    explicit ParseError(const std::string& message)
        : std::runtime_error(message) {}
};

struct piece;
struct ben_int{
    int int_val;
};

struct ben_str{
    std::string string_val;
    bool operator==(const ben_str& other) const {
        return string_val == other.string_val;
    }
};

namespace std {
    template <>
    struct hash<ben_str> {
        size_t operator()(const ben_str& b) const {
            return hash<std::string>()(b.string_val);
        }
    };
}

struct ben_list{
    std::vector<std::shared_ptr<piece>> pieces;
};

struct ben_dict{
    std::unordered_map<ben_str, std::shared_ptr<piece>> dict;
};

enum class Type {ben_int, ben_str, ben_list, ben_dict};
struct piece{
    Type type;
    union {
        struct ben_int bint;
        struct ben_str bstr;
        struct ben_list blist;
        struct ben_dict bdict;
    };
    piece() : type(Type::ben_int) {  // Initialize with default type
        bint = {};  // Default initialize ben_int, can be any type from the union
    }

    // Destructor
    ~piece() {
        switch (type) {
            case Type::ben_int:
                bint.~ben_int();
                break;
            case Type::ben_str:
                bstr.~ben_str();
                break;
            case Type::ben_list:
                blist.~ben_list();
                break;
            case Type::ben_dict:
                bdict.~ben_dict();
                break;
        }
    }

};

enum Data_Type {
    NONE,
    INT,    
    STRING,  
    LIST,
    DICT    
};

void changeType(piece &p, Data_Type newType);


class Decode {
private:
    std::string byteSequence;

public:
    // Constructor that takes a byte sequence
    Decode(const std::string& inputByteSequence);
    // methods of the class
    int decode(int start_index, piece& result) const;
    int decode_int(int start_index, ben_int& result) const;
    int decode_str(int start_index, ben_str& result) const;
    int decode_list(int start_index, ben_list& result) const;
    int decode_dict(int start_index, ben_dict& result) const;
};

class Encode {
private:
    //piece encode_piece;

public:
    // Constructor that takes nothing
    Encode();
    // methods of the class
    std::string encode(piece input_piece) const;
};