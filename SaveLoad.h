class VSaver : public AButton
    {
    VCanvas* myCanvas;

    public:

    VSaver (int x, int y, int sizex, int sizey, COLORREF givencolor, char giventext [], VCanvas* givencanvas):
        AButton (x, y, sizex, sizey, givencolor, giventext)
        {
        myCanvas = givencanvas;
        }
    void PerformAction() override
        {
        myCanvas->SaveToFile();
        }
    };

class VLoader : public AButton
    {
    VCanvas* myCanvas;
    public:
    VLoader (int x, int y, int sizex, int sizey, COLORREF givencolor, char giventext [], VCanvas* givencanvas):
        AButton (x, y, sizex, sizey, givencolor, giventext)
        {
        myCanvas = givencanvas;
        }
    void PerformAction() override
        {
        myCanvas->LoadFromFile();
        }
    };
