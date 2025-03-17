#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <iostream>

class Sequence {
public:
    Sequence(const std::string& id, const std::string& seq, const std::string& qual = "");

    std::string getId() const;
    std::string getSequence() const;
    std::string getQuality() const;
    bool hasQuality() const;

    void print() const;

private:
    std::string id;
    std::string sequence;
    std::string quality;
};

#endif
