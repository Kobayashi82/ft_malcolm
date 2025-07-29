# Modelo OSI

## ¿Qué es?
Un modelo teórico de 1984 que explica cómo se comunican las computadoras dividiendo el proceso en 7 capas.

## Las 7 Capas (de arriba a abajo)

**7. Aplicación** → Lo que ves (navegador, email, WhatsApp)

**6. Presentación** → Cifrado y compresión de datos (TLS/SSL, SSH)

**5. Sesión** → Inicia, mantiene y cierra conexiones

**4. Transporte** → Divide y reordena los datos (TCP/UDP y puertos)

**3. Red** → Encuentra el camino (direcciones IP y routers)

**2. Enlace** → Se encarga de la entrega en la red local usando direcciones MAC (ARP y switches)

**1. Física** → Hardware y señales eléctricas (cables, fibra óptica, ondas de radio)

## ¿Cómo funciona?

- Imagina enviar una carta:

#### 📤 Envío (de arriba hacia abajo)

| N | Capa                             | Analogía                                                        |
| - | -------------------------------- | --------------------------------------------------------------- |
| 7 | Aplicación                       | Escribes el mensaje                                             |
| 6 | Presentación, Sesión, Transporte | Cifras el mensaje, los divides en partes y lo metes en un sobre |
| 3 | Red                              | El cartero encuentra la dirección                               |
| 2 | Enlace                           | Se lleva al camión repartidor                                   |
| 1 | Física                           | Viaja por carreteras físicas                                    |

#### 📥 Recepción (de abajo hacia arriba)

| N | Capa                             | Analogía                                       |
| - | -------------------------------- | ---------------------------------------------- |
| 7 | Física                           | Llega por las carreteras                       |
| 6 | Enlace                           | El camión repartidor lo entrega                |
| 3 | Red                              | Se lee la dirección de destino                 |
| 2 | Transporte, Sesión, Presentación | Se abre el sobre, se reconstruye y se descifra |
| 1 | Aplicación                       | Se lee el mensaje                              |

## ¿Se usa hoy en día?

**En la teoría: SÍ** → Sigue siendo el estándar para entender y enseñar redes

**En la práctica: NO** → Internet usa TCP/IP (4 capas), no OSI

### Lo que realmente usamos:
- **Internet funciona con TCP/IP** (más simple, 4 capas)
- **OSI es principalmente educativo** y para troubleshooting
- **Los conceptos siguen siendo válidos**, pero implementados de forma diferente

## ¿Para qué sirve hoy?
1. **Entender cómo funcionan las redes** de forma ordenada
2. **Resolver problemas**: "¿Es problema de cable, de IP, o de la aplicación?"
3. **Comunicarse entre técnicos** usando un lenguaje común
4. **Diseñar redes** separando responsabilidades
