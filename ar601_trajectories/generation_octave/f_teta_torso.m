function [ x ] = f_teta_torso( t,x1,x2 )
global t0


if abs(x1-x2)<pi
    x=0.5*(x2-x1)*(1-cos(pi*(t)/(t0)))+x1;
else
    if x1<0
        x=0.5*(x2-2*pi-x1)*(1-cos(pi*(t)/(t0)))+x1;
        if x<=-pi
            x=x+2*pi;
        end
    else
        x=0.5*(x2+2*pi-x1)*(1-cos(pi*(t)/(t0)))+x1;
        if x>pi
            x=x-2*pi;
        end
    end
end
    
    
end

