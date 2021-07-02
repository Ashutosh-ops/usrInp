#include "UsrInp.h"
#include "Arduino.h"

/*______End of Libraries_______*/

UsrInp::UsrInp()
{
  box[2] = box[1] = box[0] = 0;
  k_0 = k_1 = k_2 = 100;
  X = Y = l = k1 = 0;
}

void UsrInp::PinSetup()
{
  box[2] = box[1] = box[0] = 0;
  k_0 = k_1 = k_2 = 100;
  X = Y = l = k1 = 0;
}

/***______User Input Page starts________**/
/*______Assign names to colors and pressure_______*/
#define WHITE 0x0000  //Black->White
#define YELLOW 0x001F //Blue->Yellow
#define CYAN 0xF800   //Red->Cyan
#define PINK 0x07E0   //Green-> Pink
#define RED 0x07FF    //Cyan -> Red
#define GREEN 0xF81F  //Pink -> Green
#define BLUE 0xFFE0   //Yellow->Blue
#define BLACK 0xFFFF  //White-> Black
#define PURPLE 0x4A49
#define LTPURPLE 0x8200


TSPoint UsrInp::waitTouch()
{
  TSPoint p;
  do
  {
//    Serial.println("TS Point");
    p = ts.getPoint();
    /******************/
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
  return p;
}

void UsrInp::pager(MCUFRIEND_kbv& tft) 
{
  Serial.println("In pager");
  tft.fillScreen(WHITE);
  Solid_Border(tft);
  tft.drawRect(90, 20, 200, 40, BLACK);
  tft.drawRect(255, 25, 30, 30, BLACK);
  tft.drawRect(260, 30, 20, 20, BLACK);
  tft.drawRect(265, 35, 10, 10, BLACK);
  //    tft.fillRect(265,35,10,10,PINK);

  tft.drawRect(90, 80, 200, 40, BLACK);
  tft.drawRect(255, 85, 30, 30, BLACK);
  tft.drawRect(260, 90, 20, 20, BLACK);
  tft.drawRect(265, 95, 10, 10, BLACK);
  //    tft.fillRect(265,95,10,10,PINK);

  tft.drawRect(90, 140, 200, 40, BLACK);
  tft.drawRect(255, 145, 30, 30, BLACK);
  tft.drawRect(260, 150, 20, 20, BLACK);
  tft.drawRect(265, 155, 10, 10, BLACK);
  //    tft.fillRect(265,155,10,10,PINK);

  //  tft.drawRect(90,200,200,40,BLACK);
  //  tft.drawRect(255,205,30,30,BLACK);
  //  tft.drawRect(260,210,20,20,BLACK);
  //  tft.drawRect(265,215,10,10,BLACK);
  //    tft.fillRect(265,215,10,10,PINK);

  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.fillRect(5, 197, 310, 30, PINK);
  tft.setCursor(140, 200);
  tft.print("OK:>>");

  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(15, 35);
  tft.print("Volts:");
  tft.setCursor(15, 90);
  tft.print("Amps:");
  tft.setCursor(15, 150);
  tft.print("Sec:");
}

void UsrInp::Solid_Border(MCUFRIEND_kbv& tft)
{
  tft.fillRect(0, 0, 480, 5, GREEN);
  tft.fillRect(0, 0, 5, 480, GREEN);
  tft.fillRect(315, 0, 5, 480, GREEN);
  tft.fillRect(0, 475, 320, 5, GREEN);
}

void UsrInp::draw_BoxNButtons(MCUFRIEND_kbv& tft)
{
    //Draw the Result Box
    //tft.fillRect(0, 0, 320, 120, CYAN);

    //Draw First Column
    for(int i = 250; i <= 480; i+=80){
      tft.fillRect(0, i, 107, 80, BLACK);
    }
    //Draw Second Column
    for(int i = 250; i <= 480; i+=80){
      tft.fillRect(107, i, 107, 80, BLACK);
    }
    //Draw Third Column
    for(int i = 250; i <= 480; i+=80){
      tft.fillRect(214, i, 106, 80, BLACK);
    }
    //Draw Vertical Lines
    for (int v = 0; v <= 320; v += 107)
        tft.drawFastVLine(v, 250, 320, WHITE);
        
    tft.drawFastVLine(319, 250, 320, WHITE);
        
    //Draw Horizontal Lines
    for (int h = 250; h <= 480; h += 60)
        tft.drawFastHLine(0, h, 320, WHITE);

    tft.drawFastHLine(0, 479, 320, WHITE);

    //Display keypad lables
    tft.setTextSize(3);
    tft.setTextColor(WHITE);

    tft.setCursor(45 + 0, 270 + 0);
    tft.println("7");
    tft.setCursor(45 + 105, 270 + 0);
    tft.println("8");
    tft.setCursor(45 + 210, 270 +0);
    tft.println("9");

    tft.setCursor(45 + 0, 270 + 60);
    tft.println("4");
    tft.setCursor(45 + 105, 270 + 60);
    tft.println("5");
    tft.setCursor(45 + 210, 270 +60);
    tft.println("6");

    tft.setCursor(45 + 0, 270 + 120);
    tft.println("1");
    tft.setCursor(45 + 105, 270 + 120);
    tft.println("2");
    tft.setCursor(45 + 210, 270 +120);
    tft.println("3");

    tft.setCursor(45 + 0, 270 + 180);
    tft.println("C");
    tft.setCursor(45 + 105, 270 + 180);
    tft.println("0");
    tft.setCursor(45 + 210, 270 +180);
    tft.println("=>");
}

/**______User Input Set______**/

void UsrInp::DisplayResult(int l,int op, int&k,MCUFRIEND_kbv& tft)
{
    //clear result box
    tft.setCursor(k, op);
    k+=15;
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println(l); //update new value
}


void UsrInp::clicker(int button,long &Num,int op,int &k, MCUFRIEND_kbv& tft)
{
  if (floor(log10(Num)+1) <9)
  {
     Serial.print("Button ");
     Serial.println(button);
     if (Num==0)
       Num=button;
     else
       Num = (Num*10) + button; //Pressed twice
     DisplayResult(button,op,k,tft);
   }
}

/**__UserInput___**/

void UsrInp::userInput(MCUFRIEND_kbv& tft){
  
  while(1)
  {
      X=Y=0;
      TSPoint p = waitTouch();
      delay(250);
      X = p.y;
      Y = p.x;
      if(Y > 23 && Y < 283){
        if(X > 138 && X < 159){
          //OK pressed
          return;
        }
        if(X > 161 && X < 188)
        {
          box_2:
            tft.fillRect(265,155,10,10,PINK);
            tft.fillRect(265,95,10,10,WHITE);
            tft.fillRect(265,35,10,10,WHITE);
            Serial.println("box[2] from loop//while");
//              Detectkey(box[2],150,k_2);

                  while(1)
                  {
                    Serial.print("Num: "); Serial.println(box[2]);
                    X=Y=0;
                    TSPoint jk = waitTouch();
                    X = jk.y;
                    Y = jk.x;
                    delay(250);
                    if(Y > 23 && Y < 283){
                      if(X > 138 && X < 159){
                        //OK pressed
                        return;
                      }
                      if(X > 161 && X < 188)
                      {
                          goto box_2;
                          Serial.print("box[2]: ");
                          Serial.println(box[2]);
                      }
                      if(X > 188 && X < 221)
                      {
                          goto box_1;
                          Serial.print("box[1]: ");
                          Serial.println(box[1]);
                      }
                      if(X > 221 && X < 248)
                      {
                           goto box_0;
                          Serial.print("box[0]: ");
                          Serial.println(box[0]);
                      }
                    }
                    if (X < 35 && X > 0) //Detecting Buttons on row 1 from bottom
                    {
                        if (Y > 0 && Y < 105) //If ok Button is pressed
                        {
                            Serial.println("Button ok");
                            return;
                //            return 7;
                        }
                
                        if (Y > 105 && Y < 201){ //If Button 0 is pressed
                          clicker(0,box[2],150,k_2,tft);
                        }
                        if (Y > 201 && Y < 292) //If Button backspace is pressed
                        {
                            Serial.println("Button backspace");
                            if (box[2] == 0)
                                box[2] = 0;
                            else
                                box[2]/=10; //Pressed twice
                            /*Backspace code*/
                            if(k_2 > 100){
                              l = k_2 -= 15;
                              tft.fillRect(l, 150, 15, 20, WHITE);
                            }
                        }
                        X=Y=0;
                    }
                
                    else if (X < 65 && X > 35) //Detecting Buttons on row 2 from bottom
                    {
                        if (Y > 0 && Y < 105) //If Button 3 is pressed
                          clicker(3,box[2],150,k_2,tft);
                
                        if (Y > 105 && Y < 201) //If Button 2 is pressed
                          clicker(2,box[2],150,k_2,tft);
                
                        if (Y > 201 && Y < 292) //If Button 1 is pressed
                          clicker(1,box[2],150,k_2,tft);
                        X=Y=0;
                    }
                
                    else if (X < 95 && X > 65) //Detecting Buttons on row 3 from bottom
                    {
                        if (Y > 0 && Y < 105) //If Button 6 is pressed
                          clicker(6,box[2],150,k_2,tft);
                
                        if (Y > 105 && Y < 201) //If Button 5 is pressed
                          clicker(5,box[2],150,k_2,tft);
                
                        if (Y > 201 && Y < 292) //If Button 4 is pressed
                          clicker(4,box[2],150,k_2,tft);
                        X=Y=0;
                    }
                
                    else if (X < 126 && X > 95) //Detecting Buttons on row 4 from bottom
                    {
                        if (Y > 0 && Y < 105) //If Button 9 is pressed
                          clicker(9,box[2],150,k_2,tft);
                
                        if (Y > 105 && Y < 201) //If Button 8 is pressed
                          clicker(8,box[2],150,k_2,tft);
                
                        if (Y > 201 && Y < 292) //If Button 7 is pressed
                          clicker(7,box[2],150,k_2,tft);
                        X=Y=0;
                    }
                    else
                    {
                        X=Y;
                    }
                }
            Serial.print("box[2]: ");
            Serial.println(box[2]);
        }
        if(X > 188 && X < 221)
        {
          box_1:
            tft.fillRect(265,95,10,10,PINK);
            tft.fillRect(265,155,10,10,WHITE);
            tft.fillRect(265,35,10,10,WHITE);
            Serial.println("box[1] from loop//while");
//              Detectkey(box[1],90,k_1);
                    while(1)
                    {
                      Serial.print("Num: "); Serial.println(box[1]);
                      X=Y=0;
                      TSPoint jk = waitTouch();
                      X = jk.y;
                      Y = jk.x;
                      delay(250);
                      if(Y > 23 && Y < 283)
                      {
                        if(X > 138 && X < 159){
                          //OK pressed
                          return;
                        }
                        if(X > 161 && X < 188)
                        {
                            goto box_2;
                            Serial.print("box[2]: ");
                            Serial.println(box[2]);
                        }
                        if(X > 188 && X < 221)
                        {
                            goto box_1;
                            Serial.print("box[1]: ");
                            Serial.println(box[1]);
                        }
                        if(X > 221 && X < 248)
                        {
                             goto box_0;
                            Serial.print("box[0]: ");
                            Serial.println(box[0]);
                        }
                      }
                      if (X < 35 && X > 0) //Detecting Buttons on row 1 from bottom
                      {
                          if (Y > 0 && Y < 105) //If ok Button is pressed
                          {
                              Serial.println("Button ok");
                              return;
                  //            return 7;
                          }
                  
                          if (Y > 105 && Y < 201){ //If Button 0 is pressed
                            clicker(0,box[1],90,k_1,tft);
                          }
                          if (Y > 201 && Y < 292) //If Button backspace is pressed
                          {
                              Serial.println("Button backspace");
                              if (box[1] == 0)
                                  box[1] = 0;
                              else
                                  box[1]/=10; //Pressed twice
                              /*Backspace code*/
                              if(k_1>100){
                                l = k_1 -= 15;
                                tft.fillRect(l, 90, 15, 20, WHITE);
                              }
                          }
                          X=Y=0;
                      }
                  
                      else if (X < 65 && X > 35) //Detecting Buttons on row 2 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 3 is pressed
                            clicker(3,box[1],90,k_1,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 2 is pressed
                            clicker(2,box[1],90,k_1,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 1 is pressed
                            clicker(1,box[1],90,k_1,tft);
                          X=Y=0;
                      }
                  
                      else if (X < 95 && X > 65) //Detecting Buttons on row 3 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 6 is pressed
                            clicker(6,box[1],90,k_1,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 5 is pressed
                            clicker(5,box[1],90,k_1,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 4 is pressed
                            clicker(4,box[1],90,k_1,tft);
                          X=Y=0;
                      }
                  
                      else if (X < 126 && X > 95) //Detecting Buttons on row 4 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 9 is pressed
                            clicker(9,box[1],90,k_1,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 8 is pressed
                            clicker(8,box[1],90,k_1,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 7 is pressed
                            clicker(7,box[1],90,k_1,tft);
                          X=Y=0;
                      }
                      else
                      {
                          X=Y=0;
      //                    return;
                      }
                  }
            Serial.print("box[1]: ");
            Serial.println(box[1]);
        }
        if(X > 221 && X < 248)
        {
          box_0:
            tft.fillRect(265,35,10,10,PINK);
            tft.fillRect(265,95,10,10,WHITE);
            tft.fillRect(265,155,10,10,WHITE);
            Serial.println("box[0] from loop//while");
//              Detectkey(box[0],35,k_0);
                    while(1)
                    {
                      Serial.print("Num: "); Serial.println(box[0]);
                      X=Y=0;
                      TSPoint jk = waitTouch();
                      X = jk.y;
                      Y = jk.x;
                      delay(250);
                      if(Y > 23 && Y < 283)
                      {
                        if(X > 138 && X < 159){
                          //OK pressed
                          return;
                        }
                        if(X > 161 && X < 188)
                        {
                            goto box_2;
                            Serial.print("box[2]: ");
                            Serial.println(box[2]);
                        }
                        if(X > 188 && X < 221)
                        {
                            goto box_1;
                            Serial.print("box[1]: ");
                            Serial.println(box[1]);
                        }
                        if(X > 221 && X < 248)
                        {
                             goto box_0;
                            Serial.print("box[0]: ");
                            Serial.println(box[0]);
                        }
                      }
                      if (X < 35 && X > 0) //Detecting Buttons on row 1 from bottom
                      {
                          if (Y > 0 && Y < 105) //If ok Button is pressed
                          {
                              Serial.println("Button ok");
                              return;
                  //            return 7;
                          }
                  
                          if (Y > 105 && Y < 201){ //If Button 0 is pressed
                            clicker(0,box[0],35,k_0,tft);
                          }
                          if (Y > 201 && Y < 292) //If Button backspace is pressed
                          {
                              Serial.println("Button backspace");
                              if (box[0] == 0)
                                  box[0] = 0;
                              else
                                  box[0]/=10; //Pressed twice
                              /*Backspace code*/
                              if(k_0>100){
                                l = k_0 -= 15;
                                tft.fillRect(l, 35, 15, 20, WHITE);
                              }
                          }
                          X=Y=0;
                      }
                  
                      else if (X < 65 && X > 35) //Detecting Buttons on row 2 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 3 is pressed
                            clicker(3,box[0],35,k_0,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 2 is pressed
                            clicker(2,box[0],35,k_0,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 1 is pressed
                            clicker(1,box[0],35,k_0,tft);
                          X=Y=0;
                      }
                  
                      else if (X < 95 && X > 65) //Detecting Buttons on row 3 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 6 is pressed
                            clicker(6,box[0],35,k_0,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 5 is pressed
                            clicker(5,box[0],35,k_0,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 4 is pressed
                            clicker(4,box[0],35,k_0,tft);
                          X=Y=0;
                      }
                  
                      else if (X < 126 && X > 95) //Detecting Buttons on row 4 from bottom
                      {
                          if (Y > 0 && Y < 105) //If Button 9 is pressed
                            clicker(9,box[0],35,k_0,tft);
                  
                          if (Y > 105 && Y < 201) //If Button 8 is pressed
                            clicker(8,box[0],35,k_0,tft);
                  
                          if (Y > 201 && Y < 292) //If Button 7 is pressed
                            clicker(7,box[0],35,k_0,tft);
                          X=Y=0;
                      }
                      else
                      {
                          X=Y=0;
      //                    return;
                      }
                  }
            Serial.print("box[0]: ");
            Serial.println(box[0]);
        }
      }
      //Serial.print(X); Serial.print(','); Serial.println(Y);
    }
}


