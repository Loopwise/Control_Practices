# Library Creation & System Identification
## Library Creation

## Arduino Serial Communication with Python
Para la comunicación entre Arduino y Python se empleó la librería **pySerial**. Para instalarla se debe abrir la terminal y ejecutar el siguiente comando:  
```bash
pip install pyserial
```
Y posteriormente se guardará en el archivo _data.csv_ con el código *a_Serial_csv.py* y filtrada en *b_Plot_Data.m*.

Se emplea el filtro Media Móvil Exponencial:  
$
S(0) = Y(0) \\
S(n) = \alpha S(n-1) + (1-\alpha)Y(n)\\
\alpha \in [0,1]
$

## System Identification
Posteriormente a la lectura y guardado de la data por **Serial en Python** procederemos a cargar la data filtrada en Matlab haciendo uso del código *a_Load_Data.m*.  
En este código se cargan los datos de la data filtrada y se grafican los datos de la señal de entrada y salida.  
Procedemos a emplear _systemIdentification_.  

```matlab
systemIdentification
```
Cargamos la data filtrada y empleamos *Transfer Function Estimation* para estimar la función de transferencia del sistema, la cual debe tener la siguiente forma:


$
\frac{w(s)}{V_e(s)} = \frac{K_T}{L_aJ_ms^2 + (R_aJ_m+B_mL_a)s+(K_TK_E+R_aB_m)}
$  


En donde $K_T$ es la constante de torque, $K_E$ es la constante de emf, $R_a$ es la resistencia de armadura, $L_a$ es el inductancia de armadura, $J_m$ es el momento de inercia del motor, $B_m$ es la constante de fricción del motor, $J_s$ es el momento de inercia del sistema y $B_s$ es la constante de fricción del sistema.

### Con esto finaliza la primera parte de nuestro proyecto