//fazer um buraco grande entre o carro e a base
//menor polo do motor é sentido horario e o maior antihoriario  
//será no canhao = 3 e no base = 2 
//codigo do carrinho controlado por infravermelho
//mostrando controlador no arduino
//https://www.instructables.com/Simple-CAR-Arduino-IR-Controlled/
//https://youtu.be/eTe2ZmOmkAU?si=yDcZKbcKzjvYuwAQ
//alterado o codigo do botão direita com o da esquerda
#include <IRremote.h>
#include <Servo.h>

//codigos do controle para o servo
//      cima/2/0xFF629D
//esquerda/4/0xFF22DD meio/5/0xFF02FD   direita/6/0xFFC23D
//      baixo/8/0xFFA857

int angulo1 = 90;
int angulo2 = 90;

Servo base;
Servo canhao;


char command;
int receiver_pin = 4;
int vcc = 5;
int gnd = 6;
int statusled = 13;
IRrecv irrecv(receiver_pin);
decode_results results;


int x = 90;
int y = 90;
//int test = map(x,0,1023,0,180);

//conect motor controller pins to Arduino digital pins
//motor A

int enA = 8;
int in1 = 12;
int in2 = 11;
//motor B
int enB = 7;
int in3 = 10;
int in4 = 9;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(statusled,OUTPUT);
  digitalWrite(statusled,LOW);
  //set all the motor control pins to outputs
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(vcc,OUTPUT);
  pinMode(gnd,OUTPUT);
  //initializing vcc pin high
  digitalWrite(vcc,HIGH);
  
  
  base.attach(2);
  canhao.attach(3);
}

void loop(){
  //codigo dos servos
  // char terminal = Serial.read();

  
  if(irrecv.decode(&results)){
    digitalWrite(statusled,LOW);
    irrecv.resume();
    //Serial.println(results.value);
    unsigned int getting = (results.value);
    Serial.println(results.value,HEX);

    //move a base
      if(results.value == 0xFF22DD){
      Serial.println("vira esquerda/4/0xFF22DD");
      x += 36;
    if(x >= 180) x = 180;
    Serial.print("valor de x: ");
    Serial.println(x);
    angulo1 = map(x,0, 180,0, 180);
    //mover a base
    base.write(angulo1);
  };
  //move a base
    if(results.value == 0xFFC23D){
   Serial.println("vira direita/6/0xFFC23D");
    x -= 36;
    if(x <= 0) x = 0;
    Serial.print("valor de x: ");
    Serial.println(x);    
    angulo1 = map(x,0, 180,0, 180);
    //mover a base
      base.write(angulo1);
  };
    
    //move o canhao
    if(results.value == 0xFF629D){
   Serial.println("cima/2/0xFF629D");
    y -= 18;
    if(y <= 0) y = 0;
    Serial.print("valor de y: ");
    Serial.println(y);    
    //aqui passa da metade (90) do servo até 180
    angulo2 = map(y,0, 180,0, 90);
    //mover o canhao
      canhao.write(angulo2);
  };
    
        //move o canhao
    if(results.value == 0xFFA857){
   Serial.println("baixo/8/0xFFA857");
    y += 18;
    if(y >= 180) y = 180;
    Serial.print("valor de y: ");
    Serial.println(y);    
    //aqui passa da metade (90) do servo até 180
    angulo2 = map(y,0, 180,0, 90);
    //mover o canhao
      canhao.write(angulo2);
  };
    
    
    
    if(results.value == 0xFF18E7){
      //type button 2 foward robot control
      //this function will run the both directions at fixed speed
      Serial.println("Button 2 frente");
      //turn on motor A
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn on motor B
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      //set speed to 200 out of possible to range 0-255
      analogWrite(enB,100);
      
    }else if(results.value == 0xFF5AA5){
      //type 4 button turn left robot control
      //this function will run motor A in foward directions motor B stops
      Serial.println("Button 4 carro para a esquerdaaaaa");
      //turn on motor 4
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn on motor B
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enB,100);
      
      
    }else if(results.value == 0xFF30CF){
      //type button 1 rotate left robot control
      //motor A forward direction, B back directions
      Serial.println("Button turn right");
      //turn on motor A
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn on motor B
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      //set speed to 200 out of possible range 0-255
      analogWrite(enB,100);
      
    }else if(results.value == 0xFF10EF){
      //6 turn right
      //this function will stop motor A, run B foward
      Serial.println("Button Turn Left carro para a Direitaaaaa");
      //turn on motor A
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn on motor B
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enB,100);
      
    }else if(results.value == 0xFF7A85){
      //type button 3 rotate right robot control
      //this function will run A backward, motor B foward
      //turn on motor A
      Serial.println("Button 3 rotate turn right");
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn on motor B
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enB,100);
      
    }else if(results.value == 0xFF4AB5){
      //type button 8 backward
      //this function will run motor A and b backward
      //turn on motor A
      Serial.println("Ré");
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA, 100);
      //turn on motor B
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      //set speed to 200 out of possbile range 0-255
      analogWrite(enB,100);

    }else if(results.value == 0xFF38C7){
    //type button 5 stop robot control
      //this function wil stop A and B
      //turn off motor A
      Serial.println("Stop!!!!");
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enA,100);
      //turn off motor B
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      //set speed to 200 out of possible range 0-255
      analogWrite(enB,100);
    }
}
}