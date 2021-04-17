#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/ch9326.h"

int main()
{
    unsigned char buf[128],Hbuf[256];
    int i,j;

    memset(buf, 0, sizeof(buf));

    int r = ch9326_find();

    if(r == 0) {
        printf("can not find 9326 device.\n");
        return -1;
    } else {
        printf("found %d 9326\n", r);
    }

    r = ch9326_open(0);
    printf("open : %d \n",r);
    if(r == 0) {
        printf("ch9326_open failed.\n");
        return -1;
    }

       

 	r = ch9326_set(0, B115200, P_NONE, STOP_1, BIT_8, 0x30);
	printf("set uart: %d %d\n",i,r);
	if(r == 0) {
        	printf("ch9326_set serial failed.\n");
        	return -1;
    	}
    



    r = ch9326_connected(0);
    printf("connected : %d \n", r);
    if(r == 0) {
        printf("ch9326_connect failed.\n");
    }
    for (i = 0; i < 100000; i++) {
	 // Sendata   
        snprintf(buf,sizeof(buf),"AT+ReadData=0\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        sleep(10);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
	    printf("Seriale stazione meteo: %02X%02X%02X%02X%02X%02X\n",(unsigned int)(buf[0]),(unsigned int)(buf[1]),(unsigned int)(buf[2]),(unsigned int)(buf[3]),(unsigned int)(buf[4]),(unsigned int)(buf[5]));

	    if ((unsigned int)(buf[7]) > 128) {
		    float tempout = ((float)(((unsigned int)(buf[7]) - 128 ) * 16 + (unsigned int)(buf[8]) / 16) /10);
		    printf("Temp Out: %0.1f C\n",tempout);

	    }
	    if (((unsigned int)(buf[8]) & 15)  >= 8 ) {
		    float tempin = ((float)((unsigned int)(buf[9]))/10) ;
		    printf("Temp In: %0.1f C\n",tempin);

	    }
	
	    printf("Hum Out: %d \%%\n",(unsigned int)(buf[10]));
	    printf("Hum In: %d \%%\n",(unsigned int)(buf[11]));
	    printf("Wind speed: %0.1f \n",(float)((unsigned int)(buf[15])*256 +(unsigned int)(buf[16]))/10);
	    printf("Pressure: %d hPa\n",(unsigned int)(buf[12])*256 +(unsigned int)(buf[13]));
	    printf("Rain: %0.1f mm/h\n",(float)(buf[14])*0.3);

	    for(i=6;i<r;i++)
	    {    
            	printf("%02X",(unsigned int)(buf[i]));
	    }
	    printf("\n");
        }
    }

    r = ch9326_close(0);
    printf("close : %d\n", r);
    return 0;
    
}

