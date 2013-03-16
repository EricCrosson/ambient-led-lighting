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

bool down = true;		/* directional flag */

int adc;
uchar red, green, blue;		//red, green and blue values

void setup()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    digitalWrite(adcPin, HIGH);  // set pullup on analog pin 0

    mapValueToPins(255); //run time test

    int red = 255;
    int blue = 255;
    int green = 255;
}

void loop()
{
    adc = analogRead(adcPin);

    /* writeToPins(red, green, blue); */
    mapValueToPins(adc / 4);

    delay(DELAY); //just to be safe
}

/* Analog for PWM */
void writeToPins(int red, int blue, int green)
{
    analogWrite (redPin, red);
    analogWrite (greenPin, green);
    analogWrite (bluePin, blue);
}
