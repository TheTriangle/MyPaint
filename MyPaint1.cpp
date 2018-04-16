
#include "TXLib.h"
#include "VEDInterface.h"

void runPipette (VCanvas* controlCanvas);
void saveImage();
void loadImage();

const POINT SzScr = POINT{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};

void makeInstrumentSetters (WindowManager* manager, int* windowsnum, int x, int y, int sizex, int sizey, VCanvas* gcanvas);
void makeColorSetters (WindowManager* manager, int* windowsnum, int x, int y, int sizex, int sizey, VCanvas* gcanvas);


int main()
    {
    txCreateWindow (SzScr.x, SzScr.y);

    double currentDrawingWidth = 5;

    int filledwindows = 0;
    WindowManager myPaintManager;

    VCanvas myPaintCanvas (100, SzScr.y/4, SzScr.x - 200, SzScr.y * 3/4 - 50);
    int CanvasID = 0;

    myPaintManager.addWindow (&myPaintCanvas);
    filledwindows++;

    VScroller sizeScroller (SzScr.x/3, 0, SzScr.x/3, SzScr.y/4, &currentDrawingWidth, 1, 100, &myPaintCanvas);
    myPaintManager.addWindow (&sizeScroller);
    filledwindows++;

    makeColorSetters (&myPaintManager, &filledwindows, 0, 0, SzScr.x/3, SzScr.y/4, &myPaintCanvas);

    VSaver SaveButton (SzScr.x * 2/3 + 5, 5, SzScr.x/3 - 10, SzScr.y/8 - 10,
                        RGB(183, 164, 76), ("Save Image"), &myPaintCanvas);
    SaveButton.mouseoncolor = RGB(173, 63, 54);
    myPaintManager.addWindow (&SaveButton);
    filledwindows++;

    VLoader LoadButton (SzScr.x * 2/3 + 5, SzScr.y/8 - 5, SzScr.x/3 - 10, SzScr.y/8 - 10,
                        RGB(183, 164, 76), ("Load Image"), &myPaintCanvas);
    LoadButton.mouseoncolor = RGB(173, 63, 54);
    myPaintManager.addWindow (&LoadButton);
    filledwindows++;


    makeInstrumentSetters (&myPaintManager, &filledwindows, 5, 30, 150, 50, &myPaintCanvas);

    /*VLineInstrument myLine (myPaintCanvas.getDC(), TX_WHITE, 5, myPaintCanvas.getCords());
    HDC LineIcon = txLoadImage ("LineIcon.bmp");                                    //да-да, знаю. Icon - некорректное название. Бе-бе-бе.
    HDC LineIconMouseOn = txLoadImage ("LineIconMouseOn.bmp");
    VInstrumentSetter lineSetter (5, 30, 150, 50, &myLine, &myPaintCanvas, LineIcon, LineIconMouseOn);
    myPaintManager.addWindow (&lineSetter);
    filledwindows++;


    VSpreadInstrument mySpread (myPaintCanvas.getDC(), TX_WHITE, 5, myPaintCanvas.getCords());
    HDC SpreadIcon = txLoadImage ("SpreadIcon.bmp");
    HDC SpreadIconMouseOn = txLoadImage ("SpreadIconMouseOn.bmp");
    VInstrumentSetter spreadSetter (160, 30, 150, 50, &mySpread, &myPaintCanvas, SpreadIcon, SpreadIconMouseOn);
    myPaintManager.addWindow (&spreadSetter);
    filledwindows++;*/


    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        myPaintManager.drawAll();
        myPaintManager.testAll();
        runPipette(&myPaintCanvas);

        //myPaintManager.updateCanvasWidth (CanvasID, currentDrawingWidth);

        txSetFillColor (RGB (73, 66, 183));
        txSleep(30);
        txClear();
        }

    return 0;
    }

void runPipette (VCanvas* controlCanvas)
    {
    if (GetAsyncKeyState ('P'))
        {
        POINT mpos = txMousePos();
        if (txMouseButtons() == 1)
            {
            controlCanvas->setDrawingColor (txGetPixel (mpos.x - 1, mpos.y - 1));
            }
        txSetColor (TX_BLUE, 2);
        txLine (mpos.x, mpos.y, mpos.x + 15, mpos.y - 15);

        txSetColor (TX_WHITE, 2);
        txLine (mpos.x + 15, mpos.y - 15, mpos.x + 45, mpos.y - 45);
        }
    }

void saveImage()
    {
    ShouldBeSaved = true;
    }


void loadImage()
    {
    ShouldBeLoaded = true;
    }

