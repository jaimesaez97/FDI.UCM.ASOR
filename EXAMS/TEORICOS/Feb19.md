# Examen Teórico Enero 19

## 1. ¿Cuál es el propósito de un mensaje de tipo DHCPOFFER?

Es la respuesta de un servidor a un mensaje cliente DHCPDISCOVER (éste "se descubre" a los servidores), ofreciendo una serie de parámetros que el cliente tiene que "aceptar".

## 2. ¿Cuál es la función del temporizador de persistencia en el protocolo TCP?

Está asociada a la recepción de un tamaño de ventana 0. Su función es recuperar la pérdida de un ACK posterior con el nuevo tamaño.

## 3. ¿Cuándo y cuánto se puede retrasar una confirmación de un segmento TCP?

Si no hay datos para enviar, las confirmaciones se pueden retrasar hasta 500ms para incluirlas en un segmento de datos.

## 4. Describe el tipo y los datos del registro DNS con nombre 2.1.96.147.in-addr.arpa.

Es un registro PTR que contiene la traducción inversa (IP -> nombre).
Es una asignación inversa entre la IP 147.96.1.2 y el nombre de dominio in-addr.arpa.

## 5. ¿De qué tipo es el atributo AS_PATH de BGP? ¿Qué contiene?

Es un atributo de tipo lista y contiene todos los nodos de la ruta como secuencia de ASs.

## 6. ¿Qué funciones realiza el protocolo de descubrimiento de vecinos en IPv6?

Utiliza mensajes de ICMPv6 para que los terminales aprendan las direcciones IPv6 de los vecinos de la capa de enlace.
Un nodo que se acaba de conectar a la red descubre la presencia de otros nodos en el mismo enlace, además de ver sus direcciones IP.
Se ocupa de mantener limpios las cachés donde se almacena la info relativa al contexto de la red.

## 7. Describa el propósito del flag O_SYNC en la llamada open(2).

Garantiza que la llamada no regresará antes de que todos los latos hayan sido transferidos al disco.

## 8. ¿Qué es el *nice* de un proceso? ¿En qué política de planificación se considera?

Es la prioridad que tiene un proceso para que sea seleccionado por el planificador para entrar en la CPU. Se utiliza en la política de planificación por defecto de Linux (SCHED_OTHER).

## 9. ¿Cuándo se envía la señal SIGPIPE?

Cuando se rompe una tubería; es decir, cuando se escribe en un socket que ha sido cerrado.

## 10. ¿Para qué sirve la llamada bind(2)? ¿Genera algún mensaje en la red?

Sirve para asignar una dirección IP y un puerto a un socket asociado con un descriptor de fichero.
