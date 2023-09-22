// bencode.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

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
    std::vector<piece> pieces;
};

struct ben_dict{
    std::unordered_map<ben_str, piece> dict;
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

};




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