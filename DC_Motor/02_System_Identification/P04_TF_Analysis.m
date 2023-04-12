clc; clear; close all;

%% Load data
load TF.mat

%% Transfer function
num = tf2.Numerator;
den = tf2.Denominator;

sys = tf(num, den);

%% Discrete Transfer Function
z = tf('z', 0.005);
sysd = c2d(sys, 0.005,'zoh');
C = 1/(sysd*(z - 1)); % Dead Beat

numd = cell2mat(C.numerator);
dend = cell2mat(C.denominator);

display(sysd);
display(C);