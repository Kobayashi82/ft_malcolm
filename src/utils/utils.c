/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:11:44 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 14:29:14 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma region "Includes"

	#include "utils.h"

#pragma endregion

#pragma region "STR_LEN"

	size_t ft_strlen(const char *str) {
		size_t i = 0;

		while (str && str[i]) ++i;

		return (i);
	}

#pragma endregion
