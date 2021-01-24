#include "MFRC522.h"
#include "pitches.h"
#include "Servo.h"

const int STATE_OPEN = 1;
const int STATE_CLOSED = 0;

const int SWITCH_STATE_BINARY = 1;
const int SWITCH_STATE_BLINK = 2;
const int SWITCH_STATE_SOUND = 3;
const int PUZZLE_STATE_WAITING_FOR_RFID = 4;
const int PUZZLE_STATE_SOLVED = 5;
int switchPuzzleState = SWITCH_STATE_BINARY;


const int SWITCH_OPEN_ADDRESS = 9;
const int SWITCH_1_ADDRESS = 1;
const int SWITCH_2_ADDRESS = 2;
const int SWITCH_3_ADDRESS = 3;
const int SWITCH_4_ADDRESS = 4;
const int BUTTON_EXECUTE_ADDRESS = 5;

const int SERVO_ADDRESS = 6;


int lidState = STATE_CLOSED;

const int STATE_PRESSED = 1;
const int STATE_UNPRESSED = 0;

void setup() {
  //initialize rfid

  //intialize button and switches

  //intialize leds

  //intialize buzzer

  //initialize servo

  if(lidIsClosed())
  {
    resetPuzzleState();
  }
}

void loop() {
  if(lidWasClosed())
  {
    resetPuzzleState();
  }

  lidState = lidIsClosed() ? STATE_CLOSED : STATE_OPEN;

  if(lidState == STATE_CLOSED)
  {
    if(executeButtonWasPressed())
    {
      if(isCurrentStepComplete())
      {
        moveToNextPuzzleState();
      }

      handlePuzzleState();
    }
  }
}

bool lidWasClosed()
{
  return lidState == STATE_OPEN && lidIsClosed();
}

bool lidIsClosed()
{
  return (getSwitchState(SWITCH_OPEN_ADDRESS) == STATE_PRESSED);
}

void resetPuzzleState()
{
  turnOnClueLight();
  switchPuzzleState = SWITCH_STATE_BINARY;
  setLockState(STATE_CLOSED);
}

void turnOnClueLight()
{
  //TODO 
}

bool executeButtonWasPressed()
{
  return (getSwitchState(BUTTON_EXECUTE_ADDRESS) == STATE_PRESSED);
}

bool isCurrentStepComplete()
{
  bool correct = false;

  //this is cheating a bit because i have constants but this is shorter :-(
  int BINARY_PATTERN[4] = {0,1,0,1};
  int BLINK_PATTERN[4] = {1,1,0,1};
  int SOUND_PATTERN[4] = {1,0,1,1};

  int currentPattern[4];
  
  populateCurrentSwitchPattern(currentPattern);

  switch(switchPuzzleState)
  {
    case SWITCH_STATE_BINARY:
      correct = statesAreEqual(BINARY_PATTERN, currentPattern);
      break;
    case SWITCH_STATE_BLINK:
      correct = statesAreEqual(BLINK_PATTERN, currentPattern);
      break;
    case SWITCH_STATE_SOUND:
      correct = statesAreEqual(SOUND_PATTERN, currentPattern);
      break;
    case PUZZLE_STATE_WAITING_FOR_RFID:
      correct = rfidCardIsPresent();
      break;  
  }

  return correct;
}

bool statesAreEqual(int pattern1[], int pattern2[])
{
  return 
  (pattern1[0] == pattern2[0] 
  && pattern1[1] == pattern2[1]
  && pattern1[2] == pattern2[2]
  && pattern1[3] == pattern2[3]);
}

void populateCurrentSwitchPattern(int currentPattern[])
{
  currentPattern[0] = getSwitchState(SWITCH_1_ADDRESS);
  currentPattern[1] = getSwitchState(SWITCH_2_ADDRESS);
  currentPattern[2] = getSwitchState(SWITCH_3_ADDRESS);
  currentPattern[3] = getSwitchState(SWITCH_4_ADDRESS);
}

int getSwitchState(int address)
{
  int switchState = STATE_UNPRESSED;

  //TODO get switch state for address

  return switchState;
}

void moveToNextPuzzleState()
{
  switch(switchPuzzleState)
  {
    case SWITCH_STATE_BINARY:
      switchPuzzleState = SWITCH_STATE_BLINK;
      break;
    case SWITCH_STATE_BLINK:
      switchPuzzleState = SWITCH_STATE_SOUND;
      break;
    case SWITCH_STATE_SOUND:
      switchPuzzleState = PUZZLE_STATE_WAITING_FOR_RFID;
      break;      
    case PUZZLE_STATE_WAITING_FOR_RFID:
      switchPuzzleState = PUZZLE_STATE_SOLVED;
      break; 
  }
}

void handlePuzzleState()
{
  switch(switchPuzzleState)
  {
    case SWITCH_STATE_BLINK:
      blinkLights();
    case SWITCH_STATE_SOUND:
      playSounds();
    case PUZZLE_STATE_WAITING_FOR_RFID:
      requestCrystal();
      break;      
    case PUZZLE_STATE_SOLVED:
      handlePuzzleSolved();
      break;  
  }
}

bool rfidCardIsPresent()
{
  bool cardPresent = false;
  
  //TODO

  return cardPresent;
}

void setLockState(int lockState)
{
  //open or close lock based on lockstate
}

void blinkLights()
{
  //TODO
}

void playSounds()
{
  //TODO
}

void playVictorySounds()
{
  //TODO
}

void requestCrystal()
{
  //TODO
}

void handlePuzzleSolved()
{
  setLockState(STATE_OPEN);
  playVictorySounds();
}