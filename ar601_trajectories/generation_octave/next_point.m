function [ res ] = next_point(k_p,x_p,y_p,teta_p)

global x y l_max teta_max

l_max_f=l_max;
k=k_p;
res=[];

while (l_max_f>=-0.001)    

   if(abs(l_max_f)<=1e-5)
   
   if abs(teta-teta_p)>pi
       teta_new=teta_p-teta_max*sign(teta); %%teta at 0.01
   else
       teta_new=teta_p+teta_max*sign(teta-teta_p);
   end
 
   if abs(teta_new)>pi
       res=[k_p,x_p,y_p,-sign(teta_new)*2*pi+teta_new];
   else
       res=[k_p,x_p,y_p,teta_new];
   end
   
   break 
   end 

   
teta=7;
while (k<=length(x))
    l=sqrt((x(k)-x_p)^2+(y(k)-y_p)^2);
    if (l>=l_max_f) || ((k==length(x))&&k_p~=1)
        ugol=atan2((y(k)-y(k-1)),(x(k)-x(k-1)));
        if ugol<-pi/2
            teta=ugol+1.5*pi;
        else
            teta=ugol-0.5*pi;
        end
        break
    end
    k=k+1;
end

if teta~=7
    
delta=abs(teta-teta_p);
if delta>pi
    delta=2*pi-delta;
end
if(delta<=teta_max)
    res=[k,x(k),y(k),teta];
    break
end

end


l_max_f=l_max_f-0.01;
k=k_p;



end

end

