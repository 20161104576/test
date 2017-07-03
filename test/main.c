//
//  main.c
//  test
//
//  Created by fanjiahui on 17/7/2.
//  Copyright © 2017年 fanjiahui. All rights reserved.
//

#include <stdio.h>

int main()
{
    char str1[100];//读取文件GPRMC
    char str2[100];//读取文件GPGGA
    FILE *p;
    p=fopen("//Users//a20161104576//Desktop//test//GPS.log","r");
    FILE *fp;
    fp = fopen("//Users//a20161104576//Desktop//test//excel.csv","w");
    fprintf(fp,"日期,时间,纬度方向,纬度,经度方向,经度,海拔,地面速率\n");
    while(fscanf(p,"%s\n%s\n",str1,str2)!=EOF)
    {
        printf("%s\n%s\n",str1,str2);
        char time[7];//分离时间
        int atime[7];//将time数组变为整型
        int i;
        int hour,minute,seconds;//提取出时分秒
        for(i=0; i<6; i++)
        {
            time[i]=str1[i+7];
            atime[i]=time[i]-48;
        }
        hour = atime[0]*10 + atime[1] + 8;
        minute=atime[2]*10 + atime[3];
        seconds=atime[4]*10 + atime[5];
        printf("时间 %d:%d:%d\n",hour,minute,seconds);
        
        
        char lat[9];//分离纬度
        char nlat;//定义一个维度方向
        for(i=0;i<8;i++)
        {
            lat[i]=str1[i+16];
        }
        nlat=str1[25];
        printf("纬度 %s\n纬度方向 %c\n",lat,nlat);
        
        
        char lon[10];//分离经度
        char nlon;//定义一个经度方向
        nlon=str1[37];
        for(i=0;i<9;i++)
        {
            lon[i]=str1[i+27];
        }
        printf("经度 %s\n经度方向 %c\n",lon,nlon);
        
        
        
        char speed[6];//分离地面速率
        double aspeed[6];//将speed数组变为整型数组
        double bspeed;
        for(i=0;i<5;i++)
        {
            speed[i]=str1[i+39];
            if(speed[i]=='.')
            {
                aspeed[i]=0;
            }
            else
                aspeed[i]=speed[i]-48;
        }
        bspeed = aspeed[0]*100 + aspeed[1]*10 + aspeed[2] + aspeed[4]/10;
        bspeed = bspeed*1.825;
        printf("地面速率 %.1lf\n",bspeed);
        
        
        char date[7];//分离日期
        for(i=0;i<6;i++)
        {
            date[i]=str1[i+51];
        }
        printf("%s\n",date);
        
        
        char azi[5];//分离海拔
        int aazi[5];//将azi数组变为整型数组
        int bazi;
        for(i=0;i<4;i++)
        {
            azi[i]=str2[i+43];
            aazi[i]=azi[i]-48;
        }
        bazi=aazi[0]*1000 + aazi[1]*100 + aazi[2]*10 + aazi[3];
        printf("%d千米\n",bazi);
        fprintf(fp,"20%c%c年%c%c月%c%c日,%d:%d:%d,%c,%s,%c,%s,%d千米,%.1lf\n",date[4],date[5],date[2],date[3],date[0],date[1],hour,minute,seconds,nlat,lat,nlon,lon,bazi,bspeed);
    }
    fclose(fp);
    fclose(p);
    return 0;
}
