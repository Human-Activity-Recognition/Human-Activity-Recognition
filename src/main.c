#include "hx_drv_tflm.h"
#include "synopsys_wei_delay.h"
#include "synopsys_wei_gpio.h"
#define accel_scale 10
#define accel_scale1 100
void GPIO_INIT(void);
void UART_T(float x,float y,float z);
void UART_R(void);

hx_drv_gpio_config_t hal_gpio_0;
hx_drv_gpio_config_t hal_gpio_1;
hx_drv_gpio_config_t hal_led_r;
hx_drv_gpio_config_t hal_led_g;


int number=0;
int start;

//accel_type accel_x, accel_y, accel_z;



/*typedef struct
{
	uint8_t symbol;
	uint32_t int_part;
	uint32_t frac_part;
} accel_type;*/



int main(int argc, char* argv[])
{	
	int a=0;


  	hx_drv_accelerometer_initial();
  	hx_drv_uart_initial(UART_BR_115200);
	GPIO_INIT();	
	hx_drv_led_on(HX_DRV_LED_RED);
	hal_gpio_set(&hal_gpio_1, GPIO_PIN_SET);

///////////////////////////////////////////////////// TX一直給1、紅燈亮 //////////////////////////////////////////////////////////
	while (1) 
	{	
    	uint32_t available_count = 0;
		float x, y, z;
		available_count = hx_drv_accelerometer_available_count();	
		
		for (int i = 0; i < available_count; i++) 
		{
			hx_drv_accelerometer_receive(&x, &y, &z);
		}


		do
		{
			hx_drv_gpio_get(&hal_gpio_0);
			start=hal_gpio_0.gpio_data;
		} while (start==1 && a==0);

		//if(a==0){
			UART_R();
			//a=1;
		//}
		

			if(number==0)
			{
		   		hx_drv_led_off(HX_DRV_LED_RED);
			}
			else if(number==1)
			{   
  				

				hx_drv_led_on(HX_DRV_LED_GREEN);
			}
			else if(number==2)
			{
				hx_drv_led_on(HX_DRV_LED_GREEN);
				hx_drv_led_off(HX_DRV_LED_RED);
			}

/////////////////////////////////////////////////// 做一次RX跟亮燈 //////////////////////////////////////////////////////////
			
	UART_T(x,y,z);
	
	}
	

		
	}
