/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbartell <cbartell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:12:14 by cbartell          #+#    #+#             */
/*   Updated: 2021/02/21 14:51:32 by cbartell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define SIZE 4 //this is the amount of rows and columns
#define PERIMETER 16 //this is the perimiter length around the square

int	error(int code)
{
	write(1, "Error\n", 7);
	return(code);
}

//this function initializes the 4x4 output array
void	init_output_arr(int output_arr[][SIZE])
{
	int i;
	
	i = 0;
	//this loop fills the array with zeros (as placeholders)
	while(i < SIZE * SIZE)
	{
		output_arr[i / SIZE][i % SIZE] = 0;
		i++;
	}
}

//This function removes spaces and turns it into an int array instead of a char array
int	argv_parser(char *str_arr, int *input_arr)
{
	int i;
	int j;
	int temp;
	
	i = 0;
	j = 0;
	while(str_arr[i]) //while the array isn't terminated
	{
		if (str_arr[i] == ' ') //if the current index value is a space, increment i and skip the rest of the steps but continue loop
		{
			i++;
			continue ;
		}
		temp = str_arr[i] - '0'; //turn the current index into an int, store it in temp
		if(temp < 1 || temp > SIZE) //if number isnt between 1 and 4, throw error
			return (3); //this throws the error and ends loop
		if(j >= PERIMETER) //if j becomes bigger than or equal to 16, we have too many numbers
			return (4); //throw error and end loop
		input_arr[j] = temp; //if no errors were thrown, we put the value into our input array
		j++; //increment j and i
		i++;
	}
	if (j != PERIMETER) //if j isnt 16 at the end of the loop, input is invalid
		return (5); //throw error and end
	return (0); //if no error was thrown, the function returns 0 (0 means everything went well)
}

// This function is what prints the 4x4 output
void	final_print(int output_arr[][SIZE])
{
	int i;
	char output[2*SIZE*SIZE]; /*we use this to make the 2D array one dimensional so we can print it as a string, 
	we need 2*SIZE*SIZE, because we need to print 16 characters and therefore also 16 characters of whitespace (32 chars in total)*/

	i = 0;
	while(i < 32) 
	{
		output[i] = ' '; // everything set to automatically be spaces (this saves lines)
		if((i + 1) % 8 == 0) //newline at 31, 23, 15, 7 because every 8th index need to be a newline
			output[i] = '\n';
		if(i % 2 == 0) //if no remainder - index is even - turn the int from the output array into a char and add it to the array
		{
			output[i] = output_arr[(i/2)/SIZE][(i/2)%SIZE] + '0'; //divide by two because array is double normal size (32 instead of 16)
		}
		i++;
	}
	write(1, output, 32);
}

int	main(int argc, char **argv)
{
	int input_arr[PERIMETER]; //declare input array
	int output_arr[SIZE][SIZE]; //declare output array
	
	if (argc != 2)
		return error(1);
	if (argv_parser(argv[1], input_arr)) //argv[1] is the input, argv[0] would be the name of the file. We call our argv parser with the given input and our input array
		return error(1); //we throw an error if the input is invalid
	init_output_arr(output_arr); // we call the init output function, check comments for what it does :D
	final_print(output_arr); //then we call final print funtion to print to the console
	return (0); //return zero at the end if everything went fine and end program
}
