//______________humidity sensor_________________
#include<SimpleDHT.h>
SimpleDHT11 HT_sensor(2);

//_____________moisture sensor________________
int moisture_sensors[2] = {A0, A1};
int farm_moisture;
//A0 moisture_sensor 0 - yellow wire
//A1 moisture sensor 1 - white wire

//____________Pumps and sprinkler irrigation________________
int pump_pins[2] = {3, 4};
//pump 0 for irrigation
//pump 1 for spraying

//___________water level sensor ________________________
int water_level_sensor =A3;
int water_level;

class sensors{
            public:
                void read_humidity(byte *temp, byte *hum){
                    while (true){
                                int HT_reading = HT_sensor.read(temp, hum, NULL);
                                if (HT_reading !=SimpleDHTErrSuccess){
                                     continue;
                                     //Serial.println(HT_reading);
                                     //Serial.println("Sensor encountered error while reading");
                                    }
                                 break;
                 }}
                 void read_moisture(int *farm_moisture){
                      int moisture_0 = analogRead(moisture_sensors[0]);
                      int moisture_1 = analogRead(moisture_sensors[1]);
                      moisture_1  = (moisture_0+moisture_1)/2;
                      *farm_moisture = map(moisture_1,1024,0, 0,100);
                  }};



void setup() {
  Serial.begin(9600);
  for (int pump:pump_pins){pinMode(pump, OUTPUT);}
  for (int moisture:moisture_sensors){pinMode(moisture,INPUT);}}

void loop(){
    sensors Sensors;

    //_____________Water level sensor scope_______________________________
    {
      water_level = analogRead(water_level_sensor);
      Serial.println(water_level);
    }

    //_____________moisture sensor scope____________________  
    {
        Sensors.read_moisture(&farm_moisture);
      //  Serial.print("The moisture of the farm is ");Serial.println(farm_moisture);
        if (farm_moisture<20){
              digitalWrite(pump_pins[0], 0);
              if (water_level>500){Serial.println("The water level is low");}
              else{digitalWrite(pump_pins[0], 1);}}
        else{digitalWrite(pump_pins[0], 0);} 
    }

    
    //_____________Temperature and humudity sensor scope____________________
    {
      byte temperature, humidity;
      Sensors.read_humidity(&temperature, &humidity);
     // Serial.println(temperature);Serial.println(humidity);
    }


}
