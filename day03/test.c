#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

int pixel[NUMPIXELS] = {0};

int BLUE[10][3] = {{235, 245, 251}, {214, 234, 248}, {174, 214, 241},
                   {133, 193, 233}, {93, 173, 226}, {52, 152, 219},
                   {46, 134, 193}, {40, 116, 166}, {33, 97, 140},
                   {27, 79, 114}};
int VIOLET[10][3] = {{244, 236, 247}, {232, 218, 239}, {210, 180, 222},
                     {187, 143, 206}, {165, 105, 189}, {142, 68, 173},
                     {125, 60, 152}, {108, 52, 131}, {91, 44, 111},
                     {74, 35, 90}};
int YELLOW[10][3] = {{254, 249, 231}, {252, 243, 207}, {249, 231, 159},
                     {247, 220, 111}, {244, 208, 63}, {241, 196, 15},
                     {212, 172, 13}, {183, 149, 11}, {154, 125, 10},
                     {125, 102, 8}};
int GREEN[10][3] = {{233, 247, 239}, {212, 239, 223}, {169, 223, 191},
                    {125, 206, 160}, {82, 190, 128}, {39, 174, 96},
                    {34, 153, 84}, {30, 132, 73}, {25, 111, 61},
                    {20, 90, 50}};
int RED[10][3] = {{253, 237, 236}, {250, 219, 216}, {245, 183, 177},
                  {241, 148, 138}, {236, 112, 99}, {231, 76, 60},
                  {203, 67, 53}, {176, 58, 46}, {148, 49, 38},
                  {120, 40, 31}};
int ORANGE[10][3] = {{253, 242, 233}, {250, 229, 211}, {245, 203, 167},
                     {240, 178, 122}, {235, 152, 78}, {230, 126, 34},
                     {202, 111, 30}, {175, 96, 26}, {147, 81, 22},
                     {120, 66, 18}};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second

void setup()
{
    pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

    while(1)
    {
        for(int i = 0; i < NUMPIXELS; i++)
            pixel[i] = rand() % 2;

        for (int j = 0; j < 10; j++)
        {
            for(int i = 0; i < NUMPIXELS; i++)
            {
                if (pixel[i])
                {
                    // pixels.setPixelColor(i, pixels.Color(YELLOW[j][0],YELLOW[j][1],YELLOW[j][2]));
                    // pixels.setPixelColor(i, pixels.Color(RED[j][0],RED[j][1],RED[j][2]));
                    //wave
                    pixels.setPixelColor(i, pixels.Color(BLUE[(j+i) % 10][0],BLUE[(j+i) % 10][1],BLUE[(j+i) % 10][2]));
                }
                else
                {
                    // pixels.setPixelColor(i, pixels.Color(0,0,0));
                    // pixels.setPixelColor(i, pixels.Color(VIOLET[j][0],VIOLET[j][1],VIOLET[j][2]));
                    // pixels.setPixelColor(i, pixels.Color(GREEN[j][0],GREEN[j][1],GREEN[j][2]));
                    //wave
                    pixels.setPixelColor(i, pixels.Color(ORANGE[(j+i) % 10][0],ORANGE[(j+i) % 10][1],ORANGE[(j+i) % 10][2]));
                }

                delay(5);
            }
            pixels.show();
        }
    }


    delay(1000);
}
