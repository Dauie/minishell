/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:24:19 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/22 11:48:16 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int 		ms_envchgstr_parse(t_cmd *info);

int			ms_unsetenv(t_env *shell, t_cmd *info)
{
	char **dtmp;

	dtmp = shell->env;
	if (info->av[1])
	{
		if (!(shell->env = ft_tblrmline(shell->env, info->av[1],
			ft_tbllen(shell->env))))
			return(-1);
		if (dtmp)
			ft_tbldel(dtmp, ft_tbllen(dtmp));
	}
	return (1);
}

char			*ms_craft_newenv(const char *name, const char *value)
{
	char	*newenv;

	if (name == NULL || value == NULL)
		return (NULL);
	if (!(newenv = ft_strnew((ft_strlen(name) + 1) + ft_strlen(value))))
		return (NULL);
	ft_strcpy(newenv, (char *)name);
	ft_strcat(newenv, "=");
	ft_strcat(newenv, value);
	return (newenv);
}

int				ms_setenv(t_env *shell, t_cmd *info)
{
	char 		*newenv;
	char 		**dtmp;

	newenv = NULL;
	dtmp = shell->env;
	if (!info->av[2] && ft_strchr(info->av[1], '='))
		ms_envchgstr_parse(info);
	if (info->av[1] && info->av[2])
	{
		if (!(newenv = ms_craft_newenv(info->av[1], info->av[2])))
			return (-1);
		if (!(shell->env = ft_tbladdl(shell->env, newenv)))
			return (-1);
		if (dtmp)
			ft_tbldel(dtmp, ft_tbllen(dtmp));
		shell->refrshenv = TRUE;
	}
	else
		ms_error(-1, NULL);
	return (1);
}

int 		ms_envchgstr_parse(t_cmd *info)
{
	char	**tmp;

	tmp = NULL;
	if (ft_strchr(info->av[1], '='))
	{
		if (!(tmp = ft_strsplit(info->av[1], '=')))
			return (ms_error(-1, NULL));
		ft_strdel(&info->av[1]);
		ft_strdel(&info->av[2]);
		info->av[1] = tmp[0];
		info->av[2] = tmp[1];
	}
	return (1);
}

