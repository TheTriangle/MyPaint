class VCanvas : public AWindow
    {
    private:
    HDC canvas;

    int drawingWidth = 5;
    POINT oldcords = {0, 0};
    COLORREF drawingColor;
    //RGBQUAD* canvaspixels;
    AInstrument* myInstrument;

    public:

    VCanvas (int x, int y, int sizex, int sizey):
        canvas(txCreateCompatibleDC(sizex, sizey))
        {
        cords.x = x;
        cords.y = y;

        size.x = sizex;
        size.y = sizey;

        txSetFillColor (RGB (160, 160, 160), canvas);
        txClear (canvas);
        drawingColor = TX_WHITE;

        VSpreadInstrument* lin  = new VSpreadInstrument(&canvas, TX_WHITE, drawingWidth, {x, y});
        myInstrument = lin;
        }

    void PerformAction ();

    void Draw() override
        {
        //printf ("canvas is drawing");
        txBitBlt (txDC(), cords.x, cords.y, size.x, size.y, canvas);
        }

    void SaveToFile ()
        {
        txClearConsole();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);

        char filename [64];
        printf ("enter file name\n");
        scanf  ("%s", filename);
        printf ("Saving. Please, wait\n");

        txSaveImage (filename, canvas);

        txClearConsole();
        printf ("Saved Succesfuly to %s\n", filename);
        ShouldBeSaved = false;
        }

    void LoadFromFile ()
        {
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        char filename [64];
        printf ("enter file name\n");
        scanf  ("%s", filename);

        HDC loadingdc = txLoadImage (filename);
        txBitBlt (canvas, 0, 0, size.x, size.y, loadingdc);

        txClearConsole();
        printf ("Loaded Succesfuly from %s\n", filename);
        ShouldBeLoaded = false;
        }

    POINT getCords()
        {
        return cords;
        }

    POINT getSizes()
        {
        return size;
        }

    void Test() override
        {
        myInstrument->test();

        //printf ("canvas is testing\n");
        //if (ShouldBeSaved)
        //    {
        //    SaveToFile ();
        //    }

        //if (ShouldBeLoaded)
        //    {
        //    LoadFromFile ();
        //    }
        }

    HDC* getDC()
        {
        return &canvas;
        }

    void setInstrument (AInstrument* giveninstrument)
        {
        myInstrument = giveninstrument;
        }


    void Clear (COLORREF getColor) override
        {
        txSetFillColor (getColor, canvas);
        txClear(canvas);
        }


    void updateWidth(int newWidth) override
        {
        myInstrument->setWidth (newWidth);
        drawingWidth = newWidth;
        }

    void setDrawingColor (COLORREF givencolor)
        {
        myInstrument->setColor (givencolor);
        drawingColor = givencolor;
        }
    };


void VCanvas::PerformAction()
    {
    //printf ("action performing\n");
    txSetColor (drawingColor, drawingWidth, canvas);
    txSetFillColor (drawingColor, canvas);

    if (oldcords.x != 0 ||oldcords.y != 0)
        {
        txLine (oldcords.x - cords.x, oldcords.y - cords.y, txMouseX() - cords.x, txMouseY() - cords.y, canvas);
        }

    oldcords = txMousePos();

    txEllipse (txMouseX() - cords.x, txMouseY() - cords.y,
               txMouseX() - cords.x, txMouseY() - cords.y, canvas);
    //txEllipse (x-r, y-r, x+r, y+r);
    }
