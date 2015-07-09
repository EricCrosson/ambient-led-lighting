// Oh no! My lovely PWM pin 9 is out of order. Too much entropy!
#define redPin    3		//Red pin 3 has PWM
#define greenPin  10		//Green pin 10 has PWM
#define bluePin   11		//Blue pin 11 has PWM

#define adcPin    A0
#define redAdc    A1
#define greenAdc  A2
#define blueAdc   A3

#define internalLED 13

int adc;
unsigned char red, green, blue;

enum schema {
    white,
    spectrum,  // todo: implement
    fade,      // todo: implement
    fade_warm, // todo: implement
    fade_cold, // todo: implement
};

void setup()
{
    /* Initialize hardware */
    pinMode(internalLED,OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    /* Set the pullups on the analog pins */
    digitalWrite(adcPin, HIGH);	  
    digitalWrite(redAdc, HIGH);	  
    digitalWrite(blueAdc, HIGH);  
    digitalWrite(greenAdc, HIGH); 

    /* Run-time init test */
    mapValueToPins(255); 

    /* Set the scheme used to illuminate */
    scheme = white;
}

void loop()
{
    adc = analogRead(adcPin);
    red = analogRead(redAdc) / 4;
    green = analogRead(greenAdc) / 4;
    blue = analogRead(blueAdc) / 4;

    switch(scheme) {
    case white:
        scheme_white();
        break;
    default: break;
    }
    writeToPins(red, green, blue);

    /* Safety first */
    delay(25 /* ms */);
}

/* Analog pins are used for PWM */
void writeToPins(int red, int blue, int green)
{
    keepColorsInBounds();
    analogWrite(0xFF & ((unsigned char)redPin), red);
    analogWrite(0xFF & ((unsigned char)greenPin), green);
    analogWrite(0xFF & ((unsigned char)bluePin), blue);
}

void scheme_white() {
    red /= 4;
    blue /= 4;
    green /= 4;
}
