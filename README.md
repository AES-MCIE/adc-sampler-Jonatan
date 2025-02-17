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

El script fue creado para realizar de 500 a 1000 mediciones con el ADC0 de una BeagleBone Black con una frecuencia
de muestreo de 2 kHz y con ellas calcular:

* Promedio: Suma de todos los valores dividido entre el numero de mediciones. 

![](./promedio.png)

donde `Nmes` son la cantidad de mediciones y `xi` el valor medido. 

* Mediana: Valor que se encuentra en la posición central de los valores medidos y ordenados. En caso de que el número de datos sea par, se calcula el promedio de los datos centrales, como se aprecia en la imagen. 

![](./mediana.png)

* Histograma: Es una representación gráfica de la distribución de los datos.

* RMS: Valor efectivo. 

![](./RMS.png)

donde `Nmes` son la cantidad de mediciones y `xi` el valor medido.

* Valor mínimo.

* Valor máximo.

# Características de los ADC de la BeagleBone Black

**ADC**: Es un convertidor analógico-digital. 

Las características de los ADC de la BeagleBone Black son:

* Siete canales (`AIN0`-`AIN6`).
* 12 bits de resolución.
* 125 ns de tiempo de muestreo. 
* Rango de medición de 0 a 1.8V.
* Cuenta con un pin especial para voltaje analógico llamado `VDD_ADC` y una tierra especial llamada `GNDA_ADC`.

![](./bbb.png)

# Acondicionamiento de la señal

Para realizar el acondicionamiento de la señal se hizo uso de un amplificador operacional,el cual es un dispositivo compacto activo y lineal de alta ganancia, diseñado para proporcionar la función de transferencia deseada.
Se compone de dos entradas (terminal inversora `-` y terminal no inversora `+`), una salida y las terminales de alimentación positiva y negativa, como se muestra en la imagen. 

![](./amplificador.png)

Los amplificadores se pueden configurar de diferentes maneras, sin embargo, se usó como amplificador inversor y sumador inversor.

- Amplificador inversor: La entrada no inversora se conecta a tierra, a la entrada inversora se conecta el voltaje a amplificar (V1) mediante una resistencia R1, finalmente, la resistencia Rf se conecta a la salida 
y a la terminar inversora, en la imagen se muestran las conexiones de esta configuración y la fórmula del voltaje de salida. 

![](./inversor.png)

- Amplificador sumador inversor: Tiene varias fuentes de voltaje conectadas a la terminal inversora mediante resistencias, se pueden sumar n voltajes; la resistencia Rf se conecta a la salida y a la terminar inversora; la terminal no inversora se conecta a tierra. En la imagen se muestra el circuito de un amplificador sumador y la fórmula del voltaje de salida. 

![](./sumador.png)

## Circuito utilizado

Para acondicionar la señal, primero se hizo uso de un amplificador inversor, con el fin de reducir la amplitud del voltaje de entrada, 
ya que tiene voltaje de pico a pico de 3V y se necesita que tenga voltaje de pico a pico de 1.8V, se redujó a la mitad la amplitud de la señal con
una combinación de resistencias de 2k ohms y 1k ohms, reduciendo el voltaje pico a pico a 1.5V pero aún con parte negativa y señal invertida. 

La segunda parte del circuito es un sumador inversor, con resistencias iguales para no afectar la magnitud de los voltajes, cuyo propósito es sumarle
un voltaje para poder cambiar de nivel el voltaje y que permanezca arriba de cero, para ello se le suma una señal de -1V, con ello se elimina la 
parte positiva de la señal y se le suma a la parte negativa; finalmente, como el circuito invierte la suma de los voltajes, se tiene una señal que va,
aproximadamente, de 0.160V a 1.36V. En la imagen se muestra el circuito utilizado junto con los valores de las resistencias.

![](./acondicionador.png)

## Implementacion del circuito

La señal utilizada se creó en un generador, la cual tiene voltaje de pico de 1.3 Volts, de tipo senoidal y a una frecuencia de 100 Hz, como se muestra en la imagen.

![](./generador.png)

Se armó el circuito mostrado en la sección `Circuito utilizado` y utilizando el amplificador `LM324N`, quedando como se muestra en la siguiente imagen.

![](./circuitoFisico.png)

La señal de salida del circuito se conectó a un osciloscopio, la cual tiene un voltaje mínimo de 160 mV y máxima de 1.36V, por lo que se puede conectar sin problema al AIN0 de la BeagleBone Black.

![](./osciloscopio.png)

## Conexión del circuito con la BeagleBone Black

A continuación se muestra la conexión final del circuito de acondicionamiento con el AIN0, la conexión con los pines de la BeagleBone Black, el generador de señales y el osciloscopio.

![](./esquematico.png)

### Consideraciones durante la conexión del circuito. 

- Para la medición de señales con los ADCs, la tierra se debe de conectar al pin con el nombre `GND_ADC`.
- Hacer la conexión primero del circuito acondicionador y verificar el voltaje de salida con el osciloscopio antes de conectar al ADC para evitar quemarlo. 
- En la desconexión, primero desconectar el pin del ADC y luego apagar el circuito acondicionador, ya que al usarse voltaje negativo para eliminar el offset, el pin del ADC se quemará si lo recibe directamente.

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

El pin que se usa como entrada es `AIN0`, que se puede observar en la parte izquierda de la imagen colocada en la sección `Características de los 
ADC de la BeagleBone Black`. 

El script desarrollado es muy sencillo de usar, ya que solamente recibe un parámetro, el cual es el número de mediciones que se desean
registrar o help:
```
./archivo_salida x
```
En donde `x` es el número de mediciones, el cual puede ir de 500 a 1000.

```
./archivo_salida help
```

Al colocar `help`, se muestran los comandos disponibles y las mediciones que realiza el script.  

## Nota

Cada línea `|` del histograma representa que se realizó una medición en el rango indicado a la izquierda, se dividió el rango de valores de 0 a 4095 
puede otorgar el ADC, en 25 rangos, cada uno de 164 unidades.

# Resultados

A continuación se muestran los resultados al ejecutar el script con diferente cantidad de mediciones realizadas. 

Lo primero es compilar el archivo `main.c` con el comando:
```
gcc main.c -o adc-meas -lm
```

En la siguiente imagen se observa el resultado mostrado en terminal al ejecutar el script para realizar 500 mediciones con el siguiente comando:
```
./adc-meas 500
```

![](./shell2.png)

En la siguiente imagen se observa el resultado mostrado en terminal al ejecutar el script para realizar 1000 mediciones con el siguiente comando:
```
./adc-meas 1000
```

![](./shell.png)

