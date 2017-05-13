function [y]=hermit(x,y0,y1)
    global t0  p_ds
    t=x/(p_ds*t0);
    h00=(1+2*t)*(1-t)^2;
    h01=t^2*(3-2*t);
    y=h00*y0+h01*y1;


