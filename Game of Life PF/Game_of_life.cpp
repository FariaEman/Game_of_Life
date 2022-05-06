   /*Name : Faria Eman
     Roll no: i19-0634
	 Section: CS_E
	 Programming Fundamental Final project*/


//libraries used in this program
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//declaration of functions

void file_reading(string file_name , int sec_arr[] , int &size , int &gene);
void displaying_cordinates(int sec_arr[] , int &size);
void store_in_grid(int sec_arr[] , int grid[20][20] , int neighbour_arr[] , int &size , int &gene);
int counting_neighbours(int j , int k, int grid[20][20] );
void displaying_grid(int grid[20][20] , int g);
void birthing(int x , int y , int arr[] , int &N , int grid[20][20]);
void Death_of_cells(int grid[20][20] , int sec_arr[] , int neighbour_arr[] , int &size , int &k , int &j);
bool Duplicate_checker(int x , int y , int size , int birth_cells[]);
void new_Birth(int sec_arr[] , int grid[20][20] , int arr[] , int subscript , int birth_size , int i);
void neighbour_Update(int neighbour_arr[] , int grid[20][20] , int sec_arr[] , int size);
void generation(int sec_arr[] , int grid[20][20] , int neighbour_arr[] , int &size , int &gene);
void file_writing(int sec_arr[] , int &size , int &gene);

//main function
  int main()
{
    // variables declaration 
	int sec_arr[100];
	int grid[20][20];
	int neighbour_arr[300];
	int size=0,gene=0;
	string file_name;
    //prompt to user
	cout << "Enter the name of file you want to read: " << endl;
	cin >> file_name;
     //function calling
    file_reading(file_name , sec_arr , size , gene);
	displaying_cordinates(sec_arr , size);
	store_in_grid(sec_arr , grid , neighbour_arr , size , gene);
	displaying_grid(grid , gene);
	generation(sec_arr , grid , neighbour_arr , size , gene);
	file_writing(sec_arr , size , gene);
	system("pause");
}

// function for file reading in order to read the generation, size and alive cells
	void file_reading(string file_name , int sec_arr[] , int &size , int &gene)
	{
	
		ifstream ifile(file_name);
		ifile >> gene;
		ifile >> size;
		int x, y;
		if(ifile)
		{
			for (int j = 0, k = 0; j < size; j++, k += 2)
			{
				ifile >> x;
				ifile >> y;
				sec_arr[k] = x;
				sec_arr[k + 1] = y;
			}
	    }
		else
		{
			cout<<"  Input File not Found!"<<endl;
			exit(1);
		}
		ifile.close();
    }
    
// function displaying cordinates of alive cells	
	void displaying_cordinates(int sec_arr[] , int &size)
	{
		cout<<"\n\ncoordinates of alive members in file:\n";
		for (int j = 0,k=0; k < size; j += 2,k++)
		{
			cout << sec_arr[j] << " " << sec_arr[j + 1]<<endl;
		}
		cout<<"\nGENERATION: "<< 0 << endl;
	}

// this function is used to display the grid
	void displaying_grid(int grid[20][20] , int g=0)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				if (grid[j][k] != 1)
				{
					cout << ".";                           //filled the dead cells in the grid with dots 
				}
				else
					cout << grid[j][k];
			}
			cout << endl;
		}
		cout << endl ;
	}

// this function will produce the number of generations written in input file by using coordinates of grid
	void generation(int sec_arr[] , int grid[20][20] , int neighbour_arr[] , int &size , int &gene)
	{
		int birth[100];// to save cords of alive cells
		int birth_size = 0 ;
		for (int g = 0 ; g < gene ; g++)
		{
			cout << "GENERATION: " << g + 1  << endl;                //generation updating
			birth_size = 0;
			neighbour_Update(neighbour_arr , grid , sec_arr , size);
			for (int j = 0 , k = 0 ; j < size ; j++ , k += 2)// saving cords of members to be given birth
			{
				birthing(sec_arr[k] , sec_arr[k + 1] , birth , birth_size , grid);
			
			}
			for (int j = 0 , k = 0 ; j < size ; j++ , k += 2)// killing or deleting the cells which are supposed to die
			{
				if (neighbour_arr[j] != 2 && neighbour_arr[j] != 3)
				{
					Death_of_cells(grid , sec_arr , neighbour_arr , size , k , j);
				}
			}
			for (int j = size , k = 0 , i=0 ; j <size + (birth_size / 2) ; j++ , k += 2 , i+=2)// giving birth to new members
			{
				new_Birth(sec_arr , grid , birth , j , birth_size , i);
			}
			size += (birth_size / 2);// in order to update size
			 
			displaying_grid(grid , g+1); //display of grid
		}
		  
	}

