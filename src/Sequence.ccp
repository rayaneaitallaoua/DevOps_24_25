#include <string>

class Sequence {
private:
    std::string fastaSequence;

public:
    // Constructor
    Sequence(const std::string& sequence) : fastaSequence(sequence) {}

    // Getter for the sequence
    std::string getSequence() const {
        return fastaSequence;
    }

    // Setter for the sequence
    void setSequence(const std::string& sequence) {
        fastaSequence = sequence;
    }
};