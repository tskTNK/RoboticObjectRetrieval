#include <AFMotor.h> // https://learn.adafruit.com/adafruitmotor-shield/af-dcmotor-class
AF_DCMotor endEffector(1, MOTOR12_1KHZ); // End effector
AF_DCMotor motor2(2, MOTOR12_1KHZ); // motor 2
AF_DCMotor motor3(3, MOTOR34_1KHZ); // motor 3
AF_DCMotor motor4(4, MOTOR34_1KHZ); // motor 4 Base plate motor

const int ledPin = 53; // the number of the LED pin
int analogPin1 = A8; // motor 1
int analogPin2 = A9; // motor 2
int analogPin3 = A10; // motor 3
int analogPin4 = A11; // motor 4

int val1 = 0; 
int val2 = 0; 
int val3 = 0; 
int val4 = 0;

int target_val1 = 0; 
int target_val2 = 0; 
int target_val3 = 0; 
int target_val4 = 0;

const unsigned int MAX_MESSAGE_LENGTH = 12;

void setup() {
  Serial.begin(9600);           //  setup serial
  
  endEffector.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  pinMode(ledPin,OUTPUT); // initialize the LED pin as an output:
  
  Serial.println("Goodnight moon!");
}

void serialEvent1() {
}

void loop() {

   //Check to see if anything is available in the serial receive buffer
   while (Serial.available() > 0)
   {
     //Create a place to hold the incoming message
     static char message[MAX_MESSAGE_LENGTH];
     static unsigned int message_pos = 0;
  
     //Read the next available byte in the serial receive buffer
     char inByte = Serial.read();
     
     //Message coming in (check not terminating character) and guard for over message size
     if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
     {
       //Add the incoming byte to our message
       message[message_pos] = inByte;
       message_pos++;
     }
     //Full message received...
     else
     {
       //Add null character to string
       message[message_pos] = '\0';
  
       //Print the message (or do other things)
       Serial.println(message);
  
       //Reset for the next message
       message_pos = 0;

      if (message[0] == 'H'){
        Serial.print("a: motor1 up"); Serial.print('\n');
        Serial.print("b: motor1 down "); Serial.print('\n');
        Serial.print("c: motor2 up"); Serial.print('\n');
        Serial.print("d: motor2 down "); Serial.print('\n');
        Serial.print("e: motor3 up"); Serial.print('\n');
        Serial.print("f: motor3 down "); Serial.print('\n');
        Serial.print("g: motor4 CCW"); Serial.print('\n');
        Serial.print("h: motor4 CW "); Serial.print('\n');
        Serial.print("i: close end effector"); Serial.print('\n');
        Serial.print("j: open end effector"); Serial.print('\n');
        Serial.print("k: motor1 joint variable"); Serial.print('\n');
        Serial.print("l: motor2 joint variable"); Serial.print('\n');
        Serial.print("m: motor3 joint variable"); Serial.print('\n');
        Serial.print("n: motor4 joint variable"); Serial.print('\n');
        Serial.print("r: read potentiometer "); Serial.print('\n');
        Serial.print("F: feedback control motion "); Serial.print('\n');
      }

      if (message[0] == 'a'){  
        Serial.print("not supported ");     
      }
    
      if (message[0] == 'b'){    
        Serial.print("not supported ");   
      }
      
      if (message[0] == 'c'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);        
        motor2.run(BACKWARD); delay(amount); // motor2 up
        motor2.run(RELEASE); delay(1000); 
        val2 = analogRead(analogPin2);
        Serial.print("Potentiometer 2: ");
        Serial.println(val2);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;           
      }
    
      if (message[0] == 'd'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);        
        motor2.run(FORWARD); delay(amount); // motor2 down
        motor2.run(RELEASE); delay(1000); 
        val2 = analogRead(analogPin2);
        Serial.print("Potentiometer 2: ");
        Serial.println(val2);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;           
      }
        
      if (message[0] == 'e'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);        
        motor3.run(BACKWARD); delay(amount); // motor3 up
        motor3.run(RELEASE); delay(1000); 
        val3 = analogRead(analogPin3);
        Serial.print("Potentiometer 3: ");
        Serial.println(val3);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;    
      }
    
      if (message[0] == 'f'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);        
        motor3.run(FORWARD); delay(amount); // motor3 down
        motor3.run(RELEASE); delay(1000); 
        val3 = analogRead(analogPin3);
        Serial.print("Potentiometer 3: ");
        Serial.println(val3);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;  
      }
    
      if (message[0] == 'g'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);        
        motor4.run(BACKWARD); delay(amount); // motor4 CCW
        motor4.run(RELEASE); delay(1000); 
        val4 = analogRead(analogPin4);
        Serial.print("Potentiometer 4: ");
        Serial.println(val4);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30; 
        }
    
      if (message[0] == 'h'){
        int amount = 0;
        Serial.print(message[1], DEC );
        Serial.print(message[2], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10;
        Serial.println(amount);         
        motor4.run(FORWARD); delay(amount); // motor4 CW
        motor4.run(RELEASE); delay(1000); 
        val4 = analogRead(analogPin4);
        Serial.print("Potentiometer 4: ");
        Serial.println(val4);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;     
      }
    
      if (message[0] == 'i'){
        endEffector.run(FORWARD); delay(1000); // close end effector    
        endEffector.run(RELEASE); delay(1000); 
      }
    
      if (message[0] == 'j'){
        endEffector.run(BACKWARD); delay(1000); // open end effector 
        endEffector.run(RELEASE); delay(1000); 
      }

      if (message[0] == 'k'){  
        Serial.print("not supported ");     
      }
      
      if (message[0] == 'l'){

      // motor 2 caliburation
      // 0deg -> 520
      // 3deg = 10
        
        int amount = 0;
//        Serial.print(message[1], DEC );
//        Serial.print(message[2], DEC );
//        Serial.print(message[3], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        if (message[3] > 0x39 || message[3] < 0x30 ){
          message[3] = 0x30;
          Serial.print("Not Ascii:3 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10 + (message[3]-0x30);
//        Serial.println(amount);        
        motor2Control(amount+3, 15, 1);    
        motor2Control(amount, 15, 1);
         
        val2 = analogRead(analogPin2);
        Serial.print("Potentiometer 2: ");
        Serial.println(val2);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;     
      }
    
      if (message[0] == 'm'){
        
        // motor 3 calibration 
        // +90 -> 530
        // 3deg = 10

        int amount = 0;
//        Serial.print(message[1], DEC );
//        Serial.print(message[2], DEC );
//        Serial.print(message[3], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        if (message[3] > 0x39 || message[3] < 0x30 ){
          message[3] = 0x30;
          Serial.print("Not Ascii:3 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10 + (message[3]-0x30);
//        Serial.println(amount);        
        motor3Control(amount+1, 20, 0);    
        motor3Control(amount, 20, 0);
         
        val3 = analogRead(analogPin3);
        Serial.print("Potentiometer 3: ");
        Serial.println(val3);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;    
      }

      if (message[0] == 'n'){

        // motor 4 caliburation
        // 0deg = 455
        // 1deg = 3
        
        int amount = 0;
//        Serial.print(message[1], DEC );
//        Serial.print(message[2], DEC );
//        Serial.print(message[3], DEC );
          
        if (message[1] > 0x39 || message[1] < 0x30 ){
          message[1] = 0x30;
          Serial.print("Not Ascii:1 ");
        }
        if (message[2] > 0x39 || message[2] < 0x30 ){
          message[2] = 0x30;
          Serial.print("Not Ascii:2 ");
        }
        if (message[3] > 0x39 || message[3] < 0x30 ){
          message[3] = 0x30;
          Serial.print("Not Ascii:3 ");
        }
        amount = (message[1]-0x30)*100 + (message[2]-0x30)*10 + (message[3]-0x30);
//        Serial.println(amount);        
        motor4Control(amount, 9, 1);
         
        val3 = analogRead(analogPin4);
        Serial.print("Potentiometer 4: ");
        Serial.println(val4);
        Serial.flush();     
        message[1] = 0x30; 
        message[2] = 0x30;    
      }
      
      if (message[0] == 'r'){
        val1 = analogRead(analogPin1);  // read the input pin
        val2 = analogRead(analogPin2);  
        val3 = analogRead(analogPin3);
        val4 = analogRead(analogPin4);
        Serial.print("Potentiometer 1: ");
        Serial.println(val1);          
        Serial.print("Potentiometer 2: ");
        Serial.println(val2);          
        Serial.print("Potentiometer 3: ");
        Serial.println(val3);          
        Serial.print("Potentiometer 4: ");
        Serial.println(val4);    
      }
             
      if (message[0] == 'F'){

        // Robo demo 3 task
        // implement a Bang-Bang control

        // record the initial position
        val1 = analogRead(analogPin1);  // read the input pin
        val2 = analogRead(analogPin2);  
        val3 = analogRead(analogPin3);
        val4 = analogRead(analogPin4);
        Serial.print("Potentiometer 1: ");
        Serial.println(val1);          
        Serial.print("Potentiometer 2: ");
        Serial.println(val2);          
        Serial.print("Potentiometer 3: ");
        Serial.println(val3);          
        Serial.print("Potentiometer 4: ");
        Serial.println(val4);    

        // Waypoint control

        // 1. close the end factor
        closeEndEffector(1000);

        // 2. move motor2 : up
        target_val2 = 740; 
        motor2Control(target_val2, 10, 5);
        
        // 3. move motor3 : up
        target_val3 = 550; 
        motor3Control(target_val3, 10, 5);

        // 4. move motor4 : move to a new lateral point
        target_val4 = 540; 
        motor4Control(target_val4, 10, 5);
 
        // 5. move motor3 : down
        target_val3 = 660; 
        motor3Control(target_val3, 10, 5);
 
        // 6. move motor2 : down
        target_val2 = 800; 
        motor2Control(target_val2, 10, 5);
 
        // 7. open the end factor
        openEndEffector(1000);

        // 8. move motor2 : up
        target_val2 = 740; 
        motor2Control(target_val2, 10, 5);
 
        // 9. move motor3 : up
        target_val3 = 550; 
        motor3Control(target_val3, 10, 5);
         
        // 10. move motor4 : back to the original lateral point
        target_val4 = 640; 
        motor4Control(target_val4, 10, 5);
 
        // 11. move motor3 : down
        target_val3 = 660; 
        motor3Control(target_val3, 10, 5);
         
        // 12. move motor2 : down
        target_val2 = 800; 
        motor2Control(target_val2, 10, 5);
      
      }

     }
   }
}

