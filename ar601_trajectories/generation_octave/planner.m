function [left,right,i]= planner()

global x y offset left_flag

left=zeros(1,3);
right=zeros(1,3);
center=zeros(1,3);
left_flag_s=left_flag;

k=1;
x_p=0;y_p=0;teta=0;
i=1;
left(i,1)=-offset;left(i,2)=0;left(i,3)=0;
right(i,1)=offset;right(i,2)=0;right(i,3)=0;
center(i,:)=[0 0 0];
res=[];

while (k<length(x))
res=next_point(k,x_p,y_p,teta);
i=i+1;
center(i,:)=[res(2) res(3) res(4)];
if left_flag_s==1
    left(i,:)=foot_position(res(2),res(3),res(4),1);
    right(i,:)=right(i-1,:);
else
    right(i,:)=foot_position(res(2),res(3),res(4),0);
    left(i,:)=left(i-1,:);
end
k=res(1);
x_p=res(2);y_p=res(3);teta=res(4);
left_flag_s=-left_flag_s;
end
i=i+1;
if left_flag_s==1
    left(i,:)=foot_position(res(2),res(3),res(4),1);
    right(i,:)=right(i-1,:);
else
    right(i,:)=foot_position(res(2),res(3),res(4),0);
    left(i,:)=left(i-1,:);
end

plot(x,y,'LineWidth',3,'LineStyle','--');
axis equal
hold on
quiver(center(:,1),center(:,2),-0.1*sin(center(:,3)),0.1*cos(center(:,3)),'color','blue','AutoScale','off');
quiver(right(:,1),right(:,2),-0.1*sin(right(:,3)),0.1*cos(right(:,3)),'color','red','AutoScale','off');
quiver(left(:,1),left(:,2),-0.1*sin(left(:,3)),0.1*cos(left(:,3)),'color','green','AutoScale','off');
