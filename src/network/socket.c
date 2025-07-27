/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:13:37 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 01:51:00 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

	#include <stdio.h>
	#include <errno.h>
	#include <string.h>

#pragma endregion

#pragma region "Create Socket"

	int create_socket() {
		g_malcolm.sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

		if (g_malcolm.sockfd < 0) {
			if (errno == EPERM || errno == EACCES)	fprintf(stderr, "ft_malcolm: Lacking privilege for raw socket\n");
			else									fprintf(stderr, "ft_malcolm: %s\n", strerror(errno));
			return (1);
		}

	    int optval = 1;
	   	setsockopt(g_malcolm.sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

		return (0);
	}

#pragma endregion
