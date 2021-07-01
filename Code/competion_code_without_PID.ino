/*
 push button in pullup mode
*/

//index name
#define red 0
#define green 1
#define blue 2

//define push button 
#define pb 17


//deffine motor pins:10 9 8 7
#define R1 9
#define R2 10
#define L1 8
#define L2 7

//enable 
#define enR 11
#define enL 6

//define color sensor pins 
#define s0 15
#define s1 16
#define s2 12 
#define s3 13
#define out_of_sensor 14

//define IR pins
#define IRR 5
#define IRMR 4 
#define IRML 3
#define IRL 2

//define led of pins
int led[3]={18,19,1};

//mode of color sensor
char readed_color='N';

//to count the interection
int inter1=0;
int inter2=0;
int then=0;
int then2=0;

//valuse of color sensor
int rgbvalue[3];

int track=0;

void setup() {
  // to make the serial begain
  Serial.begin(9600); 
  
  //mode of pins motor control
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);

   //set of enable pin
  pinMode(enR,OUTPUT);
  pinMode(enL,OUTPUT);
  
  //set of n IRs pins
  pinMode(IRR,INPUT);
  pinMode(IRMR,INPUT);
  pinMode(IRML,INPUT);
  pinMode(IRL,INPUT);

  //define the pins of color sensor
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out_of_sensor,INPUT);

  //set the push button 
  pinMode(pb,INPUT_PULLUP);

  //set frequance 20%
  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);

  //mode of leds 
  for(int i=0;i<3;i++)
  {
    pinMode(led[i],OUTPUT);
  }

  //to make defulte speed of motor maxmam 
  analogWrite(enR,200);
  analogWrite(enL,200);
  delay(500);
  
  }

void loop() {
  if(track==0/*digitalRead(pb)==HIGH*/){
    //to detect the color in the first:
    readcolor();
    Serial.print("R:");
   Serial.print(rgbvalue[red]);
   Serial.print("  ");
   Serial.print("G:");
   Serial.print(rgbvalue[green]);
   Serial.print("  ");
   Serial.print("B:");
   Serial.print(rgbvalue[blue]);
   Serial.print("  ");
   if(rgbvalue[red]<rgbvalue[green] && rgbvalue[red]<rgbvalue[blue]){
    Serial.println("red");
    readed_color='R';
    Serial.print("readed_color=");
    Serial.println(readed_color);
    digitalWrite(led[red],HIGH);
    digitalWrite(led[green],LOW);
    digitalWrite(led[blue],LOW);
   }else if(rgbvalue[green]<rgbvalue[red] && rgbvalue[green]<rgbvalue[blue]){
    Serial.println("green");
    readed_color='G';
    digitalWrite(led[green],HIGH);
    digitalWrite(led[red],LOW);
    digitalWrite(led[blue],LOW);
   }else if(rgbvalue[blue]<rgbvalue[green] && rgbvalue[blue]<rgbvalue[red]){
    Serial.println("blue");
    readed_color='G';
    digitalWrite(led[blue],HIGH);
    digitalWrite(led[red],LOW);
    digitalWrite(led[green],LOW);
    } 
  }
  track=1;
  
  if(readed_color=='R')
  {
    Serial.println("in function of red");
    go_ot_red();
  }
  else if(readed_color=='G')
  {
    go_to_green();
  }
  else if(readed_color=='B')
  {
    go_to_blue();
  }
  analogWrite(enR,150);
  analogWrite(enL,150);
  Serial.print(digitalRead(IRL));
  Serial.print("  ");
  Serial.print(digitalRead(IRML));
  Serial.print("  ");
  Serial.print(digitalRead(IRMR));
  Serial.print("  ");
  Serial.println(digitalRead(IRR));
  
  
  
}


