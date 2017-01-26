//HandShaking.Arduino.ino
char val;
char header = 'A';
char footer = 'Z';
int maxData = 10;
char code[10];
byte n;
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	// put your main code here, to run repeatedly:
	establishContact();
	if (Serial.available() > 0)
	{
		val = Serial.read();
		if (val == header)
		{
			for (byte i = 0; i < maxData; i++)
			{
				val = Serial.read();
				if ((val == header) or (val == footer))
				{
					break; //break out the 'for'
				}
				code[n] = val;
				n++;
			}
			if (n != maxData)
			{
			}
			else if (n == maxData)
			{
				// Reading job is done
				n = 0;
				sendData();
				//reset all recieved data to 0
				for (byte i = 0; i < maxData; i++)
				{
					code[i] = 0;
				}

			}
		}
	}
}
void establishContact() {
	while (Serial.available() <= 0) {
		Serial.println("A");   // send a capital A
		delay(300);
	}
}
void sendData()
{
	
}
