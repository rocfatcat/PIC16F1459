/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "usb.h"
#include "usb_device_hid.h"
#include "inc/app_device_custom_hid.h"
#include <string.h>
#include "mcc_generated_files/mcc.h"
/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata HID_CUSTOM_OUT_DATA_BUFFER = HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS
        unsigned char ReceivedDataBuffer[64];
        #pragma udata HID_CUSTOM_IN_DATA_BUFFER = HID_CUSTOM_IN_DATA_BUFFER_ADDRESS
        unsigned char ToSendDataBuffer[64];
        #pragma udata

    #elif defined(__XC8)
        unsigned char ReceivedDataBuffer[64] HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
        unsigned char ToSendDataBuffer[64] HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;
    #endif
#else
    unsigned char ReceivedDataBuffer[64];
    unsigned char ToSendDataBuffer[64];
#endif

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;
volatile static uint32_t dac_value =0;

/** DEFINITIONS ****************************************************/
typedef enum
{
    COMMAND_TOGGLE_LED = 0x80,
    COMMAND_GET_BUTTON_STATUS = 0x81,
    COMMAND_WRITE_DAC_POTENTIOMETER = 0x82,
    COMMAND_READ_POTENTIOMETER = 0x37,
    COMMAND_READ_DAC_POTENTIOMETER = 0x38,
} CUSTOM_HID_DEMO_COMMANDS;

