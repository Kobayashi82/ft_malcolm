/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:13:37 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 15:13:45 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

#pragma endregion

#pragma region "Create Socket"

	int create_socket() {
		g_malcolm.sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

		if (g_malcolm.sockfd < 0) {
			if (errno == EPERM || errno == EACCES)	fprintf(stderr, "ft_malcolm: Lacking privilege for raw socket\n");
			else									fprintf(stderr, "ft_malcolm: %s\n", strerror(errno));
			return (1);
		}

		if (setsockopt(g_malcolm.sockfd, SOL_SOCKET, SO_BINDTODEVICE, g_malcolm.if_name, ft_strlen(g_malcolm.if_name)) < 0) {
			fprintf(stderr, "Error: Failed to bind socket to device %s: %s\n", g_malcolm.if_name, strerror(errno));
			return (1);
		}

		// Promiscuous mode
		// struct packet_mreq mreq;
		// ft_memset(&mreq, 0, sizeof(mreq));
		// mreq.mr_ifindex = g_malcolm.if_index;
		// mreq.mr_type = PACKET_MR_PROMISC;
		// if (!mreq.mr_ifindex || setsockopt(g_malcolm.sockfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		// 	fprintf(stderr, "Failed to set promiscuous mode on %s\n", g_malcolm.if_name);
		// } else {
		// 	fprintf(stderr, "Promiscuous mode on %s\n", g_malcolm.if_name);
		// }

		return (0);
	}

#pragma endregion