void makeInstrumentSetters (WindowManager* manager, int* windowsnum, int x, int y, int sizex, int sizey, VCanvas* gcanvas)
    {
    static VLineInstrument myLine (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords());
    HDC LineIcon = txLoadImage ("LineIcon.bmp");                                    //да-да, знаю. Icon - некорректное название. Бе-бе-бе.
    HDC LineIconMouseOn = txLoadImage ("LineIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (5, 30, 150, 50, &myLine, gcanvas, LineIcon, LineIconMouseOn));
    *windowsnum++;


    static VSpreadInstrument mySpread (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords());
    HDC SpreadIcon = txLoadImage ("SpreadIcon.bmp");
    HDC SpreadIconMouseOn = txLoadImage ("SpreadIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (160, 30, 150, 50, &mySpread, gcanvas, SpreadIcon, SpreadIconMouseOn));
    *windowsnum++;


    static VRectangleInstrument myRectangle (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords());
    HDC RectangleIcon = txLoadImage ("RectangleIcon.bmp");
    HDC RectangleIconMouseOn = txLoadImage ("RectangleIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (5, 90, 150, 50, &myRectangle, gcanvas, RectangleIcon, RectangleIconMouseOn));
    *windowsnum++;


    static VEllipseInstrument myEllipse (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords());
    HDC EllipseIcon = txLoadImage ("EllipseIcon.bmp");
    HDC EllipseIconMouseOn = txLoadImage ("EllipseIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (160, 90, 150, 50, &myEllipse, gcanvas, EllipseIcon, EllipseIconMouseOn));
    *windowsnum++;


    static VTextInstrument myText (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords(), gcanvas->getSizes());
    HDC TextIcon = txLoadImage ("TextIcon.bmp");
    HDC TextIconMouseOn = txLoadImage ("TextIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (5, 150, 150, 50, &myText, gcanvas, TextIcon, TextIconMouseOn));
    *windowsnum++;

                         //UNDER CONSTRUCTION
    /*static VAreaInstrument myArea (gcanvas->getDC(), TX_WHITE, 5, gcanvas->getCords(), gcanvas->getSizes());
    HDC AreaIcon = txLoadImage ("AreaIcon.bmp");
    HDC AreaIconMouseOn = txLoadImage ("AreaIconMouseOn.bmp");
    manager->addWindow (new VInstrumentSetter (160, 150, 150, 50, &myArea, gcanvas, AreaIcon, AreaIconMouseOn));
    *windowsnum++;   //*/
    }

void makeColorSetters (WindowManager* manager, int* windowsnum, int x, int y, int sizex, int sizey, VCanvas* gcanvas)
    {
    int normalSetterSize = 20;

    int space = 5;

    int requiredsetters = sizex  * sizey / pow(normalSetterSize + space, 2);

    int horsettersamount = sizex / (normalSetterSize + space);

    COLORREF thiscolor = TX_BLACK;

    int counter = 0;

    //printf ("fa\n");
    //getch();

    //VColorSetter newsetter (x + space + (counter % horsettersamount) * (normalSetterSize + space),
    //                            y + space + counter/horsettersamount * (normalSetterSize + space),
    //                            normalSetterSize, normalSetterSize, thiscolor);

    for (int i = 0; i < horsettersamount; i++)
        {                                                    //у вас возник вопрос: что это такое?
        switch(i)                                            // это - распределение цветов colorsetter'ов
            {                                                //  -------------------
            case 0:                                          //5.r  g  b  6. r g b
                thiscolor = TX_BLACK;                        //  -             -
                break;                                       //
            case 1:                                          //
                thiscolor = TX_WHITE;                        //
                break;                                       //     -  -     -   -    -|step
            case 2:                                          //  -------------------  -/
                thiscolor = TX_CYAN;                          //
                break;                                       //
            case 3:                                          //
                thiscolor = TX_MAGENTA;                        //
                break;                                       //
            case 4:                                          //
                thiscolor = TX_YELLOW;                         //
                break;                                       //
            default:
                int stepcolor = 35 * ((i - 5) / 3);
                thiscolor = RGB (((i - 2) % 3 == 0)? 255 - stepcolor : stepcolor,
                                 ((i - 2) % 3 == 1)? 255 - stepcolor : stepcolor,
                                 ((i - 2) % 3 == 2)? 255 - stepcolor : stepcolor);
                break;
            }

        //newsetter.setNew (x + space + (counter % horsettersamount) * (normalSetterSize + space),
        //                        y + space + counter/horsettersamount * (normalSetterSize + space),
        //                        normalSetterSize, normalSetterSize, thiscolor);

        manager->addWindow (new VColorSetter (x + space + (counter % horsettersamount) * (normalSetterSize + space),
                                              y + space + counter/horsettersamount * (normalSetterSize + space),
                                              normalSetterSize, normalSetterSize, thiscolor, gcanvas));

        *windowsnum++;
        counter++;
        }
    //printf ("ff\n");
    //getch();
    }
