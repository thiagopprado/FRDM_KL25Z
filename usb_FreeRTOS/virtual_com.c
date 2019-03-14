/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 - 2015 Freescale Semiconductor;
 * All Rights Reserved
 *
 * Copyright (c) 1989-2008 ARC International;
 * All Rights Reserved
 *
 *************************************************************************** 
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************
 *
 * $FileName: virtual_com.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief  The file emulates a USB PORT as RS232 PORT.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "sistemaDinamico.h"

#include "gpio_x.h"
#include "serialProtocol.h"
#include "adc.h"
#include "dac.h"

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "virtual_com.h"


#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_port_hal.h"

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#if USBCFG_DEV_KEEP_ALIVE_MODE
#include "fsl_usb_khci_hal.h"

#if (FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED == 0)
    #error The keep alive feature can not be enabled in this platform, due to the SOC unsupports this feature.
#endif
#include "fsl_power_manager.h"
#endif
#endif

#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
static uint8_t waitfordatareceive =0;
static uint8_t comopen = 0;

typedef enum lpmode_number
{
    kDemoWait,
    kDemoStop,
    kDemoVlpr,
    kDemoVlpw,
    kDemoVlps,
    kDemoLls,
    kDemoVlls0,
    kDemoVlls1,
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE2
    kDemoVlls2,
#endif
    kDemoVlls3,
}lpmode_number_t;

power_manager_user_config_t vlprConfig;
power_manager_user_config_t vlpwConfig;
power_manager_user_config_t vlls0Config;
power_manager_user_config_t vlls1Config;
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE2
power_manager_user_config_t vlls2Config;
#endif
power_manager_user_config_t vlls3Config;
power_manager_user_config_t llsConfig;
power_manager_user_config_t vlpsConfig;
power_manager_user_config_t waitConfig;
power_manager_user_config_t stopConfig;

power_manager_user_config_t const *powerConfigs[] =
{   &waitConfig, &stopConfig,
    &vlprConfig, &vlpwConfig, &vlpsConfig, &llsConfig, &vlls0Config,
    &vlls1Config,
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE2
    &vlls2Config,
#endif
    &vlls3Config};
#endif
#endif
/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void TestApp_Init(void);

/****************************************************************************
 * Global Variables
 ****************************************************************************/
extern usb_desc_request_notify_struct_t desc_callback;
extern uint8_t USB_Desc_Set_Speed(uint32_t handle, uint16_t speed);
cdc_handle_t g_app_handle;

xQueueHandle receiveQueue = NULL;
TaskHandle_t handleSist = NULL;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void USB_App_Device_Callback(uint8_t event_type, void* val, void* arg);
uint8_t USB_App_Class_Callback(uint8_t event, uint16_t value, uint8_t ** data, uint32_t* size, void* arg);
/*****************************************************************************
 * Local Variables 
 *****************************************************************************/
uint8_t g_line_coding[LINE_CODING_SIZE] =
{
    /*e.g. 0x00,0x10,0x0E,0x00 : 0x000E1000 is 921600 bits per second */
    (LINE_CODE_DTERATE_IFACE >> 0) & 0x000000FF,
    (LINE_CODE_DTERATE_IFACE >> 8) & 0x000000FF,
    (LINE_CODE_DTERATE_IFACE >> 16) & 0x000000FF,
    (LINE_CODE_DTERATE_IFACE >> 24) & 0x000000FF,
    LINE_CODE_CHARFORMAT_IFACE,
    LINE_CODE_PARITYTYPE_IFACE,
    LINE_CODE_DATABITS_IFACE
};

uint8_t g_abstract_state[COMM_FEATURE_DATA_SIZE] =
{
    (STATUS_ABSTRACT_STATE_IFACE >> 0) & 0x00FF,
    (STATUS_ABSTRACT_STATE_IFACE >> 8) & 0x00FF
};

uint8_t g_country_code[COMM_FEATURE_DATA_SIZE] =
{
    (COUNTRY_SETTING_IFACE >> 0) & 0x00FF,
    (COUNTRY_SETTING_IFACE >> 8) & 0x00FF
};
static bool start_app = FALSE;
static bool start_transactions = FALSE;