// function used to store the live members into the grid in order to save
// the coordinates of live cells and palce 1 at that x,y coordintes place 
	void store_in_grid(int sec_arr[] , int grid[20][20] , int neighbour_arr[] , int &size , int &gene)
	{
		
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				grid[j][k] = 0;       // to initialize grid with 0
			}
		}
		for (int j = 0 , k = 0 ; k < size ; j += 2 , k++)     //to store 1 at the coordinates of alive members 
		{
			grid[sec_arr[j]][sec_arr[j + 1]]=1;
		}
		for (int j = 0 , k = 0 ; j < size ; j++ , k += 2)   // to fill neighbour_arr with the neighbouring cells counting of each alive member
		{
			neighbour_arr[j] = counting_neighbours(sec_arr[k] ,  sec_arr[k+1] , grid);
		}
	}
	
// function to count the alive neighbours of each alive member, it solves the problem of counting alive neihbours inside the grid 
	int counting_neighbours(int j , int k , int grid[20][20])
	{
		int count,x,y;
		x = j;
		y = k;
			count = 0;
					if (grid[x][y + 1] == 1 && y!=19)// below are the conditions to check for 8 neighbours 
					{
						count++;
					}
					if (grid[x][y - 1] == 1 && y!=0)
					{
						count++;
					}
					if (grid[x - 1][y - 1] == 1 && x!=0 && y!=0)
					{
						count++;
					}
					if (grid[x - 1][y + 1] == 1 && x!=0 && y!=19)
					{
						count++;
					}
					if (grid[x + 1][y - 1] == 1 && y!=0 && x!=19)
					{
						count++;
					}
					if (grid[x + 1][y + 1] == 1 && x!=19 && y!=19)
					{
						count++;
					}
					if (grid[x + 1][y] == 1 && x!=19)
					{
						count++;
					}
					if (grid[x - 1][y] == 1 && x!=0)
					{
						count++;
					}
					return count;
	}

