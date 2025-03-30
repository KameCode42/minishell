/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:09:27 by david             #+#    #+#             */
/*   Updated: 2025/03/30 12:00:38 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =============================================================================
// execute_pwd
// =============================================================================
//
// cwd represente le repertoire
// PATH_MAX = longueur maximale du chemin d'un fichier
// si lechemin absolu comme /home/user/documents/mon_fichier.txt
// ce chemin doit tenir dans PATH_MAX
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
