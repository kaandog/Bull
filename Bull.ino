#include <SPI.h>  
#include <Pixy.h>
#include <Timer.h>

#define incrementSpeed 5
#define maxChargingSpeed 190

int r_motor_n = 9;  //PWM control Right Motor -
int r_motor_p = 10;  //PWM control Right Motor +
int l_motor_p = 5;   //PWM control Left Motor +
int l_motor_n = 6;   //PWM control Left Motor -

int chargingSpeed = 290;
int turningSpeed = 290;

int choice = 0;

Timer t;

Pixy pixy;

void setup()
{
  pinMode(r_motor_n, OUTPUT);  //Set control pins to be outputs
  pinMode(r_motor_p, OUTPUT);
  pinMode(l_motor_p, OUTPUT);
  pinMode(l_motor_n, OUTPUT);
  
  digitalWrite(r_motor_n, LOW);  //set both motors off for start-up
  digitalWrite(r_motor_p, LOW);
  digitalWrite(l_motor_p, LOW);
  digitalWrite(l_motor_n, LOW);
  
  t.every(500,updateChoice);
  pixy.init();
}
void loop()
{
  t.update(); //used for random behavior
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  int maxProd;
  int prod;
  int skip = 0;
  int maxJ;
  blocks = pixy.getBlocks();
  
  if (blocks) //if something is detected
  {
    for (j = 0; j < blocks; j++){ //find the largest object that fits the signature
      prod = pixy.blocks[j].width * pixy.blocks[j].height;
      skip = 0;
      if (prod > maxProd)
          maxJ = j;  
    }

    if (skip != 1){
      if (pixy.blocks[maxJ].x < 100){
       digitalWrite(r_motor_p, HIGH);  //Set motor direction, 1 low, 2 high
       analogWrite(r_motor_n, chargingSpeed);
       analogWrite(l_motor_n, chargingSpeed);  
       digitalWrite(l_motor_p, HIGH);
      }
      //turn right
      else if (pixy.blocks[maxJ].x > 200){
       digitalWrite(r_motor_n, HIGH);  //Set motor direction, 1 low, 2 high
       analogWrite(r_motor_p, chargingSpeed);
       analogWrite(l_motor_p, chargingSpeed);  
       digitalWrite(l_motor_n, HIGH);
      }
      //forward!
      else {
       digitalWrite(r_motor_p, HIGH);  //Set motor direction, 1 low, 2 high
       analogWrite(r_motor_n, chargingSpeed);
       analogWrite(l_motor_p, chargingSpeed);  
       digitalWrite(l_motor_n, HIGH);
      }
    }
  }
  else{ //commented out are random behaviors for the purpose of debugging
//       if (choice == 0 || choice == 1 || choice == 2){
         digitalWrite(r_motor_n, LOW);  //Set motor direction, 1 low, 2 high
         digitalWrite(r_motor_p, LOW);
         digitalWrite(l_motor_p, LOW);  
         digitalWrite(l_motor_n, LOW);
//       }
//        else if (choice == 3){
//       digitalWrite(r_motor_n, HIGH);  //Set motor direction, 1 low, 2 high
//       analogWrite(r_motor_p, turningSpeed);
//       digitalWrite(l_motor_p, HIGH);  
//       analogWrite(l_motor_n, turningSpeed);
//        }
//       else if (choice == 4){
//       analogWrite(r_motor_n, turningSpeed);  //Set motor direction, 1 low, 2 high
//       digitalWrite(r_motor_p, HIGH);
//       analogWrite(l_motor_p, turningSpeed);  
//       digitalWrite(l_motor_n, HIGH);
//       }
  } 
  delay(30);
}

void updateChoice(){
  choice = random(0,5);
}
  
 
           

