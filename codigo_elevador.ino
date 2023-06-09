    // Código completo para controle de um elevador de três pavimentos onde são utilizadas: 
// - Três botoeiras em cada andar(em paralelo,)para comandar o andar de destino do elevador;
// - Uma botoeira de emergência em cada andar;
// - Uma sinaleira verde,em cada pavimento, para indicar parada;  
// - Uma sinaleira vermelha,em cada pavimento, para indicar movimentação;
// - Um modulo de 4 relês, para controlar o sentido de rotação de um motor monofásico de 220v

#define porta_rele1 12  // 11 -> 12
#define porta_rele2 13  // 10 -> 13
#define porta_rele3 10  // 13 -> 10
#define porta_rele4 11  // 12 -> 11

#define port_button1 2
#define port_button2 3
#define port_button3 4

#define interruptPin1 18
#define interruptPin2 19
#define interruptPin3 20

#define ch_01 49 // 6 -> 35 -> 39 -> 41 -> 49(laranja)
#define ch_02 51 //14 -> 32 -> 37 -> 28 -> 51(verde)
#define ch_03 53 //15 -> 31 -> 36 -> 45 -> 53 (Branco)


#define led_Red1 40
#define led_Red2 42
#define led_Red3 44

#define led_Green1 50
#define led_Green2 48
#define led_Green3 46

unsigned long startTime = 0; 
unsigned long ledTurnoff = 180000;


//-------------------------Setup-------------------------------------
void setup()
{
  
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  pinMode(porta_rele3, OUTPUT); 
  pinMode(porta_rele4, OUTPUT);
  
  pinMode(port_button1, INPUT_PULLUP); 
  pinMode(port_button2, INPUT_PULLUP);
  pinMode(port_button3, INPUT_PULLUP);

  pinMode(ch_01, INPUT_PULLUP);
  pinMode(ch_02, INPUT_PULLUP);
  pinMode(ch_03, INPUT_PULLUP);

  pinMode(led_Red1, OUTPUT);
  pinMode(led_Red2, OUTPUT); 
  pinMode(led_Red3, OUTPUT);
  pinMode(led_Green1, OUTPUT);
  pinMode(led_Green2, OUTPUT); 
  pinMode(led_Green3, OUTPUT);



  
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), emergButton1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), emergButton2, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), emergButton3, RISING);
  

  digitalWrite(led_Red1, LOW);
  digitalWrite(led_Red2, LOW);
  digitalWrite(led_Red3, LOW);
  digitalWrite(led_Green1, LOW);
  digitalWrite(led_Green2, LOW);
  digitalWrite(led_Green3, LOW);


  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
  digitalWrite(porta_rele3, HIGH);
  digitalWrite(porta_rele4, HIGH);
  Serial.begin(9600);
}

//-------------------------Interupt Emergency Button-----------------------------
void emergButton1() {
   while(digitalRead(interruptPin1) == HIGH){ // Retirar pisca 
     digitalWrite(porta_rele1, 1);
     digitalWrite(porta_rele2, 1); 
     digitalWrite(porta_rele3, 1);
     digitalWrite(porta_rele4, 1); // Desligar 
     
     digitalWrite(led_Red1, HIGH);
     digitalWrite(led_Red2, HIGH);
     digitalWrite(led_Red3, HIGH);
     delay(1000);
     digitalWrite(led_Red1, LOW);
     digitalWrite(led_Red2, LOW);
     digitalWrite(led_Red3, LOW);
     delay(1000);
   }
}
void emergButton2() {
   while(digitalRead(interruptPin2) == HIGH){
     digitalWrite(porta_rele1, 1);
     digitalWrite(porta_rele2, 1); 
     digitalWrite(porta_rele3, 1);
     digitalWrite(porta_rele4, 1); // Desligar 

     digitalWrite(led_Red1, HIGH);
     digitalWrite(led_Red2, HIGH);
     digitalWrite(led_Red3, HIGH);
     delay(1000);
     digitalWrite(led_Red1, LOW);
     digitalWrite(led_Red2, LOW);
     digitalWrite(led_Red3, LOW);
     delay(1000);
   }
}
void emergButton3() {
   while(digitalRead(interruptPin3) == HIGH){
     digitalWrite(porta_rele1, 1);
     digitalWrite(porta_rele2, 1); 
     digitalWrite(porta_rele3, 1);
     digitalWrite(porta_rele4, 1); // Desligar 

     digitalWrite(led_Red1, HIGH);
     digitalWrite(led_Red2, HIGH);
     digitalWrite(led_Red3, HIGH);
     delay(1000);
     digitalWrite(led_Red1, LOW);
     digitalWrite(led_Red2, LOW);
     digitalWrite(led_Red3, LOW);
     delay(1000);
   }
}

