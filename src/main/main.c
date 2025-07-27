/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:46:47 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 15:10:58 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

#pragma endregion

#pragma region "Variables"

	t_malcolm g_malcolm;

#pragma endregion

#pragma region "Signals"

	static void termination_handler(int sig) { (void) sig; g_malcolm.running = false; }

	static int set_signals() {
		signal(SIGINT,  termination_handler);
		signal(SIGQUIT, termination_handler);
		signal(SIGTERM, termination_handler);
		signal(SIGHUP,  termination_handler);

		return (0);
	}

#pragma endregion

#pragma region "Main"

	int main(int argc, char **argv) {
		// ** TEMPORAL **
			static char *my_argv[6] = { "ft_malcolm", "127.0.0.1", "af:af:af:af:af:af", "127.0.0.1", "af:af:af:af:af:af", NULL };
			argv = my_argv; argc = 5;
		// ** TEMPORAL **

		int result = set_signals();
		if (!result && parse_arguments(argc, argv))	result = 1;
		// if (!result && get_interface())				result = 1;
		// if (!result && create_socket())				result = 1;
		// if (!result && wait_request())				result = 1;
		// if (!result && send_reply())				result = 1;
		if (!result) fprintf(stdout, "Exiting program...\n");

		// clean (if necessary)

		return (result);
	}

#pragma endregion

#pragma region "Information"

	// 1. Interfaz de red
	//
	//	Usar getifaddrs() para obtener una lista de interfaces
	//	Encontrar una interfaz activa (eth0)
	//
	//	"Found available interface: <interface>"


	// 2. Crear socket
	//
	//	socket() con parámetros apropiados para capturar y enviar paquetes ARP
	//	Probablemente SOCK_RAW y a nivel de layer 2


	// 3. Escuchar ARP requests (loop)
	//
	//	Usar recvfrom() para capturar paquetes
	//	Filtrar solo ARP requests que:
	//
	//	Sean broadcast y pregunten por source_ip y vengan de target_ip


	// 4. Cuando detecta la ARP request correcta:
	//
	//	"An ARP request has been broadcast."
	//	"    mac address of request: <mac>"
	//	"    IP address of request: <ip>"
	//	"Now sending an ARP reply to the target address with spoofed source, please wait..."


	// 5. Enviar ARP reply
	//
	//	Construir paquete ARP reply con source_mac falsa
	//	sendto() al target
	//
	//	"Sent an ARP reply packet, you may now check the arp table on the target."

#pragma endregion
