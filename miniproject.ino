#include "chords.h"
#include <Wire.h>
#include "Adafruit_Trellis.h"

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A6
#define delayPin A8
#define randomPin A9
#define octavePin A7

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

int randomVal;
int octaveVal;
int midiVal1;
int midiVal2;
int channel = 1;
int chord = 0;
int scale = 0;
int complexity = 0;
//int mapping[16] = {15,11,7,3,14,10,6,2,13,9,5,1,12,8,4,0};
int mapping[16] = {3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12};
int invertionMode = 0;

float finger_delay = 10;

bool chordReleased = false;
bool changeChord = false;
bool complexityMode = false;
bool majorMinor = true;
bool chordPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  // only one

  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }

  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}


void loop() {
  delay(30);
    // If a button was just pressed or released...
    finger_delay = map(analogRead(delayPin), 1023, 0, 0, 150); // reading delay pn
    randomVal = map(analogRead(randomPin), 1023, 0, 0, 70); // velocity randomization pn
    octaveVal = map(analogRead(octavePin), 1023, 0, 0, 2); // octave control pn

    if(chordPressed){
      playChord(selectChord(chord, 100, majorMinor, scale), finger_delay, randomVal, octaveVal, invertionMode);
      chordPressed = false;
      Serial.print(octaveVal);
     }
     
    trellis.setLED(mapping[12]);
    if (trellis.readSwitches()) {
      // go through every button

      for (uint8_t i=0; i<numKeys; i++) {
        if(mapping[i] == mapping[12]) {
          if(trellis.justPressed(mapping[12]) && changeChord == false) {
            changeChord = true;
          } 
          else if(trellis.justPressed(mapping[12]) && changeChord == true) {
            changeChord = false;
          }
        } 
        else if(mapping[i] == mapping[13]) {
          if(trellis.justPressed(mapping[13]) && majorMinor == false) {
            majorMinor = true; 
          } 
          
          else if(trellis.justPressed(mapping[13]) && majorMinor == true) {
              majorMinor = false;
          }
        } 
        else if(mapping[i] == mapping[14]) {
          if(trellis.justPressed(mapping[14]) && complexityMode == false) {
            complexityMode = true;
          } 
          else if(trellis.justPressed(mapping[14]) && complexityMode == true) {
            complexityMode = false;
          }
        } else if (mapping[i] == mapping[15]) {
          if(trellis.justPressed(mapping[15])) {
            if (invertionMode == 3) {
              Serial.println(invertionMode);
              invertionMode = 0;
            } else {
              Serial.println(invertionMode);
              invertionMode++;
            }
          }
        } else {
          // if in change scale mode
          if(changeChord) {
              if(mapping[i] != mapping[14] && mapping[i] != mapping[15] && mapping[i] != mapping[13] && mapping[i] != mapping[12]) {
                  trellis.setLED(mapping[i]);
                  if(trellis.justPressed(mapping[i])) {
                    scale = i;
                    changeChord = false;
                    Serial.println(i);
                  }
              }
           } else if (complexityMode) {
            if (mapping[i] == mapping[0] || mapping[i] == mapping[1] || mapping[i] == mapping[2]) {
              trellis.setLED(mapping[i]);
              if(trellis.justPressed(mapping[i])) {
                complexity = i;
                complexityMode = false;
                Serial.println(i);
               }
            }
           } else {
            if(mapping[i] != mapping[14] && mapping[i] != mapping[15] && mapping[i] != mapping[13] && mapping[i] != mapping[12]) {
            trellis.clrLED(mapping[i]);
              if (trellis.justPressed(mapping[i])) {
                // Serial.println(i);
                chordPressed = true;
                chord = i;
                trellis.setLED(mapping[i]);
               } 
                // if it was released, turn it off
              if (trellis.justReleased(mapping[i])) {
                
                stopChord(selectChord(i, 0, majorMinor, scale), octaveVal); 
                trellis.clrLED(mapping[i]);
              }
            }
          }
        }
      }
     }
     
    if(majorMinor) {
      trellis.setLED(mapping[13]);
    }
    else{
      trellis.clrLED(mapping[13]);
    }
    
    trellis.writeDisplay();  
  }

