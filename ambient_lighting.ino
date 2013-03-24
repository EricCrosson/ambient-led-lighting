#define uchar unsigned char
#define bool boolean

#define mapValueToPins(value) writeToPins(value, value, value)
#define DELAY 25		/* in milliseconds */
#define LOWER 10		/* /255 */
#define UPPER 250		/* /255 */

// Oh no! My lovely PWM pin 9 is out of order. Too much entropy!
#define redPin    3		//Red pin 3 has PWM
#define greenPin  10		//Green pin 10 has PWM
#define bluePin   11		//Blue pin 11 has PWM

#define adcPin    A0
#define redAdc    A1
#define greenAdc  A2
#define blueAdc   A3

#define internalLED 13

bool down = true;		/* directional flag */

int adc;
uchar red, green, blue;		//red, green and blue values

void setup()
{
    pinMode(internalLED,OUTPUT);

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    digitalWrite(adcPin, HIGH);	  // set pullup on analog pin 0
    digitalWrite(redAdc, HIGH);	  // set pullup on analog pin 1
    digitalWrite(blueAdc, HIGH);  // set pullup on analog pin 2
    digitalWrite(greenAdc, HIGH); // set pullup on analog pin 3

    mapValueToPins(255); //run time test
}

void loop()
{
    adc = analogRead(adcPin);

    red = analogRead(redAdc) / 4;
    green = analogRead(greenAdc) / 4;
    blue = analogRead(blueAdc) / 4;

    writeToPins(red, green, blue);

    delay(DELAY); //safety first
}

/* Analog for PWM */
void writeToPins(int red, int blue, int green)
{
    keepColorsInBounds();
    analogWrite (redPin, red);
    analogWrite (greenPin, green);
    analogWrite (bluePin, blue);
}

void keepColorsInBounds()
{
    if (red < 0)          red	= 0;
    else if (red > 255)   red	= 255;
    if (green < 0)        green = 0;
    else if (green > 255) green = 255;
    if (blue < 0)         blue	= 0;
    else if (blue > 255)  blue	= 255;
}
