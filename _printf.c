#include "main.h"

void print_buffer(char buffer[], int *index);

/**
 * _printf - writes output to stdout
 * @format: the character string (c, s, %)
 * Return: the number of printed characters.
 */
int _printf(const char *format, ...)
{
	int i, chars = 0, output = 0;
	int flags, len, correctness, size, index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[index++] = format[i];
			if (index == BUFF_SIZE)
				print_buffer(buffer, &index);
			output++;
		}
		else
		{
			print_buffer(buffer, &index);
			flags = get_flags(format, &i);
			len = get_width(format, &i, list);
			correctness = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			chars = handle_print(format, &i, list, buffer,
				flags, len, correctness, size);
			if (chars == -1)
				return (-1);
			output += chars;
		}
	}

	print_buffer(buffer, &index);

	va_end(list);

	return (output);
}

/**
 * print_buffer - Prints buffer contents
 * @buffer: Character array
 * @index: current buffer length
 */
void print_buffer(char buffer[], int *index)
{
	if (*index > 0)
		write(1, &buffer[0], *index);

	*index = 0;
}
