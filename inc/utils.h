/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzurera- <vzurera-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:12:28 by vzurera-          #+#    #+#             */
/*   Updated: 2025/07/27 19:31:30 by vzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma region "Includes"

	#include <stddef.h>

#pragma endregion

#pragma region "Methods"

	size_t	ft_strlen(const char *str);
	char	*ft_strcpy(char *dst, const char *src);
	int		ft_strlcpy(char *dst, const char *src, int dstsize);

#pragma endregion
