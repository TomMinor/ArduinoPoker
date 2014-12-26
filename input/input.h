#ifndef INPUT_H__
#define INPUT_H__

class input
{

public:

    input(int _pin);
    ~input();

    bool buttonUP();
    bool buttonDOWN();
    bool buttonLEFT();
    bool buttonRIGHT();
    bool buttonSELECT();


private:

    int m_x;

};


#endif
