function [ x ] = f_zmp_x(t,x1,x2 )
global t0 p_ds

if t<=p_ds*t0
    x=hermit(t,x1,x2);
else
    x=x2;
end

end

