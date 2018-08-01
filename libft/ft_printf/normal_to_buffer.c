#include "ft_printf.h"
#include <libft.h>

static void		get_color(t_env *env)
{
	env->i += 2;
	putstr_to_buffer("\033[", env);
	if (env->form[env->i] == 'o')
		putchar_to_buffer('1', env);
	else if (env->form[env->i] == 'i')
		putchar_to_buffer('3', env);
	else if (env->form[env->i] == 'u')
		putchar_to_buffer('4', env);
	else if (ft_strncmp(&env->form[env->i], "eoc", 3))
	{
		if (env->form[env->i] == 'b')
		{
			putstr_to_buffer("48;5;", env);
			env->i++;
		}
		else
			putstr_to_buffer("38;5;", env);
		while (ft_isdigit(env->form[env->i]))
			putchar_to_buffer(env->form[env->i++], env);
	}
	putchar_to_buffer('m', env);
	while (env->form[env->i - 1] != '}')
		env->i++;
	env->i++;
}

void			normal_to_buffer(t_env *env)
{
	while (env->form[env->i] && env->form[env->i] != '%')
	{
		while (env->form[env->i] == '{' && env->form[env->i + 1] == '$')
			get_color(env);
		env->buf[env->j++] = env->form[env->i++];
		if (env->j == BUFF_SIZE)
		{
			print_buffer(env);
			env->j = 0;
		}
	}
}