/** FUNCTIONS ******************************************************/
#define MCP4725_I2CADDR_DEFAULT (0x60) ///< Default i2c address
#define MCP4725_CMD_WRITEDAC (0x40)    ///< Writes data to the DAC
#define MCP4725_CMD_WRITEDACEEPROM (0x60) 
void MCP4725_Init(void)
{
    uint8_t i=0;
    uint8_t sendData[17] = {0x00,0x00,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF};
    uint8_t receiveData[15];
    i2c_writeNBytes(MCP4725_I2CADDR_DEFAULT,sendData,sizeof(sendData)); // Writes sendData[] to EEPROM
}
void MCP4725_SetVoltage(uint16_t output, bool writeEEPROM  )
{
  uint8_t packet[3];

  if (writeEEPROM) {
    packet[0] = MCP4725_CMD_WRITEDACEEPROM;
  } else {
    packet[0] = MCP4725_CMD_WRITEDAC;
  }
  packet[1] = output / 16;        // Upper data bits (D11.D10.D9.D8.D7.D6.D5.D4)
  packet[2] = (output % 16) << 4; // Lower data bits (D3.D2.D1.D0.x.x.x.x)

  i2c_writeNBytes(MCP4725_I2CADDR_DEFAULT,packet,sizeof(packet));
}
/*********************************************************************
* Function: void APP_DeviceCustomHIDInitialize(void);
*
* Overview: Initializes the Custom HID demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDInitialize()
{
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,(uint8_t*)&ReceivedDataBuffer[0],64);
}

/*********************************************************************
* Function: void APP_DeviceCustomHIDTasks(void);
*
* Overview: Keeps the Custom HID demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_DeviceCustomHIDInitialize() and APP_DeviceCustomHIDStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_DeviceCustomHIDTasks()
{   
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
    
    //Check if we have received an OUT data packet from the host
    if(HIDRxHandleBusy(USBOutHandle) == false)
    {   
        //We just received a packet of data from the USB host.
        //Check the first uint8_t of the packet to see what command the host
        //application software wants us to fulfill.
        switch(ReceivedDataBuffer[0])				//Look at the data the host sent, to see what kind of application specific command it sent.
        {
            case COMMAND_TOGGLE_LED:  //Toggle LEDs command
                //LED_Toggle(LED_USB_DEVICE_HID_CUSTOM);
                LED0_Toggle();
                break;
            case COMMAND_GET_BUTTON_STATUS:  //Get push button state
                //Check to make sure the endpoint/buffer is free before we modify the contents
                if(!HIDTxHandleBusy(USBInHandle))
                {
                    ToSendDataBuffer[0] = 0x81;				//Echo back to the host PC the command we are fulfilling in the first uint8_t.  In this case, the Get Pushbutton State command.
#if 0
                    if(BUTTON_IsPressed(BUTTON_USB_DEVICE_HID_CUSTOM) == false)	//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
                    {
                            ToSendDataBuffer[1] = 0x01;
                    }
                    else									//sw3 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                            ToSendDataBuffer[1] = 0x00;
                    }
#endif
                    if(PORTAbits.RA3 == 1)
                    {
                            ToSendDataBuffer[1] = 0x01;
                    }
                    else									//sw3 must be == 0, pushbutton is pressed and overpowering the pull up resistor
                    {
                            ToSendDataBuffer[1] = 0x00;
                    }
                    //Prepare the USB module to send the data packet to the host
                    USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                }
                break;
            case COMMAND_WRITE_DAC_POTENTIOMETER:
                {
                    dac_value = ReceivedDataBuffer[1] | ReceivedDataBuffer[2] <<8;
                    MCP4725_SetVoltage(dac_value,false);
                }
                break;
            case COMMAND_READ_POTENTIOMETER:	//Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host
                {
                    uint16_t pot;

                    //Check to make sure the endpoint/buffer is free before we modify the contents
                    if(!HIDTxHandleBusy(USBInHandle))
                    {
                        //Use ADC to read the I/O pin voltage.  See the relevant HardwareProfile - xxxxx.h file for the I/O pin that it will measure.
                        //Some demo boards, like the PIC18F87J50 FS USB Plug-In Module board, do not have a potentiometer (when used stand alone).
                        //This function call will still measure the analog voltage on the I/O pin however.  To make the demo more interesting, it
                        //is suggested that an external adjustable analog voltage should be applied to this pin.

//                        pot = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);

                        ToSendDataBuffer[0] = 0x37;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
//                        ToSendDataBuffer[1] = (uint8_t)pot; //LSB
//                        ToSendDataBuffer[2] = pot >> 8;     //MSB
                        ToSendDataBuffer[1] = 0x00;
                        ToSendDataBuffer[2] = 0x01;

                        //Prepare the USB module to send the data packet to the host
                        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                    }
                }
                break;
            case COMMAND_READ_DAC_POTENTIOMETER:	//Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host
                    //Check to make sure the endpoint/buffer is free before we modify the contents
                    if(!HIDTxHandleBusy(USBInHandle))
                    {
                        //Use ADC to read the I/O pin voltage.  See the relevant HardwareProfile - xxxxx.h file for the I/O pin that it will measure.
                        //Some demo boards, like the PIC18F87J50 FS USB Plug-In Module board, do not have a potentiometer (when used stand alone).
                        //This function call will still measure the analog voltage on the I/O pin however.  To make the demo more interesting, it
                        //is suggested that an external adjustable analog voltage should be applied to this pin.

//                        pot = ADC_Read10bit(ADC_CHANNEL_POTENTIOMETER);

                        ToSendDataBuffer[0] = 0x38;  	//Echo back to the host the command we are fulfilling in the first uint8_t.  In this case, the Read POT (analog voltage) command.
//                        ToSendDataBuffer[1] = (uint8_t)pot; //LSB
//                        ToSendDataBuffer[2] = pot >> 8;     //MSB
                        ToSendDataBuffer[1] = (uint8_t)dac_value;
                        ToSendDataBuffer[2] = dac_value >> 8;

                        //Prepare the USB module to send the data packet to the host
                        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);
                    }
                break;
        }
        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer[0], 64);
    }
}

void USB_Initialize( SYSTEM_STATE state )
{
    switch(state)
    {
        case SYSTEM_STATE_USB_START:
            #if defined(USE_INTERNAL_OSC)
                //Make sure to turn on active clock tuning for USB full speed 
                //operation from the INTOSC
                OSCCON = 0xFC;  //HFINTOSC @ 16MHz, 3X PLL, PLL enabled
                ACTCON = 0x90;  //Active clock tuning enabled for USB
            #endif
#if 0
            LED_Enable(LED_USB_DEVICE_STATE);
            LED_Enable(LED_USB_DEVICE_HID_CUSTOM);
            
            BUTTON_Enable(BUTTON_USB_DEVICE_HID_CUSTOM);
            
            ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
            ADC_Enable(ADC_CHANNEL_POTENTIOMETER);
#endif
            break;
            
        case SYSTEM_STATE_USB_SUSPEND: 
            break;
            
        case SYSTEM_STATE_USB_RESUME:
            break;
    }
}

