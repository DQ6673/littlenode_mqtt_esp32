#ifndef _SHT20_APP_H_
#define _SHT20_APP_H_

typedef struct
{
    float temp;
    float RH;
}sht20_data_t;

void sht20_app_start(void);

#endif