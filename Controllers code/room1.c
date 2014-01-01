
/*

Conected by an i2c bus to a raspberry pi

Using a Dallas DS18B20 for the temperature
*/




#include <OneWire.h>
#include <DallasTemperature.h>


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



void setup(void)
{
	Serial.begin(9600);
	ds18s20Setup();

}

void loop(void)
{ 
	delay(5000);
	tempC= getTemperature();


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