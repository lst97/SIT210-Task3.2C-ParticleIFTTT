int sensor_pin = A0;
int sensor_value = 0; // variable to store the value coming from the sensor void setup() {

void setup() {
  Serial.begin(9600);
}

bool NO_SUN = false;
bool TWO_HOURS = false;
int EXPOSURE_TIME = 0;
int SENSOR_DELAY = 10000;
int CURRENT_DAY = Time.day();
void loop() {
  delay(SENSOR_DELAY);
  sensor_value = analogRead(sensor_pin);

  if (CURRENT_DAY != Time.day()){
    CURRENT_DAY = Time.day();
    TWO_HOURS = false;
    EXPOSURE_TIME = 0;
  }

  if(EXPOSURE_TIME >= 120) {
    Particle.publish("ENOUGHT", "", PRIVATE);
    TWO_HOURS = true;
  } // two hours

  if(TWO_HOURS == false){
    if(sensor_value > 600 && NO_SUN == false){
      Particle.publish("HIDDEN", "", PRIVATE);
      NO_SUN = true;
      return;
    }

    if(sensor_value <= 600 && NO_SUN == true){
      Particle.publish("EXPOSED", "", PRIVATE);
      NO_SUN = false;
      return;
    }

    if(NO_SUN == false){
      EXPOSURE_TIME += int(SENSOR_DELAY / 1000);
    }
  }
}
