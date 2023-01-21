/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:14:57 by ccariou           #+#    #+#             */
/*   Updated: 2022/09/09 11:53:45 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

/* struct to hold all modifiers %[flags][width][.precision][size]type */
typedef struct s_info{
	va_list		list;
	char		*copy;
	char		*mod;
	char		*minus_mod;
	int			isneg;
	int			copylen;
	int			modlen;
	char		flag[4];
	char		type;
	int			width;
	int			precision;
	char		size[3];
	int			charcount;
	int			cnull;
	int			minuslen;
}				t_info;

typedef int	t_conv(t_info *info);

void	print(t_info *info);
void	dispatch(t_info *info, t_conv **type, int select);
void	get_info(const char **ptr, t_info *info);
void	clean_up(t_info *info);
void	set_struc(t_info *info);

/* Check for all possible modifiers %[flags][width][.precision][size]type */
int		check_flag(const char **ptr, t_info *info);
void	check_width(const char **ptr, t_info *info);
int		check_precision(const char **ptr, t_info *info);
int		check_size(const char **ptr, t_info *info);
int		check_conv(const char **ptr, t_info *info);

/* converter modifiable base*/
int		convert(t_info *info, unsigned long long num, int base);
int		signed_numb(t_info *info, long long num, int base);
int		edge_case(t_info *info, long long numb);
int		numb_len(unsigned long long numb, int base);

/* printers, separated to take in considerations modifiers cspdiouxXf%*/
int		type_c(t_info *info);
int		type_str(t_info *info);
int		type_int(t_info *info);
int		type_p(t_info *info);
int		type_o(t_info *info);
int		type_unsigned(t_info *info);
int		type_x(t_info *info);
int		type_xcap(t_info *info);
int		type_f(t_info *info);
int		type_percent(t_info *info);
int		ft_printf(const char *str, ...);
#endif
