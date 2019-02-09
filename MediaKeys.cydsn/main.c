/*******************************************************************************
* File Name: Main.c
* Version 1.0
*
* Description:
* This file contains the main function for the USB HID Keyboard application.
*
* Note:
*
********************************************************************************
* Copyright (2009), Cypress Semiconductor Corporation. All rights reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign),United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating 
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement. 
*******************************************************************************/

/*************************************************************************************
                                THEORY OF OPERATION
* This project is a keyboard that when a user presses a button, will print a pre-defined 
* string into a text editor. The program is also constantly display the status of num lock,
* caps lock, and scroll lock on both LEDs and an LCD.
*
*************************************************************************************/

#include <device.h>
#include <ConsumerAPI.h>

void Check_User_Button(void);

int main()
{
    CYGlobalIntEnable;
	/*Start USBFS Operation and Device 0 and with 5V operation*/ 
	USBFS_1_Start(0, USBFS_1_DWR_VDDD_OPERATION);  
	/*Waits for USB to enumerate*/ 
	while(!USBFS_1_bGetConfiguration());   
	/*Begins USB Traffic for Media Keys*/
	ConsumerAPI_begin();
	
    for(;;)
    {
		/*Checks for ACK from host for Media Keys */
		if(USBFS_1_bGetEPAckState(1) != 0)
		{
			Check_User_Button();
		}
    }
    
    return 0;
}

void Check_User_Button (void)
{
    static uint8_t User_Button_Status, User_Button_Status_Previous = 0;
    
    User_Button_Status = User_Button_Read() == 0;

    // If the button was pressed but it is now released.
    if (User_Button_Status_Previous == 1 && User_Button_Status == 0) {
        // Send the WWWBack button
        ConsumerAPI_write(HID_CONSUMER_AC_BACK);
        LED_Pin_Write(User_Button_Status);
    } else {
        // Otherwise release all keys
        ConsumerAPI_releaseAll();
    }
    
    User_Button_Status_Previous = User_Button_Status;
}

/* End of File */