static uint8_t g_curr_recv_buf[DATA_BUFF_SIZE];
static uint8_t g_curr_send_buf[DATA_BUFF_SIZE];

static uint32_t g_recv_size;
static uint32_t g_send_size;

static uint16_t g_cdc_device_speed;
static uint16_t g_bulk_out_max_packet_size;
static uint16_t g_bulk_in_max_packet_size;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Get_Line_Coding
 *
 * @brief The function returns the Line Coding/Configuration
 *
 * @param handle:        handle     
 * @param interface:     interface number     
 * @param coding_data:   output line coding data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Get_Line_Coding(uint32_t handle,
    uint8_t interface,
    uint8_t * *coding_data)
{
    //UNUSED_ARGUMENT(handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get line coding data*/
        *coding_data = g_line_coding;
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Line_Coding
 *
 * @brief The function sets the Line Coding/Configuration
 *
 * @param handle: handle     
 * @param interface:     interface number     
 * @param coding_data:   output line coding data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Set_Line_Coding(uint32_t handle,
    uint8_t interface,
    uint8_t * *coding_data)
{
    uint8_t count;

    //UNUSED_ARGUMENT(handle)

    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set line coding data*/
        for (count = 0; count < LINE_CODING_SIZE; count++)
        {
            g_line_coding[count] = *((*coding_data + USB_SETUP_PKT_SIZE) + count);
        }
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Get_Abstract_State
 *
 * @brief The function gets the current setting for communication feature
 *                                                  (ABSTRACT_STATE)
 * @param handle:        handle
 * @param interface:     interface number     
 * @param feature_data:   output comm feature data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Get_Abstract_State(uint32_t handle,
    uint8_t interface,
    uint8_t * *feature_data)
{
    //UNUSED_ARGUMENT(handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get line coding data*/
        *feature_data = g_abstract_state;
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Get_Country_Setting
 *
 * @brief The function gets the current setting for communication feature
 *                                                  (COUNTRY_CODE)
 * @param handle:        handle     
 * @param interface:     interface number     
 * @param feature_data:   output comm feature data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Get_Country_Setting(uint32_t handle,
    uint8_t interface,
    uint8_t * *feature_data)
{
    //UNUSED_ARGUMENT(handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get line coding data*/
        *feature_data = g_country_code;
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Abstract_State
 *
 * @brief The function gets the current setting for communication feature
 *                                                  (ABSTRACT_STATE)
 * @param handle:        handle     
 * @param interface:     interface number     
 * @param feature_data:   output comm feature data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Set_Abstract_State(uint32_t handle,
    uint8_t interface,
    uint8_t * *feature_data)
{
    uint8_t count;
    //UNUSED_ARGUMENT(handle)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set Abstract State Feature*/
        for (count = 0; count < COMM_FEATURE_DATA_SIZE; count++)
        {
            g_abstract_state[count] = *(*feature_data + count);
        }
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Country_Setting
 *
 * @brief The function gets the current setting for communication feature
 *                                                  (COUNTRY_CODE)
 * @param handle: handle     
 * @param interface:     interface number     
 * @param feature_data:   output comm feature data     
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Set_Country_Setting(uint32_t handle,
    uint8_t interface,
    uint8_t * *feature_data)
{
    uint8_t count;
    //UNUSED_ARGUMENT (handle)

    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        for (count = 0; count < COMM_FEATURE_DATA_SIZE; count++)
        {
            g_country_code[count] = *(*feature_data + count);
        }
        return USB_OK;
    }

    return USBERR_INVALID_REQ_TYPE;
}
/*****************************************************************************
 *  
 *    @name         APP_init
 * 
 *    @brief         This function do initialization for APP.
 * 
 *    @param         None
 * 
 *    @return       None
 **                  
 *****************************************************************************/
void APP_init(void)
{

    cdc_config_struct_t cdc_config;
    cdc_config.cdc_application_callback.callback = USB_App_Device_Callback;
    cdc_config.cdc_application_callback.arg = &g_app_handle;
    cdc_config.vendor_req_callback.callback = NULL;
    cdc_config.vendor_req_callback.arg = NULL;
    cdc_config.class_specific_callback.callback = USB_App_Class_Callback;
    cdc_config.class_specific_callback.arg = &g_app_handle;
    cdc_config.board_init_callback.callback = usb_device_board_init;
    cdc_config.board_init_callback.arg = CONTROLLER_ID;
    cdc_config.desc_callback_ptr = &desc_callback;
    /* Always happen in control endpoint hence hard coded in Class layer*/
    
    g_cdc_device_speed = USB_SPEED_FULL;
    g_bulk_out_max_packet_size = FS_DIC_BULK_OUT_ENDP_PACKET_SIZE;
    g_bulk_in_max_packet_size = FS_DIC_BULK_IN_ENDP_PACKET_SIZE;
    /* Initialize the USB interface */
    USB_Class_CDC_Init(CONTROLLER_ID, &cdc_config, &g_app_handle);
    g_recv_size = 0;
    g_send_size = 0;
#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
    uint32_t powerModeAmount=sizeof(powerConfigs)/
    sizeof(power_manager_user_config_t *);

    vlprConfig.mode = kPowerManagerVlpr;
    //vlprConfig.policy = kPowerManagerPolicyAgreement;

    vlprConfig.sleepOnExitValue = false;

    vlpwConfig = vlprConfig;
    vlpwConfig.mode = kPowerManagerVlpw;

    vlpsConfig = vlprConfig;
    vlpsConfig.mode = kPowerManagerVlps;

    stopConfig = vlprConfig;
    stopConfig.mode = kPowerManagerStop;

    POWER_SYS_Init((power_manager_user_config_t const ** )&powerConfigs, powerModeAmount, NULL, 1U);
#if(defined FRDM_KL27Z)
    PORTA_PCR4 = 0;
    PORTA_PCR13 = 0;
    PORTB_PCR18 = 0;
    PORTB_PCR19 = 0;
    PORTC_PCR1 = 0;
    PORTC_PCR2 = 0;
    PORTC_PCR3 = 0;
#endif
#endif
#endif    
}

/*****************************************************************************
 *  
 *   @name        APP_task
 * 
 *   @brief       This function runs APP task.
 *   @param       None
 * 
 *   @return      None
 **                
 *****************************************************************************/

/*void APP_task(void)
{
    while (TRUE)
    {
        // call the periodic task function
        USB_CDC_Periodic_Task();

        //check whether enumeration is complete or not
        if ((start_app == TRUE) && (start_transactions == TRUE))
        {
            Virtual_Com_App();
        }
    }// Endwhile
}
*/

/******************************************************************************
 * 
 *    @name        USB_App_Device_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       handle : handle to Identify the controller
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void USB_App_Device_Callback(uint8_t event_type, void* val, void* arg)
{
    uint32_t handle;
    handle = *((uint32_t *) arg);
    if (event_type == USB_DEV_EVENT_BUS_RESET)
    {
        start_app = FALSE;
        if (USB_OK == USB_Class_CDC_Get_Speed(handle, &g_cdc_device_speed))
        {
            USB_Desc_Set_Speed(handle, g_cdc_device_speed);
            if (USB_SPEED_HIGH == g_cdc_device_speed)
            {
                g_bulk_out_max_packet_size = HS_DIC_BULK_OUT_ENDP_PACKET_SIZE;
                g_bulk_in_max_packet_size = HS_DIC_BULK_IN_ENDP_PACKET_SIZE;
            }
            else
            {
                g_bulk_out_max_packet_size = FS_DIC_BULK_OUT_ENDP_PACKET_SIZE;
                g_bulk_in_max_packet_size = FS_DIC_BULK_IN_ENDP_PACKET_SIZE;
            }
        }
    }
    else if (event_type == USB_DEV_EVENT_CONFIG_CHANGED)
    {
        /* Schedule buffer for receive */
        USB_Class_CDC_Recv_Data(handle, DIC_BULK_OUT_ENDPOINT, g_curr_recv_buf, g_bulk_out_max_packet_size);
        start_app = TRUE;
    }
    else if (event_type == USB_DEV_EVENT_ERROR)
    {
        /* add user code for error handling */
    }
    return;
}

/******************************************************************************
 * 
 *    @name        USB_App_Class_Callback
 *    
 *    @brief       This function handles the callback for Get/Set report req  
 *                  
 *    @param       request  :  request type
 *    @param       value    :  give report type and id
 *    @param       data     :  pointer to the data 
 *    @param       size     :  size of the transfer
 *
 *    @return      status
 *                  USB_OK  :  if successful
 *                  else return error
 *
 *****************************************************************************/
uint8_t USB_App_Class_Callback
(
    uint8_t event,
    uint16_t value,
    uint8_t ** data,
    uint32_t* size,
    void* arg
) 
{
    cdc_handle_t handle;
    uint8_t error = USB_OK;
    handle = *((cdc_handle_t *) arg);
    switch(event)
    {
    case GET_LINE_CODING:
        error = USB_Get_Line_Coding(handle, value, data);
        break;
    case GET_ABSTRACT_STATE:
        error = USB_Get_Abstract_State(handle, value, data);
        break;
    case GET_COUNTRY_SETTING:
        error = USB_Get_Country_Setting(handle, value, data);
        break;
    case SET_LINE_CODING:
        error = USB_Set_Line_Coding(handle, value, data);
        break;
    case SET_ABSTRACT_STATE:
        error = USB_Set_Abstract_State(handle, value, data);
        break;
    case SET_COUNTRY_SETTING:
        error = USB_Set_Country_Setting(handle, value, data);
        break;
    case USB_APP_CDC_DTE_ACTIVATED:
        if (start_app == TRUE)
        {
            start_transactions = TRUE;
#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
            waitfordatareceive = 1;
            usb_hal_khci_disable_interrupts((uint32_t)USB0, INTR_SOFTOK);
            comopen = 1;
            USB_PRINTF("USB_APP_CDC_DTE_ACTIVATED\r\n");
#endif
#endif
        }
        break;
    case USB_APP_CDC_DTE_DEACTIVATED:
        if (start_app == TRUE)
        {
            start_transactions = FALSE;
        }
        break;
    case USB_DEV_EVENT_DATA_RECEIVED:
        {
        if ((start_app == TRUE) && (start_transactions == TRUE))
        {
            g_recv_size = *size;
#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
            waitfordatareceive = 0;
            usb_hal_khci_enable_interrupts((uint32_t)USB0, INTR_SOFTOK);
#endif
#endif

            if (!g_recv_size)
            {
                /* Schedule buffer for next receive event */
                USB_Class_CDC_Recv_Data(handle, DIC_BULK_OUT_ENDPOINT, g_curr_recv_buf, g_bulk_out_max_packet_size);
#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
                waitfordatareceive = 1;
                usb_hal_khci_disable_interrupts((uint32_t)USB0, INTR_SOFTOK);
#endif
#endif
            }
        }
    }
        break;
    case USB_DEV_EVENT_SEND_COMPLETE:
        {
        if ((size != NULL) && (*size != 0) && (!(*size % g_bulk_in_max_packet_size)))
        {
            /* If the last packet is the size of endpoint, then send also zero-ended packet,
             ** meaning that we want to inform the host that we do not have any additional
             ** data, so it can flush the output.
             */
            USB_Class_CDC_Send_Data(g_app_handle, DIC_BULK_IN_ENDPOINT, NULL, 0);
        }
        else if ((start_app == TRUE) && (start_transactions == TRUE))
        {
            if ((*data != NULL) || ((*data == NULL) && (*size == 0)))
            {
                /* User: add your own code for send complete event */
                /* Schedule buffer for next receive event */
                USB_Class_CDC_Recv_Data(handle, DIC_BULK_OUT_ENDPOINT, g_curr_recv_buf, g_bulk_out_max_packet_size);
#if USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
                waitfordatareceive = 1;
                usb_hal_khci_disable_interrupts((uint32_t)USB0, INTR_SOFTOK);
#endif
#endif
            }
        }
    }
        break;
    case USB_APP_CDC_SERIAL_STATE_NOTIF:
        {
        /* User: add your own code for serial_state notify event */
    }
        break;
    default:
        {
        error = USBERR_INVALID_REQ_TYPE;
        break;
    }

    }

    return error;
}

#define ms(arg) (arg*configTICK_RATE_HZ)/1000 //Ou arg/portTICK_PERIOD_MS
#define us(arg) (arg*configTICK_RATE_HZ)/1000000 //Ou arg/(portTICK_PERIOD_MS*1000)

void sistema (void *p){

	TickType_t xLastWakeTime;
	uint16_t ts;

	xLastWakeTime = xTaskGetTickCount();

	initSist();

	adcInit();
	dacInit();

	PORTB_Mode(1, OUTPUT);

	while(1){
		ts = getTime();
		if (ts > 0){
			vTaskDelayUntil(&xLastWakeTime, us(ts));
		}
		else{
			vTaskDelayUntil(&xLastWakeTime, ms(500));
		}
		PORTB_Write(1, HIGH);
		//Correcao
		dacWrite(calculaSist(adcRead(PT_B0)>>4)); //Reduz os 16 bits do ADC para os 12 bits do DAC
		PORTB_Write(1, LOW);


	}
}

void usb_comm (void * p){
	uint8_t init = 0;
	
	xMessage mensagem;
	mensagem.position = 0;

	APP_init();
	receiveQueue = xQueueCreate(2, sizeof(xMessage));

	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();



	while(1){

		vTaskDelayUntil(&xLastWakeTime, ms(100));
		//PORTB_Write(1, HIGH);
		USB_CDC_Periodic_Task();


		if ((g_recv_size != 0) && (g_recv_size != 0xFFFFFFFF)){

			uint32_t i;

			for (i = 0; i < g_recv_size; i++){
				g_curr_send_buf[g_send_size++] = g_curr_recv_buf[i];
				//Process

				if (g_curr_recv_buf[i] == '@'){
					mensagem.position = 0;
					init = 1;
					continue;
				}
				if (g_curr_recv_buf[i] == '$'){
					if (init){
						init = 0;
						mensagem.data[mensagem.position] = 0;
						xQueueSend(receiveQueue, &mensagem, 500);
					}
					init = 0;
					continue;
				}
				if (init){
					mensagem.data[mensagem.position] = g_curr_recv_buf[i];
					mensagem.position++;
					if (mensagem.position > MAX_BUFF){
						//Wrong message
						mensagem.position = 0;
						init = 0;
					}
				}
			}
			g_recv_size = 0;

			//echo

			if (g_send_size){
				uint8_t error;
				uint32_t size = g_send_size;

				g_send_size = 0;
				error = USB_Class_CDC_Send_Data(g_app_handle, DIC_BULK_IN_ENDPOINT, g_curr_send_buf, size);

				if (error != USB_OK){
					/* Failure to send Data Handling code here */
				}
			}
		}
	}
}

void interpret(void *p){
	coeficientes tempDiff;
	xMessage mensagem;

	while(1){
		//TODO esperar pro resto da vida -> portMAX_DELAY -> https://www.freertos.org/a00118.html
		uint32_t i;
		if (xQueueReceive(receiveQueue, &mensagem, portMAX_DELAY)){
			//PORTB_Write(1, HIGH);
			if ((mensagem.data[0] == 'n') && (mensagem.data[1] == ',')){ //Byte de entrada
				int atual = 0, inicio = 2, flag_d = 0;

				for (i = 2; i < mensagem.position; i++){ //Procura a virgula
					if (mensagem.data[i] == 'd'){ //Byte de saida
						if (flag_d) //d duas vezes
							break;
						if (mensagem.data[i+1] == ','){
							atual = 0;
							flag_d = 1;
							inicio = i+2;
							i++;
							continue;
						}
						break; //Erro (faltou a virgula)
					}
					if(!flag_d){ //Coeficientes do numerador
						if (mensagem.data[i] == ','){
							tempDiff.in[atual] = string_to_float(mensagem.data, inicio, i);
							if (tempDiff.in[atual] == ERRO)
								break;
							atual++;
							inicio = i + 1;
							tempDiff.ultimoIn = atual;
						}
					}
					else{ //Coeficientes do denominador
						if (mensagem.data[i] == ','){
							tempDiff.out[atual] = string_to_float(mensagem.data, inicio, i);
							if (tempDiff.out[atual] == ERRO)
								break;
							atual++;
							inicio = i + 1;
							tempDiff.ultimoOut = atual;
							if (mensagem.data[i+1] == 't'){ //Tempo de amostragem
								if (mensagem.data[i+2] == ','){
									float aux;
									aux = string_to_float(mensagem.data, i+3, mensagem.position);
									if ((aux > 0)&&(aux != ERRO)){
										tempDiff.amostragem = (uint32_t)(aux*1000); //transforma ms em us
										setDiff(&tempDiff);
									}
								}
								break;
							}
						}
					}
				}
				//Erro
			}
			if ((mensagem.data[0] == 'p') && (mensagem.data[1] == 'i') && (mensagem.data[2] == 'd') && (mensagem.data[3] == ',')){
				double kp = 0, kd = 0, ki = 0;
				int32_t	ta = 50;
				uint32_t j = 0, inicio = 0;
				for (i = 4; i<mensagem.position; i++){
					if (mensagem.data[i] == ','){
						if (j == 0){
							kd = string_to_float(mensagem.data, 4, i);
							if (kd == ERRO){
									PORTB_Write(19, HIGH);
								break;
							}
							inicio = i+1;
						}
						if (j == 1){
							kp = string_to_float(mensagem.data, inicio, i);
							if (kp == ERRO){
								PORTB_Write(19, HIGH);
								break;
							}
							inicio = i+1;
						}
						if (j == 2){
							ki = string_to_float(mensagem.data, inicio, i);
							if (ki == ERRO){
								PORTB_Write(19, HIGH);
								break;
							}
							inicio = i+1;
						}
						j++;
					}
					
				}
				ta = string_to_float(mensagem.data, inicio, mensagem.position);
				if ((ta != ERRO )&&(ta > 0)){
					setPID(kd, kp, ki, ta); //ta em ms
				}
				else{
					PORTB_Write(19, HIGH);
				}

			}
			if ((mensagem.data[0] == 's') && (mensagem.data[1] == 'p')&&(mensagem.data[2] == ',')&&(mensagem.position <= 7)){ //sp,4095
				int32_t setPoint = 0;
				for (i = 3; i< mensagem.position; i++){
					if ((mensagem.data[i] >= '0')&&(mensagem.position <= '9')){
						setPoint*=10;
						setPoint += (mensagem.data[i]-'0');
					}
					else{
						setPoint = 0;
						break;
					}
				}
				if((mensagem.data[3] == '-')&&(mensagem.data[4] == '1')){
					i = 5;
					setPoint = -1;
				}
				if (i == mensagem.position){
					setSP(setPoint);
				}
			}
			if ((mensagem.data[0] == 's') && (mensagem.data[1] == 't')&&(mensagem.data[2] == 'a') && (mensagem.data[3] == 'r') && (mensagem.data[4] == 't') && (mensagem.position == 5)){
				setStart(1);
				vTaskResume(handleSist);
			}
			if ((mensagem.data[0] == 's') && (mensagem.data[1] == 't')&&(mensagem.data[2] == 'o') && (mensagem.data[3] == 'p') && (mensagem.position == 4)){
				setStart(0);
				dacWrite(0);
				//TODO Suspende o sistema
				vTaskSuspend(handleSist);

			}
		}
	}
}

void idle (void *p){
	while(1){
		PORTB_Write(1, LOW);
	}
}

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)

#if defined(FSL_RTOS_MQX)
void Main_Task(uint32_t param);
TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    {   1L, Main_Task, 2500L, MQX_MAIN_TASK_PRIORITY, "Main", MQX_AUTO_START_TASK},
    {   0L, 0L, 0L, 0L, 0L, 0L}
};
#endif


#if defined(FSL_RTOS_MQX)
void Main_Task(uint32_t param)
#else

#if defined(__CC_ARM) || defined(__GNUC__)
int main(void)
#else
void main(void)
#endif

#endif
{
    hardware_init();
    dbg_uart_init();

    xTaskCreate(sistema, "sistema_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &handleSist);
    xTaskCreate(usb_comm, "usb_comm_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL);
    xTaskCreate(interpret, "interpret_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL);
    //xTaskCreate(idle, "idle_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    //IDLE -> Task com menor prioridade
    vTaskStartScheduler();

#if (!defined(FSL_RTOS_MQX))&(defined(__CC_ARM) || defined(__GNUC__))
    return 1;
#endif
}
#endif
