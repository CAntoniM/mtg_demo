#ifndef _bloomburrow_h_
#define _bloomburrow_h_

#include "mtgdl.h"

class BloomBurrow : public Set {

public:
    BloomBurrow();
    ~BloomBurrow();
    virtual std::string name();
    virtual std::vector<Card*> getCards();

private:
    std::vector<Card*> _cards;
};

#endif
