# Examen Teórico Febrero 17

## 1. Describa brevemente los mecanismos de retransmisión usados en TCP.

Hay un temporizador de retransmisión que, una vez se llega al timeout, se reenvía el segmento para el cuál se ha activado (hay uno por cada segmento).
También existe otro mecanismo para cuándo la red está saturada consistente en envíar un segmento para el que se han recibido 3 ACKs repetidos.

## 2. ¿Cuál es el propósito, ámbito y tipo de la dirección IPv6 de nodo solicitado?

Se usan en el protocolo de descubrimiento de vecinos.

## 3. Explique la diferencia entre servidores DNS recursivos y no recursivos.

Los servidores DNS no recursivos, si no contienen el servidor final que contiene el nobmre, devuelven el nombre del siguiente servidor de la cadena.
Sin embargo, los recursivos resuelven cada dependencia hasta llegar al servidor que contiene el nombre.

Por ejemplo:
	DNS:	A -> B -> C -> D
	No-REC:	A -> B
	REC:	A -> D

## 4. Indique la diferencia entre el UID real y el UID efectivo de un proceso. ¿Cuándo pueden ser diferentes?

El UID real es quién eres realmente, y el UID efectivo es el que mira el OS para tomar decisiones sobre si se te permite o no hacer algo.
Si se ejecuta un programa 'setuid', se cambia el UID efectivo pero no el real.

## 5. Enumere las diferencias entre una tubería sin nombre y una tubería con nombre.

La comunicación mediante tuberías sin nombre solo se puede realizar entre **procesos con relación de parentesco**.
Una tubería con nombre es similar a la sin nombre, pero se accede como parte del sistema de ficheros.