void playChord(int *chord, int delayValue, int randomVal, int octaveVal, int invertionMode) {  
  int velocity1 = random(100-randomVal, 100);
  int rootNote = (octaveVal*12) + chord[0];
  if (invertionMode == 1) {
    rootNote = rootNote + 12;    
  }
  usbMIDI.sendNoteOn(rootNote, velocity1, channel);
  delay(delayValue);
  
  int velocity2 = random(100-randomVal, 100);
  int secondNote = (octaveVal*12) + chord[1];
  if (invertionMode == 2) {
    secondNote = secondNote + 12;
  }
  
  usbMIDI.sendNoteOn(secondNote, velocity2, channel);
  delay(delayValue);
  
  int velocity3 = random(100-randomVal, 100);
  int thirdNote = (octaveVal*12) + chord[2];
  if (invertionMode == 3) {
    thirdNote = thirdNote - 12;
  }
  
  usbMIDI.sendNoteOn(thirdNote, velocity3, channel);
  
  if(complexity > 0) {
    playComplexityNote(chord, complexity, delayValue);
  }

  delay(delayValue);
}

void playComplexityNote(int *chord, int complexity, int delayValue) {
  if (chord[3] == 0) {
    if(complexity == 1) {
        int fourthNote = ((octaveVal*12) + chord[2]) + 4;
        int velocity4 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fourthNote, velocity4, channel);
    }
    
    if (complexity == 2) {
        int fourthNote = ((octaveVal*12) + chord[2]) + 4;
        int velocity4 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fourthNote, velocity4, channel);

        int fifthNote = fourthNote + 3;
        int velocity5 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fifthNote, velocity5, channel);
    }
  }
  
  if (chord[3] == 1) {
    if (complexity == 1) {
        int fourthNote = ((octaveVal*12) + chord[2]) + 3;
        int velocity4 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fourthNote, velocity4, channel);
    }
    
    if (complexity == 2) {
        int fourthNote = ((octaveVal*12) + chord[2]) + 3;
        int velocity4 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fourthNote, velocity4, channel);

        int fifthNote = fourthNote + 4;
        int velocity5 = random(100-randomVal, 100);
        delay(delayValue);
        usbMIDI.sendNoteOn(fifthNote, velocity5, channel);
    }
  }
}

void stopChord(int *chord, int octaveVal) {   
  int rootNote = (octaveVal*12) + chord[0];
  if (invertionMode == 1) {
    rootNote = rootNote + 12;    
  }
  usbMIDI.sendNoteOff(rootNote, 0, channel);

  int secondNote = (octaveVal*12) + chord[1];
  if (invertionMode == 2) {
    secondNote = secondNote + 12;    
  }
  usbMIDI.sendNoteOff(secondNote, 0, channel);

  int thirdNote = (octaveVal*12) + chord[2];
  if (invertionMode == 3) {
    thirdNote = thirdNote - 12;    
  }
  usbMIDI.sendNoteOff(thirdNote, 0, channel);

  if(complexity > 0)
  {
    if(chord[3] == 0) 
    {
      if(complexity == 1)
      {
          int fourthNote = ((octaveVal*12) + chord[2]) + 4;
          usbMIDI.sendNoteOff(fourthNote, 0, channel);
      }
      if(complexity == 2)
      {
          int fourthNote = ((octaveVal*12) + chord[2]) + 4;
          usbMIDI.sendNoteOff(fourthNote, 0, channel);

          int fifthNote = fourthNote + 3;
          usbMIDI.sendNoteOff(fifthNote, 0, channel);
      }
    }
    if(chord[3] == 1)
    {
      if(complexity == 1)
      {
          int fourthNote = ((octaveVal*12) + chord[2]) + 3;
          usbMIDI.sendNoteOff(fourthNote, 0, channel);
      }
      if(complexity == 2)
      {
          int fourthNote = ((octaveVal*12) + chord[2]) + 3;
          usbMIDI.sendNoteOff(fourthNote, 0, channel);

          int fifthNote = fourthNote + 4;
          usbMIDI.sendNoteOff(fifthNote, 0, channel);
      }
    } 
  }
}

void stopComplexityNote() {
  
}


