# Funciones Utilizadas

## Interfaces de Red

- **`getifaddrs`**: Obtiene una lista completa de las interfaces de red disponibles y sus direcciones asociadas (por ejemplo, eth0, wlan0).

- **`freeifaddrs`**: Libera la memoria utilizada por la estructura de datos devuelta por `getifaddrs`.

- **`if_nametoindex`**: Obtiene el índice numérico de una interfaz de red a partir de su nombre.

## Conversión de Direcciones IP

- **`inet_pton`**: Convierte direcciones IP en formato texto a binario de red.

- **`inet_ntop`**: Convierte direcciones IP binarias a formato texto.

## Conversión de Orden de Bytes

- **`htons`**: Convierte del orden de bytes del host al orden de bytes de red.

- **`ntohs`**: Convierte del orden de bytes de red al orden de bytes del host.

## Gestión de Sockets

- **`socket`**: Crea un canal de comunicación para enviar y recibir datos.

## Envío y Recepción de Datos

- **`sendto`**: Envía un paquete de datos a una dirección específica.

- **`recvfrom`**: Recibe datos de una dirección específica.

## Manejo de Errores

- **`strerror`**: Convierte códigos de error del sistema en mensajes descriptivos.

## Utilidades del Sistema

- **`close`**: Cierra un descriptor de archivo o socket, liberando los recursos asociados.

## Manejo de Señales

- **`signal`**: Establece manejadores para señales de terminación (SIGINT, SIGQUIT, SIGTERM, SIGHUP).

## Salida Formateada

- **`printf`**: Imprime texto formateado a la salida estándar (stdout).

- **`fprintf`**: Imprime texto formateado a un archivo específico o stream.

- **`sscanf`**: Lee datos de una cadena de texto y los convierte en los tipos de datos especificados.
