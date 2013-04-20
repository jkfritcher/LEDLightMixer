
#include "LightMixer.h"
#include "time.h"
#include "status.h"

/* Circular buffers to hold data to and from the USB and USART devices. */
//static RingBuffer_t USB_In_Buffer;
//static uint8_t      USB_In_Buffer_Data[64];

//static RingBuffer_t USB_Out_Buffer;
//static uint8_t      USB_Out_Buffer_Data[64];

//static RingBuffer_t USART_In_Buffer;
//static uint8_t      USART_In_Buffer_Data[64];

//static RingBuffer_t USART_Out_Buffer;
//static uint8_t      USART_Out_Buffer_Data[64];

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t LightMixer_CDC_Interface =
    {
        .Config =
            {
                .ControlInterfaceNumber         = 0,
                .DataINEndpoint                 =
                    {
                        .Address                = CDC_TX_EPADDR,
                        .Size                   = CDC_TXRX_EPSIZE,
                        .Banks                  = 1,
                    },
                .DataOUTEndpoint                =
                    {
                        .Address                = CDC_RX_EPADDR,
                        .Size                   = CDC_TXRX_EPSIZE,
                        .Banks                  = 1,
                    },
                .NotificationEndpoint           =
                    {
                        .Address                = CDC_NOTIFICATION_EPADDR,
                        .Size                   = CDC_NOTIFICATION_EPSIZE,
                        .Banks                  = 1,
                    },
            },
    };

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
    SetupHardware();

    //RingBuffer_InitBuffer(&USB_In_Buffer, USB_In_Buffer_Data, sizeof(USB_In_Buffer_Data));
    //RingBuffer_InitBuffer(&USB_Out_Buffer, USB_Out_Buffer_Data, sizeof(USB_Out_Buffer_Data));
    //RingBuffer_InitBuffer(&USART_In_Buffer, USART_In_Buffer_Data, sizeof(USART_In_Buffer_Data));
    //RingBuffer_InitBuffer(&USART_Out_Buffer, USART_Out_Buffer_Data, sizeof(USART_Out_Buffer_Data));

    sei();

    status_led_change_status(STATUS_IDLE);
    millis_t now;
    for (;;)
    {
        now = millis_get();
        status_led_update(now);

        if ((PINB & (1 << PORTB4)) != 0) {
            OCR1A = 0; /* blue */
            OCR1B = 0; /* green */
            OCR1C = 0; /* red */
        } else {
            OCR1A = 127; /* blue */
            OCR1B = 127; /* green */
            OCR1C = 127; /* red */
        }

        /* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
        CDC_Device_ReceiveByte(&LightMixer_CDC_Interface);

        CDC_Device_USBTask(&LightMixer_CDC_Interface);
        USB_USBTask();
    }
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Scale system clock down to 1 MHz */
    clock_prescale_set(clock_div_16);

    /* Setup elapsed time timer */
    init_elapsed_timer();

    /* Init status LED */
    status_led_init();

    /* Setup Timer 1A-C for PWM mode */
    DDRB |= (1 << DDB7) | (1 << DDB6) | (1 << DDB5); /* Set B5-7 as outputs */
    PORTB &= ~((1 << PORTB7) | (1 << PORTB6) | (1 << PORTB5)); /* Disable pull-ups */
    /* PWM, Phase correct, 8-bit, CLK_IO / 8, PWM @ 245.1 Hz */
    TCCR1B = (1 << CS11);
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM10);
    OCR1A = 0; /* blue */
    OCR1B = 0; /* green */
    OCR1C = 0; /* red */

    /* Init switch input */
    DDRB &= ~(1 << DDB4); /* Set B4 as input */
    PORTB |= (1 << PORTB4); /* Enable pull-up */

    /* Hardware Initialization */
    USB_Init();

    /* Configure unused pins as inputs with a pull-up */
    DDRB &= ~((1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0));
    PORTB |= (1 << PORTB3) | (1 << PORTB2) | (1 << PORTB1) | (1 << PORTB0);
    DDRC = 0;
    PORTC = (1 << PORTC7) | (1 << PORTC6);
    DDRD &= ~((1 << DDD7) | (1 << DDD6) | (1 << DDD5) |
              (1 << DDD4) | (1 << DDD1) | (1 << DDD0));
    PORTD |= (1 << PORTD7) | (1 << PORTD6) | (1 << PORTD5) |
             (1 << PORTD4) | (1 << PORTD1) | (1 << PORTD0);
    DDRF = 0;
    PORTF = (1 << PORTF7) | (1 << PORTF6) | (1 << PORTF5) |
            (1 << PORTF4) | (1 << PORTF1) | (1 << PORTF0);
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
    CDC_Device_ConfigureEndpoints(&LightMixer_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
    CDC_Device_ProcessControlRequest(&LightMixer_CDC_Interface);
}
