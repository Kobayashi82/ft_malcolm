# Referencia de Funciones Permitidas

## Interfaces de Red

### `getifaddrs` y `freeifaddrs`
- **`getifaddrs`**: Obtiene una lista completa de las interfaces de red disponibles y sus direcciones asociadas (por ejemplo, `eth0`, `wlan0`).
- **`freeifaddrs`**: Libera la memoria utilizada por la estructura de datos devuelta por `getifaddrs`.

### `if_nametoindex`
- **`if_nametoindex`**: Obtiene el índice numérico de una interfaz de red a partir de su nombre (como `eth0`, `wlan0`). Útil para operaciones que requieren especificar una interfaz de red particular.

## Resolución de Nombres

### `getaddrinfo` y `freeaddrinfo`
- **`getaddrinfo`**: Función moderna para resolver nombres de host a direcciones IP. Más flexible que `gethostbyname`, soporta tanto IPv4 como IPv6, y puede manejar servicios por nombre.
- **`freeaddrinfo`**: Libera la memoria asignada dinámicamente por `getaddrinfo`.

### `gethostbyname` (Obsoleta)
- **`gethostbyname`**: Función obsoleta para resolver nombres de dominio (como `"google.com"`) a direcciones IP. Ha sido reemplazada por `getaddrinfo`, que es más flexible y soporta IPv6.

## Conversión de Direcciones IP

### `inet_pton` y `inet_ntop`
- **`inet_pton`**: Convierte direcciones IP (IPv4 o IPv6) desde formato texto legible a formato binario de red. Si recibe texto que no representa una IP válida, devuelve un código de error.
- **`inet_ntop`**: Realiza la conversión inversa, transformando direcciones IP binarias (como estructuras `in_addr` o `in6_addr`) a formato texto legible.

### `inet_addr` (Obsoleta)
- **`inet_addr`**: Función obsoleta utilizada para convertir direcciones IP de texto a formato binario de red. Se recomienda usar `inet_pton` en su lugar, ya que es más robusta y soporta IPv6.

## Conversión de Orden de Bytes

### `htons` y `ntohs`
- **`htons`**: Convierte un valor de 16 bits (como un puerto) del orden de bytes del host al orden de bytes de red (big-endian).
- **`ntohs`**: Realiza la conversión inversa, del orden de bytes de red al orden de bytes del host.

## Gestión de Sockets

### `socket` y `setsockopt`
- **`socket`**: Crea un nuevo socket. Internamente, el sistema operativo asigna un descriptor de archivo al socket. Dependiendo del tipo especificado (TCP/UDP, IPv4/IPv6), el kernel maneja la comunicación de red correspondiente.
- **`setsockopt`**: Permite configurar diversas opciones del socket, como activar el modo "reuse address" (`SO_REUSEADDR`) o ajustar el tamaño de los buffers de envío y recepción.

## Envío y Recepción de Datos

### `sendto` y `recvfrom`
- **`sendto`**: Envía datos a una dirección específica, no necesariamente a un socket conectado. Especialmente útil para protocolos sin conexión como UDP.
- **`recvfrom`**: Recibe datos de un socket y también proporciona información sobre la dirección de origen de los datos.
- **Diferencia con `write` y `read`**: Las funciones `write` y `read` son más generales y se utilizan para el flujo de datos a través de cualquier descriptor de archivo, mientras que `sendto` y `recvfrom` están específicamente diseñadas para sockets de red y pueden incluir detalles sobre las direcciones de origen y destino.

## Manejo de Errores

### `strerror` y `gai_strerror`
- **`strerror`**: Convierte un código de error numérico (típicamente de `errno`) en un mensaje de error descriptivo en formato texto.
- **`gai_strerror`**: Similar a `strerror`, pero específicamente diseñada para manejar códigos de error de las funciones de la familia `getaddrinfo`.

## Utilidades del Sistema

### `getuid`
- **`getuid`**: Obtiene el ID del usuario real del proceso (no el usuario efectivo, que puede diferir cuando se usan mecanismos como `sudo` o `setuid`).

### `close`
- **`close`**: Cierra un descriptor de archivo, incluyendo sockets y archivos abiertos, liberando los recursos asociados.

### `sleep`
- **`sleep`**: Suspende la ejecución del programa durante un número específico de segundos completos.

## Manejo de Señales

### `sigaction` y `signal`
- **`sigaction`**: Método moderno y flexible para configurar manejadores de señales. Permite un control detallado sobre el comportamiento de las señales, incluyendo opciones para manejo asíncrono y bloqueo de señales durante la ejecución del manejador.
- **`signal`**: Función más simple para establecer manejadores de señales (por ejemplo, capturar `SIGINT` cuando se presiona Ctrl+C). Menos flexible que `sigaction`.

## Salida Formateada

### Familia `printf`
- **`printf`**: Imprime texto formateado a la salida estándar (stdout).
- **`fprintf`**: Imprime texto formateado a un archivo específico o stream.
- **`dprintf`**: Imprime texto formateado directamente a un descriptor de archivo.
- **`snprintf`**: Escribe texto formateado a un buffer de cadena con límite de tamaño, evitando desbordamientos de buffer.