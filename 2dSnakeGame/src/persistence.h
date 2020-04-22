#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <string>

struct TopScore{
    std::string name{""};
    int score{0};
};

class Persistence{
    public:
        void writeContent(const TopScore &topScore);
        TopScore readContent();
};

#endif