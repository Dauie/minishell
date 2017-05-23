/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:24:19 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 17:50:51 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_unsetenv(t_env *shell, t_cmd *info)
{
	int i;
	
	i = 0;
	while (info->av[++i])
	{
		if ((unsetenv(info->av[i])) < 0)
			ft_printf("%s: issue unsetting variable %s",G_PROJ, info->av[i]);
	}
	shell->renv = TRUE;
	return (1);
}

int			ms_setenv(t_env *shell, t_cmd *info)
{
	setenv(info->av[1], info->av[2], 1);
	shell->renv = TRUE;
	return (1);
}
