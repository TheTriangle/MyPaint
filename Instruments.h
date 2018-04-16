class AInstrument
    {
    public:
    COLORREF color;
    HDC* mycanvas;
    POINT canvcords;
    int width;
    POINT oldcords;

    virtual void draw(){};

    virtual void test()
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (mousestate == 1)
            {
            //printf ("performAction called\n");
            //oldcords = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};
            this->draw();
            }
        else
            {
            oldcords = {0, 0};
            }
        };


    void setColor (COLORREF givencolor)
        {
        color = givencolor;
        }

    void setWidth (int givenwidth)
        {
        width = givenwidth;
        }

    AInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords):
        mycanvas (givencanvas),
        color (givencolor),
        canvcords (gcords),
        width (givenwidth)
        {}

    AInstrument (HDC* givencanvas):
        mycanvas (givencanvas),
        color (TX_WHITE),
        canvcords ({0, 0}),
        width (5)
        {}

    };


class VSpreadInstrument : public AInstrument
    {
    public:
    VSpreadInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords):
        AInstrument (givencanvas, givencolor, givenwidth, gcords)
        {}

    VSpreadInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}


    void draw () override
        {
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        RGBQUAD *helppix = new RGBQUAD[width * width];
        HDC helpdc = txCreateDIBSection (width, width, &helppix);

        COLORREF codecolor = RGB(240, 204, 24);

        txSetFillColor (codecolor, helpdc);
        txClear (helpdc);

        for (int i = 0; i < width * 3; i++)    //width * 3 is hardcoded
            {
            helppix[rand()%width + rand()%width * width] = {GetBValue(color), GetGValue(color), GetRValue(color)};
            }
        txTransparentBlt (*mycanvas, mposcanv.x - width/2, mposcanv.y - width/2, width, width, helpdc, 0, 0, codecolor);
        }
    };


class VLineInstrument : public AInstrument
    {
    private:

    public:
    VLineInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords):
        AInstrument (givencanvas, givencolor, givenwidth, gcords)
        {}

    VLineInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}

    void draw () override
        {
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        if (oldcords.x != 0 ||oldcords.y != 0)
            {
            txLine (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
            }

        oldcords = mposcanv;
        }
    };



class VRectangleInstrument : public AInstrument
    {
    private:
    bool drawingRectangle = false;

    public:
    VRectangleInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords):
        AInstrument (givencanvas, givencolor, givenwidth, gcords)
        {}

    VRectangleInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}

    void test() override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (mousestate == 1)
            {
            //printf ("performAction called\n");
            if (!drawingRectangle)
                {
                oldcords = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};
                drawingRectangle = true;
                }
            this->draw();
            }
        else
            {
            oldcords = {0, 0};
            drawingRectangle = false;
            }
        };


    void draw () override
        {
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        if (oldcords.x != 0 ||oldcords.y != 0)
            {
            txRectangle (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
            }
        }
    };




class VEllipseInstrument : public AInstrument
    {
    private:
    bool drawingEllipse = false;

    public:
    VEllipseInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords):
        AInstrument (givencanvas, givencolor, givenwidth, gcords)
        {}

    VEllipseInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}

    void test() override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (mousestate == 1)
            {
            //printf ("performAction called\n");
            if (!drawingEllipse)
                {
                oldcords = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};
                drawingEllipse = true;
                }
            this->draw();
            }
        else
            {
            oldcords = {0, 0};
            drawingEllipse = false;
            }
        };


    void draw () override
        {
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        if (oldcords.x != 0 ||oldcords.y != 0)
            {
            txEllipse (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
            }
        }
    };



