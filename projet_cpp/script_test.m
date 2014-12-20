clear all;
close all;

toto=importdata('test.txt')


hold on;
plot(toto(:,1),toto(:,2),toto(:,1),toto(:,3))
