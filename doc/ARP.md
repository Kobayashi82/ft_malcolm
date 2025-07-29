# Address Resolution Protocol (ARP)

## ¿Cómo funciona ARP?

1. **ARP Request**: Cuando un dispositivo necesita comunicarse con una `IP` en su red local pero no conoce su `MAC`, envía una petición `ARP` por broadcast preguntando "¿Quién tiene la `IP` **X.X.X.X** ?"

2. **ARP Reply**: El dispositivo con esa `IP` responde con su dirección `MAC`

3. **ARP Table**: Ambos dispositivos guardan la asociación **IP-MAC** en su tabla `ARP` para futuras comunicaciones

## Estructura de un paquete ARP

|                                      |                                |
| ------------------------------------ | ------------------------------ |
| **Hardware Type**                    | Tipo de hardware, ej: Ethernet |
| **Protocol Type**                    | Tipo de protocolo, ej: IPv4    |
| **Hardware/Protocol Address Length** | Longitud de direcciones        |
| **Operation**                        | 1=Request ; 2=Reply            |
| **Sender Hardware Address**          | MAC del emisor                 |
| **Sender Protocol Address**          | IP del emisor                  |
| **Target Hardware Address**          | MAC del objetivo               |
| **Target Protocol Address**          | IP del objetivo                |
|                                      |                                |

## Vulnerabilidad ARP Spoofing

El protocolo `ARP` no tiene autenticación, lo que permite ataques de `ARP` spoofing donde un atacante puede:
- Enviar respuestas `ARP` falsas
- Asociar su MAC con la IP de otro dispositivo (como el gateway)
- Interceptar o redirigir tráfico de red

## Ejemplo práctico (ft_malcolm):

Cuando tu programa espera una petición `ARP` broadcast del target solicitando la IP source, y luego envía una respuesta `ARP` falsa asociando tu MAC con esa IP, estás realizando `ARP` spoofing. El target actualizará su tabla `ARP` con la información falsificada, creyendo que tu MAC pertenece a la IP source.
