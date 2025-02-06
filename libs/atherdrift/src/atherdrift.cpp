#include <atherdrift.h>

class DriftCard : public Card {
private:
    std::string _name;

public:
    DriftCard(std::string name)
    {
        _name = name;
    }

    virtual std::string name()
    {
        return _name;
    }
};

Atherdrift::Atherdrift()
{
    _cards = { new DriftCard("foo") };
}

Atherdrift::~Atherdrift()
{
    for (Card* card : _cards) {
        delete card;
    }
}

std::string Atherdrift::name()
{
    return "atherdrift";
}

std::vector<Card*> Atherdrift::getCards()
{
    return _cards;
}

Set* dlmain()
{
    return new Atherdrift();
}