a=importdata("particles.dat");
n_particle=a(1,1);
iterations=a(1,2);
figure
hold on
for i=1:n_particle
    plot(a((i+1):n_particle:end,1),a((i+1):n_particle:end,2),'.');
end
axis equal



        