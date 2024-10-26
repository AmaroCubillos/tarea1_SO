# Cálculo de números primos con fork y pipes

## Descripción

Este programa en C calcula los números primos dentro de un rango dado utilizando procesamiento en paralelo. Para esto, divide el trabajo entre varios procesos hijos, asignando a cada uno la búsqueda de números primos en un subrango particular. La comunicación entre los procesos hijos y el proceso principal se realiza a través de pipes, y el proceso principal reúne los resultados y los guarda en un archivo de salida.

## Instrucciones de uso

El programa requiere 2 argumentos de entrada:

1.- M: El número máximo del rango donde se buscarán los números primos.

2.- Número de procesos: Cantidad de procesos hijos que se usarán para realizar el cálculo en paralelo.

Ejemplo para 10000 el número máximo y 4 subprocesos:

./primos 100000 4

En este ejemplo, el programa buscará números primos hasta 100,000, utilizando 4 procesos hijos, y almacenará los resultados en el archivo resultados_primos.txt.

## Gráfico de speedup

Para visualizar el speedup del programa en función del número de procesos, se realizaron varias ejecuciones desde un solo proceso hasta dieciséis. A continuación se muestra la tabla de datos obtenidos:

![image](https://github.com/user-attachments/assets/8beb2e70-5e09-450c-a956-bb950ff84e10)

Se presenta el gráfico generado a partir de los datos:

![Captura desde 2024-10-25 19-01-26](https://github.com/user-attachments/assets/1d93fd80-cd0d-49ad-ad17-ebbdcdeaa621)

## Hardware utilizado para pruebas

![image](https://github.com/user-attachments/assets/d953d03a-e7f8-44c1-b2d0-0a007f5ac612)

## Conclusión

El programa demuestra que al incrementar el número de procesos acelera el cálculo de números primos hasta alcanzar el límite de núcleos disponibles en el procesador. Al exceder este límite, el rendimiento disminuye y los tiempos de ejecución se vuelven menos predecibles debido a la sobrecarga en la gestión de múltiples procesos.
