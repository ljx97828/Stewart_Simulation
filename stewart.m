clear all
clc
clf
syms h
sta=0;
timea=30;
timeb=0;
for timea=-15:15
      sta=sta+1; 
for timeb=-15:15
title('六自由度平台matlab仿真');
ju=[0 -120/360*2*pi -240/360*2*pi 0 120/360*2*pi 240/360*2*pi ];
px=0;
py=0;
a=(timea/1)/1/360*2*pi;
if(mod(sta,2)==1)
    pb=-1;
else
    pb=1;
end
b=(timeb/1)/360*2*pi;
r=(0/1)/360*2*pi;

ap=zeros(6,1);


duo=13.5;
len=88;
xbl=44;
ybl=16;
cc=cos(ju(2));
x_bottle=[xbl xbl xbl*cos(ju(2))-ybl*sin(ju(2)) xbl*cos(ju(2))+ybl*sin(ju(2)) xbl*cos(ju(3))-ybl*sin(ju(3)) xbl*cos(ju(3))+ybl*sin(ju(3)) xbl];
y_bottle=[ybl -ybl xbl*sin(ju(2))+ybl*cos(ju(2)) xbl*sin(ju(2))-ybl*cos(ju(2)) xbl*sin(ju(3))+ybl*cos(ju(3)) xbl*sin(ju(3))-ybl*cos(ju(3)) ybl];
z_bottle(1:7)=-88;

xtl=37;
ytl=27;
x_top=[xtl xtl xtl*cos(ju(2))-ytl*sin(ju(2)) xtl*cos(ju(2))+ytl*sin(ju(2)) xtl*cos(ju(3))-ytl*sin(ju(3)) xtl*cos(ju(3))+ytl*sin(ju(3)) xtl];
y_top=[ytl -ytl xtl*sin(ju(2))+ytl*cos(ju(2)) xtl*sin(ju(2))-ytl*cos(ju(2)) xtl*sin(ju(3))+ytl*cos(ju(3)) xtl*sin(ju(3))-ytl*cos(ju(3)) ytl];
z_top(1:7)=0;

axis([-50 50 -50 50 -110 20])
hold on
grid on


plot3(x_bottle,y_bottle,z_bottle,'k','linewidth',5);

for i=1:6
    x_topk=(x_top(i)*cos(b)+z_top(i)*sin(b))*cos(r)-y_top(i)*sin(r);
    y_topk=(y_top(i)*cos(a)-z_top(i)*sin(a))*cos(r)+x_top(i)*sin(r);
    z_topk=(y_top(i)*sin(a)+z_top(i)*cos(a))*cos(b)-x_top(i)*sin(b);
    x_top(i)=x_topk;
    y_top(i)=y_topk;
    z_top(i)=z_topk;
end
x_top(7)=x_top(1);
y_top(7)=y_top(1);
z_top(7)=z_top(1);

xp=px*ones(1,7);
yp=py*ones(1,7);
x_top=x_top+xp;
y_top=y_top+yp;
plot3(x_top,y_top,z_top,'k','linewidth',5);

length=sqrt((x_top-x_bottle).^2+(y_top-y_bottle).^2+(z_top-z_bottle).^2);

for i=1:6
    plot3([x_top(i) x_bottle(i)],[y_top(i) y_bottle(i)],[z_top(i) z_bottle(i)],'r','linewidth',3);
end

