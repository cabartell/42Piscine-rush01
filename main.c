/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbartell <cbartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:12:14 by cbartell          #+#    #+#             */
/*   Updated: 2021/02/21 01:35:50 by cbartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define SIZE 4 //this is the amount of rows and columns
#define PERIMETER 16 

int	error(int code)
{
	write(1, "Error\n", 7);
	return(code);
}

void	init_output_arr(int output_arr[][SIZE])
{
	int i;
	
	i = 0;
	while(i < SIZE * SIZE)
	{
		output_arr[i / SIZE][i % SIZE] = 0;
		i++;
	}
}

//removes spaces and turns it into an int array instead of a char array
int	argv_parser(char *str_arr, int *input_arr)
{
	int i;
	int j;
	int temp;
	
	i = 0;
	j = 0;
	while(str_arr[i])
	{
		if (str_arr[i] == ' ')
		{
			i++;
			continue ;
		}
		temp = str_arr[i] - '0';
		if(temp < 1 || temp > SIZE)
			return (3);
		if(j >= PERIMETER)
			return (4);
		input_arr[j] = temp;
		j++;
		i++;
	}
	if (j != PERIMETER)
		return (5);
	return (0);
}

void	final_print(int output_arr[][SIZE])
{
	int i;
	char output[2*SIZE*SIZE];

	i = 0;
	while(i < 32)
	{
		output[i] = ' '; // everything set to automatically be spaces
		if((i + 1) % 8 == 0) //newl at 31, 23 15, 7,  
			output[i] = '\n';
		if(i % 2 == 0) //if no remainder - even
		{
			output[i] = output_arr[(i/2)/SIZE][(i/2)%SIZE] + '0'; //divide by two because array is double normal size (32 instead of 16)
		}
		i++;
	}
	write(1, output, 32);
}

int	main(int argc, char **argv)
{
	int input_arr[PERIMETER]; 
	int output_arr[SIZE][SIZE]; 
	
	if (argc != 2)
		return error(1);
	if (argv_parser(argv[1], input_arr)) //argv[1] is the input, argv[0] would be the name of the file
		return error(1);
	init_output_arr(output_arr);
	final_print(output_arr);
	return (0);
}
