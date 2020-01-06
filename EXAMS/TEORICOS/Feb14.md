# Examen Teórico Febrero 2014

## 1. Indicar qué tipo de direcciones IPv6 son cada una de las siguientes, señalando también su ámbito:

### a) fe80::218:43ff:fe25:de20

Link-Local Unicast.

### b) 2001:db8:2512::2

Global Unicast.

### c) fdfb:946e:2c3a::

Unique Local Address.

### d) ff02::1

Multicast.

### e) ff12::1180:add2

Multicast.

## 2. Explicar brevemente cómo se genera el identificador de interfaz a partir de la dirección MAC en el proceso de autoconfiguración de IPv6. Poner un ejemplo. ¿Qué implicaciones puede tener este mecanismo desde el punto de vista de la privacidad?

Una direccion MAC de 48 bits se convierte en una dirección EUI-64 de 64 bits insertando FF:FE en el medio.
00:1D:BA:06:37:64 -> 00:1D:BA:FF:FE:06:37:64.

Puede suponer un problema de privacidad porque permite relacionar loa dirección de red con la MAC.

## 3. Comparar brevemente el protocolo ARP empleado en IPv4 con el descubrimiento de vecinos de IPv6.

El protocolo ARP es una tabla simple que mantiene las direcciones IP de las últimas máquinas con las que nos hemos comunicado y las direcciones Ethernet asociadas.

El protocolo de descubrimiento de vecinos tiene, además de resolución de direcciones como ARP, detección de direcciones duplicadas o vecinos inalcanzables y anuncio de cambios en la dirección de enlace.

## 4. Un encaminador que utliza el proyocolo de encaminamiento RIP tiene la siguiente table de encaminamiento. Desde 192.168.3.1 este encaminador decibe la siguiente info de vectores distancia. Determinar cómo queda la tabla.

Destino		Distancia	Encaminador
192.168.1.0	    1		     -
192.168.2.0	    2		192.168.3.1
192.168.3.0	    1 		     -
192.168.4.0	    2		192.168.3.1
192.168.5.0	    3		192.168.3.1
192.168.6.0	    7		192.168.1.1

## 5. Describe de manera breve los tipos de encaminadores definidos en OSPF.

* Internal router (IR): mantiene información de la topología de su área.
* Area Border Router (ABR): mantiene una DB para cada una de las áreas a las que está conectado.
* Autonomous System Boundary Router (ASBR): transmite rutas externas a la red OSPF, pudiendo inyectar rutas aprendidas mediante otro protocolo.

## 6. Explica brevemente los distintos tipos de Sistemas Autónomos y su relación entre ellos.

Un Sistema Autónomo es un conjunto de redes y encaminadores gestionados y administrados por una misma autoridad.
Hay tres tipos:
* Stub: conectado únicamente a otro AS. Es destino u origen del tráfico.
* Tránsito: conectado a varios AS, permitiendo el tráfico de reenvío.
* Multihomed: conectado a varios AS por redundancia y balanceo de carga, siendo origen y destino del tráfico.

## 7. Explicar el mecanismo que aplica TCP para detectar y pailar una congestión en la red.

Utiliza la ventana de congestión, pudiendo siempre enviar tantos bytes como el mínimo entre la ventana de congestión y la de recepción.

	AW = mín {RW, CW}

Utiliza un mecanismo basado en tres fases:
- Arranque lento: empieza un arranque en el que por cada segmento confirmado se duplica la tasa, es decir, es un arranque exponencial hasta alcanzar un máximo.
- Velocidad media: cuando alcanza el SST, aumenta en orden lineal hasta llegar al tamaño indicado por la ventana de recepción.
- Cuando se recibe el 3 ACK duplicado, se empieza con el arranque lento (pero no en 0, en un valor establecido).

## 8. Explicar brevemente el uso de los principales tipos de registros en el sistema DNS.

- A: asignación nombre->IP (IPv4).
- AAAA: asignación nombre->IP (IPv6).
- NS: especifica los servidores autoritativos para la zona.
- MX: sirve para encaminar los mensajes eficientemente.
- SOA: registro principal y que marca el comienzo de definición de zona.
- PTR: asiganción IP->nombre.
