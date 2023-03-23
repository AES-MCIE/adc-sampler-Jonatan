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
	//int Nmes = strtol(argv[1], NULL, 10);
	//printf("%d\n", Nmes);
	char *valor = "help";
    //Cuando los argumentos no son dos
    if(argc != 2){
        printf("No. de argumentos: %d\n", argc);
        printf("El comando es: ./adc n\n");
        printf("Donde n es el numero de lecturas\n");
        return 2;
    }

	if(strcmp(argv[1], valor) == 0){
		printf("Autor: Jonatan Ali Medina Molina\n");
		printf("IT Morelia\n");
		printf("Morelia, Michoacan\n");
		printf("Marzo del 2023\n");
		printf("\n");
		printf("El script sirve para realizar de 500 a 1000 mediciones usando el AIN0 de una BeagleBone Black\n");
		printf("Realiza las siguientes acciones:\n");
		printf("* Histograma\n");
		printf("* Promedio\n");
		printf("* RMS\n");
		printf("* Maximo\n");
		printf("* Minimo\n");
		printf("* Mediana\n");
		printf("\n\n");
		printf("Los comandos disponibles son: \n");
		printf("%s help\n",argv[0]);
		printf("%s n\n",argv[0]);
		printf("Donde n es el numero de mediciones (de 500 a 1000)\n");
		return 1;
	}	
		//Convertir el argumento a entero
	int Nmes = strtol(argv[1], NULL, 10);
	if (Nmes > 0){
		if(Nmes < 500 || Nmes > 1000){
			printf("Numero de mediciones incorrecto\n");
			printf("EL script solo admite valores de 500-1000\n");
			printf("Para mas informacion introduzca %s help\n", argv[0]);
			return 2;
		}
	}
	else {
		printf("Comando no reconocido, para mas informacion introduzca %s help\n",argv[0]);
		return 2;
	}
    printf("No. de repeticiones: %d\n", Nmes);
    FILE *fp;
    char reads[80];
	int mediciones[Nmes];
	int ordenados[Nmes];
	int aux2 = 0;
	int control = 0;
	int histograma[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
	//Ciclos de n lecturas
    for(i = 0; i < Nmes; i++){
        fp = fopen(ADC0, "rt");
        fgets(reads, 20, fp);
        //printf("%s", reads);
		mediciones[i] = strtol(reads, NULL, 10);
		ordenados[i] = strtol(reads, NULL, 10);
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
	//Se ordena la matriz para la mediana y se calcula histograma
	for (i = 0; i < Nmes; i++){
		if(mediciones[i] <= 164){
			histograma[0] = histograma[0]+1;
		}
		else if(mediciones[i] > 164 && mediciones[i] <= 328){
			histograma[1] = histograma[1]+1;}		
		else if(mediciones[i] > 328 && mediciones[i] <= 492){
			histograma[2] = histograma[2]+1;}
		else if(mediciones[i] > 492 && mediciones[i] <= 656){
			histograma[3] = histograma[3]+1;}
		else if(mediciones[i] > 656 && mediciones[i] <= 820){
			histograma[4] = histograma[4]+1;}
		else if(mediciones[i] > 820 && mediciones[i] <= 984){
			histograma[5] = histograma[5]+1;}
		else if(mediciones[i] > 984 && mediciones[i] <= 1148){
			histograma[6] = histograma[6]+1;}
		else if(mediciones[i] > 1148 && mediciones[i] <= 1312){
			histograma[7] = histograma[7]+1;}
		else if(mediciones[i] > 1312 && mediciones[i] <= 1476){
			histograma[8] = histograma[8]+1;}
		else if(mediciones[i] > 1476 && mediciones[i] <= 1640){
			histograma[9] = histograma[9]+1;}
		else if(mediciones[i] > 1640 && mediciones[i] <= 1804){
			histograma[10] = histograma[10]+1;}
		else if(mediciones[i] > 1804 && mediciones[i] <= 1968){
			histograma[11] = histograma[11]+1;}
		else if(mediciones[i] > 1968 && mediciones[i] <= 2132){
			histograma[12] = histograma[12]+1;}
		else if(mediciones[i] > 2132 && mediciones[i] <= 2296){
			histograma[13] = histograma[13]+1;}
		else if(mediciones[i] > 2296 && mediciones[i] <= 2460){
			histograma[14] = histograma[14]+1;}
		else if(mediciones[i] > 2460 && mediciones[i] <= 2624){
			histograma[15] = histograma[15]+1;}
		else if(mediciones[i] > 2624 && mediciones[i] <= 2788){
			histograma[16] = histograma[16]+1;}
		else if(mediciones[i] > 2788 && mediciones[i] <= 2952){
			histograma[17] = histograma[17]+1;}
		else if(mediciones[i] > 2952 && mediciones[i] <= 3116){
			histograma[18] = histograma[18]+1;}
		else if(mediciones[i] > 3116 && mediciones[i] <= 3280){
			histograma[20] = histograma[19]+1;}
		else if(mediciones[i] > 3280 && mediciones[i] <= 3444){
			histograma[20] = histograma[20]+1;}
		else if(mediciones[i] > 3444 && mediciones[i] <= 3608){
			histograma[21] = histograma[21]+1;}
		else if(mediciones[i] > 3608 && mediciones[i] <= 3772){
			histograma[22] = histograma[22]+1;}
		else if(mediciones[i] > 3772 && mediciones[i] <= 3936){
			histograma[23] = histograma[23]+1;}
		else if(mediciones[i] > 3936){
			histograma[24] = histograma[24]+1;}

		for (j = i+1; j < Nmes; j++){
			if (ordenados[i] > ordenados[j]){
				aux2 = ordenados [i];
				ordenados[i] = ordenados[j];
				ordenados[j] = aux2;
			}
		}
	}
	/*	Comprobar ordenamiento de matriz
	for (i = 0; i < Nmes; i++){
		printf("%d\n", ordenados[i]);
	}*/

	//Calculo de mediana
	if(Nmes % 2 == 0){
		int divi = (Nmes-1)/2;
		//printf("%d\n",divi);
		mediana =(ordenados[divi]+ordenados[divi+1])/2.0;
	}
	else {
		int divi = (Nmes-1)/2;
		//printf("%d\n",divi);
		mediana = ordenados[divi];
	}

	//Valor total de la suma
	//printf("RMS1 = %f\n",SumRMS);

	promedio = SumPro/(Nmes*1.0);
	rms =sqrt(SumRMS/Nmes);
	rms = rms*100.0;
	printf("El promedio es: %f\n", promedio);
	printf("El valor RMS es: %f\n", rms);
	printf("El valor minimo es: %d\n",min);
	printf("El valor maximo es: %d\n",max);
	printf("Mediana: %f\n",mediana);
	printf("\nHistograma de mediciones\n");
	//Impresion de histograma
	int contador = 0;
	int rango1 = 0;
	int rango2 = 0;
	for(i = 0; i < 25; i++){
		if(i == 0){
			printf("000");
			rango1=0;
		}else{
			rango1=(164*i)+1;
		}
		rango2=164*(i+1);
		contador = histograma[i];
		//Arreglo de formato para cientos en rango1
		if(rango1 > 0 && rango1 <1000){
			printf("0%d - ",rango1);
		}else{	
			printf("%d - ",rango1);
		}
		//Arreglo de formato para cientos en rango2
		if(rango2 < 1000){
			printf("0%d  ",rango2);
		}else{
			printf("%d  ",rango2);
		}

		for(j = 0; j < contador; j++){
			printf("|");
		}
		printf("\n");
	}
	printf("\n");
    return 0;
}

