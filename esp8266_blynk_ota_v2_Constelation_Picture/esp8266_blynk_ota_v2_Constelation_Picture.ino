
////////////////////////////////////////////////////////////////////////////////////
// This template has several files of code.                                       //
// * Only edit this file.                                                         //
// * Only edit settings where instructed and add code in places indicated.        //
// * Do not remove any #include... lines. These are very important.               //
//                                                                                //
// * Remember not to change too much before next compiling. This way it is easier //
// to find the bugs.                                                              //
// * Do experiment. You can always start again!                                   //
//                                                                                //
////////////////////////////////////////////////////////////////////////////////////

#include "preSETUP.h"; // Leave this alone

////////////////////////////////////////////////////////////////////////////////////
// Update these settings as required.                                             //
////////////////////////////////////////////////////////////////////////////////////

// This must be set here. It can always be changed at runtime so you can leave this example value.
char blynk_token[] = "13ef44c5cc5f447ba0050b4c23dab0a3"; // Blynk auth token found in the Blynk mobile app.

const int FW_VERSION = 2019010403 ; /// year, month, day & release number

//Set to 1 for school Blynk server or 0 for Public Blynk server use.
const int schoolServer = 0;

////////////////////////////////////////////////////////////////////////////////////
#include "procedures.h" // Leave this alone

////////////////////////////////////////////////////////////////////////////////////
// Add any defines and included you need below here                               //
////////////////////////////////////////////////////////////////////////////////////


int r;
int g;
int b;

int option = 1;

BlynkTimer timer;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            D1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second


////////////////////////////////////////////////////////////////////////////////////
// Code in the setup function will run once on each startup.                      //
////////////////////////////////////////////////////////////////////////////////////
void setup()
{
#include "SETUP.h"; // Leave this alone


pixels.begin(); // This initializes the NeoPixel library.


// pixels.setPixelColor(0, pixels.Color(0,0,0)); // 
// pixels.setPixelColor(1, pixels.Color(0,0,0)); // 
// pixels.setPixelColor(2, pixels.Color(0,0,0)); // 
// pixels.setPixelColor(3, pixels.Color(0,0,0)); // 
 
// pixels.show(); // This sends the updated pixel color to the hardware.

timer.setInterval (1000L, leds);//EVERY 10 SECONDS
  
}

////////////////////////////////////////////////////////////////////////////////////
// Code in the loop function will run in a forever loop.                          //
////////////////////////////////////////////////////////////////////////////////////
void loop()
{



  timer.run();

   
#include "LOOP.h"; // Leave this alone

}
////////////////////////////////////////////////////////////////////////////////////
// Add additional procedures below here                                           //
////////////////////////////////////////////////////////////////////////////////////

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0, V1);
}

BLYNK_WRITE(V0) //get consteallation selection
{
  option = param.asInt(); 
  leds();
}

BLYNK_WRITE(V1) // zeRGBa assigned to V1 
{
    // get a RED channel value
    r = param[0].asInt();
    // get a GREEN channel value
    g = param[1].asInt();
    // get a BLUE channel value
    b = param[2].asInt();
    leds();
}


void leds()
{
  if (option==1){
     pixels.setPixelColor(0, pixels.Color(r,g,b)); // 
     pixels.setPixelColor(1, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(2, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(3, pixels.Color(0,0,0)); //    
  }else if (option==2){
     pixels.setPixelColor(0, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(1, pixels.Color(r,g,b)); // 
     pixels.setPixelColor(2, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(3, pixels.Color(0,0,0)); //       
  }else if (option==3){
     pixels.setPixelColor(0, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(1, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(2, pixels.Color(r,g,b)); // 
     pixels.setPixelColor(3, pixels.Color(0,0,0)); //       
  }else if (option==4){
     pixels.setPixelColor(0, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(1, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(2, pixels.Color(0,0,0)); // 
     pixels.setPixelColor(3, pixels.Color(r,g,b)); //       
  }
 pixels.show(); // This sends the updated pixel color to the hardware.
}


