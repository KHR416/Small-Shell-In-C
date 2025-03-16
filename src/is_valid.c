#include "minishell.h"
#include "astree.h"
#include "token.h"

int	is_input_redirect(t_token_type type)
{
	return (type == TOKEN_INPUT_REDIRECT || type == TOKEN_HERE_DOC);
}

int	is_output_redirect(t_token_type type)
{
	return (type == TOKEN_OUTPUT_REDIRECT || type == TOKEN_APPEND_REDIRECT);
}

int	is_redirect(t_token_type type)
{
	return (is_input_redirect(type) || is_output_redirect(type));
}

int	is_ceu(t_token_type type)
{
	return (type == TOKEN_LITERAL || is_redirect(type));
}

int	is_ceu_valid(t_token_stream *stream)
{
	if (!is_ceu(stream->arr[stream->offset].type))
	{
		print_error_unexpected_token(stream->arr[stream->offset].type);
		return (0);
	}
	while (is_ceu(stream->arr[stream->offset].type))
	{
		if (is_input_redirect(stream->arr[stream->offset].type) || is_output_redirect(stream->arr[stream->offset].type))
		{
			++stream->offset;
			if (stream->arr[stream->offset].type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(stream->arr[stream->offset].type);
				return (0);
			}
			++stream->offset;
		}
		else
			++stream->offset;
	}
	return (1);
}

int	is_logical_operator(t_token_type type)
{
	return (type == TOKEN_AND_OPERATOR || type == TOKEN_OR_OPERATOR);
}

int	is_paran(t_token_type type)
{
	return (type == TOKEN_AND_OPERATOR || type == TOKEN_OR_OPERATOR);
}

int	is_valid(t_token_stream *stream, t_msvar *msvar)
{
	size_t	p_count = 0;

	while (stream->arr[stream->offset].type != TOKEN_NONE)
	{
		if (stream->arr[stream->offset].type == TOKEN_LITERAL)
			++stream->offset;
		else if (is_redirect(stream->arr[stream->offset].type))
		{
			++stream->offset;
			if (stream->arr[stream->offset].type != TOKEN_LITERAL)
			{
				print_error_unexpected_token(stream->arr[stream->offset].type);
				return (0);
			}
		}
		else if (stream->arr[stream->offset].type == TOKEN_PIPE || is_logical_operator(stream->arr[stream->offset].type))
		{
			if (!stream->offset || (stream->arr[stream->offset - 1].type != TOKEN_LITERAL && stream->arr[stream->offset - 1].type != TOKEN_PARENTHESIS_CLOSE))
			{
				print_error_unexpected_token(stream->arr[stream->offset].type);
				return (0);
			}
			++stream->offset;
			if (stream->arr[stream->offset].type == TOKEN_NONE)
				if (read_and_append(stream, msvar))
				{
					ft_putendl_fd("bash: syntax error: unexpected end of file", STDERR_FILENO);
					return (0);
				}
		}
		else if (stream->arr[stream->offset].type == TOKEN_PARENTHESIS_OPEN)
		{
			if (stream->offset && stream->arr[stream->offset - 1].type == TOKEN_LITERAL)
			{
				print_error_unexpected_token(stream->arr[stream->offset].type);
				return (0);
			}
			++p_count;
			++stream->offset;
		}
		else if (stream->arr[stream->offset].type == TOKEN_PARENTHESIS_CLOSE)
		{
			if (!stream->offset || stream->arr[stream->offset - 1].type != TOKEN_LITERAL || !p_count)
			{
				print_error_unexpected_token(stream->arr[stream->offset].type);
				return (0);
			}
			--p_count;
			++stream->offset;
		}
		else
		{
			fprintf(stderr, "Unexpected exception\n");
			return (0);
		}
		if (stream->arr[stream->offset].type == TOKEN_NONE && p_count)
			if (read_and_append(stream, msvar))
			{
				ft_putendl_fd("bash: syntax error: unexpected end of file", STDERR_FILENO);
				return (0);
			}
	}
	stream->offset = 0;
	return (1);
}

