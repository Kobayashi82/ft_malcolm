/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:40:08 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 13:52:58 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <errno.h>
	#include <string.h>
	#include <net/if.h>
	#include <ifaddrs.h>
	#include <arpa/inet.h>
	#include <linux/if_packet.h>

#pragma endregion

#pragma region "Defines"

	#define SO_BINDTODEVICE	25
	#define ARP_REQUEST		1
	#define ARP_REPLY		2
	#define ETH_P_IP		0x0800
	#define ETH_P_ARP		0x0806

#pragma endregion

#pragma region "Structures"

	struct __attribute__((__packed__)) arp_packet {
		// Ethernet header
		uint8_t  dest_mac[6];		// Target MAC address (FF:FF:FF:FF:FF:FF for broadcast)
		uint8_t  src_mac[6];		// Sender MAC address
		uint16_t eth_type;			// ARP_PROTOCOL
		// ARP header
		uint16_t hw_type;			// 1 (Ethernet)
		uint16_t proto_type;		// ETH_P_IP (IPv4)
		uint8_t  hw_len;			// 6 (MAC length)
		uint8_t  proto_len;			// 4 (IP length)
		uint16_t operation;			// 1 (ARP Request) 2 (ARP Reply)
		uint8_t  sender_mac[6];		// Sender MAC address
		uint32_t sender_ip;			// Sender IP address
		uint8_t  target_mac[6];		// Target MAC address (00:00:00:00:00:00 if unkown)
		uint32_t target_ip;			// Target IP address
	};

#pragma endregion

#pragma region "Methods"

	int create_socket();
	int get_interface();
	int receive_request();
	int send_reply();

#pragma endregion
