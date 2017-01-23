#ifndef CAU_BATTLED_ONLYWRAPPER_H
#define CAU_BATTLED_ONLYWRAPPER_H

// Initialize the battery LED
void CAU_BattLED_Init(uint8_T ledNum);
// Turn the LED ON or OFF, (1 or 0)
void CAU_BattLED_SetValue(uint8_T ledNum, uint8_T ledVal);
// read the status of the battery LED
uint8_T CAU_BattLED_GetValue(uint8_T ledNum);
// Free dynamically allocated memory
void CAU_BattLED_Terminate(uint8_T ledNum);

// Initialize all of the battery LEDs
void CAU_BattLEDs_Init();
void CAU_BattLEDs_ShowState(int stateIndex, int errState, int stateSwitchNotice) ;
void CAU_BattLEDs_Terminate();
#endif