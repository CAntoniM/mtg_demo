#include <bloomburrow.h>

class BloomBurrowCard : public Card {
private:
    std::string _name;

public:
    BloomBurrowCard(std::string name)
    {
        _name = name;
    }

    virtual std::string name()
    {
        return _name;
    }
};

BloomBurrow::BloomBurrow()
{
    _cards = { new BloomBurrowCard("test") };
}

std::string BloomBurrow::name() {
    return "BloomBurrow";
}

std::vector<Card*> BloomBurrow::getCards() {
    return _cards;
}

Set* dlmain()
{
    return new BloomBurrow();
}