class AButton : public AWindow
    {
    private:
    bool ispressed = false;

    COLORREF currentcolor;
    COLORREF passivecolor;

    char* text = new char[64];

    public:

    COLORREF mouseoncolor = RGB (0, 204, 204);
    COLORREF pressedcolor = RGB (0, 255, 130);

    //void (*PerformAction)();

    AButton (int x, int y, int sizex, int sizey, COLORREF givencolor, char giventext []):
        currentcolor(givencolor),
        passivecolor(givencolor),
        text(giventext)
        {
        cords.x = x;
        cords.y = y;

        size.x = sizex;
        size.y = sizey;
        }

    AButton ():
        currentcolor (TX_WHITE),
        passivecolor (TX_WHITE),
        text("noname")
        {
        cords.x = 0;
        cords.y = 0;

        size.x = 150;
        size.y = 50;
        }

    ~AButton()
        {
        delete [] text;
        }

    virtual void PerformAction () {printf ("you've called PerformAction method of AButton. Çðÿ-Çðÿ.\n");};

    void Draw() override
        {
        txSetColor (currentcolor);
        txSetFillColor (currentcolor);
        txRectangle (cords.x, cords.y, cords.x + size.x, cords.y + size.y);
        txSetColor (TX_BLACK);
        txDrawText (cords.x, cords.y, cords.x + size.x, cords.y + size.y, text, DT_CENTER);
        }

    void Test () override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (In (std::nomeow, mousepos.x, cords.x, cords.x + size.x) &&
            In (std::nomeow, mousepos.y, cords.y, cords.y + size.y))
            {
            if (mousestate != 1)
                {
                currentcolor = mouseoncolor;
                ispressed = false;
                }
            else
                {
                if (!ispressed)
                    {
                    currentcolor = pressedcolor;
                    this->PerformAction();
                    }
                ispressed = true;
                }
            }
        else
            {
            currentcolor = passivecolor;
            ispressed = false;
            }
        }
    };





