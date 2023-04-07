clc; clear; close all;

%% Load data
load TF.mat

%% Transfer function
num = tf2.Numerator;
den = tf2.Denominator;

sys = tf(num, den);

sysd = c2d(sys, 0.01,'zoh')
