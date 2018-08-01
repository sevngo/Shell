#include "ft_printf.h"

static void	get_flags(t_env *env)
{
	while (isflag(env->form[env->i]))
	{
		if (env->form[env->i] == '#')
			env->conv->flags->hash = 1;
		else if (env->form[env->i] == '0')
			env->conv->flags->zero = 1;
		else if (env->form[env->i] == '-')
			env->conv->flags->min = 1;
		else if (env->form[env->i] == ' ')
			env->conv->flags->space = 1;
		else if (env->form[env->i] == '+')
		{
			env->conv->flags->plus = 1;
			env->conv->flags->space = 0;
		}
		else if (env->form[env->i] == '\'')
			env->conv->flags->apos = 1;
		env->i++;
	}
}

static void	get_width(va_list *ap, t_env *env)
{
	int		id;

	if (env->form[env->i] == '*')
	{
		env->i++;
		if ((id = get_id(env)))
			goto_arg(ap, id, env);
		env->conv->width = va_arg(*ap, int);
	}
	else
	{
		env->conv->width = ft_atoi(&env->form[env->i]);
		while (ft_isdigit(env->form[env->i]))
			env->i++;
	}
	if (env->conv->width < 0)
	{
		env->conv->flags->min = 1;
		env->conv->width *= -1;
	}
}

static void	get_preci(va_list *ap, t_env *env)
{
	int		id;

	if (env->form[++env->i] == '*')
	{
		env->i++;
		if ((id = get_id(env)))
			goto_arg(ap, id, env);
		env->conv->preci = va_arg(*ap, int);
	}
	else
	{
		env->conv->preci = ft_atoi(&env->form[env->i]);
		while (ft_isdigit(env->form[env->i]))
			env->i++;
	}
}

static void	get_len(t_env *env)
{
	if (env->form[env->i] == env->form[env->i + 1])
	{
		if (env->form[env->i] == 'l' && env->conv->len < ll)
			env->conv->len = ll;
		else if (env->form[env->i] == 'h' && env->conv->len < hh)
			env->conv->len = hh;
		env->i++;
	}
	else if (env->form[env->i] == 'h' && env->conv->len < h)
		env->conv->len = h;
	else if (env->form[env->i] == 'l' && env->conv->len < l)
		env->conv->len = l;
	else if (env->form[env->i] == 'j' && env->conv->len < j)
		env->conv->len = j;
	else if (env->form[env->i] == 't' && env->conv->len < t)
		env->conv->len = t;
	else if (env->form[env->i] == 'z' && env->conv->len < z)
		env->conv->len = z;
	else if (env->form[env->i] == 'q' && env->conv->len < q)
		env->conv->len = q;
	else if (env->form[env->i] == 'L' && env->conv->len < L)
		env->conv->len = L;
	env->i++;
}

void		get_conv(va_list *ap, t_env *env)
{
	env->i++;
	while (!istype(env->form[env->i]) && (isflag(env->form[env->i]) ||
		islenght(env->form[env->i]) || ft_isdigit(env->form[env->i]) ||
		(ft_strchr("*.$", env->form[env->i]) && env->form[env->i])))
	{
		env->conv->id = get_id(env);
		get_flags(env);
		if ((ft_isdigit(env->form[env->i]) && env->form[env->i] != '0') ||
				env->form[env->i] == '*')
			get_width(ap, env);
		if (env->form[env->i] == '.')
			get_preci(ap, env);
		while (islenght(env->form[env->i]))
			get_len(env);
	}
	if (env->conv->id)
		goto_arg(ap, env->conv->id, env);
	env->conv->type = env->form[env->i];
}
