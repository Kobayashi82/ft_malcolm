/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:45 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 00:59:13 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"
	#include "utils.h"

	#include <stdio.h>

#pragma endregion

#pragma region "Validate IP"

	static int validate_ip(const char *ip, struct sockaddr_in *sockaddr) {   
		if (!ip) return (1);

		sockaddr->sin_family = AF_INET;

		return (inet_pton(AF_INET, ip, &sockaddr->sin_addr) != 1);
	}

#pragma endregion

#pragma region "Validate MAC"

	static int validate_mac(const char *mac) {
		if (!mac) return (1);

		int len = ft_strlen(mac);
		if (len != 17)	return (1);

		for (int i = 0; i < 17; ++i) {
			if (i % 3 == 2) { if (mac[i] != ':') return (1); }
			else { if (!((mac[i] >= '0' && mac[i] <= '9') || (mac[i] >= 'a' && mac[i] <= 'f') || (mac[i] >= 'A' && mac[i] <= 'F'))) return (1); }
		}

		return (sscanf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
					(unsigned int*)&g_malcolm.source_mac[0], (unsigned int*)&g_malcolm.source_mac[1],
					(unsigned int*)&g_malcolm.source_mac[2], (unsigned int*)&g_malcolm.source_mac[3],
					(unsigned int*)&g_malcolm.source_mac[4], (unsigned int*)&g_malcolm.source_mac[5]) == 6 ? 0 : 1);
	}

#pragma endregion

#pragma region "Parse"

	int parse_arguments(int argc, char **argv) {
		int result = 0;

		if (argc != 5)													{ fprintf(stderr, "ft_malcolm: expected 4 arguments\n\n");					result = 1; }
		if (!result && validate_ip(argv[1], &g_malcolm.source_addr))	{ fprintf(stderr, "ft_malcolm: invalid IP address: (%s)\n\n", argv[1]);		result = 1; }
		if (!result && validate_mac(argv[2]))							{ fprintf(stderr, "ft_malcolm: invalid MAC address: (%s)\n\n", argv[2]);	result = 1; }
		if (!result && validate_ip(argv[3], &g_malcolm.target_addr))	{ fprintf(stderr, "ft_malcolm: invalid IP address: (%s)\n\n", argv[3]);		result = 1; }
		if (!result && validate_mac(argv[4]))							{ fprintf(stderr, "ft_malcolm: invalid MAC address: (%s)\n\n", argv[4]);	result = 1; }

		if (result) fprintf(stderr, "Usage: ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>\n");

		return (result);
	}

#pragma endregion
