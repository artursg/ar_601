global t0
offset=0.09;
T=0.004;
zmp_x_offset=0.02;

t0=300.0;

%still
left=[-offset 0 0;-offset 0 0;-offset 0 0];
right=[offset 0 0;offset 0 0;offset 0 0];

x_left=zeros(1,t0/T);
y_left=ones(1,t0/T)*offset;
z_left=zeros(1,t0/T);
teta_left=zeros(1,t0/T);

x_right=zeros(1,t0/T);
y_right=ones(1,t0/T)*(-offset);
z_right=zeros(1,t0/T);
teta_right=zeros(1,t0/T);

zmp_x=ones(1,t0/T)*zmp_x_offset;
zmp_y=zeros(1,t0/T);

teta_torso=zeros(1,t0/T);

result_matrix=[x_left' y_left' z_left' teta_left' x_right' y_right' z_right' teta_right' zmp_x' zmp_y' teta_torso'];
%dlmwrite('still.traj',result_matrix);
dlmwrite('~/catkin_ws/src/ar_601/ar601_trajectories/trajectories/still.traj',result_matrix);



