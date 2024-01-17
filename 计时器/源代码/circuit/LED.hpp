#ifndef LED
#define LED
#include "mytype.hpp"
#include <iostream>
#include <string.h>
using std::cout;
#define DEBUG(cir_hour,cir_minute,cir_second) printf("%d%d:%d%d:%d%d\n",\
            cir_hour.high4.Q.to_ulong(),cir_hour.low4.Q.to_ulong(),\
            cir_minute.high4.Q.to_ulong(),cir_minute.low4.Q.to_ulong(),\
            cir_second.high4.Q.to_ulong(),cir_second.low4.Q.to_ulong()\
            )

void high1(char g[5][6]){
    for(int i=0;i<5;i++)g[0][i]='*';
}
void high2(char g[5][6]){
    for(int i=0;i<3;i++)g[i][4]='*';
}
void high3(char g[5][6]){
    for(int i=2;i<5;i++)g[i][4]='*';
}
void high4(char g[5][6]){
    for(int i=0;i<5;i++)g[4][i]='*';
}
void high5(char g[5][6]){
    for(int i=2;i<5;i++)g[i][0]='*';
}
void high6(char g[5][6]){
    for(int i=0;i<3;i++)g[i][0]='*';
}
void high7(char g[5][6]){
    for(int i=0;i<5;i++)g[2][i]='*';
}

char** init_g(){
    int m=5,n=39;
    char** g=(char**)malloc(m*sizeof(char*));
    for (int i=0;i<m;i++) {
        g[i]=(char*)malloc((n+1)*sizeof(char));
        for(int j=0;j<n;j++)
            g[i][j]=' ';
        g[i][n]='\0';
    }
    return g;
}
void release_g(char**g){
    int m=5;
    for(int i=0;i<m;i++)
        free(g[i]);
    free(g);
}
//接收BCD-七段显示译码器的输出并将高电平的相应位置显示
void LEDshow(char** g,out7447 hh_high,out7447 hh_low,out7447 mm_high,out7447 mm_low,out7447 ss_high,out7447 ss_low){
    char gs[6][5][6];
    for(int k=0;k<6;k++)
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                gs[k][i][j]=' ';

    void (*highs[7])(char[5][6])={high1,high2,high3,high4,high5,high6,high7};
        
    for(int i=0;i<7;i++){
        if(hh_high[i]==1) highs[i](gs[0]);
        if(hh_low[i]==1) highs[i](gs[1]);
        if(mm_high[i]==1) highs[i](gs[2]);
        if(mm_low[i]==1) highs[i](gs[3]);
        if(ss_high[i]==1) highs[i](gs[4]);
        if(ss_low[i]==1) highs[i](gs[5]);
    }

    int r=0;
    for(int k=0;k<6;k++){
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                g[i][r+j]=gs[k][i][j];
        
        r+=6;
        if(k&1) r+=2;
    }
    g[1][12]=g[1][26]=g[3][12]=g[3][26]='*';

    for(int i=0;i<5;i++)
        cout<<g[i]<<'\n';
    cout.flush();
}
#endif