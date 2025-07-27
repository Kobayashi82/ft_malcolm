/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:37:52 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 00:23:14 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "malcolm.h"
	#include "utils.h"

	#include <stdio.h>
	#include <net/if.h>
	#include <ifaddrs.h>

#pragma endregion

#pragma region "Get Interface"

	int get_interface() {
		struct ifaddrs		*ifaddr, *ifa;
		struct sockaddr_in	*sa, *mask;
		int					found = 0;

		if (getifaddrs(&ifaddr)) return (1);

		for (ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
			if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;

			sa = (struct sockaddr_in *)ifa->ifa_addr;
			mask = (struct sockaddr_in *)ifa->ifa_netmask;

			// Skip loopback interface (127.0.0.1)
			if (sa->sin_addr.s_addr == htonl(INADDR_LOOPBACK)) continue;

			uint32_t interface_network = sa->sin_addr.s_addr & mask->sin_addr.s_addr;
			uint32_t source_network = g_malcolm.source_addr.sin_addr.s_addr & mask->sin_addr.s_addr;
			uint32_t target_network = g_malcolm.target_addr.sin_addr.s_addr & mask->sin_addr.s_addr;

			// Source and Target must be in the same network
			if (interface_network == source_network && source_network == target_network) { found = 1; break; }
		}

		if (!found) {
			fprintf(stderr, "No interface found that can reach both source and target IPs\n");
			freeifaddrs(ifaddr); return (1);
		}

		ft_strlcpy(g_malcolm.if_name, ifa->ifa_name, sizeof(g_malcolm.if_name));
		g_malcolm.if_index = if_nametoindex(ifa->ifa_name);

		printf("Found available interface: %s\n", ifa->ifa_name);

		freeifaddrs(ifaddr);

		return (0);
	}

#pragma endregion
