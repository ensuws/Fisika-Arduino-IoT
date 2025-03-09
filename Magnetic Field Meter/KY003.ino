int LED =13;
int SENSOR = 10;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  while(digitalRead(SENSOR)==HIGH);
  digitalWrite(LED, HIGH);
  while(digitalRead(SENSOR)==LOW);
  digitalWrite(LED, LOW);
  
  //digitalWrite(LED, !digitalRead(SENSOR));
  
  
  /*if(digitalRead(SENSOR)==HIGH){
    digitalWrite(LED, LOW);
  }else{
    digitalWrite(LED, HIGH);
  }*/
}

