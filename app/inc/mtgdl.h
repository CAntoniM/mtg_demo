#ifndef _mtg_dl_h_
#define _mtg_dl_h_

#include <string>
#include <vector>
class Card {
    public: 
        virtual std::string name() = 0;
};

class Set {
    public:
        virtual std::string name() = 0;
        virtual std::vector<Card*> getCards() = 0;
};

extern "C" {
    __declspec(dllexport) Set* dlmain();
};


#endif
