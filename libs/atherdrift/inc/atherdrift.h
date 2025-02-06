#ifndef _atherdrift_h_
#define _atherdrift_h_

#include "mtgdl.h"

class Atherdrift : public Set {

public:
    Atherdrift();

    virtual std::string name();
    virtual std::vector<Card*> getCards();

private:
    std::vector<Card*> _cards;
};

#endif
