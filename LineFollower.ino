#define rightmotor1 6
#define rightmotor2 5
#define rightmotorPWM 10
#define leftmotor1 4
#define leftmotor2 3
#define leftmotorPWM 11

const int ls = A4;
const int cs = A2;
const int rs = A0;


int l1=1;
int l2=1;
int l3=1;

int x=0;
void setup() {
  // put your setup code here, to run once:
 pinMode(rightmotor1, OUTPUT);
  pinMode(rightmotor2, OUTPUT);
  pinMode(rightmotorPWM, OUTPUT);
  pinMode(leftmotor1, OUTPUT);
  pinMode(leftmotor2, OUTPUT);
  pinMode(leftmotorPWM, OUTPUT);
  pinMode(ls, INPUT);
  pinMode(cs,INPUT);
  pinMode(rs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
l1=digitalRead(ls);
l2=digitalRead(cs);
l3=digitalRead(rs);


if(l1==1&&l2==0&&l3==0||l1==1&&l2==1&&l3==0)   //left turn
{
  digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,1);
  digitalWrite(leftmotor2,0);
   analogWrite(rightmotorPWM,200);
   analogWrite(leftmotorPWM, 200);
}
else
if(l1==0&&l2==0&&l3==1||l1==0&&l2==1&&l3==1)  //right turn
{
  digitalWrite(rightmotor1,0);
  digitalWrite(rightmotor2,1);
  digitalWrite(leftmotor1,0);
  digitalWrite(leftmotor2,1);
  analogWrite(rightmotorPWM, 200);
   analogWrite(leftmotorPWM, 200);
}
else
if(l1==0&&l2==1&&l3==0)  //go forward straight
{
  digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,0);
  digitalWrite(leftmotor2,1);
  analogWrite(rightmotorPWM, 255);
   analogWrite(leftmotorPWM, 255);
}
else
if(l1==1&&l2==1&&l3==1) //stop
{ 
 digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,1);
  digitalWrite(leftmotor2,0);
  analogWrite(rightmotorPWM, 250);
   analogWrite(leftmotorPWM, 250);
   delay(300);}
   }
