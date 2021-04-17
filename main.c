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
    


/*
    r = ch9326_set_gpiodir(0, 0x0F);
    printf("set gpio dir: %d\n", r);
    if(r == 0) {
        printf("ch9326_set gpio failed.\n");
        return -1;
    }
*/
//    r = ch9326_set_gpio(0, 0, 0);
//    printf("set gpio: %d\n", r);
//    if(r == 0) {
//        printf("ch9326_set failed.\n");
//        return -1;
//    }
//
//    r = ch9326_get_gpio(0, &data);
//    printf("get gpio: %d\n", r);
//    if(r == 0) {
//        printf("ch9326_set failed.\n");
//        return -1;
//    }

    r = ch9326_connected(0);
    printf("connected : %d \n", r);
    if(r == 0) {
        printf("ch9326_connect failed.\n");
    }
/*
    r = ch9326_get_manufacturer_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get ch9326_get_manufacturer_string error.\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }

    r = ch9326_get_product_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get prod error\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }

    r = ch9326_get_serial_number_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get serial error\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }
*/
    for (i = 0; i < 100000; i++) {
	 // Sendata   
        snprintf(buf,sizeof(buf),"AT+ReadData=0\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
//        printf("send : %s %d\n",buf, r);
        sleep(10);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
/*
      	    memset(Hbuf,0,sizeof(Hbuf));
	    for(i=0,j=0;i<strlen(buf);i++,j+=2)
			{ 
				sprintf((char*)Hbuf+j,"%02X",buf[i]);
			}
	    Hbuf[j]='\0';
*///	    printf("%s\n",buf);
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
	    printf("Wind speed: %0.1f \n",(float)(unsigned int)(buf[15])*256 +(unsigned int)(buf[16])/10);

	    for(i=6;i<r;i++)
	    {    
            	printf("%02X",(unsigned int)(buf[i]));
	    }
	    printf("\n");
        }
/*	
	 // Sendata
        snprintf(buf,sizeof(buf),"AT+ReadData=0\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        printf("send : %s %d\n",buf, r);
        sleep(1);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
            printf("%s\n",buf);
        }
	/*
        sleep(1);
        snprintf(buf,sizeof(buf),"AT+ReadData=0\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        printf("send : %s %d\n",buf, r);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        sleep(10);

	// Requestdata
        snprintf(buf,sizeof(buf),"AT+UNIT?\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        printf("send : %s %d\n",buf, r);
        sleep(1);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
            printf("%s\n",buf);
        }
        snprintf(buf,sizeof(buf),"AT+ReadData=1\r\n");
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        printf("send : %s %d\n",buf, r);
        sleep(1);
        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
            printf("%s\n",buf);
        }

*/
/*
        ch9326_set_gpiodata(0,0x04);
        sleep(1);
        ch9326_set_gpiodata(0,0x08);
*/
    }

    r = ch9326_close(0);
    printf("close : %d\n", r);
    return 0;
    
}

