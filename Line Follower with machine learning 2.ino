#define rightmotor1 6
#define rightmotor2 5
#define rightmotorPWM 10
#define leftmotor1 4
#define leftmotor2 3
#define leftmotorPWM 11
#define training_Count 5

const int ls = A4;
const int cs = A2;
const int rs = A0;


int left_sensor;
int center_sensor;
int right_sensor;

float ALPHA = 0.1;
float GAMMA = 0.5;
char Robot_CurrentState;
char Robot_Action_ToTake;
char Next_State;
float Q_new,Q_old,Q_Max;
char Actions[4] = {0, 1, 2, 3} ;

void Update_Q(float Q_TABLE[8][4] , char current_state, char next_state, char Action,  int Reward, float LEARNING_RATE, float DISCOUNT_FACTOR);
void MoveForward(void);
void TurnLeft(void);
void TurnRight(void);
void Stop(void);
char Get_stateNumber(void);
void Start_Robot_Trainig(void);
float Get_max_Q(float Q_TABLE[8][4],char stateNum);
char Get_max_Q_Index(float Q_TABLE[8][4] , char stateNum);
void Start_Robot_Testing(void);


#define States_count 8    

#define Actions_count 4   

/*2D Array of size 8*4 to store the values of Q calculated for each (S,a) pair, initialized with all 0's */
float Q[States_count][Actions_count]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

/*2D Array of size 8*4 to store the values of Rewards calculated for each (S,a) pair, initialized with all 0's */
 int Rewards[States_count][Actions_count]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
 
void Update_Q(float Q_TABLE[8][4] , char current_state, char next_state, char Action,  int Reward, float LEARNING_RATE, float DISCOUNT_FACTOR)
{

  Q_old = Q_TABLE[current_state][Action];
  Q_Max = Get_max_Q(Q_TABLE, next_state);
  Q_new = ( ( 1-LEARNING_RATE ) * Q_old ) + ( LEARNING_RATE * ( Reward + ( DISCOUNT_FACTOR * Q_Max ) ) );
  Q_TABLE[current_state][Action] = Q_new;
}


void MoveForward(void)
{
   digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,0);
  digitalWrite(leftmotor2,1);
  analogWrite(rightmotorPWM, 255);
   analogWrite(leftmotorPWM, 255);
}


void TurnLeft(void)
{
  digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,1);
  digitalWrite(leftmotor2,0);
   analogWrite(rightmotorPWM,200);
   analogWrite(leftmotorPWM, 200);
}


void TurnRight(void)
{
  digitalWrite(rightmotor1,0);
  digitalWrite(rightmotor2,1);
  digitalWrite(leftmotor1,0);
  digitalWrite(leftmotor2,1);
  analogWrite(rightmotorPWM, 200);
   analogWrite(leftmotorPWM, 200);
}

void Stop(void)
{
  digitalWrite(rightmotor1,1);
  digitalWrite(rightmotor2,0);
  digitalWrite(leftmotor1,1);
  digitalWrite(leftmotor2,0);
  analogWrite(rightmotorPWM, 0);
   analogWrite(leftmotorPWM, 0);
   delay(300);
}

char Get_stateNumber(){

  char state_number;

  
  if ( (left_sensor==0) && (center_sensor==0) && (right_sensor==0) )
  {
    state_number=0;
  }
  else if ( (left_sensor==0) && (center_sensor==0) && (right_sensor==1) )
  {
    state_number=1;
  }
  else if ( (left_sensor==0) && (center_sensor==1) && (right_sensor==0) )
  {
    state_number=2;
  }
  else if ( (left_sensor==0) && (center_sensor==1) && (right_sensor==1) )
  {
    state_number=3;
  }
  else if ( (left_sensor==1) && (center_sensor==0) && (right_sensor==0) )
  {
    state_number=4;
  }
  else if ( (left_sensor==1) && (center_sensor==0) && (right_sensor==1) )
  {
    state_number=5;
  }
  else if ( (left_sensor==1) && (center_sensor==1) && (right_sensor==0) )
  {
    state_number=6;
  }
  else if ( (left_sensor==1) && (center_sensor==1) && (right_sensor==1) )
  {
    state_number=7;
  }
  return state_number;
}


