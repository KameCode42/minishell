/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:09:27 by david             #+#    #+#             */
/*   Updated: 2025/03/21 15:26:06 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// execute_pwd
// =============================================================================
//
// cwd represente le repertoire
// PATH_MAX = taille max du repertoire
// si le repertoire existe on le print
// sinon perror
//
// =============================================================================

void	execute_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		perror("minishell: cd");
}
