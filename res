/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeadd_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:41:08 by abittel           #+#    #+#             */
/*   Updated: 2022/01/27 10:45:16 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_tree.h"

void	ft_treeadd_f(t_tree *t, t_tree *f, int is_a)
{
	if (!t)
		return ;
	if (is_a)
		t->f_a = (struct s_tree *)f;
	else
		t->f_b = f;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:25:59 by abittel           #+#    #+#             */
/*   Updated: 2022/01/29 17:19:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H
# include <stdlib.h>
typedef struct s_tree
{
	void			*content;
	struct s_tree	*f_a;
	struct s_tree	*f_b;
}				t_tree;
t_tree	*ft_treenew(void *content);
void	ft_treeadd_f(t_tree *t, t_tree *f, int is_a);
int		ft_treeprof(t_tree *t);
t_tree	*ft_treenew_fill (void *content, t_tree *fils_a, t_tree *fils_b);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:25:59 by abittel           #+#    #+#             */
/*   Updated: 2022/01/29 17:19:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H
# include <stdlib.h>
typedef struct s_tree
{
	void			*content;
	struct s_tree	*f_a;
	struct s_tree	*f_b;
}				t_tree;
t_tree	*ft_treenew(void *content);
void	ft_treeadd_f(t_tree *t, t_tree *f, int is_a);
int		ft_treeprof(t_tree *t);
t_tree	*ft_treenew_fill (void *content, t_tree *fils_a, t_tree *fils_b);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abittel <abittel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:25:59 by abittel           #+#    #+#             */
/*   Updated: 2022/01/29 17:19:07 by abittel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_H
# define FT_TREE_H
# include <stdlib.h>
typedef struct s_tree
{
	void			*content;
	struct s_tree	*f_a;
	struct s_tree	*f_b;
}				t_tree;
t_tree	*ft_treenew(void *content);
void	ft_treeadd_f(t_tree *t, t_tree *f, int is_a);
int		ft_treeprof(t_tree *t);
t_tree	*ft_treenew_fill (void *content, t_tree *fils_a, t_tree *fils_b);
#endif
