# Guía de Testing para ft_malcolm

## Índice
1. [Requisitos previos](#requisitos-previos)
2. [Configuración del entorno](#configuración-del-entorno)
3. [Configuración con múltiples VMs](#configuración-con-múltiples-vms)
4. [Configuración con una sola VM](#configuración-con-una-sola-vm)
5. [Ejecución de las pruebas](#ejecución-de-las-pruebas)
6. [Verificación de resultados](#verificación-de-resultados)
7. [Herramientas de debugging](#herramientas-de-debugging)
8. [Casos de prueba](#casos-de-prueba)
9. [Troubleshooting](#troubleshooting)

## Requisitos previos

### Software necesario:
- Linux con kernel > 3.14 (preferible Debian)
- Privilegios de root/sudo
- Compilador GCC
- Herramientas de red básicas (`ping`, `arp`, `ip`)

## Configuración del entorno

### Compilar ft_malcolm:
```bash
make
# Verificar que el ejecutable se creó correctamente
ls -la ft_malcolm
```

### Verificar permisos:
```bash
# ft_malcolm necesita privilegios de root
sudo ./ft_malcolm
```

## Configuración con múltiples VMs

### Topología recomendada:
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│     VM1     │    │     VM2     │    │     VM3     │
│ (Atacante)  │    │ (Víctima)   │    │ (Objetivo)  │
│192.168.1.10 │    │192.168.1.20 │    │192.168.1.30 │
└─────────────┘    └─────────────┘    └─────────────┘
       │                   │                   │
       └───────────────────┼───────────────────┘
                     Switch/Red
```

### Configuración de red:

#### En cada VM configurar la red:
```bash
# Verificar configuración actual
ip addr show

# Si necesitas configurar manualmente:
sudo ip addr add 192.168.1.X/24 dev eth0
sudo ip link set eth0 up
```

#### Obtener direcciones MAC:
```bash
# En cada VM ejecutar:
ip link show eth0
# Anotar la dirección MAC (ej: 08:00:27:12:34:56)
```

### Configuración específica por VM:

#### VM1 (Atacante) - 192.168.1.10:
```bash
# Compilar ft_malcolm
make clean && make

# Verificar conectividad básica
ping -c 2 192.168.1.20
ping -c 2 192.168.1.30
```

#### VM2 (Víctima) - 192.168.1.20:
```bash
# No requiere software especial
# Solo herramientas estándar de red
```

#### VM3 (Objetivo) - 192.168.1.30:
```bash
# Opcional: puede estar apagada durante el test
# Solo necesitamos su IP para el spoofing
```

## Configuración con una sola VM

### Para pruebas básicas en una sola máquina:

```bash
# Obtener tu IP actual
MY_IP=$(ip route get 8.8.8.8 | awk '{print $7; exit}')

# Obtener tu MAC actual  
MY_MAC=$(ip link show eth0 | grep ether | awk '{print $2}')

echo "Mi IP: $MY_IP"
echo "Mi MAC: $MY_MAC"
```

## Ejecución de las pruebas

### Sintaxis del comando:
```bash
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

### Ejemplo con múltiples VMs:

#### En VM1 (Atacante):
```bash
# Spoofear que 192.168.1.30 tiene MAC falsa aa:bb:cc:dd:ee:ff
# Dirigido a la víctima 192.168.1.20
sudo ./ft_malcolm 192.168.1.30 aa:bb:cc:dd:ee:ff 192.168.1.20 08:00:27:ab:cd:ef
```

#### En VM2 (Víctima):
```bash
# Limpiar tabla ARP para forzar nueva resolución
sudo arp -d 192.168.1.30

# Generar ARP request haciendo ping
ping 192.168.1.30
```

### Ejemplo con una sola VM:
```bash
# Test básico usando tu propia IP
sudo ./ft_malcolm 192.168.1.10 aa:bb:cc:dd:ee:ff 192.168.1.10 08:00:27:12:34:56

# En otra terminal, generar ARP request
sudo arp -d 192.168.1.10
ping 192.168.1.10
```

## Verificación de resultados

### 1. Salida esperada de ft_malcolm:
```
Found available interface: eth0
Waiting for ARP request...
An ARP request has been broadcast.
    mac address of request: 08:00:27:ab:cd:ef
    IP address of request: 192.168.1.20
Now sending an ARP reply to the target address with spoofed source, please wait...
Sent an ARP reply packet, you may now check the arp table on the target.
Exiting program...
```

### 2. Verificar tabla ARP en la víctima:
```bash
# En VM2 (víctima)
arp -a | grep 192.168.1.30
# Debería mostrar: 192.168.1.30 (192.168.1.30) at aa:bb:cc:dd:ee:ff [ether] on eth0

# Formato alternativo
ip neigh show
```

### 3. Verificar conectividad:
```bash
# En VM2, el ping debería fallar o comportarse extraño
ping 192.168.1.30
# Porque está intentando enviar a una MAC falsa
```

## Herramientas de debugging

### tcpdump (captura de paquetes):
```bash
# En cualquier VM, capturar tráfico ARP
sudo tcpdump -i eth0 arp -v

# Salida esperada:
# ARP request: who has 192.168.1.30 tell 192.168.1.20
# ARP reply: 192.168.1.30 is at aa:bb:cc:dd:ee:ff
```

### Wireshark (interfaz gráfica):
```bash
# Instalar Wireshark
sudo apt-get install wireshark

# Ejecutar (requiere X11)
sudo wireshark

# Filtros útiles:
# - arp
# - arp.opcode == 1  (solo requests)
# - arp.opcode == 2  (solo replies)
```

### Análisis manual de interfaces:
```bash
# Ver todas las interfaces
ip link show

# Ver tabla ARP completa
arp -a

# Ver rutas de red
ip route

# Ver estadísticas de interfaz
cat /proc/net/dev
```

## Casos de prueba

### Test 1: Funcionalidad básica
**Objetivo**: Verificar que ft_malcolm funciona correctamente

```bash
# VM1 (Atacante)
sudo ./ft_malcolm 192.168.1.30 aa:bb:cc:dd:ee:ff 192.168.1.20 08:00:27:ab:cd:ef

# VM2 (Víctima)
sudo arp -d 192.168.1.30
ping -c 1 192.168.1.30

# Verificar resultado
arp -a | grep 192.168.1.30
```

**Resultado esperado**: La tabla ARP muestra la MAC falsa

### Test 2: Manejo de errores
**Objetivo**: Verificar validación de argumentos

```bash
# IP inválida
sudo ./ft_malcolm 192.168.1.999 aa:bb:cc:dd:ee:ff 192.168.1.20 08:00:27:ab:cd:ef

# MAC inválida
sudo ./ft_malcolm 192.168.1.30 aa:bb:cc:dd:ee:gg 192.168.1.20 08:00:27:ab:cd:ef

# Argumentos insuficientes
sudo ./ft_malcolm 192.168.1.30
```

**Resultado esperado**: Mensajes de error apropiados

### Test 3: Interrupción con Ctrl+C
**Objetivo**: Verificar manejo de señales

```bash
# Ejecutar ft_malcolm
sudo ./ft_malcolm 192.168.1.30 aa:bb:cc:dd:ee:ff 192.168.1.20 08:00:27:ab:cd:ef

# Presionar Ctrl+C antes de que llegue un ARP request
```

**Resultado esperado**: Programa termina limpiamente

### Test 4: Múltiples requests
**Objetivo**: Verificar que solo responde una vez

```bash
# VM1 (Atacante)
sudo ./ft_malcolm 192.168.1.30 aa:bb:cc:dd:ee:ff 192.168.1.20 08:00:27:ab:cd:ef

# VM2 (Víctima) - generar múltiples requests
ping -c 5 192.168.1.30
```

**Resultado esperado**: ft_malcolm termina después del primer reply

## Troubleshooting

### Problema: "Lacking privilege for raw socket"
**Solución**: 
```bash
# Ejecutar con sudo
sudo ./ft_malcolm ...

# O dar permisos especiales al ejecutable
sudo setcap cap_net_raw+ep ./ft_malcolm
```

### Problema: "No interface found"
**Solución**:
```bash
# Verificar que source_ip y target_ip están en la misma red
ip route

# Verificar interfaces disponibles
ip addr show
```

### Problema: No se reciben ARP requests
**Posibles causas**:
1. **Firewall bloqueando**: `sudo iptables -F`
2. **IPs en diferentes subredes**: Verificar configuración de red
3. **No hay tráfico ARP**: Generar requests manualmente

```bash
# Generar ARP request manualmente
sudo arping -c 1 192.168.1.30
```

### Problema: La tabla ARP no se actualiza
**Verificar**:
```bash
# Limpiar tabla ARP antes del test
sudo arp -d 192.168.1.30

# Verificar que el ARP reply llegó
sudo tcpdump -i eth0 arp

# Verificar formato del paquete con Wireshark
```

### Problema: "Bad file descriptor" al presionar Ctrl+C
**Es normal**: El programa está cerrando el socket correctamente

### Logs del sistema:
```bash
# Ver logs del kernel (puede mostrar errores de red)
dmesg | tail -20

# Ver logs del sistema
journalctl -f
```

## Consejos adicionales

### Seguridad:
- **SOLO usa IPs que te pertenezcan** (como especifica el PDF)
- No hagas ARP spoofing en redes de producción
- Usa VMs aisladas para las pruebas

### Rendimiento:
- El programa debería ser rápido (< 1 segundo para responder)
- Usar `time` para medir: `time sudo ./ft_malcolm ...`

### Documentación:
- Anota los resultados de cada test
- Guarda capturas de Wireshark para análisis
- Documenta cualquier comportamiento inesperado

---

**Nota importante**: Este proyecto es solo para fines educativos. El ARP spoofing puede ser detectado por sistemas de seguridad modernos y solo debe usarse en entornos controlados.