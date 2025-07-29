## Cambiar la Dirección MAC

#### Usando `ip`:
```bash
sudo ip link set dev <interface> down                       # Desactivar
sudo ip link set dev <interface> address XX:XX:XX:XX:XX:XX  # Cambiar MAC
sudo ip link set dev <interface> up                         # Reactivar
ip link show <interface>                                    # Verificar
```

#### Usando `ifconfig`:
```bash
sudo ifconfig <interface> down                              # Desactivar
sudo ifconfig <interface> hw ether XX:XX:XX:XX:XX:XX        # Cambiar MAC
sudo ifconfig <interface> up                                # Reactivar
ifconfig <interface>                                        # Verificar
```
##
- \<interface> Es una interfaz de red como `eth0`

- El cambio de la dirección MAC no es persistente después de un reinicio.
