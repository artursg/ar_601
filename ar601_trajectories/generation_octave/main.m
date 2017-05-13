global x y l_max teta_max offset left_flag
global t0 p_ds h
l_max=0.15;
teta_max=5*pi/180;
offset=0.09;

N=100;
t=0:1:N;
%x=0.1-0.1*cos(2*pi*(t)/(N));
%y=1*sin(2*pi*(t)/(N));
y=0.01*t;
x=0*t;

left_flag=1;
[left,right,steps]=planner;

t_preview=2;
T=0.004;
t0=3;
p_ds=0.2;
h=0.04;
zmp_x_offset=0.02;

x_left=[];y_left=[];z_left=[];teta_left=[];
x_left_next=zeros(1,t0/T);y_left_next=zeros(1,t0/T);z_left_next=zeros(1,t0/T);teta_left_next=zeros(1,t0/T);

x_right=[];y_right=[];z_right=[];teta_right=[];
x_right_next=zeros(1,t0/T);y_right_next=zeros(1,t0/T);z_right_next=zeros(1,t0/T);teta_right_next=zeros(1,t0/T);

zmp_x=[];zmp_y=[];zmp_x_next=zeros(1,t0/T);zmp_y_next=zeros(1,t0/T);
teta_torso=[];teta_torso_next=zeros(1,t0/T);

x_left(1:t_preview/T)=left(1,2);
y_left(1:t_preview/T)=-left(1,1);
z_left(1:t_preview/T)=0;
teta_left(1:t_preview/T)=0;

x_right(1:t_preview/T)=right(1,2);
y_right(1:t_preview/T)=-right(1,1);
z_right(1:t_preview/T)=0;
teta_right(1:t_preview/T)=0;

zmp_x(1:t_preview/T)=0;
zmp_y(1:t_preview/T)=0;
teta_torso(1:t_preview/T)=0;

for k=1:(steps-1)

for i=0:(t0/T-1)
    t=i*T;
    x_left_next(i+1)=f_x(t,left(k,2),left(k+1,2));
    y_left_next(i+1)=f_x(t,-left(k,1),-left(k+1,1));
    z_left_next(i+1)=f_z(t,left_flag);
    teta_left_next(i+1)=f_teta(t,left(k,3),left(k+1,3));
    x_right_next(i+1)=f_x(t,right(k,2),right(k+1,2));
    y_right_next(i+1)=f_x(t,-right(k,1),-right(k+1,1));
    z_right_next(i+1)=f_z(t,-left_flag);
    teta_right_next(i+1)=f_teta(t,right(k,3),right(k+1,3));
    
    if k==1
        zmp_x_next(i+1)=f_zmp_x(t,0,zmp_x_offset);
        if left_flag==1
            zmp_y_next(i+1)=f_zmp_x(t,0,-right(k+1,1));
        else
            zmp_y_next(i+1)=f_zmp_x(t,0,-left(k+1,1));
        end
    else
        if left_flag==1
            zmp_x_next(i+1)=f_zmp_x(t,left(k,2)+zmp_x_offset*cos(left(k,3)),right(k+1,2)+zmp_x_offset*cos(right(k+1,3)));
            zmp_y_next(i+1)=f_zmp_x(t,-left(k,1)-zmp_x_offset*sin(left(k,3)),-right(k+1,1)-zmp_x_offset*sin(right(k+1,3)));
        else
            zmp_x_next(i+1)=f_zmp_x(t,right(k,2)+zmp_x_offset*cos(right(k,3)),left(k+1,2)+zmp_x_offset*cos(left(k+1,3)));
            zmp_y_next(i+1)=f_zmp_x(t,-right(k,1)-zmp_x_offset*sin(right(k,3)),-left(k+1,1)-zmp_x_offset*sin(left(k+1,3)));
        end          
    end
    
    if left_flag==1
        teta_torso_next(i+1)=f_teta(t,right(k,3),left(k+1,3)); %%could be torso function for teta
    else
        teta_torso_next(i+1)=f_teta(t,left(k,3),right(k+1,3));
    end
    
end
x_left=[x_left,x_left_next];
y_left=[y_left,y_left_next];
z_left=[z_left,z_left_next];
teta_left=[teta_left,teta_left_next];
x_right=[x_right,x_right_next];
y_right=[y_right,y_right_next];
z_right=[z_right,z_right_next];
teta_right=[teta_right,teta_right_next];
zmp_x=[zmp_x,zmp_x_next];
zmp_y=[zmp_y,zmp_y_next];
teta_torso=[teta_torso,teta_torso_next];

left_flag=-left_flag;
end

x_left=[x_left,ones(1,t_preview/T)*x_left(length(x_left))];
y_left=[y_left,ones(1,t_preview/T)*y_left(length(y_left))];
z_left=[z_left,ones(1,t_preview/T)*z_left(length(z_left))];
teta_left=[teta_left,ones(1,t_preview/T)*teta_left(length(teta_left))];
x_right=[x_right,ones(1,t_preview/T)*x_right(length(x_right))];
y_right=[y_right,ones(1,t_preview/T)*y_right(length(y_right))];
z_right=[z_right,ones(1,t_preview/T)*z_right(length(z_right))];
teta_right=[teta_right,ones(1,t_preview/T)*teta_right(length(teta_right))];
teta_torso=[teta_torso,ones(1,t_preview/T)*teta_torso(length(teta_torso))];


zmp_x_next=zeros(1,t_preview/T);
zmp_y_next=zeros(1,t_preview/T);
for i=0:(t_preview/T-1)
    t=i*T;
    zmp_x_next(i+1)=f_zmp_x(t,zmp_x(length(zmp_x)),0.5*(left(steps,2)+right(steps,2)));
    zmp_y_next(i+1)=f_zmp_x(t,zmp_y(length(zmp_y)),0.5*(-left(steps,1)-right(steps,1)));
end
    
zmp_x=[zmp_x,zmp_x_next];
zmp_y=[zmp_y,zmp_y_next];


result_matrix=[x_left' y_left' z_left' teta_left' x_right' y_right' z_right' teta_right' zmp_x' zmp_y' teta_torso'];
%dlmwrite('0.traj',result_matrix);
dlmwrite('~/catkin_ws/src/ar_601/ar601_trajectories/trajectories/0.traj',result_matrix);











