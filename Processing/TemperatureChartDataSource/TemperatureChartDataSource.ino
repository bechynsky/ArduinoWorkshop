#define RESISTOR_CONNECT_THERMISTOR	10000
#define TEMPERATURE_SENSOR	A0

void setup()
{
  pinMode(TEMPERATURE_SENSOR, INPUT);
  Serial.begin(9600);
}
void loop()
{
  int8_t temperature;
  temperature = getTemperature();
  Serial.print(temperature);
  Serial.print('\n');
  delay(2000);
}

float getTemperature()
{
  float temperature,resistance;
  int a;
  a = analogRead(TEMPERATURE_SENSOR);
  resistance   = (float)(1023-a)*RESISTOR_CONNECT_THERMISTOR/a; 
  int B = 3975;
  temperature  = 1/(log(resistance/RESISTOR_CONNECT_THERMISTOR)/B+1/298.15)-273.15;
  return temperature;
}
