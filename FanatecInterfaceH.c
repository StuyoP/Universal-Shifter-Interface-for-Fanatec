/*
 * File:   FanatecInterfaceH.c
 * Author: Stuyo
 *
 * Created on September 15, 2022, 3:49 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000

#pragma config FOSC=INTRCIO, WDTE=OFF, PWRTE=OFF, MCLRE=OFF, CP=OFF, \
                CPD=OFF, BOREN=OFF, IESO=OFF, FCMEN=OFF

#define G1      PORTAbits.RA4 //1st Gear switch
#define G2	    PORTAbits.RA3 //2nd Gear switch
#define G3	    PORTCbits.RC5 //3rd Gear switch
#define G4	    PORTCbits.RC4 //4th Gear switch
#define G5	    PORTCbits.RC3 //5th Gear switch
#define G6	    PORTCbits.RC6 //6th Gear switch
#define G7	    PORTCbits.RC7 //7th Gear switch
#define GR	    PORTBbits.RB7 //Reverse Gear switch

#define Y1      PORTAbits.RA0 //Y-Axis LOW (900Ohm)
#define Y2      PORTAbits.RA1 //Y-Axis MED (4.7K)
#define Y3      PORTAbits.RA2 //Y-Axis HIGH (20K)
#define X1      PORTCbits.RC1 //X-Axis LOW (direct connection)
#define X2      PORTCbits.RC2 //X-Axis LOW-MED (2.2K)
#define X3      PORTBbits.RB4 //X-Axis MED (4.2K)
#define X4      PORTBbits.RB5 //X-Axis MED-HIGH (6.2K)
#define X5      PORTBbits.RB6 //X-Axis HIGH (10K)

int main()
{
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0b00111000; //RA0,1,2 - Digital Outputs; RA3,4,5 - Digital Input; RA6,7 - N/A
    TRISB = 0b10000000; //RB4,5,6 - Digital Outputs; RB7 - Digital Input; RB0,1,2,3 - N/A
    TRISC = 0b11111000; //RC0,1,2 - Digital Outputs; Rc3,4,5,6,7 - Digital Input
    
    //Define starting reference point for Neutral
    Y2 = 1; //Set Y-Axis in Neutral Position
    X3 = 1; //Set X-Axis in Neutral Position



    while(1){

        if(G1==1){                                  //While 1st Gear Button Active
			Y1 = 1; Y2 = 0; Y3 = 0;                 //Y-LOW
			X1 = 0; X2 = 1; X3 = 0; X4 = 0; X5 = 0; //X-LOW-MED
        }
		
        else if(G2==1){                             //While 2nd Gear Button Active
			Y1 = 0; Y2 = 0; Y3 = 1;                 //Y-HIGH
			X1 = 0; X2 = 1; X3 = 0; X4 = 0; X5 = 0; //X-LOW-MED 
        }

        else if(G3==1){                             //While 3rd Gear Button Active 
			Y1 = 1; Y2 = 0; Y3 = 0;                 //Y-LOW
			X1 = 0; X2 = 0; X3 = 1; X4 = 0; X5 = 0; //X-MED  
		}
        
        else if(G4==1){                             //While 4th Gear Button Active
			Y1 = 0; Y2 = 0; Y3 = 1;                 //Y-HIGH
			X1 = 0; X2 = 0; X3 = 1; X4 = 0; X5 = 0; //X-MED 
        }
        
        else if(G5==1){                             //While 5th Gear Button Active
			Y1 = 1; Y2 = 0; Y3 = 0;                 //Y-LOW
			X1 = 0; X2 = 0; X3 = 0; X4 = 1; X5 = 0; //X-MED-HIGH
        }
        
        else if(G6==1){                             //While 6th Gear Button Active
			Y1 = 0; Y2 = 0; Y3 = 1;                 //Y-HIGH
			X1 = 0; X2 = 0; X3 = 0; X4 = 1; X5 = 0; //X-MED-HIGH   
        }
        
        else if(G7==1){                             //While 7th Gear Button Active
			Y1 = 1; Y2 = 0; Y3 = 0;                 //Y-LOW
			X1 = 0; X2 = 0; X3 = 0; X4 = 0; X5 = 1; //X-HIGH
        }
        
        else if(GR==1){                             //While Reverse Gear Button Active
			Y1 = 1; Y2 = 0; Y3 = 0;                 //Y-LOW
			X1 = 1; X2 = 0; X3 = 0; X4 = 0; X5 = 0; //X-LOW
        }
        
        else{                                       //Return all switches in Neutral Position
			Y1 = 0; Y2 = 1; Y3 = 0;                 //Y-MED
			X1 = 0; X2 = 0; X3 = 1; X4 = 0; X5 = 0; //X-MED
		}
    }
    return 0;
}