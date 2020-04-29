#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NormRANu (2.3283063671E-10F)

unsigned int irr[256];
unsigned int ir1;
unsigned char ind_rand,ig1,ig2,ig3;

void ini_rand(int SEMILLA)
{
    int INI,FACTOR,SUM;

    srand(SEMILLA);
    INI=SEMILLA;
    FACTOR=67397;
    SUM=7364893;

    for(int i=0;i<256;i++)
    {
        INI=(INI*FACTOR+SUM);
        irr[i]=INI;
    }

    ind_rand=ig1=ig2=ig3=0;
}

float random(void)
{
    float r;
    unsigned int ir1;

    ig1=ind_rand-24;
    ig2=ind_rand-55;
    ig3=ind_rand-61;
    irr[ind_rand]=irr[ig1]+irr[ig2];
    ir1=(irr[ind_rand]^irr[ig3]);
    ind_rand++;
    return r=ir1*NormRANu;
}
