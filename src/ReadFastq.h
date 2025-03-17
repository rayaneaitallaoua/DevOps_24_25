#ifndef READFASTQ_HPP
#define READFASTQ_HPP

#include "Sequence.hpp"
#include <vector>
#include <fstream>
#include <string>

class ReadFastq {
public:
    ReadFastq(const std::string& filename);
    void load();
    void printReads() const;

private:
    std::string filename;
    std::vector<Sequence> reads;
};

#endif