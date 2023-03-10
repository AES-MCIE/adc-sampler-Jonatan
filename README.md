# adc-sampler
Implement the next Data logger for the adc using C to program the function to collet 500-1000 samples and computes the required data.

![](./adc.001.jpeg)

# Muestreo con ADC0 en BeagleBone Black

El script fue creado para realizar de 500 a 1000 mediciones y con ellas calcular:

*Promedio.

*Mediana.

*Densidad de potencia.

*Mostrar histograma.

*RMS.

*Valor minimo.

*Valor maximo.

# Antes de ejecutar el script
Para poder utilizar el script, es necesario primero compilarlo con `gcc`, el comando completo seria:
```
gcc main.c -o archivo_salida -lm
```
Se le puede colocar el nombre que se desee en `archivo_salida`, solamente que se debe tener en cuenta que ese nombre es el que 
se escribira a la hora de ejecutar el script. 

**IMPORTANTE** 

- Para compilar el archivo es necesario que se encuentre en la carpeta en la que se tiene almacenado.

- Ya no es necesario darle permisos de ejecucion a `archivo_salida`, ya que tiene el permiso al momento de crearse.

# Modo de uso
El script desarrollado es muy sencillo de usar, ya que solamente recibe un parametro, el cual es el numero de mediciones que se desean
registrar, por lo que el comando es:
```
./archivo_salida x
```
En donde `x` es el numero de mediciones, el cual puede ir de 500 a 1000.
