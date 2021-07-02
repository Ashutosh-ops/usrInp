#ifndef UsrInp_h
#define UsrInp_h
#include "Arduino.h"
#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"

/*______Define LCD pins (I have asigned the default values)_______*/
#define YP A1 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 7  // can be a digital pin
#define XP 6  // can be a digital pin


/*For mega*/
#define LCD_CS A4
#define LCD_CD A3
#define LCD_WR A2
#define LCD_RD A1
#define LCD_RESET A5
/*_______End of defanitions______*/



#define MINPRESSURE 10
#define MAXPRESSURE 1000
/*_______Assigned______*/

/*____Calibrate TFT LCD_____*/
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905
/*______End of Calibration______*/


/*________ENDS OF CALIBRATION CONFIGURATION_________*/

class UsrInp
{
public:
    long box[3];
protected:
    int k_0 = 100, k_1 = 100, k_2 = 100;
    int X, Y, l, k1 = 0; //Stores the touch co-ordinates
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 is the sensitivity
    TSPoint tp;

public:
    UsrInp();
    void PinSetup();
    void Sequence1();
    TSPoint waitTouch();
    void Solid_Border(MCUFRIEND_kbv&);
    void pager(MCUFRIEND_kbv&);
    void draw_BoxNButtons(MCUFRIEND_kbv&);
    void DisplayResult(int,int, int&,MCUFRIEND_kbv&);
    void clicker(int,long &,int,int &,MCUFRIEND_kbv&);
    void userInput(MCUFRIEND_kbv&);
};

#endif