function [ x ] = f_x( t,x1,x2 )
global t0 p_ds

vertical_time=0.5;

if t<=p_ds*t0
    x=x1;
else
    if t>=(t0-vertical_time)
        x=x2;
    else
        x=0.5*(x2-x1)*(1-cos(pi*(t-p_ds*t0)/(t0-p_ds*t0-vertical_time)))+x1;
    end
end


end

