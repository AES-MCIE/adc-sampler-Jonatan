//Jonatan Ali Medina
//Molina                                                                                                                                                                                                        
 //6/03/2023
 //Mediciones con el ADC usando C
 //ADC0 <----- input
  /*
  *   Descripcion:
  *  - [x] ADC0 test
  *  - [x] print ADC0 9 veces
  *  - [x] pass the n as argument
  *  - [x] print ADC0 n veces
  * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
  
#define ADC0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
int main(int argc, char *argv[]){
    printf("Script ejecutandose\n");
    int i;
	int j;
	int min = 0;
	int max = 0;
	unsigned long int SumPro = 0;
	unsigned long int SumRMS1 = 0;
	unsigned long int SumRMS2 = 0;
	unsigned long int SumRMS3 = 0;
	unsigned long int SumRMS4 = 0;
	long long sRMS = 0;
	double promedio = 0;
	double rms = 0;

    //Cuando los argumentos no son dos
    if(argc != 2){
        printf("No. de argumentos: %d\n", argc);
        printf("El comando es: ./adc n\n");
        printf("Donde n es el numero de lecturas\n");
        return 2;
    }
    //Convertir el argumento a entero
    int Nmes = strtol(argv[1], NULL, 10);
	if(Nmes < 500 || Nmes > 1000){
		printf("Numero de mediciones incorrecto\n");
		printf("EL script solo admite valores de 500-1000\n");
		printf("Intente ./adc-meas 500\n");
		return 2;
	}

    printf("No. de repeticiones: %d\n", Nmes);
    FILE *fp;
    char reads[80];
	int mediciones[Nmes];
	int contador = 0;
	int control = 0;
	//Ciclos de n lecturas
    for(i = 0; i < Nmes; i++){
        fp = fopen(ADC0, "rt");
        fgets(reads, 20, fp);
        //printf("%s", reads);
		mediciones[i] = strtol(reads, NULL, 10);
		if (i == 0 ){
			min = mediciones[i];
			max = mediciones[i];
		}
		else{
			if (min > mediciones[i]){
				min = mediciones[i];
			}
			if (max < mediciones[i]){
				max = mediciones[i];
			}
		}
		SumPro = SumPro + mediciones[i];
		contador++;
		if (contador <= 250){
			SumRMS1 = SumRMS1 + pow(mediciones[i], 2);
		}
		else if (contador > 250 && contador <= 500){
			SumRMS2 = SumRMS2 + pow(mediciones[i], 2);
		}
		else if (contador > 500 && contador <= 750){
			SumRMS3 = SumRMS3 + pow(mediciones[i], 2);
		}
		else {	
			SumRMS4 = SumRMS4 + pow(mediciones[i], 2);
		}
		
        sleep(0.01);
    }
	printf("RMS1 = %lu\n",SumRMS1);
	printf("RMS2 = %lu\n",SumRMS2);
	printf("RMS3 = %lu\n",SumRMS3);
	printf("RMS4 = %lu\n",SumRMS4);
	promedio = SumPro/Nmes;
	sRMS = SumRMS1+SumRMS2+SumRMS3+SumRMS4;
	printf("%f\n", sRMS);
	rms =sqrt(sRMS/Nmes);
	printf("El promedio es: %f\n", promedio);
	printf("El valor RMS es: %f\n", rms);
	printf("El valor minimo es: %d\n",min);
	printf("El valor maximo es: %d\n",max);
	printf("\n\nHistograma de mediciones\n\n");
	int aux = 0;
	for(i = 0; i < Nmes; i++){
		contador = mediciones[i];
		if(i < 9){
			printf("000%d]  ", i+1);
		}
		else if (i > 8 && i < 99){
			printf("00%d]  ", i+1);
		}
		else if (i > 98 && i < 999){
			printf("0%d]  ", i+1);
		}
		else {
			printf("%d]  ", i+1);
		}
		for(j = 0; j <= contador; j++){
			aux++;
			if (aux == 20){
				aux = 0;
				printf("|");
			}
		}
		printf("\n");
	}
    return 0;
}

