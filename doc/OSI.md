# Modelo OSI

## ¿Qué es el Modelo OSI?

El modelo OSI (Open Systems Interconnection) es un modelo conceptual creado por la ISO (International Organization for Standardization) en 1984 que describe cómo los sistemas de comunicación deberían funcionar. No es una implementación real, sino un marco teórico que divide la comunicación de red en 7 capas distintas.

**Propósito principal**: Estandarizar la comunicación entre sistemas diferentes, permitiendo que equipos de distintos fabricantes puedan comunicarse entre sí.

## Las 7 Capas del Modelo OSI

### Capa 7: Aplicación (Application Layer)
**¿Qué hace?**
- Es la capa más cercana al usuario final
- Proporciona servicios de red directamente a las aplicaciones
- Define protocolos para servicios específicos como correo, web, transferencia de archivos

**Protocolos típicos:**
- HTTP/HTTPS (navegación web)
- SMTP (envío de correo)
- POP3/IMAP (recepción de correo)
- FTP (transferencia de archivos)
- DNS (resolución de nombres)
- SSH (acceso remoto seguro)

**Ejemplo práctico:** Cuando abres tu navegador y escribes "google.com", la capa de aplicación usa HTTP para solicitar la página web.

### Capa 6: Presentación (Presentation Layer)
**¿Qué hace?**
- Traduce datos entre el formato que usa la aplicación y el formato de red
- Se encarga del cifrado/descifrado de datos
- Compresión y descompresión de datos
- Conversión de formatos (ASCII, EBCDIC, etc.)

**Funciones clave:**
- Cifrado SSL/TLS
- Compresión de archivos
- Conversión de caracteres
- Serialización de datos

**Ejemplo práctico:** Cuando accedes a un sitio HTTPS, esta capa se encarga de cifrar tus datos antes de enviarlos y descifrar los que recibes.

### Capa 5: Sesión (Session Layer)
**¿Qué hace?**
- Establece, mantiene y termina sesiones entre aplicaciones
- Controla los diálogos/conexiones entre computadoras
- Gestiona si la comunicación es half-duplex o full-duplex
- Implementa puntos de control para recuperación

**Funciones principales:**
- Autenticación de usuarios
- Establecimiento de sesiones
- Sincronización de datos
- Recuperación de sesiones interrumpidas

**Ejemplo práctico:** Cuando te conectas a una base de datos, esta capa mantiene tu sesión activa durante toda la interacción y la cierra cuando terminas.

### Capa 4: Transporte (Transport Layer)
**¿Qué hace?**
- Proporciona transferencia de datos confiable entre hosts
- Segmenta y reensambla datos
- Control de flujo y control de errores
- Multiplexación de conexiones

**Protocolos principales:**
- **TCP (Transmission Control Protocol)**: Confiable, orientado a conexión, garantiza entrega
- **UDP (User Datagram Protocol)**: No confiable, sin conexión, más rápido

**Conceptos clave:**
- **Puertos**: Identifican aplicaciones específicas (puerto 80 para HTTP, 443 para HTTPS)
- **Segmentación**: Divide datos grandes en segmentos más pequeños
- **Control de flujo**: Evita que el emisor sature al receptor

**Ejemplo práctico:** Cuando descargas un archivo, TCP se asegura de que todos los segmentos lleguen correctamente y en orden.

### Capa 3: Red (Network Layer)
**¿Qué hace?**
- Enrutamiento de paquetes entre diferentes redes
- Direccionamiento lógico (direcciones IP)
- Determinación del mejor camino para enviar datos
- Fragmentación y reensamblado de paquetes

**Protocolo principal:**
- **IP (Internet Protocol)**: IPv4 e IPv6
- **ICMP**: Mensajes de control y error
- **Protocolos de enrutamiento**: OSPF, BGP, RIP

**Dispositivos típicos:**
- Routers
- Switches de capa 3

**Ejemplo práctico:** Cuando envías un correo a alguien en otra ciudad, los routers usan esta capa para determinar la mejor ruta a través de Internet.

### Capa 2: Enlace de Datos (Data Link Layer)
**¿Qué hace?**
- Proporciona comunicación confiable entre nodos adyacentes
- Control de acceso al medio (MAC)
- Detección y corrección de errores de la capa física
- Control de flujo local

**Subcapas:**
- **LLC (Logical Link Control)**: Control de enlace lógico
- **MAC (Media Access Control)**: Control de acceso al medio

**Protocolos/Tecnologías:**
- Ethernet
- Wi-Fi (802.11)
- PPP (Point-to-Point Protocol)

