/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:40:25 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/29 14:52:17 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"

#pragma endregion

#pragma region "ARP Request"

	static int arp_request(struct arp_packet *packet) {
		if (ntohs(packet->eth_type) != ETH_P_ARP)						return (0);
		if (ntohs(packet->operation) != ARP_REQUEST)					return (0);

		if (packet->sender_ip != g_malcolm.target_addr.sin_addr.s_addr)	return (0);
		if (packet->target_ip != g_malcolm.source_addr.sin_addr.s_addr)	return (0);

		uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		if (ft_memcmp(packet->dest_mac, broadcast, 6))					return (0);

		return (1);
	}

#pragma endregion

#pragma region "Receive Request"

	int receive_request() {
		printf("Waiting for ARP request...\n");

		struct arp_packet *packet = &g_malcolm.packet;

		while (g_malcolm.running) {
			ssize_t received = recvfrom(g_malcolm.sockfd, packet, sizeof(struct arp_packet), 0, NULL, NULL);

			if (received < 0) {
				if (errno == EINTR || (errno == EBADF && g_malcolm.sockfd == -1) || errno == EAGAIN || errno == EWOULDBLOCK)	continue;
				fprintf(stderr, "Error receiving packet: %s\n", strerror(errno));					return (1);
			}

			if (arp_request(packet)) {
				printf("An ARP request has been broadcast.\n");
				printf("    mac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n", packet->sender_mac[0], packet->sender_mac[1], packet->sender_mac[2], packet->sender_mac[3], packet->sender_mac[4], packet->sender_mac[5]);

				char ip[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &packet->sender_ip, ip, INET_ADDRSTRLEN);
				printf("    IP address of request: %s\n", ip);

				return (0);
			}
		}

		return (2);
	}

#pragma endregion

#pragma region "Information"

	//                     32 bits
	//    ┌─────────────────────┬─────────────────┐
	//    │  Hardware Type      │  Protocol Type  │
	//    ├──────────┬──────────┼─────────────────┤
	//    │ Hardware │ Protocol │    Operation    │
	//    │  Length  │  Length  │    1:Request    │
	//    │          │          │    2:Reply      │
	//    ├──────────┴──────────┴─────────────────┤
	//    │        Sender Hardware Address        │
	//    ├───────────────────────────────────────┤
	//    │        Sender Protocol Address        │
	//    ├───────────────────────────────────────┤
	//    │        Target Hardware Address        │
	//    ├───────────────────────────────────────┤
	//    │        Target Protocol Address        │
	//    └───────────────────────────────────────┘

#pragma endregion
