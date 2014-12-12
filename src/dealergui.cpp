#include "include/dealergui.h"
//ignore this line, just adding so git will actually notice the fucking changes

DealerGUI::DealerGUI(const unsigned int &_numPlayers, CardInfo *_cardInfo, LabelFormat *_labelFormat) :
    //m_publicCards(Hand(SDL_Point(),std::vector<Card>(),BOTTOM)),
    m_maker(ElementMaker(_cardInfo, _labelFormat))
{
}

void DealerGUI::broadcastMessage(const std::string &_message)
{
}

void DealerGUI::update()
{

}

void DealerGUI::draw()
{

}
