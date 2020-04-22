#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <memory>

#include "player.h"

class Persistence{
    public:
        void WriteContent(const std::shared_ptr<Player> top_score);
        Player ReadContent();
};

#endif