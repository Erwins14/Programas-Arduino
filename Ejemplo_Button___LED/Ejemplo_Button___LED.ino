int PULSADOR = 2; 
int LED=13; 
 
void setup(){ 
  pinMode(PULSADOR,INPUT); 
  pinMode(LED, OUTPUT);  
  } 
  
void loop(){ 
  while(digitalRead(PULSADOR)==LOW);  
  digitalWrite(LED,LOW);
  
  while(digitalRead(PULSADOR)==HIGH);
  digitalWrite(LED,HIGH);
  
  
}
