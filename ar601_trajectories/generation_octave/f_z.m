function [ z ] = f_z(t,up)

global t0 p_ds h

if up==1
    
    if t<=p_ds*t0
        z=0;
    else
        z=0.5*h*(1-cos(2*(1/(t0-p_ds*t0))*pi*(t-p_ds*t0)));
    end
    
else
    z=0;
end

end