void UART_T(float x,float y,float z)
{
	int a[12];
	int UART_TR[12][8]={
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0}
							};
	int i,j;

    int32_t int_buf;
	
	int_buf = x * accel_scale1; //scale value

	if(int_buf < 0)
		{
			int_buf = int_buf * -1;
			a[0]=129;
		}
		else 
		{
			a[0]=128;
		}

	a[1] = int_buf / accel_scale1;
	int_buf = int_buf % accel_scale1;
	a[2] = int_buf / accel_scale;
	a[3] = int_buf % accel_scale;

		int_buf = y * accel_scale1; //scale value

		if(int_buf < 0)
		{
			int_buf = int_buf * -1;
			a[4]=129;
		}
		else 
		{
			a[4]=128;
		}
		
		a[5] = int_buf / accel_scale1;
		int_buf = int_buf % accel_scale1;
		a[6] = int_buf / accel_scale;
		a[7] = int_buf % accel_scale;

		int_buf = z * accel_scale1; //scale value

		if(int_buf < 0)
		{
			int_buf = int_buf * -1;
			a[8]=129;
		}
		else 
		{
			a[8]=128;
		}

		a[9] = int_buf / accel_scale1;
		int_buf = int_buf % accel_scale1;
		a[10] = int_buf / accel_scale;
		a[11] = int_buf % accel_scale;



	   for(i=0;i<12;i++)
	   {
		switch(a[i])
		{
		case 0:	 { UART_TR[i][0]=0;  UART_TR[i][1]=0; UART_TR[i][2]=0; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 1:  { UART_TR[i][0]=1;  UART_TR[i][1]=0; UART_TR[i][2]=0; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 2:  { UART_TR[i][0]=0;  UART_TR[i][1]=1; UART_TR[i][2]=0; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 3:  { UART_TR[i][0]=1;  UART_TR[i][1]=1; UART_TR[i][2]=0; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
  		case 4:  { UART_TR[i][0]=0;  UART_TR[i][1]=0; UART_TR[i][2]=1; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
  		case 5:	 { UART_TR[i][0]=1;  UART_TR[i][1]=0; UART_TR[i][2]=1; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 6:  { UART_TR[i][0]=0;  UART_TR[i][1]=1; UART_TR[i][2]=1; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 7:  { UART_TR[i][0]=1;  UART_TR[i][1]=1; UART_TR[i][2]=1; UART_TR[i][3]=0; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 8:  { UART_TR[i][0]=0;  UART_TR[i][1]=0; UART_TR[i][2]=0; UART_TR[i][3]=1; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
  		case 9:  { UART_TR[i][0]=1;  UART_TR[i][1]=0; UART_TR[i][2]=0; UART_TR[i][3]=1; UART_TR[i][4]=1; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
  		case 128:{ UART_TR[i][0]=1;  UART_TR[i][1]=1; UART_TR[i][2]=0; UART_TR[i][3]=1; UART_TR[i][4]=0; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
		case 129:{ UART_TR[i][0]=1;  UART_TR[i][1]=0; UART_TR[i][2]=1; UART_TR[i][3]=1; UART_TR[i][4]=0; UART_TR[i][5]=1; UART_TR[i][6]=0; UART_TR[i][7]=0; break; }
  		default: {UART_TR[i][7]=1;break; }
  		}
	   }
   
	
///////////////////////////////////////////////////// 資料判別 ////////////////////////////////////////////////////////////////
for(j=0;j<12;j++){
	for(i=0;i<10;i++)																
	{ 
		if(i==0)
     	{
       		hal_gpio_set(&hal_gpio_1, GPIO_PIN_RESET);
     	}
     	else if(i==9)
     	{
       		hal_gpio_set(&hal_gpio_1, GPIO_PIN_SET);
     	}
     	else
     	{
       		if(UART_TR[j][i-1]==0)
	   			hal_gpio_set(&hal_gpio_1, GPIO_PIN_RESET);
       		else
	   			hal_gpio_set(&hal_gpio_1, GPIO_PIN_SET);
     	}      
	   	hal_delay_ms(7);
    }
}
///////////////////////////////////////////////////// 發送資料 ////////////////////////////////////////////////////////////////
}

void UART_R(void)
{
  int UART_BF[]={0,0,0,0,0,0,0,0};
  int i;
  for(i=0;i<8;i++)
  { 
	hal_delay_ms(7);
    hx_drv_gpio_get(&hal_gpio_0);
    start=hal_gpio_0.gpio_data;
    UART_BF[i]=start;
  }

	hal_delay_ms(7);
	hx_drv_gpio_get(&hal_gpio_0);
	start=hal_gpio_0.gpio_data;

	if(UART_BF[0]==0 && UART_BF[1]==0 && UART_BF[2]==0 && UART_BF[3]==1 && UART_BF[4]==1 && UART_BF[5]==1 && UART_BF[6]==0 && UART_BF[7]==0)
	number=1;

    else if(UART_BF[0]==1 && UART_BF[1]==0 && UART_BF[2]==0 && UART_BF[3]==0 && UART_BF[4]==1 && UART_BF[5]==1 && UART_BF[6]==0 && UART_BF[7]==0)
	number=2;
}
void GPIO_INIT(void)
{
	if(hal_gpio_init(&hal_gpio_0, HX_DRV_PGPIO_0, HX_DRV_GPIO_INPUT, GPIO_PIN_RESET) == HAL_OK)
    	hx_drv_uart_print("62\n");
  	else
    	hx_drv_uart_print("GPIO0 Initialized: Error\n");

  	if(hal_gpio_init(&hal_gpio_1, HX_DRV_PGPIO_1, HX_DRV_GPIO_OUTPUT, GPIO_PIN_RESET) == HAL_OK)
    		hx_drv_uart_print("Gsdasdas5\n");
  	else
    		hx_drv_uart_print("GPIO1 Initialized: Error\n");
}
