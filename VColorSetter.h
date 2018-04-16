class VColorSetter : public AWindow
    {
    private:
    VCanvas* controlCanvas;
    COLORREF thiscolor = TX_BLACK;

    public:

    VColorSetter (int x, int y, int sizex, int sizey, COLORREF getcolor, VCanvas* givenCanvas):
        thiscolor (getcolor)
        {
        cords.x = x;
        cords.y = y;

        size.x = sizex;
        size.y = sizey;

        controlCanvas = givenCanvas;
        }

    void PerformAction ();
    void setNew (int x, int y, int sizex, int sizey, COLORREF getcolor);
    void Draw() override
        {
        //printf ("drawing started\n");
        txSetColor (thiscolor);
        txSetFillColor (thiscolor);
        txRectangle (cords.x, cords.y, cords.x + size.x, cords.y + size.y);
        //printf ("drawing finished\n");
        }


    void Test() override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        if (In (std::nomeow, mousepos.x, cords.x, cords.x + size.x) &&
            In (std::nomeow, mousepos.y, cords.y, cords.y + size.y) &&
            mousestate == 1)
            {
            this->PerformAction();
            }
        }
    };

void VColorSetter::setNew (int x, int y, int sizex, int sizey, COLORREF getcolor)
    {
    thiscolor = getcolor;
    cords.x = x;
    cords.y = y;

    size.x = sizex;
    size.y = sizey;
    }


void VColorSetter::PerformAction()
    {
    controlCanvas->setDrawingColor (thiscolor);
    }


