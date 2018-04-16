class VInstrumentSetter : public AButton
    {
    private:
    VCanvas* controlCanvas;
    AInstrument* thisInstrument;
    HDC instrDC;// = txCreateCompatibleDC(150, 50);
    HDC mouseonDC;
    HDC currentDC;

    public:

    VInstrumentSetter (int x, int y, int sizex, int sizey, AInstrument* getInstrument, VCanvas* givenCanvas, HDC givenDC, HDC givenmouseonDC):
        currentDC (givenDC),
        instrDC (givenDC),
        mouseonDC (givenmouseonDC),
        thisInstrument (getInstrument)
        {
        cords.x = x;
        cords.y = y;

        size.x = sizex;
        size.y = sizey;

        controlCanvas = givenCanvas;
        }

    void PerformAction ();

    void Draw() override
        {
        //printf ("drawing started\n");
        txBitBlt (txDC(), cords.x, cords.y, size.x, size.y, currentDC);
        //printf ("drawing finished\n");
        }


    void Test() override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (In (std::nomeow, mousepos.x, cords.x, cords.x + size.x) &&
            In (std::nomeow, mousepos.y, cords.y, cords.y + size.y))
            {
            if (mousestate == 1)
                {
                this->PerformAction();
                }
            currentDC = mouseonDC;
            }
        else
            {
            currentDC = instrDC;
            }
        }

    };

void VInstrumentSetter::PerformAction()
    {
    controlCanvas->setInstrument (thisInstrument);
    }
