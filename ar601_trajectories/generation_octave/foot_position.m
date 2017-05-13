function [ res] = foot_position( x,y,teta,left)

global offset

if left==1
    res=[x-offset*cos(teta),y-offset*sin(teta),teta];

else
    res=[x+offset*cos(teta),y+offset*sin(teta),teta];
end
end

