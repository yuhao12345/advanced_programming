nbody = load('particles.dat','-ascii');
nbodies = nbody(1,1); ntimes = nbody(1,2);
nbody = nbody(2:end,:); %remove header
%nbody = reshape(nbody, ntimes, nbodies, 3); %chunk by time
