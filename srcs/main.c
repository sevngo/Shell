#include "../incs/minishell.h"

/*
**	-------------------------------------------------------------------------- +
**	If the tty is valid, initializes terminfo database.
**	-------------------------------------------------------------------------- +
*/

static int	tty_check(void)
{
	char	*term_name;
	char	bp[1024];
	int		ret;
	int		sw;

	if (!isatty(STDIN_FILENO))
		return (EXIT_SUCCESS);
	sw = 0;
	if (!(term_name = getenv("TERM")))
	{
		sw = 1;
		if (!(term_name = ft_strdup("xterm-256color")))
			return (sh_return("malloc(3) failed"));
	}
	if ((ret = tgetent(bp, term_name)) < 1)
	{
		ft_strdel(sw == 1 ? &term_name : NULL);
		if (ret == 0)
			return (sh_return("no such entry for current terminal type"));
		else if (ret == -1)
			return (sh_return("terminfo database could not be found"));
	}
	ft_strdel(sw == 1 ? &term_name : NULL);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Builds the AST, and executes it.
**	-------------------------------------------------------------------------- +
*/

static int	main_ast(t_ast **ast, t_token *tokens, char **heredocs)
{
	*ast = NULL;
	if (ast_build(ast, tokens, heredocs) == EXIT_FAILURE)
		sh_exit("build_ast() failed somewhere");
	free_token(&tokens);
	ft_arrfree(heredocs);
	if (read_ast(*ast))
		sh_exit("read_ast() failed somewhere");
	free_ast(ast);
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Tokenizes `input`, and check its grammar.
**	-------------------------------------------------------------------------- +
*/

static int	main_token(t_token **tokens, char **heredocs, char *input)
{
	t_token	*mem;

	mem = NULL;
	*tokens = NULL;
	if (tokenizer(input, tokens) == EXIT_FAILURE)
		sh_exit("tokenizer() failed somewhere");
	ft_strdel(&input);
	if (main_token_is_empty(*tokens) == TRUE)
	{
		free_token(tokens);
		ft_arrfree(heredocs);
		return (EXIT_FAILURE);
	}
	mem = *tokens;
	if (!(is_command(tokens)))
	{
		ft_putendl_fd("42sh: syntax error", STDERR_FILENO);
		free_token(&mem);
		ft_arrfree(heredocs);
		if (!isatty(STDIN_FILENO))
			exit(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	*tokens = mem;
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	Fills `input` and `heredocs`.
**	-------------------------------------------------------------------------- +
*/

static int	main_input(char ***heredocs, char **input)
{
	int	ret;

	*input = NULL;
	*heredocs = NULL;
	if (isatty(STDIN_FILENO))
	{
		if (input_catch(input, heredocs) == EXIT_FAILURE)
			sh_exit("input_catch() failed somewhere");
	}
	else if ((ret = get_next_line(STDIN_FILENO, input)) < 1)
	{
		free_hist(&g_hist);
		exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	if (ft_strisblank(*input) == TRUE)
	{
		ft_strdel(input);
		ft_arrfree(*heredocs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
**	-------------------------------------------------------------------------- +
**	After initializing termcaps & environment, calls main loop of the shell.
**	-------------------------------------------------------------------------- +
*/

int			main(void)
{
	char	**heredocs;
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

	ast = NULL;
	input = NULL;
	g_hist = NULL;
	tokens = NULL;
	heredocs = NULL;
	if (tty_check() == EXIT_FAILURE)
		sh_exit(NULL);
	if (env_init() == EXIT_FAILURE)
		sh_exit("env_init() failed somewhere");
	while (TRUE)
	{
		signal_handler();
		if (main_input(&heredocs, &input) == EXIT_FAILURE)
			continue ;
		if (main_token(&tokens, heredocs, input) == EXIT_FAILURE)
			continue ;
		main_ast(&ast, tokens, heredocs);
	}
}
