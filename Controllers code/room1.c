
/*

Conected by an i2c bus to a raspberry pi
The data is sent in groups of 4 bytes 
but it's a float of 4 digits xx.xx so it has to be
reconstructed after receiving it.

Using a Dallas DS18B20 for the temperature
*/


#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>


// Temperature sensor pin 
#define ONE_WIRE_BUS 3
// Temperature sensor precission
#define TEMPERATURE_PRECISION 12


//===============================
//  	Temperature stuff
//===============================


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; 
float tempC;

//===============================
//  	General stuff
//===============================


char *input;




void setup(void)
{
	Serial.begin(9600);
	ds18s20Setup();

	Wire.begin(0x05);
	Wire.onReceive(decryptInput);

}

void loop(void)
{ 
	delay(5000);
	tempC= getTemperature();
        sendTemp();


}

void ds18s20Setup(){
	sensors.begin();
	if(sensors.getAddress(tempDeviceAddress, 0))
		sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
	else
		Serial.print("Found ghost device but no address ");	
}


float getTemperature(){

	sensors.requestTemperatures();
	delay(100);
	if(sensors.getAddress(tempDeviceAddress, 0)){
		float output = sensors.getTempC(tempDeviceAddress);
		return output;
	}
	else return -1;
}

void decryptInput(int howMany){

	int i=0;

	while(Wire.available()) 
	{
	char intake = Wire.read(); 
		input[i] = intake;
		i++;
	}

	if (input[0]=='A')
	{
		sendTemp();
	}

}

void sendTemp(){
	int buffer = tempC*100;
	unsigned char output[4];
	Serial.print(buffer);

	output[0] = buffer;
	output[1] = buffer>>8;
	output[2] = buffer>>16;
	output[3] = buffer>>24;
	
	Wire.beginTransmission(0x02);
	Wire.write(output,4);         
	Wire.endTransmission();     // stop transmitting
}