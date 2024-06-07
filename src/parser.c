#include "ft_ssl.h"

void	parse_input(char **argv, int argc, t_ssl *data)
{
	data->cmd = command_token(argv[1]);
	if (!data->cmd)
	{
		// print error
		exit(1);
	}
	for (int i = 2; i < argc; i++)
	{
		switch(flags_token(argv[i])) {
		case APPEND:
			data->opt.append = 1;
			break;
		case QUIET:
			data->opt.quiet = 1;
			break;
		case REVERSE:
			data->opt.reverse = 1;
			break;
		case SUM:
			data->opt.sum = 1;
			break;
		default:
			if (i == argc - 1)
			{
				data->input = strdup(argv[i]);
				break;
			}
			// print error
			exit(1);
		}
	}
}


void	debug_data(t_ssl *data)
{
	fprintf(stdout, "Data Options\n");
	fprintf(stdout, "Quiet: %d\n", data->opt.quiet);
	fprintf(stdout, "Append: %d\n", data->opt.append);
	fprintf(stdout, "Reverse: %d\n", data->opt.reverse);
	fprintf(stdout, "Sum: %d\n", data->opt.sum);
	fprintf(stdout, "Command: %d\n", data->cmd);
	fprintf(stdout, "Input: %s\n", data->input);
}
