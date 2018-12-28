#include "stewart.h"
#include "math.h"
#include "usart.h"
const double high=-84;
const double duo=13.5;
const double len=88;
const double xbl=44;
const double ybl=16;
const double xtl=37;
const double ytl=27;
const double pi=3.14159265;


	
void ste(double ax,double ay,double az,double xp,double yp,double zp)
{
	
	double step1=(104.0-24.0)/180.0;
double step2=(104.0-26.0)/180.0;
double step3=(110.0-30.0)/180.0;
double step4=(108.0-30.0)/180.0;
double step5=(110.0-31.0)/180.0;
double step6=(106.0-26.0)/180.0;

  double x_bottle[6]={0};
	double y_bottle[6]={0};
	double z_bottle[6]={0};
	double x_top[6]={0};
	double y_top[6]={0};
	double z_top[6]={0};
	int i;
	int num;
	double x_topk;
	double y_topk;
	double z_topk;
	double length[6];
	double ll[6]={0};
	
	double last_er;
	double point;
	double er;
	double ap[6];
	double x_bottlek;
	double y_bottlek;
	double z_bottlek;
	double x_bottlet;
	double y_bottlet;
	double z_bottlet;
	
	double a=ax/360.0*2.0*pi;
	double b=ay/360.0*2.0*pi;
	double r=az/360.0*2.0*pi;
	double px=xp;
	double py=yp;
	double pz=zp;
	
	
	
	double ju[6]={0.0,-120.0/360.0*2.0*pi,-240.0/360.0*2.0*pi,0,120.0/360.0*2.0*pi,240.0/360.0*2.0*pi};

	
	
	x_bottle[0]=xbl;
	x_bottle[1]=xbl;
	x_bottle[2]=xbl*cos(ju[1])-ybl*sin(ju[1]);
	x_bottle[3]=xbl*cos(ju[1])+ybl*sin(ju[1]);
	x_bottle[4]=xbl*cos(ju[2])-ybl*sin(ju[2]);
	x_bottle[5]=xbl*cos(ju[2])+ybl*sin(ju[2]);
	
	
	y_bottle[0]=ybl;
	y_bottle[1]=-ybl;
	y_bottle[2]=xbl*sin(ju[1])+ybl*cos(ju[1]);
	y_bottle[3]=xbl*sin(ju[1])-ybl*cos(ju[1]);
	y_bottle[4]=xbl*sin(ju[2])+ybl*cos(ju[2]);
	y_bottle[5]=xbl*sin(ju[2])-ybl*cos(ju[2]);
	
	
	z_bottle[0]=high+pz;
	z_bottle[1]=high+pz;
	z_bottle[2]=high+pz;
	z_bottle[3]=high+pz;
	z_bottle[4]=high+pz;
	z_bottle[5]=high+pz;
	
	
	x_top[0]=xtl;
	x_top[1]=xtl;
	x_top[2]=xtl*cos(ju[1])-ytl*sin(ju[1]);
	x_top[3]=xtl*cos(ju[1])+ytl*sin(ju[1]);
	x_top[4]=xtl*cos(ju[2])-ytl*sin(ju[2]);
	x_top[5]=xtl*cos(ju[2])+ytl*sin(ju[2]);
	
	
	y_top[0]=ytl;
	y_top[1]=-ytl;
	y_top[2]=xtl*sin(ju[1])+ytl*cos(ju[1]);
	y_top[3]=xtl*sin(ju[1])-ytl*cos(ju[1]);
	y_top[4]=xtl*sin(ju[2])+ytl*cos(ju[2]);
	y_top[5]=xtl*sin(ju[2])-ytl*cos(ju[2]);
	
	
	for(i=0;i<6;i++)
	{
		x_topk=(x_top[i]*cos(b)+z_top[i]*sin(b))*cos(r)-y_top[i]*sin(r);
		y_topk=(y_top[i]*cos(a)-z_top[i]*sin(a))*cos(r)+x_top[i]*sin(r);
    z_topk=(y_top[i]*sin(a)+z_top[i]*cos(a))*cos(b)-x_top[i]*sin(b);
    x_top[i]=x_topk;
    y_top[i]=y_topk;
    z_top[i]=z_topk;
	}
	
	for(i=0;i<6;i++)
	{
		x_top[i]=x_top[i]+px;
		y_top[i]=y_top[i]+py;
	}
	for(i=0;i<6;i++)
	{
		length[i]=sqrt((x_top[i]-x_bottle[i])*(x_top[i]-x_bottle[i])+(y_top[i]-y_bottle[i])*(y_top[i]-y_bottle[i])+(z_top[i]-z_bottle[i])*(z_top[i]-z_bottle[i]));
	}
	
	for(i=0;i<6;i=i+2)
	{
		last_er=1000;
    point=-90;
		for(num=-85;num<85;num=num+1)
		{
			 ap[i]=num*1.0/360.0*2.0*pi;
        a=0;
        b=0;
        r=ju[3+i/2];
        x_bottlek=(x_bottle[i]*cos(a)+z_bottle[i]*sin(b))*cos(r)-y_bottle[i]*sin(r);
        y_bottlek=(y_bottle[i]*cos(a)-z_bottle[i]*sin(a))*cos(r)+x_bottle[i]*sin(r);
        z_bottlek=(y_bottle[i]*sin(a)+z_bottle[i]*cos(a))*cos(b)-x_bottle[i]*sin(b);
        x_topk=(x_top[i]*cos(b)+z_top[i]*sin(b))*cos(r)-y_top[i]*sin(r);
        y_topk=(y_top[i]*cos(a)-z_top[i]*sin(a))*cos(r)+x_top[i]*sin(r);
        z_topk=(y_top[i]*sin(a)+z_top[i]*cos(a))*cos(b)-x_top[i]*sin(b);
        
        er=2*duo*(z_bottlek-z_topk)*sin(ap[i])-2*duo*((y_bottlek-y_topk)*cos(ap[i]))+length[i]*length[i]+duo*duo-len*len;
        er=er*er;
				if(er<last_er)
				{
            last_er=er;
            point=num*1.0;
        }
		}
		ap[i]=point/360.0*2.0*pi;
    
    a=0;
    b=0;
    r=ju[i/2];
    x_bottlet=(x_bottlek*cos(0)+(z_bottlek+duo*sin(ap[i]))*sin(b))*cos(r)-(y_bottlek-duo*cos(ap[i]))*sin(r);
    y_bottlet=((y_bottlek-duo*cos(ap[i]))*cos(a)-(z_bottlek+duo*sin(ap[i]))*sin(a))*cos(r)+x_bottlek*sin(r);
    z_bottlet=((y_bottlek-duo*cos(ap[i]))*sin(a)+(z_bottlek+duo*sin(ap[i]))*cos(a))*cos(b)-x_bottlek*sin(b);
        
    ll[i]=sqrt((x_bottlet-x_top[i])*(x_bottlet-x_top[i])+(y_bottlet-y_top[i])*(y_bottlet-y_top[i])+(z_bottlet-z_top[i])*(z_bottlet-z_top[i])); 
		
	}
	
	for(i=1;i<6;i=i+2)
	{
		last_er=1000;
    point=-90.0;
		for(num=-85;num<85;num=num+1)
		{
			ap[i]=num*1.0/360.0*2.0*pi;
        a=0;
        b=0;
        r=ju[3+(i-1)/2];
        x_bottlek=(x_bottle[i]*cos(0)+z_bottle[i]*sin(b))*cos(r)-y_bottle[i]*sin(r);
        y_bottlek=(y_bottle[i]*cos(a)-z_bottle[i]*sin(a))*cos(r)+x_bottle[i]*sin(r);
        z_bottlek=(y_bottle[i]*sin(a)+z_bottle[i]*cos(a))*cos(b)-x_bottle[i]*sin(b);
        x_topk=(x_top[i]*cos(b)+z_top[i]*sin(b))*cos(r)-y_top[i]*sin(r);
        y_topk=(y_top[i]*cos(a)-z_top[i]*sin(a))*cos(r)+x_top[i]*sin(r);
        z_topk=(y_top[i]*sin(a)+z_top[i]*cos(a))*cos(b)-x_top[i]*sin(b);
        
				er=2*duo*(z_bottlek-z_topk)*sin(ap[i])+2*duo*((y_bottlek-y_topk)*cos(ap[i]))+length[i]*length[i]+duo*duo-len*len;
        er=er*er;
        if(er<last_er)
				{
            last_er=er;
            point=num*1.0;
        }
		}
		ap[i]=point/360.0*2.0*pi;
    
    a=0;
    b=0;
    r=ju[(i-1)/2];
    x_bottlet=(x_bottlek*cos(0)+(z_bottlek+duo*sin(ap[i]))*sin(b))*cos(r)-(y_bottlek+duo*cos(ap[i]))*sin(r);
    y_bottlet=((y_bottlek+duo*cos(ap[i]))*cos(a)-(z_bottlek+duo*sin(ap[i]))*sin(a))*cos(r)+x_bottlek*sin(r);
    z_bottlet=((y_bottlek+duo*cos(ap[i]))*sin(a)+(z_bottlek+duo*sin(ap[i]))*cos(a))*cos(b)-x_bottlek*sin(b);
        
    ll[i]=sqrt((x_bottlet-x_top[i])*(x_bottlet-x_top[i])+(y_bottlet-y_top[i])*(y_bottlet-y_top[i])+(z_bottlet-z_top[i])*(z_bottlet-z_top[i])); 
		
	}
	
	
	 TIM_SetCompare1(TIM5,64-step1*ap[0]*180.0/pi);
	 TIM_SetCompare2(TIM5,64+step2*ap[1]*180.0/pi);
	 TIM_SetCompare3(TIM5,70-step3*ap[2]*180.0/pi);
	 TIM_SetCompare4(TIM5,70+step4*ap[3]*180.0/pi);
	 TIM_SetCompare1(TIM3,71-step5*ap[4]*180.0/pi);
	 TIM_SetCompare2(TIM3,66+step6*ap[5]*180.0/pi);
}