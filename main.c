//Jonatan Ali Medina
//Molina                                                                                                                                                                                                        
 //6/03/2023
 //Mediciones con el ADC usando C
 //ADC0 <----- input
  /*
  *   Descripcion:
  *  - [x] Valor minimo
  *  - [x] Valor maximo
  *  - [x] Promedio
  *  - [x] Mediana
  *  - [x] Histograma
  *  - [x] RMS
  *  - [ ] Densidad de potencia
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
	double SumRMS = 0.0;
	double promedio = 0.0;
	double rms = 0.0;
	double mediana = 0.0;

    //Cuando los argumentos no son dos
    if(argc != 2){
        printf("No. de argumentos: %d\n", argc);
        printf("El comando es: ./adc n\n");
        printf("Donde n es el numero de lecturas\n");
        return 2;
    }
    //Convertir el argumento a entero
    int Nmes = strtol(argv[1], NULL, 10);
	if(Nmes < 10 || Nmes > 1000){
		printf("Numero de mediciones incorrecto\n");
		printf("EL script solo admite valores de 500-1000\n");
		printf("Intente ./nombre_archivo 500\n");
		return 2;
	}

    printf("No. de repeticiones: %d\n", Nmes);
    FILE *fp;
    char reads[80];
	int mediciones[Nmes];
	int control = 0;
	//Ciclos de n lecturas
    for(i = 0; i < Nmes; i++){
        fp = fopen(ADC0, "rt");
        fgets(reads, 20, fp);
        //printf("%s", reads);
		mediciones[i] = strtol(reads, NULL, 10);
		//Registrar max y min
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
		//Suma de valores para promedio
		SumPro = SumPro + mediciones[i];
		//Suma de valores rms
		SumRMS = SumRMS + pow(mediciones[i]/100.0, 2);
        sleep(0.01);
    }
	//Calculo de mediana
	if(Nmes % 2 == 0){
		int divi = (Nmes-1)/2;
		//printf("%d\n",divi);
		mediana =(mediciones[divi]+mediciones[divi+1])/2;
	}
	else {
		int divi = (Nmes-1)/2;
		//printf("%d\n",divi);
		mediana = mediciones[divi];
	}

	printf("RMS1 = %f\n",SumRMS);

	promedio = SumPro/Nmes;
	rms =sqrt(SumRMS/Nmes);
	rms = rms*100.0;
	printf("El promedio es: %f\n", promedio);
	printf("El valor RMS es: %f\n", rms);
	printf("El valor minimo es: %d\n",min);
	printf("El valor maximo es: %d\n",max);
	printf("Mediana: %f\n",mediana);
	printf("\n\nHistograma de mediciones\n\n");
	//Impresion de histograma
	int aux = 0;
	int contador = 0;
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
	printf("\n");
    return 0;
}

