#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include "player.h"

class Persistence{
    public:
        void WriteContent(const Player &top_score);
        Player ReadContent();
};

#endif