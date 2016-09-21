
/*Operation:
Sends string to terminal
enters a loop waiting for user to input the hour
enters a loop waiting for user to iput the minute
enters the infinite for loop
Reads the current counter value of the pwm module which is set to change every second
the sec veriable gets incremented every second.
A series of if statements increment the time that was input by the user
Each second the time is printed to the serial monitor.*/

#include <project.h>//What's the diff btw <> and "" ?
#include "stdio.h"


int main()
{
    //Start modules
    PWM_Start();
    UART_Start();
    
    //Declare variables
    uint8 Clk_1;
    uint8 Clk_2;
    uint8 sec;
    uint8 min[2] = {0};
    uint8 hr[2] = {0};
    uint8 sec_comp;
  
    //Initialize variables
    char TransmitBuffer[20];//Array w/ 8 indices//This must be big enough to store string. 16 is not large enough.
    
    //Initial user prompt
    UART_PutString("Enter the time when prompted \n\r");  
    
    //Get hour
    UART_PutString("Please enter the hour: \n\r");//Might want to store inputs as an array
    do{hr[0] = UART_GetChar();}while(hr[0] == 0);
    UART_PutChar(hr[0]);
    do{hr[1] = UART_GetChar();}while(hr[1] == 0);
    UART_PutChar(hr[1]);
    UART_PutString("\n\r");  

    //Get minute
    UART_PutString("Please enter the minute: \n\r");
    do{min[0] = UART_GetChar();}while(min[0] == 0);
    UART_PutChar(min[0]);
    do{min[1] = UART_GetChar();}while(min[1] == 0);
    UART_PutChar(min[1]);
    UART_PutString("\n\r");  
    
    for(;;)//Infinite loop
    {    
        Clk_1 = PWM_ReadCounter();//This will count the seconds//Counts down for some reason
        
        if (Clk_1 != Clk_2)
        {
            sec++;
            if(sec==60){min[1]++;sec=0;}
            if(min[1]==58){min[0]++; min[1]=48;}//have to use ascii equivalents for minute and hour
            if(min[0]==54){hr[1]++; min[0]=48;}
            if(hr[1]==51){hr[0]=48; hr[1]=49;}
            
            sprintf(TransmitBuffer, "Time: %c%c:%c%c:%d\r\n",hr[0],hr[1],min[0],min[1],sec);
           // sprintf(TransmitBuffer, "Time: %c %d\r\n",min[1],sec);
            
            UART_PutString(TransmitBuffer);
            Clk_2 = PWM_ReadCounter();
        }  
    }
}