// function to check if the given coordinates in the grid are coordinates of a dead neighbour.
// if yes then it will count the alive neighbours of that dead neighbour.
	void birthing(int x , int y , int arr[] , int &N , int grid[20][20])
	{
		int count = 0;
		// the below conditions will check if the count of alive neighbours of a Dead Neighbour is 3. if yes then it will save its cords
		if (grid[x][y + 1] == 0 && y != 19)
		{
			count = counting_neighbours(x , y + 1 , grid);
			if (count == 3 && Duplicate_checker(x , y+1 , N , arr))
			{
				arr[N] = x;
				arr[N+1] = y + 1;
				N+=2;
			}
			count = 0;
		}
		if (grid[x][y - 1] == 0 && y != 0)
		{
			count = counting_neighbours(x , y - 1 , grid);
			if (count == 3 && Duplicate_checker(x , y - 1 , N , arr))
			{
				arr[N] = x;
				arr[N + 1] = y - 1;
				N += 2;
			}
			count = 0;
		}
		if (grid[x - 1][y - 1] == 0 && x != 0 && y != 0)
		{
			count = counting_neighbours(x - 1 , y - 1 , grid);
			if (count == 3 && Duplicate_checker(x - 1 , y - 1 , N , arr))
			{
				arr[N] = x-1;
				arr[N + 1] = y - 1;
				N += 2;
			}
			count = 0;
		}
		if (grid[x - 1][y + 1] == 0 && x != 0 && y != 19)
		{
			count = counting_neighbours(x - 1 , y + 1 , grid);
			if (count == 3 && Duplicate_checker(x - 1 , y + 1 , N , arr))
			{
				arr[N] = x - 1;
				arr[N + 1] = y + 1;
				N += 2;
			}
			count = 0;
		}
		if (grid[x + 1][y - 1] == 0 && y != 0 && x != 19)
		{
			count = counting_neighbours(x + 1 , y - 1 , grid);
			if (count == 3 && Duplicate_checker(x + 1 , y - 1 , N , arr))
			{
				arr[N] = x + 1;
				arr[N + 1] = y - 1;
				N += 2;
			}
			count = 0;
		}
		if (grid[x + 1][y + 1] == 0 && x != 19 && y != 19)
		{
			count = counting_neighbours(x + 1 , y + 1 , grid);
			if (count == 3 && Duplicate_checker(x + 1 , y + 1 , N , arr))
			{
				arr[N] = x + 1;
				arr[N + 1] = y + 1;
				N += 2;
			}
			count = 0;
		}
		if (grid[x + 1][y] == 0 && x != 19)
		{
			count = counting_neighbours(x + 1 , y , grid);
			if (count == 3 && Duplicate_checker(x + 1 , y , N , arr))
			{
				arr[N] = x + 1;
				arr[N + 1] = y;
				N += 2;
			}
			count = 0;
		}
		if (grid[x - 1][y] == 0 && x != 0)
		{
			count = counting_neighbours(x - 1 , y , grid);
			if (count == 3 && Duplicate_checker(x - 1 , y , N , arr))
			{
				arr[N] = x - 1;
				arr[N + 1] = y;
				N += 2;
			}
			count = 0;
		}
		
	}
//function to kill the given member, it solves the problem of removing the
//dead neighbour from secondary file and update it for other alive members
	void Death_of_cells(int grid[20][20] , int sec_arr[] , int neighbour_arr[] , int &size , int &k , int &j)
	{
	
		grid[sec_arr[k]][sec_arr[k + 1]] = 0;// making grid 0 from 1
		sec_arr[k] = sec_arr[(size*2) - 2];// over writing the sec_arr index with last alive member
		sec_arr[k+1] = sec_arr[(size*2) - 1];
		neighbour_arr[j] = neighbour_arr[size - 1];// updating the neighbour count as well
		size--;
		k -= 2;
		j -= 1;
	}

// this function will not check the duplicate coordinates in birth_cells arr, 
//in order to avoid the repetiton of same coordinates 
	bool Duplicate_checker(int x , int y , int size , int birth_cells[])
	{
		for (int j = 0; j < size; j+=2)
		{
			if (x == birth_cells[j] && y == birth_cells[j + 1])
			{
				return false;
			}
		}
		return true;
	}

//this function will give birth to new members,by solving the probelm of updation sec_arr for the birth of new members
	void new_Birth(int sec_arr[] , int grid[20][20] , int arr[] , int subscript , int birth_size , int i)
	{
		
			sec_arr[subscript*2] = arr[i];// updating the  sec_arr with new_birth arr
			sec_arr[(subscript*2)+1] = arr[i+1];
			grid[arr[i]][arr[i+1]] = 1;// updating the grid
	}
// this function will update the  neighbour_arr with count of alive neighbours
	void neighbour_Update(int neighbour_arr[] , int grid[20][20] , int sec_arr[] , int size)
	{
		 
		for (int j = 0 , k=0 ; j < size ; j++ , k+=2)
		{
			neighbour_arr[j] = counting_neighbours(sec_arr[k] , sec_arr[k + 1] , grid);
		}
	}


//function used to write updated sec_arr in the output file or the alive 
//members present in the last generation and also the generation and size
    void file_writing(int sec_arr[] , int &size , int &gene)
	{
		ofstream ofile("output_file.txt");  //file name
		ofile << gene << endl;
		ofile << size << endl;
		int x, y;
			for (int j = 0, k = 0; k < size; j += 2 , k++)
			{
				x = sec_arr[j];
				y = sec_arr[j + 1];
				ofile << x <<"  "<< y <<endl;
				
			}
    }



