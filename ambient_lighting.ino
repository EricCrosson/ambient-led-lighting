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

#define brightnessPin A0
#define wavelengthPin A1

bool down = true;		/* directional flag */

uchar brightnessValue;
uchar wavelengthValue;
uchar red, green, blue;		//red, green and blue values

void setup()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    digitalWrite(brightnessPin, HIGH);  // set pullup
    digitalWrite(wavelengthPin, HIGH);  // set pullup

    mapValueToPins(255); //run time test

    int red = 255;
    int blue = 255;
    int green = 255;
}

void loop()
{
    /* writeToPins(50, 50, 255); */

    brightnessValue = analogRead(brightnessPin) / 4;
    /* Will be 0-255 (actually a little higher than 0).
     * Now we will scale it to x-100 */
    brightnessValue *= (100/255);

    wavelengthValue = analogRead(wavelengthPin);
    /* Normalizing from 0-1023 to 380-780 */
    wavelengthValue *= (400/1023 + 380);

    wavelengthToRGB(wavelengthValue, brightnessValue);

    delay(DELAY); //to be safe
}

void wavelengthToRGB(int wavelength, uchar brightness)
{
    // color
    if (wavelength >= 380 && wavelength < 440) {
        red = -(wavelength - 440.) / (440. - 350.);
        green = 0.0;
        blue = 1.0;
    }
    else if (wavelength >= 440 && wavelength < 490) {
	red = 0.0;
	green = (wavelength - 440.) / (490. - 440.);
	blue = 1.0;
    }
    else if (wavelength >= 490 && wavelength < 510) {
	red = 0.0;
	green = 1.0;
	blue = -(wavelength - 510.) / (510. - 490.);
    }
    else if (wavelength >= 510 && wavelength < 580) {
        red = (wavelength - 510.) / (580. - 510.);
	green = 1.0;
	blue = 0.0;
    }
    else if (wavelength >= 580 && wavelength < 645) {
	red = 1.0;
	green = -(wavelength - 645.) / (645. - 580.);
	blue = 0.0;
    }
    else if (wavelength >= 645 && wavelength <= 780) {
	red = 1.0;
	green = 0.0;
	blue = 0.0;
    }
    else {
	red = 0.0;
	green = 0.0;
	blue = 0.0;
    }

    // intensity correction
    double SSS;
    if (wavelength >= 380 && wavelength < 420)
    	SSS = 0.3 + 0.7*(wavelength - 350) / (420 - 350);
    else if (wavelength >= 420 && wavelength <= 700)
    	SSS = 1.0;
    else if (wavelength > 700 && wavelength <= 780)
    	SSS = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
    else
    {
    	SSS = 0.0;
    	SSS *= 255;
    }

    SSS = 1;
    writeToPins(SSS*red, SSS*green, SSS*blue);
}

/* Analog for PWM */
void writeToPins(int red, int green, int blue)
{
    analogWrite (redPin, red);
    analogWrite (greenPin, green);
    analogWrite (bluePin, blue);
}
