#include<iostream>
#include<fstream>
using namespace std;
class Maze
{
	private:
		char **matrix;
		int rows;
		int columns;
		int startrow;
		int startcolumn;
	public:	
		Maze()
		{
			ifstream file;
			file.open("input3.txt");
            file >> rows;
        	startrow = -1;
        	startcolumn = -1;
            matrix = new char*[rows];
            file >> columns;
			char temp,temp2;
            for(int a=0; a<rows ; a++)
            {
                matrix[a] = new char[columns];
            }
            for(int i=0; i<rows ;i++)
            {
            	for(int j=0;j<columns;j++)
            	{	
					file.read(&temp,sizeof(char));
					file.read(&temp2,sizeof(char));
					if(temp2 != ' ')
					{	matrix[i][j] = temp2;
						temp = temp2;}
					if(temp != ' ')
						matrix[i][j] = temp;
            		if(temp == 's')
            		{
            			startrow = i;
            			startcolumn = j;
					}
				}
			}
			if(startrow != -1 && startcolumn != -1)
			{
				findroute(startrow,startcolumn);
			}
			else 
				cout << "no start found";
		}
		void findroute(int i,int j)
		{	
			cout << i << " " << j << endl;
			ofstream outfile("output3.txt",ios::app);
			if(matrix[i+1][j] == '-' && i!= rows-1)
			{ 
				outfile << i << ' ' << j << ' ' << '\n';
				matrix[i][j] = '!';
				findroute(i+1,j);		
			}
			else if(matrix[i][j+1] == '-' && j!=columns-1)
			{
				outfile << i << ' ' << j << '\n';
				matrix[i][j] = '!';
				findroute(i,j+1);				
			}
			else if(matrix[i-1][j] == '-' && i!=0)
			{
				outfile << i << ' ' << j << '\n';
				matrix[i][j] = '!';
				findroute(i-1,j);		
			}
			else if(matrix[i][j-1] == '-' && j!=columns-1)
			{
				outfile << i << ' ' << j << '\n';
				matrix[i][j] = '!';
				findroute(i,j-1);					
			}
			else
			{	
				if(matrix[i-1][j] == 'e' && i!=0)
				{
					outfile << i << ' ' << j << '\n';
			        outfile << i-1 << ' ' << j << '\n';
				}
				else if(matrix[i][j+1] == 'e' && j!=columns-1)
				{
					outfile << i << ' ' << j << '\n';
			        outfile << i << ' ' << j+1 << '\n';
				}
				else if(matrix[i+1][j] == 'e' && i!=rows-1)
				{
					outfile << i << ' ' << j << '\n';
			        outfile << i+1 << ' ' << j << '\n';
				}
				else if(matrix[i][j-1] == 'e' && j!=0)
				{
					outfile << i << ' ' << j << '\n';
			        outfile << i << ' ' << j-1 << '\n';
				}
			}
			outfile.close();
		}
		char &operator()(int i,int j)
		{
			char a = '~';
			if(i<0 || i>rows-1)
			{	
				cout << "Array out bound" << endl;
				return a;
			}
			if(j<0 || j>rows-1)
			{	
				cout << "Array out bound" << endl;
				return a;
			}
			return matrix[i][j];
		}
		~Maze()
		{
			for(int z=rows-1;z>=0;--z)
			{
				delete matrix[z];
			}
			delete [] matrix;
		}
};
int main()
{
	Maze m;
}
