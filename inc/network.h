/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:40:08 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 17:11:22 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <sys/socket.h>		// socket, setsockopt, sendto, recvfrom
	#include <arpa/inet.h>		// inet_pton, inet_ntop, inet_addr, htons, ntohs
	#include <netinet/in.h>		// structures like sockaddr_in
	#include <netdb.h>			// gethostbyname, getaddrinfo, freeaddrinfo, gai_strerror
	#include <net/if.h>			// if_nametoindex
	#include <stdbool.h>

#pragma endregion

#pragma region "Structures"



#pragma endregion

#pragma region "Methods"

	int get_interface();

#pragma endregion