**Direccionamiento:**
- Direcciones MAC (físicas): identifican únicamente cada interfaz de red

**Dispositivos típicos:**
- Switches
- Bridges
- Puntos de acceso Wi-Fi

**Ejemplo práctico:** En tu red local, esta capa usa direcciones MAC para entregar datos al dispositivo correcto en el mismo segmento de red.

### Capa 1: Física (Physical Layer)
**¿Qué hace?**
- Transmisión de bits en bruto a través del medio físico
- Define características eléctricas, mecánicas y funcionales
- Especifica conectores, voltajes, temporización

**Aspectos que define:**
- **Medios de transmisión**: Cables de cobre, fibra óptica, ondas de radio
- **Conectores**: RJ45, USB, conectores de fibra
- **Señalización**: Cómo se representan los 0s y 1s
- **Sincronización**: Temporización de las señales

**Dispositivos típicos:**
- Hubs
- Repetidores
- Cables
- Antenas

**Ejemplo práctico:** El cable Ethernet que conecta tu computadora al router, las señales eléctricas que viajan por él.

## Flujo de Datos en el Modelo OSI

### Envío (De arriba hacia abajo)
1. **Aplicación**: El usuario envía datos
2. **Presentación**: Cifra/comprime los datos
3. **Sesión**: Establece sesión y añade información de control
4. **Transporte**: Segmenta datos y añade puertos
5. **Red**: Añade direcciones IP de origen y destino
6. **Enlace**: Añade direcciones MAC y control de errores
7. **Física**: Convierte a señales eléctricas/ópticas/radio

### Recepción (De abajo hacia arriba)
1. **Física**: Recibe señales y las convierte a bits
2. **Enlace**: Verifica errores y extrae datos
3. **Red**: Examina dirección IP de destino
4. **Transporte**: Reensambla segmentos
5. **Sesión**: Gestiona la sesión
6. **Presentación**: Descifra/descomprime
7. **Aplicación**: Entrega datos al usuario

## Encapsulación de Datos

Cada capa añade su propia información de control (headers/trailers):

- **Capa 7**: Datos
- **Capa 6**: Datos + Header de Presentación
- **Capa 5**: Datos + Header de Sesión
- **Capa 4**: **Segmento** = Datos + Header TCP/UDP
- **Capa 3**: **Paquete** = Segmento + Header IP
- **Capa 2**: **Trama** = Paquete + Header Ethernet + Trailer
- **Capa 1**: **Bits** = Señales físicas

## Modelo OSI vs TCP/IP

**Diferencias principales:**
- **OSI**: 7 capas, modelo teórico
- **TCP/IP**: 4 capas, implementación práctica de Internet

**Correspondencia aproximada:**
- **OSI 7,6,5** ↔ **TCP/IP Aplicación**
- **OSI 4** ↔ **TCP/IP Transporte**
- **OSI 3** ↔ **TCP/IP Internet**
- **OSI 2,1** ↔ **TCP/IP Acceso a Red**

## Ventajas del Modelo OSI

1. **Modularidad**: Cada capa tiene funciones específicas
2. **Interoperabilidad**: Estándar universal para comunicación
3. **Troubleshooting**: Facilita localizar problemas por capas
4. **Desarrollo**: Permite desarrollar protocolos independientemente
5. **Educación**: Excelente marco para entender redes

## Críticas al Modelo OSI

1. **Complejidad**: Demasiadas capas para implementaciones prácticas
2. **Rendimiento**: Overhead por múltiples capas
3. **Flexibilidad limitada**: Muy rígido comparado con TCP/IP
4. **Adopción**: TCP/IP se impuso en la práctica

## Aplicación Práctica del Modelo OSI

**Para troubleshooting:**
- **Capa 1**: ¿Está conectado el cable? ¿Funciona la interfaz?
- **Capa 2**: ¿Se ven las direcciones MAC? ¿Funciona el switch?
- **Capa 3**: ¿Hay conectividad IP? ¿Funciona el enrutamiento?
- **Capa 4**: ¿Están abiertos los puertos? ¿Funciona TCP/UDP?
- **Capas superiores**: ¿Funciona la aplicación específica?

**Para diseño de redes:**
- Permite separar responsabilidades
- Facilita la selección de tecnologías por capa
- Ayuda en la documentación y planificación

## Conclusión

El modelo OSI sigue siendo fundamental para entender cómo funcionan las redes, aunque en la práctica se use más TCP/IP. Su valor radica en proporcionar un framework conceptual claro que ayuda a organizar el conocimiento sobre comunicaciones de red y facilita tanto el aprendizaje como la resolución de problemas.