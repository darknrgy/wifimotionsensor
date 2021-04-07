#include "wifi.h"
#include <driver/adc.h>

void setup()
{
	Serial.begin(115200);
	pinMode(5, OUTPUT);      // set the LED pin mode

	adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);

	delay(10);
	setupwifi();
}

int value = 0;

void loop(){
	static bool motion = false;
	int analogIn;

	motion = pollwifi(motion);
	analogIn = adc1_get_raw(ADC1_CHANNEL_0);
	if (analogIn > 2000) motion = true;	
}
