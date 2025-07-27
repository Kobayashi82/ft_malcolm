/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:11:44 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 19:30:06 by vzurera-         ###   ########.fr       */
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

#pragma region "STR_CPY"

	#pragma region "StrCpy"

		char *ft_strcpy(char *dst, const char *src) {
			int	i = -1;

			if (!dst || !src) return (NULL);
			while (src[++i]) dst[i] = src[i];
			dst[i] = '\0';
			return (dst);
		}

	#pragma endregion

	#pragma region "StrLCpy"

		int ft_strlcpy(char *dst, const char *src, int dstsize) {
			int		i = 0, srclen = 0;

			if (!src) return (0);
			while (src[srclen]) ++srclen;
			if (dstsize > 0) {
				while (dstsize > 0 && src[i] && i < dstsize - 1) { dst[i] = src[i]; ++i; }
				dst[i] = '\0';
			}

			return (srclen);
		}

	#pragma endregion

#pragma endregion

#pragma endregion