int openEndEffector(int speed){
    endEffector.run(BACKWARD); delay(speed); // open
    endEffector.run(RELEASE); delay(1000); 
}

int closeEndEffector(int speed){
    endEffector.run(FORWARD); delay(speed); // close
    endEffector.run(RELEASE); delay(1000); 
}
 
int motor2Control(int target_val2, int speed, int error){
  
    val2 = analogRead(analogPin2);  // read the input pin
    
    while (val2 < target_val2 - error || val2 > target_val2 + error)
    { 
      val2 = analogRead(analogPin2);  // read the input pin
//      Serial.print("val2: ");
//      Serial.println(val2);    
//      Serial.print("target val1 2: ");     
//      Serial.println(target_val2);           
      
      if (val2 < target_val2 - error)
      {
        motor2.run(FORWARD); delay(speed); // down -> increase val1
        motor2.run(RELEASE); delay(10); 
      }
      if (val2 > target_val2 + error)
      {
        motor2.run(BACKWARD); delay(speed); // up -> decrease val1
        motor2.run(RELEASE); delay(10); 
      } 
    }
}

int motor3Control(int target_val3, int speed, int error){
  
    val3 = analogRead(analogPin3);  // read the input pin
    
    while (val3 < target_val3 - error || val3 > target_val3 + error)
    { 
      val3 = analogRead(analogPin3);  // read the input pin
//      Serial.print("val3: ");
//      Serial.println(val3);    
//      Serial.print("target val1 3: ");     
//      Serial.println(target_val3);           
      
      if (val3 < target_val3 - error)
      {
        motor3.run(FORWARD); delay(speed); // down -> increase val2
        motor3.run(RELEASE); delay(10); 
      }
      if (val3 > target_val3 + error)
      {
        motor3.run(BACKWARD); delay(speed); // up -> decrease val2
        motor3.run(RELEASE); delay(10); 
      } 
    }
}

int motor4Control(int target_val4, int speed, int error){
  
    val4 = analogRead(analogPin4);  // read the input pin
    
    while (val4 < target_val4 - error || val4 > target_val4 + error)
    { 
      val4 = analogRead(analogPin4);  // read the input pin
//      Serial.print("val4: ");
//      Serial.println(val4);    
//      Serial.print("target val1 4: ");     
//      Serial.println(target_val4);           
      
      if (val4 < target_val4 - error)
      {
        motor4.run(BACKWARD); delay(speed); // motor4 CCW -> incrase val4
        motor4.run(RELEASE); delay(40); 
      }
      if (val4 > target_val4 + error)
      {
        motor4.run(FORWARD); delay(speed); // motor4 CW -> decrease val4
        motor4.run(RELEASE); delay(40); 
      } 
    }
}
