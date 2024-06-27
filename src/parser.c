#include "ft_ssl.h"

int	handle_fallback(int opt, char *str, t_ssl *data) {
	if (!opt)
		return (1);
	data->file = ft_append_array(str, data->file);
	return (opt);
}

void	parse_input(char **argv, int argc, t_ssl *data)
{
	if (!(data->cmd = command_token(argv[1])))
	{
		print_error("Error", USAGE_CMD_ERROR);
		exit(EXIT_FAILURE);
	}
	for (int i = 2; i < argc; i++)
	{
		switch(flags_token(argv[i])) {
		case APPEND:
			data->opt.append = handle_fallback(data->opt.append, argv[i], data);
			break;
		case QUIET:
			data->opt.quiet = handle_fallback(data->opt.quiet, argv[i], data);
			break;
		case REVERSE:
			data->opt.reverse = handle_fallback(data->opt.reverse, argv[i], data);
			break;
		case SUM:
			data->opt.sum = handle_fallback(data->opt.sum, argv[i], data);
			if (argv[i + 1] && !data->str_input) {
				data->str_input = ft_strdup(argv[++i]);
			}
			break;
		default:
			data->file = ft_append_array(argv[i], data->file);
			break;
		}
	}
}

void	free_data(t_ssl *data) {
	for (size_t i = 0; data->file && data->file[i]; i++) {
        free(data->file[i]);
    }
	data->file ? free(data->file) : NULL;
	data->stdin_input ? free(data->stdin_input) : NULL;
	data->str_input ? free(data->str_input) : NULL;
}

void	debug_data(t_ssl *data)
{
	fprintf(stdout, "Data Options\n");
	fprintf(stdout, "Quiet: %d\n", data->opt.quiet);
	fprintf(stdout, "Append: %d\n", data->opt.append);
	fprintf(stdout, "Reverse: %d\n", data->opt.reverse);
	fprintf(stdout, "Sum: %d\n", data->opt.sum);
	fprintf(stdout, "Command: %d\n", data->cmd);
	fprintf(stdout, "Input: %s\n", data->str_input);
	if (data->file) {
		fprintf(stdout, "File: %s\n", data->file[0]);
	}
}
