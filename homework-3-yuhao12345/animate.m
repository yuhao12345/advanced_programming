nt = ntimes;
nb = nbodies;
xmax = max(nbody(:,1));
ymax = max(nbody(:,2));
xmin = min(nbody(:,1));
ymin = min(nbody(:,2));
axis manual;
%xmax = 100;
%ymax = 100;
%xmin = -100;
%ymin = -100;

axis([xmin,xmax, ymin,ymax]);
gc = scatter(nbody(1:nb,1), nbody(1:nb,2));
for i=1:nt-1
    disp(i)
    axis([xmin,xmax, ymin,ymax]);
    ntmin = i*nb+1; ntmax = (i+1)*nb;
    set(gc,'xdata',nbody(ntmin:ntmax,1), 'ydata', nbody(ntmin:ntmax,2));
    pause(.01);
end