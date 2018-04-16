COLORREF SelectedColor = TX_WHITE;

bool ShouldBeSaved = false;
bool ShouldBeLoaded = false;

int SelectedWidth = 1;

void DoNothing();

void DoNothing()
    {}

void drawPixels();

class AWindow
    {
    protected:
    POINT cords;
    POINT size;

    public:
    //virtual void PerformAction();
    virtual void Draw() = 0;
    virtual void Test() = 0;
    virtual void Clear(COLORREF getColor) {};
    virtual void updateWidth (int newwidth) {};
    };

#include "Instruments.h"
#include "VCanvas.h"
#include "VColorSetter.h"
#include "VScroller.h"
#include "VButton.h"
#include "AButton.h"
#include "SaveLoad.h"
#include "VInstrumentSetter.h"


class WindowManager
    {
    private:

    int windowscounter = 0;
    AWindow *Windows [128];

    public:
    WindowManager ()
        {}

    AWindow* operator[] (int elnum)
        {
        return Windows[elnum];
        }

    void addWindow (AWindow* givenWindow);
    void drawAll();
    void testAll();
    void updateCanvasWidth (int id, int newwitdth);
    void clearCanvas (int id, COLORREF color = TX_WHITE);
    };


void WindowManager::updateCanvasWidth (int id, int newwidth)
    {
    Windows[id]->updateWidth (newwidth);
    }

void WindowManager::clearCanvas (int id, COLORREF color)
    {
    Windows[id]->Clear(color);
    }


void WindowManager::drawAll()
    {
    //printf ("windowscounter == %d\n", windowscounter);
    for (int i = 0; i < windowscounter; i++)
        {
        //printf ("drawing %d window\n", i);
        Windows[i]->Draw();
        }
    }



void WindowManager::testAll()
    {
    //printf ("windowscounter == %d\n", windowscounter);
    for (int i = 0; i < windowscounter; i++)
        {
        //printf ("testing %d window\n", i);
        Windows[i]->Test();
        }
    }

void WindowManager::addWindow(AWindow* givenWindow)
    {
    Windows[windowscounter] = givenWindow;
    windowscounter++;
    }
