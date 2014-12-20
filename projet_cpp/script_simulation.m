clear all;
close all;

toto=importdata('Simulation.txt')


hold on;
plot(toto(:,1),toto(:,2),toto(:,1),toto(:,3))