void Start_Robot_Trainig(void){

  int training_LoopCount;

  for( training_LoopCount = 0 ; training_LoopCount < training_Count ; training_LoopCount++ )
  { Robot_CurrentState=  Get_stateNumber();
    while (Robot_CurrentState==2){
      MoveForward();
       Rewards[Robot_CurrentState][0]= 5;
       Next_State= Get_stateNumber();
       Update_Q(Q, Robot_CurrentState, Next_State, 0 , Rewards[Robot_CurrentState][0], ALPHA, GAMMA);
    }
 Robot_CurrentState=  Get_stateNumber();
    int random_action;
   random_action=random(1,3);
    if(random_action==1)
      {
        TurnRight();
        Stop();
        if(( Robot_CurrentState == 1)||( Robot_CurrentState == 3))
      
        {
          
          Rewards[Robot_CurrentState][random_action]=5;
          Next_State= Get_stateNumber();
          Update_Q(Q, Robot_CurrentState, Next_State, random_action , Rewards[Robot_CurrentState][random_action], ALPHA, GAMMA);
        }
        else
        {
          Rewards[Robot_CurrentState][random_action]= -1;
        }
      }

      else if(random_action==2)
      {
        TurnLeft();
        Stop();
        if( ( Robot_CurrentState == 4)||( Robot_CurrentState == 6))
        {
        
          Rewards[Robot_CurrentState][random_action]= 5;
          Next_State= Get_stateNumber();
          Update_Q(Q, Robot_CurrentState, Next_State, random_action , Rewards[Robot_CurrentState][random_action], ALPHA, GAMMA);      }
        
        else
        {
          Rewards[Robot_CurrentState][random_action]= -1;
        }
      }
      else if(random_action==3)
      {
        Stop();
        
        if( Robot_CurrentState == 7)
        {
          Rewards[Robot_CurrentState][random_action]= 5;
          Next_State=Get_stateNumber();
          Update_Q(Q, Robot_CurrentState, Next_State, random_action , Rewards[Robot_CurrentState][random_action], ALPHA, GAMMA);
        }
        else
        {
          Rewards[Robot_CurrentState][random_action]= -1;
        }
      }
  }
}

float Get_max_Q(float Q_TABLE[8][4],char stateNum)
{

  float maximum;
  char actionNum;
  maximum=Q_TABLE[stateNum][0];
  for(actionNum=0; actionNum < 4 ; actionNum++ )
  {
    if(maximum<Q_TABLE[stateNum][actionNum])
    {
      maximum=Q_TABLE[stateNum][actionNum];
    }
  }
  return maximum;
}

char Get_max_Q_Index(float Q_TABLE[8][4],char stateNum)
{
  char index;
  float max=Q_TABLE[stateNum][0];
  char actionNum;
  for(actionNum=0;actionNum<4;actionNum++)
  {
    if(max < Q_TABLE[stateNum][actionNum] )
    {
      max=Q_TABLE[stateNum][actionNum];
      index=actionNum;
    }
  }
  return index;
}


void Start_Robot_Testing(void)
{
  Robot_CurrentState = Get_stateNumber();
  Robot_Action_ToTake = Get_max_Q_Index( Q , Robot_CurrentState );
  if(Robot_Action_ToTake==0)
  {
    MoveForward();
    _delay_ms(1500);
    Stop();
  }
  else if(Robot_Action_ToTake==1)
  {
    TurnRight();
    _delay_ms(1500);
    Stop();
  }
  else if(Robot_Action_ToTake==2)
  {
    TurnLeft();
    _delay_ms(1500);
    Stop();
  }
  else if(Robot_Action_ToTake==3)
  {
    Stop();
    _delay_ms(1500);
  }
}


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

void loop() 
{
  
left_sensor=digitalRead(ls);
center_sensor=digitalRead(cs);
right_sensor=digitalRead(rs);
Start_Robot_Trainig();
Start_Robot_Testing();
}
