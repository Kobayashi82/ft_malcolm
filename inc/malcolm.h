/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:27:38 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/28 00:54:01 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include "network.h"

#pragma endregion

#pragma region "Structures"

	typedef struct s_malcolm {
		int					running;
		int					sockfd;
		unsigned int		if_index;
		char				if_name[16];
		struct sockaddr_in	source_addr;
		struct sockaddr_in	target_addr;
		uint8_t				source_mac[6];
		uint8_t				spoofed_mac[6];
		struct arp_packet	packet;
	}	t_malcolm;

#pragma endregion

#pragma region "Variables"

	extern t_malcolm g_malcolm;

#pragma endregion

#pragma region "Methods"

	int	parse_arguments(int argc, char **argv);

#pragma endregion
