# Examen Teórico Febrero 18

## 1. Describe brevemente el mecanismo que usa el protocolo IPv6 para añadir opciones a los datagramas IP.

Es un mecanismo pensado para añadir futuras opciones y no tener que modificar el datagrama, por lo que las opciones van codificadas en los datos del paquete y no en la cabecera.
Hay un campo de 8 bits en el paquete llamado "NextHeader", que define la siguiente cabecera en el datagrama encapsulada en la sección de datos. Estas se llaman cabeceras de extensión.

## 2. Describa brevemente en qué consiste el algoritmo de encaminamiento de vector de rutas.

Se basa en el encaminamiento por vector de distancias, intentando resolver los problemas de convergencia para el encaminamiento inter-AS.
A partir de la información sobre destinos alcanzables, cada encaminador obtiene la lista de destinos alcanzables y la ruta completa.

## 3. Indique el nombre, tipo y datos del registro DNS para:

### A. Establecer el nombre alternativo *web.ucm.es* para el nombre de dominio www.ucm.es.

web.ucm.es	86400	IN	CNAME	www.ucm.es

### B. Asociar el nombre de dominio www.ucm.es a la IP 147.96.1.2.

www.ucm.es	IN	A	147.96.1.2

### C. Asociar la IP 147.96.1.2 al nombre de dominio www.ucm.es.

147.96.1.2	IN	PTR	www.ucm.es

### D. Establecer como servidor de correo del dominio ucm.es. la máquina mail.ucm.es.

ucm.es.		IN	MX	10	mail.ucm.es

## 4. Respecto a la máscara umask:

### Describa su propósito

Es una máscara que define el tipo de fichero y los permisos para grupo-usuario-superusuario.

### ¿Es una propiedad que se define por usuario, para el sistema o por proceso?

Se define por proceso.

### ¿Qué efecto tiene la máscara 022?

Ningún permiso para el super-user y permiso de escritura para grupo y usuario.

## 5. Describa brevemente las alternativas para sincronizar las operaciones de E/S de un proceso sobre múltiples descriptores.

'select': una función que te dice, de un conjunto de descriptores de ficheros, cuál está disponible para escribir y/o para leer.

