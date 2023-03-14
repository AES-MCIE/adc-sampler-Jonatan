# adc-sampler
Implement the next Data logger for the adc using C to program the function to collet 500-1000 samples and computes the required data.

![](./adc.001.jpeg)



# Antes de iniciar

Para poder ejecutar el script es necesario tener instalado ´gcc´, para comprobarlo teclee el siguiente comando:
```
gcc -version
```
Si le aparece una versión instalada, ya está listo para iniciar, en caso contrario, se puede instalar `gcc` con el comando: 
```
sudo apt install GCC
```

# Muestreo con ADC0 en BeagleBone Black

El script fue creado para realizar de 500 a 1000 mediciones con el ADC0 de una BeagleBone Black y con ellas calcular:

*Promedio: Suma de todos los valores dividido entre el numero de mediciones. 

![](./promedio.png)

donde `Nmes` son la cantidad de mediciones y `xi` el valor medido. 

*Mediana: Valor que se encuentra en la posición central de los valores medidos. En caso de que el número de datos sea par, se calcula el promedio de los datos centrales, como se aprecia en la imagen. 

![](./mediana.png)

*Densidad de potencia.

*Mostrar histograma.

*RMS: Valor efectivo. 

![](./RMS.png)

donde `Nmes` son la cantidad de mediciones y `xi` el valor medido.

*Valor mínimo.

*Valor máximo.

# Acondicionamiento de la señal

Para realizar el acondicionamiento de la señal se hizo uso de un amplificador operacional,el cual es un dispositivo compacto activo y lineal de alta ganancia, diseñado para proporcionar la función de transferencia deseada.
Se compone de dos entradas (terminal inversora '-' y terminal no inversora '+') y una salida, además de las terminales de alimentación positiva y negativa, como se muestra en la imagen. 

![](./amplificador.png)

Los amplificadores se pueden configurar de diferentes maneras, sin embargo, se usó como amplificador inversor y sumador.

- Amplificador inversor: La entrada no inversora se conecta a tierra, a la entrada inversora se conecta el voltaje a amplificar (V1) mediante una resistencia R1, finalmente, la resistencia Rf se conecta a la salida 
y a la terminar inversora, en la imagen se muestran las conexiones de esta configuración y la fórmula del voltaje de salida. 

![](./inversor.png)

- Amplificador sumador: Tiene varias fuentes de voltaje conectadas a la terminal inversora mediante resistencias, se pueden sumar n voltajes; la resistencia Rf se conecta a la salida y a la terminar inversora; la terminal no inversora se conecta a tierra. En la imagen se muestra el circuito de un amplificador sumador y la fórmula del voltaje de salida. 

![](./sumador.png)

## Circuito utilizado

Para acondicionar la señal, primero se hizo uso de un amplificador inversor, con el fin de reducir la amplitud del voltaje de entrada, ya que tiene voltaje de pico a pico de 3V y se necesita que tenga voltaje de pico a 
pico de 1.8V, en esta parte se sigue teniendo una señal de AC pero invertida respecto de la original. La segunda parte del circuito es un sumador, cuya propósito es sumarle un voltaje para poder mover el offset del 
voltaje que sale del inversor, para ello se le suma un voltaje de -0.9V, con ello se elimina la parte positiva de la señal y se le suma a la parte negativa; finalmente, como el circuito invierte la suma de los voltajes, se tiene
una señal que va de 0 a 1.8V. En la imagen se muestra el circuito utilizado junto con los valores de las resistencias.

# Antes de ejecutar el script

Para poder utilizar el script, es necesario primero compilarlo con `gcc`, el comando es:
```
gcc main.c -o archivo_salida -lm
```
Se le puede colocar el nombre que se desee en `archivo_salida`, solamente que se debe tener en cuenta que ese nombre es el que 
se escribirá a la hora de ejecutar el script. 

**IMPORTANTE** 

- Para compilar el archivo es necesario que se encuentre en la carpeta en la que se tiene almacenado.

- Ya no es necesario darle permisos de ejecución a `archivo_salida`, ya que tiene el permiso desde que se crea.

# Modo de uso

El pin que se usa como entrada es `AIN0`, que se puede observar en la parte izquierda de la imagen. 

![](./bbb.png)

El script desarrollado es muy sencillo de usar, ya que solamente recibe un parámetro, el cual es el número de mediciones que se desean
registrar, el comando es:
```
./archivo_salida x
```
En donde `x` es el número de mediciones, el cual puede ir de 500 a 1000.

# Nota

Cada línea `|` del histograma representa 20 unidades del valor medido, esto se realizó para que se pudiera visualizar bien en la
terminal, aun así, puede que no quepa en pantalla, por lo que puede que se necesite alejar la vista.