int * selectChord(int i, float velocity, bool isMajor, int scale) {
  if (isMajor) {    
    switch (scale) {
        case 0:
            switch (i) {
              case 0:
                return Cmaj;
                break;
              case 1:
                return Dmin;
                break;
              case 2:
                return Emin;
                break;
              case 3:
                return Fmaj;
                break;
              case 4:
                return Gmin;
                break;
              case 5:
                return Amin;
                break;
              case 6:
                return Bdim;
                break;
              case 7:
                return Cmaj2;
                break;
              case 8:
                return Dmin2;
                break;
              case 9:
                return Emin2;
                break;
              case 10:
                return Fmaj2;
                break;
              case 11:
                return Gmin2;
                break;
              default:
                return Cmin;
                break;
            }
            break;
        case 1:
            switch (i) {
              case 0:
                return Csmaj;
                break;
              case 1:
                return Dsmin;
                break;
              case 2:
                return Fmin;  
                break;
              case 3:
                return Fsmaj;  
                break;
              case 4:
                return Gsmin;  
                break;
              case 5:
                return Asmin;  
                break;
              case 6:
                return Cdim;  
                break;
              case 7:
                return Csmaj2;  
                break;
              case 8:
                return Dsmin2;  
                break;
              case 9:
                return Fmin2;  
                break;
              case 10:
                return Fsmaj2;  
                break;
              case 11:
                return Gsmin2;  
                break;
              default:
                return Csmaj;
                break;
            }
            
            break;
        case 2:
            switch (i) {
              case 0:
                  return Dmaj;
                  break;
              case 1:
                  return Emin;
                  break;
              case 2:
                  return Fsmin;
                  break;
              case 3:
                  return Gmaj;
                  break;
              case 4:
                  return Amaj;
                  break;
              case 5:
                  return Bmin;
                  break;
              case 6:
                  return Csdim;
                  break;
              case 7:
                  return Dmaj2;
                  break;
              case 8:
                  return Emin2;
                  break;
              case 9:
                  return Fsmin2;
                  break;
              case 10:
                  return Gmaj2;
                  break;
              case 11:
                  return Amaj2;
                  break;
              default:
                return Dmaj;
                break;
            }
            
            break;
        case 3:
            switch (i) {
              case 0:
                return Dsmaj;
                break;
              case 1:
                return Fmin;
                break;  
              case 2:
                return Gmin;
                break;  
              case 3:
                return Gsmaj;
                break;  
              case 4:
                return Asmaj;
                break;  
              case 5:
                return Ddim;
                break;  
              case 6:
                return Ddim;
                break;  
              case 7:
                return Dsmaj2;
                break;  
              case 8:
                return Emin2;
                break;  
              case 9:
                return Fsmin2;
                break;  
              case 10:
                return Gmaj2;
                break;  
              case 11:
                return Amaj2;
                break; 
              default:
                return Dsmaj;
                break;
            }
            
            break;
        case 4:
            switch (i) {
              case 0:
                return Emaj;
                break;  
              case 1:
                return Fsmin;
                break;  
              case 2:
                return Gsmin;
                break;  
              case 3:
                return Amaj;
                break;  
              case 4:
                return Bmaj;
                break;  
              case 5:
                return Csmin;
                break;  
              case 6:
                return Dsdim;
                break;  
              case 7:
                return Emaj2;
                break;  
              case 8:
                return Fsmin2;
                break;  
              case 9:
                return Gsmin2;
                break;  
              case 10:
                return Amaj2;
                break;  
              case 11:
                return Bmaj2;
                break;  
              default:
                return Emaj;
                break;
            }
            
            break; 
        case 5:
            switch (i) {
              case 0:
                return Fmaj;
                break;  
              case 1:
                return Gmin;
                break; 
              case 2:
                return Amin;
                break; 
              case 3:
                return Asmaj;
                break; 
              case 4:
                return Cmaj;
                break; 
              case 5:
                return Dmin;
                break; 
              case 6:
                return Edim;
                break; 
              case 7:
                return Fmaj2;
                break;
              case 8:
                return Gmin2;
                break; 
              case 9:
                return Amin2;
                break; 
              case 10:
                return Asmaj2;
                break; 
              case 11:
                return Cmaj2;
                break; 
              default:
                return Fmaj;
                break;
            }
            
            break;
        case 6:
            switch (i) {
              case 0:
                return Fsmaj;
                break;  
              case 1:
                return Gsmin;
                break;
              case 2:
                return Asmin;
                break;  
              case 3:
                return Bmaj;
                break;
              case 4:
                return Csmaj; 
                break;
              case 5:
                return Dsmin;
                break; 
              case 6:
                return Fdim;
                break;
              case 7:
                return Fsmaj2; 
                break;
              case 8:
                return Gsmin2;
                break;
              case 9:
                return Asmin2; 
                break;
              case 10:
                return Bmaj2;
                break;
              case 11:
                return Csmaj2; 
                break;
              default:
                return Fsmaj;
                break;
            }
            break;
        case 7:
            switch (i) {
              case 0:
                return Gmaj;
                break;
              case 1:
                return Amin;
                break;
              case 2:
                return Bmin;
                break;    
              case 3:
                return Cmaj;
                break;
              case 4:
                return Dmaj;
                break;
              case 5:
                return Emin;
                break;
              case 6:
                return Fsdim;
                break;
              case 7:
                return Gmaj2;
                break;
              case 8:
                return Amin2;
                break;
              case 9:
                return Bmin2;
                break;
              case 10:
                return Cmaj2;
                break;
              case 11:
                return Dmaj2;
                break;
              default:
                return Gmaj;
                break;
            }
            
            break;
        case 8:
            switch (i) {
              case 0:
                return Gsmaj;
                break;
              case 1:
                return Asmin;
                break;    
              case 2:
                return Cmin;
                break;
              case 3:
                return Csmaj;
                break;
              case 4:
                return Dsmaj;
                break;                  
              case 5:
                return Fmin;
                break;
              case 6:
                return Gdim;
                break;
              case 7:
                return Gsmaj2;
                break;
              case 8:
                return Asmin2;
                break;
              case 9:
                return Cmin2;
                break;
              case 10:
                return Csmaj2;
                break;
              case 11:
                return Dsmaj2;
                break;
              default:
                return Gsmaj;
                break;
            }
            
            break;
        case 9:
            switch (i) {
              case 0:
                return Amaj;
                break;
              case 1:
                return Bmin;
                break;    
              case 2:
                return Csmin;
                break;
              case 3:
                return Dmaj;
                break;
              case 4:
                return Emaj;
                break;
              case 5:
                return Fsmin;
                break;
              case 6:
                return Gsdim;
                break;
              case 7:
                return Amaj2;
                break;
              case 8:
                return Bmin2;
                break;
              case 9:
                return Csmin2;
                break;
              case 10:
                return Dmaj2;
                break;
              case 11:
                return Emaj2;
                break;
              default:
                return Amaj;
                break;
            }
            
            break;
        case 10:
            switch (i) {
              case 0:
                return Asmaj;
                break;
              case 1:
                return Cmin;
                break;    
              case 2:
                return Dmin;
                break;
              case 3:
                return Dsmaj;
                break;
              case 4:
                return Fmaj;
                break;
              case 5:
                return Gmin;
                break;
              case 6:
                return Adim;
                break;
              case 7:
                return Asmaj2;
                break;
              case 8:
                return Cmin2;
                break;
              case 9:
                return Dmin2;
                break;
              case 10:
                return Dsmaj2;
                break;
              case 11:
                return Fmaj2;
                break;
              default:
                return Asmaj;
                break;
            }
            
            break;
        case 11:
            switch (i) {
              case 0:
                return Bmaj;
                break;
              case 1:
                return Csmin;
                break;    
              case 2:
                return Dsmin;
                break;
              case 3:
                return Emaj;
                break;
              case 4:
                return Fsmaj;
                break;    
              case 5:
                return Gsmin;
                break;    
              case 6:
                return Asdim;
                break;    
              case 7:
                return Bmaj2;
                break;    
              case 8:
                return Csmin2;
                break;    
              case 9:
                return Dsmin2;
                break;    
              case 10:
                return Emaj2;
                break;    
              case 11:
                return Fsmaj2;
                break;    
              default:
                return Bmaj;
                break;
            }
        default:
          return Cmaj;
          break;
        }
  } else {
    switch (scale) {
      case 0:
        switch (i) {
          case 0:
            return Cmin;
            break;
          case 1:
            return Ddim;
            break;
          case 2:
            return Dsmaj;
            break;
          case 3:
            return Fmin;
            break;
          case 4:
            return Gmin;
            break;
          case 5:
            return Gsmaj;
            break;
          case 6:
            return Asmaj;
            break; 
          case 7:
            return Cmin2;
            break;
          case 8: 
            return Ddim2; 
            break;
          case 9:
            return Dsmaj2;
            break;
          case 10:
            return Fmin2;
            break;
          case 11:
            return Gmin2;
            break;
          default:
            return Cmin;
            break;
        }
        
        break;
      case 1:
          switch (i) {
          case 0:
            return Csmin;
            break;
          case 1:
            return Dsdim;
            break;
          case 2:
            return Emaj;
            break;
          case 3:
            return Fsmin;
            break;
          case 4:
            return Gsmin;
            break;
          case 5:
            return Amaj;
            break;
          case 6:
            return Bmaj;
            break; 
          case 7:
            return Csmin2;
            break;
          case 8: 
            return Dsdim2; 
            break;
          case 9:
            return Fsmin2;
            break;
          case 10:
            return Gsmin2;
            break;
          case 11:
            return Gmin2;
            break;
          default:
            return Cmin;
            break;
        }
      
        break;
      case 2:
        switch (i) {
          case 0:
            return Dmin;
            break;
          case 1:
            return Edim;
            break;
          case 2:
            return Fmaj;
            break;
          case 3:
            return Gmin;
            break;
          case 4:
            return Amin;
            break;
          case 5:
            return Asmaj;
            break;
          case 6:
            return Cmaj;
            break; 
          case 7:
            return Dmin2;
            break;
          case 8: 
            return Edim2; 
            break;
          case 9:
            return Fmaj2;
            break;
          case 10:
            return Gmin2;
            break;
          case 11:
            return Amin2;
            break;
          default:
            return Dmin;
            break;
        }
        
        break;
      case 3:
        switch (i) {
            case 0:
              return Dsmin;
              break;
            case 1:
              return Fdim;
              break;
            case 2:
              return Fsmaj;
              break;
            case 3:
              return Gsmin;
              break;
            case 4:
              return Asmin;
              break;
            case 5:
              return Bmaj;
              break;
            case 6:
              return Csmaj;
              break; 
            case 7:
              return Dsmin2;
              break;
            case 8: 
              return Fdim2; 
              break;
            case 9:
              return Fsmaj2;
              break;
            case 10:
              return Gsmin2;
              break;
            case 11:
              return Asmin2;
              break;
            default:
              return Dsmin;
              break;
          }
          
        break;
      case 4:
          switch (i) {
            case 0:
              return Emin;
              break;
            case 1:
              return Fsdim;
              break;
            case 2:
              return Gmaj;
              break;
            case 3:
              return Amin;
              break;
            case 4:
              return Bmin;
              break;
            case 5:
              return Cmaj;
              break;
            case 6:
              return Dmaj;
              break; 
            case 7:
              return Emin2;
              break;
            case 8: 
              return Fsdim2; 
              break;
            case 9:
              return Gmaj2;
              break;
            case 10:
              return Amin2;
              break;
            case 11:
              return Bmin2;
              break;
            default:
              return Emin;
              break;
          }
          
        break;
      case 5:
          switch (i) {
            case 0:
              return Fmin;
              break;
            case 1:
              return Gdim;
              break;
            case 2:
              return Gsmaj;
              break;
            case 3:
              return Asmin;
              break;
            case 4:
              return Cmin;
              break;
            case 5:
              return Csmaj;
              break;
            case 6:
              return Dsmaj;
              break; 
            case 7:
              return Fmin2;
              break;
            case 8: 
              return Gdim2; 
              break;
            case 9:
              return Gsmaj2;
              break;
            case 10:
              return Asmin2;
              break;
            case 11:
              return Cmin2;
              break;
            default:
              return Fmin;
              break;
          }
          
        break;
      case 6:
          switch (i) {
            case 0:
              return Fsmin;
              break;
            case 1:
              return Gsdim;
              break;
            case 2:
              return Amaj;
              break;
            case 3:
              return Bmin;
              break;
            case 4:
              return Csmin;
              break;
            case 5:
              return Dmaj;
              break;
            case 6:
              return Emaj;
              break; 
            case 7:
              return Fsmin2;
              break;
            case 8: 
              return Gsdim2; 
              break;
            case 9:
              return Amaj2;
              break;
            case 10:
              return Bmin2;
              break;
            case 11:
              return Csmin2;
              break;
            default:
              return Fsmin;
              break;
          }
          
        break;
      case 7:
          switch (i) {
            case 0:
              return Gmin;
              break;
            case 1:
              return Adim;
              break;
            case 2:
              return Asmaj;
              break;
            case 3:
              return Cmin;
              break;
            case 4:
              return Dmin;
              break;
            case 5:
              return Dsmaj;
              break;
            case 6:
              return Fmaj;
              break; 
            case 7:
              return Gmin2;
              break;
            case 8: 
              return Adim2; 
              break;
            case 9:
              return Asmaj2;
              break;
            case 10:
              return Cmin2;
              break;
            case 11:
              return Dmin2;
              break;
            default:
              return Gmin;
              break;
          }
          
        break;
      case 8:
          switch (i) {
            case 0:
              return Gsmin;
              break;
            case 1:
              return Asdim;
              break;
            case 2:
              return Bmaj;
              break;
            case 3:
              return Csmin;
              break;
            case 4:
              return Dsmin;
              break;
            case 5:
              return Emaj;
              break;
            case 6:
              return Fsmaj;
              break; 
            case 7:
              return Gsmin2;
              break;
            case 8: 
              return Asdim2; 
              break;
            case 9:
              return Bmaj;
              break;
            case 10:
              return Csmin2;
              break;
            case 11:
              return Dsmin2;
              break;
            default:
              return Gsmin;
              break;
          }
          
        break;

      case 9:
          switch (i) {
            case 0:
              return Amin;
              break;
            case 1:
              return Bdim;
              break;
            case 2:
              return Cmaj;
              break;
            case 3:
              return Dmin;
              break;
            case 4:
              return Emin;
              break;
            case 5:
              return Fmaj;
              break;
            case 6:
              return Gmaj;
              break; 
            case 7:
              return Amin;
              break;
            case 8: 
              return Bdim2; 
              break;
            case 9:
              return Cmaj2;
              break;
            case 10:
              return Dmin2;
              break;
            case 11:
              return Emin2;
              break;
            default:
              return Amin;
              break;
          }
          
        break;
      case 10:
          switch (i) {
            case 0:
              return Asmin;
              break;
            case 1:
              return Cdim;
              break;
            case 2:
              return Csmaj;
              break;
            case 3:
              return Dsmin;
              break;
            case 4:
              return Fmin;
              break;
            case 5:
              return Fsmaj;
              break;
            case 6:
              return Gsmaj;
              break; 
            case 7:
              return Asmin2;
              break;
            case 8: 
              return Cdim2; 
              break;
            case 9:
              return Csmaj2;
              break;
            case 10:
              return Dsmin2;
              break;
            case 11:
              return Fmin2;
              break;
            default:
              return Asmin;
              break;
          }
          
        break;
      case 11:
          switch (i) {
            case 0:
              return Bmin;
              break;
            case 1:
              return Csdim;
              break;
            case 2:
              return Dmaj;
              break;
            case 3:
              return Emin;
              break;
            case 4:
              return Fsmin;
              break;
            case 5:
              return Gmaj;
              break;
            case 6:
              return Amaj;
              break; 
            case 7:
              return Bmin2;
              break;
            case 8: 
              return Csdim2; 
              break;
            case 9:
              return Dmaj2;
              break;
            case 10:
              return Emin2;
              break;
            case 11:
              return Fsmin2;
              break;
            default:
              return Bmin;
              break;
          }
          
        break;
      default:
        return Cmaj;
        break;
    }
  }
}
