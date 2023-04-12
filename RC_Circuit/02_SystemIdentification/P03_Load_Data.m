clc; clear; close all;

%% Cargamos la data filtrada
filename = 'data.csv';
data = readtable(filename);
data = table2array(data);

%% Asignamos variables
t = data(:, 1);
In = data(:, 4);
Out = data(:, 5);

%% Guardamos la data
save Data.mat In Out

%% Ploteo
grid on
plot(t, In);
plot(t, In, 'blue', t, Out, 'r--');