ll=zeros(6,1);
for i=1:2:6
    last_er=1000;
    point=-90;
    for num=-90:1:90
        ap(i)=num/360*2*pi;
        a=0;
        b=0;
        r=ju(4+(i-1)/2);
        x_bottlek=(x_bottle(i)*cos(0)+z_bottle(i)*sin(b))*cos(r)-y_bottle(i)*sin(r);
        y_bottlek=(y_bottle(i)*cos(a)-z_bottle(i)*sin(a))*cos(r)+x_bottle(i)*sin(r);
        z_bottlek=(y_bottle(i)*sin(a)+z_bottle(i)*cos(a))*cos(b)-x_bottle(i)*sin(b);
        x_topk=(x_top(i)*cos(b)+z_top(i)*sin(b))*cos(r)-y_top(i)*sin(r);
        y_topk=(y_top(i)*cos(a)-z_top(i)*sin(a))*cos(r)+x_top(i)*sin(r);
        z_topk=(y_top(i)*sin(a)+z_top(i)*cos(a))*cos(b)-x_top(i)*sin(b);
        
        er=abs(2*duo*(z_bottlek-z_topk)*sin(ap(i))-2*duo*((y_bottlek-y_topk)*cos(ap(i)))+length(i).^2+duo.^2-len.^2);
        if(er<last_er)
            last_er=er;
            point=num;
        end
    end
    ap(i)=point/360*2*pi;
    
    a=0;
    b=0;
    r=ju(1+(i-1)/2);
    x_bottlet=(x_bottlek*cos(0)+(z_bottlek+duo*sin(ap(i)))*sin(b))*cos(r)-(y_bottlek-duo*cos(ap(i)))*sin(r);
    y_bottlet=((y_bottlek-duo*cos(ap(i)))*cos(a)-(z_bottlek+duo*sin(ap(i)))*sin(a))*cos(r)+x_bottlek*sin(r);
    z_bottlet=((y_bottlek-duo*cos(ap(i)))*sin(a)+(z_bottlek+duo*sin(ap(i)))*cos(a))*cos(b)-x_bottlek*sin(b);
        
    ll(i)=sqrt((x_bottlet-x_top(i)).^2+(y_bottlet-y_top(i)).^2+(z_bottlet-z_top(i)).^2);    
    plot3([x_bottle(i) x_bottlet],[y_bottle(i) y_bottlet],[z_bottle(i) z_bottlet],'m','linewidth',3);
    plot3([x_bottlet x_top(i)],[y_bottlet y_top(i)],[z_bottlet z_top(i)],'b','linewidth',3);
end

for i=2:2:6
    last_er=1000;
    point=-90;
    for num=-90:1:90
        ap(i)=num/360*2*pi;
        a=0;
        b=0;
        r=ju(4+(i-2)/2);
        x_bottlek=(x_bottle(i)*cos(0)+z_bottle(i)*sin(b))*cos(r)-y_bottle(i)*sin(r);
        y_bottlek=(y_bottle(i)*cos(a)-z_bottle(i)*sin(a))*cos(r)+x_bottle(i)*sin(r);
        z_bottlek=(y_bottle(i)*sin(a)+z_bottle(i)*cos(a))*cos(b)-x_bottle(i)*sin(b);
        x_topk=(x_top(i)*cos(b)+z_top(i)*sin(b))*cos(r)-y_top(i)*sin(r);
        y_topk=(y_top(i)*cos(a)-z_top(i)*sin(a))*cos(r)+x_top(i)*sin(r);
        z_topk=(y_top(i)*sin(a)+z_top(i)*cos(a))*cos(b)-x_top(i)*sin(b);
        
        er=abs(2*duo*(z_bottlek-z_topk)*sin(ap(i))+2*duo*((y_bottlek-y_topk)*cos(ap(i)))+length(i).^2+duo.^2-len.^2);
        if(er<last_er)
            last_er=er;
            point=num;
        end
        
    end
    
        ap(i)=point/360*2*pi;
        a=0;
        b=0;
        r=ju(1+(i-2)/2);
        x_bottlet=(x_bottlek*cos(0)+(z_bottlek+duo*sin(ap(i)))*sin(b))*cos(r)-(y_bottlek+duo*cos(ap(i)))*sin(r);
        y_bottlet=((y_bottlek+duo*cos(ap(i)))*cos(a)-(z_bottlek+duo*sin(ap(i)))*sin(a))*cos(r)+x_bottlek*sin(r);
        z_bottlet=((y_bottlek+duo*cos(ap(i)))*sin(a)+(z_bottlek+duo*sin(ap(i)))*cos(a))*cos(b)-x_bottlek*sin(b);
        
    ll(i)=sqrt((x_bottlet-x_top(i)).^2+(y_bottlet-y_top(i)).^2+(z_bottlet-z_top(i)).^2);        
    plot3([x_bottle(i) x_bottlet],[y_bottle(i) y_bottlet],[z_bottle(i) z_bottlet],'m','linewidth',3);
    plot3([x_bottlet x_top(i)],[y_bottlet y_top(i)],[z_bottlet z_top(i)],'b','linewidth',3);
end

pause(0.01);
 clf
end
end