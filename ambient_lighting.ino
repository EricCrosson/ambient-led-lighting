// Oh no! My lovely PWM pin 9 is out of order. Too much entropy!
#define redPin    3		//Red pin 3 has PWM
#define greenPin  10		//Green pin 10 has PWM
#define bluePin   11		//Blue pin 11 has PWM

#define adcPin    A0
#define redAdc    A1
#define greenAdc  A2
#define blueAdc   A3

#define internalLED 13

int brightness;
unsigned char red, green, blue;

enum schema {
    white,
    spectrum,  // todo: implement
    fade,      // todo: implement
    fade_warm, // todo: implement
    fade_cold, // todo: implement
    echo,
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
    switch(scheme) {
    case white: scheme_white(); break;
    case echo:  scheme_echo();  break
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
    brightness = analogRead(adcPin);
    red = brightness;
    blue = brightness;
    green = brightness;
}

void scheme_echo() {
    brightness = analogRead(adcPin)/4;
    red = analogRead(redAdc)*brightness;
    green = analogRead(greenAdc)*brightness;
    blue = analogRead(blueAdc)*brightness;
}

void wavelength_to_rgb(unsigned int wavelength) {
        var w = SSS, R, G, B;

        if (w >= 380 && w < 440) {
            R = -(w - 440.0) / (440.0 - 350.0);
            G = 0.0;
            B = 1.0;
        } else if (w >= 440 && w < 490) {
            R = 0.0;
            G = (w - 440.0) / (490.0 - 440.0);
            B = 1.0;
        } else if (w >= 490 && w < 510) {
            R = 0.0;
            G = 1.0;
            B = -(w - 510.0) / (510.0 - 490.0);
        } else if (w >= 510 && w < 580) {
            R = (w - 510.0) / (580.0 - 510.0);
            G = 1.0;
            B = 0.0;
        } else if (w >= 580 && w < 645) {
            R = 1.0;
            G = -(w - 645.0) / (645.0 - 580.0);
            B = 0.0;
        } else if (w >= 645 && w <= 780) {
            R = 1.0;
            G = 0.0;
            B = 0.0;
        } else {
            R = 0.0;
            G = 0.0;
            B = 0.0;
        }

        if (w >= 380 && w < 420) {
            SSS = 0.3 + 0.7 * (w - 350) / (420 - 350);
        } else if (w >= 420 && w <= 700) {
            SSS = 1.0;
        } else if (w > 700 && w <= 780) {
            SSS = 0.3 + 0.7 * (780 - w) / (780 - 700);
        } else {
            SSS = 0.0;
        }

        SSS *= 255;
        red =  SSS*R;
        green = SSS*G;
        blue = SSS*B;
}