//-------------------------Read Current Level-----------------------------

int readcurrentLevel() {
  
 byte contador = 0;
 
  if(digitalRead(ch_01) == HIGH ){
    contador = contador + 1;
    Serial.println("cahve 1 ativada");
  } 
  if(digitalRead(ch_02) == HIGH ){
    contador = contador + 1;
  Serial.println("cahve 2 ativada");
  } 
  if(digitalRead(ch_03) == HIGH ){
    contador = contador + 1;
    Serial.println("cahve 3 ativada");
  } 

  if(contador > 1 ){ //Alterar essa parte e por todas as cores verdes e vermelhas
    while(digitalRead(port_button1) == LOW){
         
      digitalWrite(led_Red1, HIGH);
      digitalWrite(led_Red2, HIGH);
      digitalWrite(led_Red3, HIGH);
      delay(1000);
      digitalWrite(led_Red1, LOW);
      digitalWrite(led_Red2, LOW);
      digitalWrite(led_Red3, LOW);
      delay(1000);
    }
    return;
  } else{
   
    if(digitalRead(ch_01) == HIGH ){
      return 1;
    } 
    if(digitalRead(ch_02) == HIGH ){
      return 2;
    } 
    if(digitalRead(ch_03) == HIGH ){
      return 3;
    } else{
       return 0;
      }
    }
}
//-------------------------Go Down The Elevator-----------------------------

void downElevator(byte nextL){

  byte targetLevel = nextL;
  
  if(targetLevel == 1 ){
    while(digitalRead(ch_01) == LOW){

     digitalWrite(porta_rele3, 1); 
     digitalWrite(porta_rele4, 1);
     delay(100);
     digitalWrite(porta_rele1, 0); 
     digitalWrite(porta_rele2, 0); // Descer
           
     digitalWrite(led_Green1, 0);
     digitalWrite(led_Green2, 0);
     digitalWrite(led_Green3, 0);

     digitalWrite(led_Red1, 1);
     digitalWrite(led_Red2, 1);
     digitalWrite(led_Red3, 1);
    }   
    digitalWrite(porta_rele1, 1);
    digitalWrite(porta_rele2, 1); 
    digitalWrite(porta_rele3, 1);
    digitalWrite(porta_rele4, 1); // Desligar 

    digitalWrite(led_Red1, 0);
    digitalWrite(led_Red2, 0);
    digitalWrite(led_Red3, 0);
    digitalWrite(led_Green1, 1);
  } 

  if(targetLevel == 2 ){
    while(digitalRead(ch_02) == LOW){

      digitalWrite(porta_rele3, 1); 
      digitalWrite(porta_rele4, 1);
      delay(100);
      digitalWrite(porta_rele1, 0); 
      digitalWrite(porta_rele2, 0);  // Descer
             
      digitalWrite(led_Green1, 0);
      digitalWrite(led_Green2, 0);
      digitalWrite(led_Green3, 0);

      digitalWrite(led_Red1, 1);
      digitalWrite(led_Red2, 1);
      digitalWrite(led_Red3, 1);
      
      if(digitalRead(ch_01) == HIGH ){
    
        digitalWrite(porta_rele1, 1);
        digitalWrite(porta_rele2, 1); 
        digitalWrite(porta_rele3, 1);
        digitalWrite(porta_rele4, 1); // Desligar 
    
        digitalWrite(led_Red1, 0);
        digitalWrite(led_Red2, 0);
        digitalWrite(led_Red3, 0);
        
        return;
     } 
    }
    digitalWrite(porta_rele1, 1);
    digitalWrite(porta_rele2, 1); 
    digitalWrite(porta_rele3, 1);
    digitalWrite(porta_rele4, 1); // Desligar 

    digitalWrite(led_Red1, 0);
    digitalWrite(led_Red2, 0);
    digitalWrite(led_Red3, 0);
    digitalWrite(led_Green2, 1);

  } else{
    return;
  }
  startTime = millis();
}
//-------------------------Go Up The Elevator-----------------------------