class VTextInstrument : public AInstrument
    {
    private:
    COLORREF textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
    bool drawingText = false;
    POINT canvsizes;

    public:
    VTextInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords, POINT gsizes):
        AInstrument (givencanvas, givencolor, givenwidth, gcords),
        canvsizes (gsizes)
        {}

    VTextInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}

    void test() override
        {
        textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (mousestate == 1)
            {
            //printf ("performAction called\n");
            if (!drawingText)
                {
                oldcords = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};
                drawingText = true;
                }
            this->draw();
            }
        else
            {
            POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

            if (drawingText && txMouseX() > canvcords.x && txMouseY() > canvcords.y && txMouseX() < canvcords.x + canvsizes.x && txMouseY() < canvcords.y + canvsizes.y)
                {
                const char* inputtext = txInputBox ("Что вы имеете мне написать?");

                txSetColor (color, width, *mycanvas);
                txSetFillColor (color, *mycanvas);

                if (oldcords.x != 0 ||oldcords.y != 0)
                    {
                    txRectangle (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
                    txSetColor (textcolor, 1, *mycanvas);
                    txSetFillColor (textcolor, *mycanvas);
                    txDrawText  (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, inputtext, DT_CENTER|DT_VCENTER, *mycanvas);
                    }
                }

            drawingText = false;

            oldcords = {0, 0};
            }
        };


    void draw () override
        {
        textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        if (oldcords.x != 0 ||oldcords.y != 0)
            {
            txRectangle (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
            txSetColor (textcolor, 1, *mycanvas);
            txSetFillColor (textcolor, *mycanvas);
            txDrawText  (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, "Здесь мог быть ваш текст", DT_CENTER|DT_VCENTER, *mycanvas);
            }
        }
    };

                                          //UNDER CONSTRUCTION
                                         /*                  /*

class VAreaInstrument : public AInstrument
    {
    private:
    COLORREF textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
    bool drawingText = false;
    POINT canvsizes;

    HDC myDC;

    public:
    VTextInstrument (HDC* givencanvas, COLORREF givencolor, int givenwidth, POINT gcords, POINT gsizes):
        AInstrument (givencanvas, givencolor, givenwidth, gcords),
        canvsizes (gsizes)
        {}

    VTextInstrument (HDC* givencanvas):
        AInstrument (givencanvas)
        {}

    void test() override
        {
        textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (mousestate == 1)
            {
            //printf ("performAction called\n");
            if (!drawingText)
                {
                oldcords = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};
                drawingText = true;
                }
            this->draw();
            }
        else
            {
            POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

            if (drawingText && txMouseX() > canvcords.x && txMouseY() > canvcords.y && txMouseX() < canvcords.x + canvsizes.x && txMouseY() < canvcords.y + canvsizes.y)
                {
                const char* inputtext = txInputBox ("Что вы имеете мне написать?");

                txSetColor (color, width, *mycanvas);
                txSetFillColor (color, *mycanvas);

                if (oldcords.x != 0 ||oldcords.y != 0)
                    {
                    txRectangle (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
                    txSetColor (textcolor, 1, *mycanvas);
                    txSetFillColor (textcolor, *mycanvas);
                    txDrawText  (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, inputtext, DT_CENTER|DT_VCENTER, *mycanvas);
                    }
                }

            drawingText = false;

            oldcords = {0, 0};
            }
        };


    void draw () override
        {
        textcolor = ((GetRValue(color) + GetGValue(color) + GetBValue(color))/3 > 127)? TX_BLACK : TX_WHITE;
        txSetColor (color, width, *mycanvas);
        txSetFillColor (color, *mycanvas);

        POINT mposcanv = {txMouseX() - canvcords.x, txMouseY() - canvcords.y};

        if (oldcords.x != 0 ||oldcords.y != 0)
            {
            txRectangle (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, *mycanvas);
            txSetColor (textcolor, 1, *mycanvas);
            txSetFillColor (textcolor, *mycanvas);
            txDrawText  (oldcords.x, oldcords.y, mposcanv.x, mposcanv.y, "Здесь мог быть ваш текст", DT_CENTER|DT_VCENTER, *mycanvas);
            }
        }
    };
//*/
