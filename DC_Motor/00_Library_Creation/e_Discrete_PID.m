clc; clear; close all;

%% Constants
Ts = 0.005;
P = 0.832986249315699;
I = 13.6979650476227;
D = -0.00498600607382707;
N = 18.0378273917559;

%% Transfer Function
z = tf('z', Ts);

Cz = P + I*Ts/(z-1) + D*N/(1 + N*Ts/(z-1));

display(Cz)