void upElevator(byte nextL) {

  int targetLevel = nextL;
  
  if(targetLevel == 2 ){
    while(digitalRead(ch_02) == LOW ){
             
      digitalWrite(porta_rele1, 1); 
      digitalWrite(porta_rele2, 1);
      delay(100);
      digitalWrite(porta_rele3, 0); 
      digitalWrite(porta_rele4, 0); // Subir
        
      digitalWrite(led_Green1, 0);
      digitalWrite(led_Green2, 0);
      digitalWrite(led_Green3, 0);

      digitalWrite(led_Red1, 1);
      digitalWrite(led_Red2, 1);
      digitalWrite(led_Red3, 1);

      if(digitalRead(ch_03) == HIGH ){
    
        digitalWrite(porta_rele1, 1);
        digitalWrite(porta_rele2, 1); 
        digitalWrite(porta_rele3, 1);
        digitalWrite(porta_rele4, 1); // Desligar 
    
        digitalWrite(led_Red1, 0);
        digitalWrite(led_Red2, 0);
        digitalWrite(led_Red3, 0);
        
        return;
      }
    }
    digitalWrite(porta_rele1, 1);
    digitalWrite(porta_rele2, 1); 
    digitalWrite(porta_rele3, 1);
    digitalWrite(porta_rele4, 1);   // Desligar

    digitalWrite(led_Red1, 0);
    digitalWrite(led_Red2, 0);
    digitalWrite(led_Red3, 0);
    digitalWrite(led_Green2, 1);
  } 

  if(targetLevel == 3 ){
    while(digitalRead(ch_03) == LOW){

      digitalWrite(porta_rele1, 1); 
      digitalWrite(porta_rele2, 1);
      delay(100);
      digitalWrite(porta_rele3, 0); 
      digitalWrite(porta_rele4, 0);  // Subir

      digitalWrite(led_Green1, 0);
      digitalWrite(led_Green2, 0);
      digitalWrite(led_Green3, 0);
      digitalWrite(led_Red1, 1);
      digitalWrite(led_Red2, 1);
      digitalWrite(led_Red3, 1);
    }
    digitalWrite(porta_rele1, 1);
    digitalWrite(porta_rele2, 1); 
    digitalWrite(porta_rele3, 1);
    digitalWrite(porta_rele4, 1);   // Desligar

    digitalWrite(led_Red1, 0);
    digitalWrite(led_Red2, 0);
    digitalWrite(led_Red3, 0);
    digitalWrite(led_Green3, 1);

  } else{
    return;
  }
  startTime = millis();
}

//-------------------------Go First Floor-----------------------------
void Go_P1() {
  
  byte nextLevel = 1;
  int currentLevel = readcurrentLevel();

  if(currentLevel == 1){
    return;
  } 
  else if(currentLevel == 2 || currentLevel == 3){
    downElevator(nextLevel);
  } 
  else {
    downElevator(1);
  } 
}
//-------------------------Go Third Floor-----------------------------
void Go_P3() {
  
  byte nextLevel = 3;
  int currentLevel = readcurrentLevel();
  Serial.println(currentLevel);
  if (currentLevel == 3){
    return;
  } 
  else if (currentLevel == 1 || currentLevel == 2){
    upElevator(nextLevel);
  } 
  else {
    downElevator(1);
  }
}
//-------------------------Go Second Floor-----------------------------
void Go_P2() {
  
  byte nextLevel = 2;
  int currentLevel = readcurrentLevel();

  if(currentLevel == 2){
    return;
  } 
  else if(currentLevel == 1 ){
    upElevator(nextLevel);
  } 
  else if(currentLevel == 3 ){
    downElevator(nextLevel);
  }
  else{
    downElevator(1);
  }


}
//-------------------------Detect Next Floor-----------------------------


byte nextFloorDetect() {

  if (digitalRead(port_button1) == LOW)
    return 1;
  else if (digitalRead(port_button2) == LOW)
    return 2;
  else if (digitalRead(port_button3) == LOW)
    return 3;

}





//-------------------------Loop----------------------------------------------

void loop() {

byte nextFloor = 0;
Serial.println("Funcionando");
Serial.println((String) "FimCurso 1 Andar: "+digitalRead(ch_01));
Serial.println((String) "FimCurso 2 Andar: "+digitalRead(ch_02));
Serial.println((String) "FimCurso 3 Andar: "+digitalRead(ch_03));
Serial.println(" ");
 
  if (digitalRead(port_button1) == LOW || digitalRead(port_button2) == LOW || digitalRead(port_button3) == LOW )
  {
    byte nextFloor = nextFloorDetect();

    Serial.println((String) "Botão 1 Andar: "+digitalRead(port_button1));
    Serial.println((String) "Botão 2 Andar: "+digitalRead(port_button2));
    Serial.println((String) "Botão 3 Andar: "+digitalRead(port_button3));
    Serial.println((String) "Proximo Andar: "+nextFloor);
    Serial.println(" ");
    
    
    if(nextFloor == 1){
    Go_P1();
    } 
   if(nextFloor == 2 ){
    Go_P2();
    } 
    if(nextFloor == 3 ){
    Go_P3();
    }
  }

if ((millis() - startTime) > ledTurnoff) {
 
  digitalWrite(led_Green1, 0);
  digitalWrite(led_Green2, 0);
  digitalWrite(led_Green3, 0);
}
  Serial.println("---------------------------------------------------------------- ");
}
