clc; clear; close all;

%% Cargamos la data filtrada
filename = 'filtered_data.csv';
data = readtable(filename);
data = table2array(data);

%% Asignamos variables
t = data(:, 1);
In = data(:, 2);
Out = data(:, 3);

%% Guardamos la data
save Data.mat In Out

%% Ploteo
grid on
plot(t, In, 'b--', t, Out, 'r');