void readcolor(){
  //read red 
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  rgbvalue[red]=pulseIn(out_of_sensor,LOW);
  //read green
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  rgbvalue[green]=pulseIn(out_of_sensor,LOW);
  //read blue
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  rgbvalue[blue]=pulseIn(out_of_sensor,LOW);
}
//<<-------start of motor functions------->>
void back()
{
  Serial.print("forward");
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  
}
void forward()
{
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  
}
void sharp_right()
{
  Serial.print("right");
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  
}
void left()
{
  analogWrite(enR,100);
  analogWrite(enL,120);
  
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  
}
void sharp_left()
{
  Serial.print("left");
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  
}

void right()
{
  analogWrite(enR,120);
  analogWrite(enL,100);
  
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  
}

void stopcar()
{
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  
}
//<<-------------end of motor functions----------------->>
//track control:
/*void outomatic()
{
  if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==0 )
  {
    forward();
  }
  if( digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==1 || digitalRead(IRR)==1 )
  {
    
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1)
  {
    forward();
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0)
  {
    
  }
}*/
//go to:
void go_ot_red()
{
if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 &&then==0)
{
  inter1=inter1+1;
  then=1;
}

  if(digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==1 )
  {
    sharp_right();
  }
  if(digitalRead(IRL)==1 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0 )
  {
    sharp_left();
  }
  Serial.println("in go function");
  if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==0 )
  {
    Serial.println("if 1");
    forward();
    then=0;
  }
  /*if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==1)
  {
    forward();
    
  }*/
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1)
  {
    sharp_right();
    delay(250);
  }
  if( digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0)
  {
    forward();
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1&&inter1==2)
  {
    sharp_right();
     delay(500);
  }
  
   if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1&&inter1==3)
  {
    forward();
    
  }
   if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1&&inter1==4)
  {
    stopcar();
    
  }
}


void go_to_blue()
{
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 &&then==0)
{
  inter1=inter1+1;
  then=1;
}
if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 &&then2==0)
{
  inter2=inter2+1;
  then2=1;
}
  if(digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==1 )
  {
    sharp_right();
  }
  if(digitalRead(IRL)==1 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0 )
  {
    sharp_left();
  }
  if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==0 )
  {
    forward();
    then=0;
    then2=0;
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==1)
  {
    forward();
    
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==1)
  {
    forward();
    
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==2)
  {
    forward();
    
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==2)
  {
    sharp_right();
    delay(500);
    
  }
  
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==3)
  {
    sharp_right();
    delay(500);
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==4)
  {
    forward();
    
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==3)
  {
    forward();
    
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==5)
  {
    forward();
    
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1&&inter1==6)
  {
    stopcar();
    
  }
}


void go_to_green()
{
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 &&then==0)
{
  inter1=inter1+1;
  then=1;
}
if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 &&then2==0)
{
  inter2=inter2+1;
  then2=1;
}
  if(digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==1 )
  {
    sharp_right();
  }
  if(digitalRead(IRL)==1 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0 )
  {
    sharp_left();
  }
  if( digitalRead(IRL)==0 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==0 )
  {
    forward();
    then=0;
    then2=0;
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==1)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==1)
  {
    forward();
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==2)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==2)
  {
    forward();
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==3)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==3)
  {
    sharp_right();
    delay(500);
    
  }
  if( digitalRead(IRL)==0 && digitalRead(IRML)==0 && digitalRead(IRMR)==0 && digitalRead(IRR)==0)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==4)
  {
    sharp_right();
    delay(500);
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==4)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==5)
  {
    forward();
   
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==5)
  {
    forward();
  }
  if( digitalRead(IRL)==0 && (digitalRead(IRML)==1 && digitalRead(IRMR)==1) && digitalRead(IRR)==1 && inter2==6)
  {
    forward();
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1 && inter1==6)
  {
    forward();
   
  }
  if( digitalRead(IRL)==1 && digitalRead(IRML)==1 && digitalRead(IRMR)==1 && digitalRead(IRR)==1&&inter1==7)
  {
    stopcar();
    
  }
}
