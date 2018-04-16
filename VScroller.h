class VScroller : public AWindow
    {
    private:
    VCanvas* controlcanvas;

    int spaceSize = 5;
    int scrollRadius = 25;

    int minValue = 1;
    int maxValue = 10;
    double currentValue = 1;
    double *changingValue;
    bool followMouse = false;

    public:

    VScroller (int x, int y, int sizex, int sizey, double* givenchanging, int givenmin, int givenmax, VCanvas* givencanvas);

    void PerformAction ();
    int getValue();


    void Test() override
        {
        POINT mousepos = txMousePos();
        int mousestate = txMouseButtons();
        int scrollSpace = size.x - 2 * spaceSize;
        POINT scrollCenter = {cords.x + spaceSize + (double)(currentValue - minValue) * scrollSpace/(maxValue - minValue),
                              cords.y + size.y/2};
        if (pow ((mousepos.x - scrollCenter.x), 2) + pow ((mousepos.y - scrollCenter.y), 2)
                <= scrollRadius * scrollRadius && mousestate == 1)
            {
            //printf ("mouseon\n");
            this->PerformAction();
            }
        else
            {
            if (mousestate != 1)
                {
                followMouse = false;
                }
            }
        if (followMouse) this->PerformAction();
        }

    void Draw() override
        {
        txSetFillColor (RGB (0, 204, 204));
        txSetColor (RGB (180, 180, 180), 6);
        txLine (cords.x + spaceSize, cords.y + size.y/2, cords.x + size.x - spaceSize, cords.y + size.y/2);
        //txSetColor (RGB (220, 0, 110), 6);
        txCircle (cords.x + spaceSize + (size.x - 2 * spaceSize)/(double)(maxValue - minValue) * (currentValue - minValue),
                  cords.y + size.y/2, scrollRadius);
        }

    };


VScroller::VScroller (int x, int y, int sizex, int sizey, double* givenchanging, int givenmin, int givenmax, VCanvas* givencanvas):
    currentValue  (*givenchanging),
    changingValue (givenchanging),
    minValue (givenmin),
    maxValue (givenmax)
    {
    cords.x = x;
    cords.y = y;

    size.x = sizex;
    size.y = sizey;

    controlcanvas = givencanvas;
    }


int VScroller::getValue()
    {
    return currentValue;
    }




void VScroller::PerformAction()
    {
    followMouse = true;
    POINT mousepos = txMousePos();

    if (In (mousepos.x, cords.x + spaceSize, cords.x + size.x - spaceSize))
        {           // |min|---m-------|max|
        double mouseratio = (double)(mousepos.x - cords.x - spaceSize)/(size.x - 2 * spaceSize);
        currentValue = minValue + mouseratio * (maxValue - minValue);
        }
    *changingValue = currentValue;
    controlcanvas->updateWidth(currentValue);
    }

