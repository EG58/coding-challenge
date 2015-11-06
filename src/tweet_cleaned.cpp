#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>
#include <string.h>


using namespace std;

int clean_text ( string input_string, ofstream& , string );
string extract_time (string line) ; 

int main ()
{
	fstream in_tweet ; 

	in_tweet.open ("../tweet_input/tweet.txt") ;
 
	ofstream out_file  ("../tweet_output/ft1.txt");

	string line;

	char * pch;

	int line_size = 0 ; 

	int i = 0 ; 

	int num_of_unicod_tweets = 0 ; 

	string tweet_time ; 

	while ( in_tweet )
	{
		getline (in_tweet,line);

		//cout << line ;

		line_size = line . size () ; 

		for ( i = 0 ; i < line_size - 4 ; i ++ )
		{
			if ( line [i] == ',' || i == 0  )
			{
				if ( line [i+1] == '\"'  )
				{

					if ( line [i+2] == 't' && line [i+3] == 'e' && line [i+4] == 'x' && line [i+5] == 't' ) 
					{
						
						num_of_unicod_tweets = num_of_unicod_tweets + clean_text ( line . substr (i+6+3,line_size - (i+11) ) , out_file , tweet_time );
					}


					else if ( (line [i+2] == 'c' && line [i+3] == 'r' && line [i+4] == 'e' && line [i+5] == 'a') && i == 0 ) // Created at 
					{
						tweet_time = extract_time (line);

						//out_file << "(timestamp: " << tweet_time << ")" << endl ; 
						
					}


				}



				
			}

			

		}
		 


		
	}

	cout << endl << "Hello Wolrd" << endl << endl ; 

	cout << " num_of_unicod_tweets = " << num_of_unicod_tweets << endl ; 

	out_file << endl << num_of_unicod_tweets << " tweets contained unicode." << endl ; 

	return  0;
}


int clean_text ( string line , ofstream& out_file , string ttime)
{

	cout << line << endl ; 

	string modified = "" ;  

	int i = 0 ; 

	int j = 0 ; 

	int has_unicode = 0 ;

	while (  i < line . size ()  )	
	{
		if ( line [i] == '\\') // one character
		{

			if ( line [i+1] == 'n' || line [i+1] == 't')
			{
				modified = modified + " " ;
				i = i + 2 ;	
			}

			else if ( line [i+1] == '"' )
			{
				modified = modified + "\"" ;
				i = i + 2 ;	
			}

			else if (  line [i+1] == '\'' )
			{
				modified = modified + "'" ;
				i = i + 2 ;	
			}
			else if (  line [i+1] == '\\' )
			{
				modified = modified + "\\" ;
				i = i + 2 ;	
			}
			else if (  line [i+1] == '/' )
			{
				modified = modified + "/" ;
				i = i + 2 ;	
			}

			
			if (  line [i+1] == 'u')
			{	
				has_unicode = 1 ; 
				i = i + 6 ;
			}	
		

				
		}
		
		else
		{
			modified = modified + line [i++];
		}
		
	
	}


	cout << "--------Modified --------" << endl ;
	cout << modified << endl << endl ; 

	out_file << modified << " (timestamp: " << ttime << ")" << endl ;  ;  

	return has_unicode ;
}


/*
\/ -> /
\\ -> \
\' -> '
\” -> “
\n -> space
\t -> space
*/ 

string extract_time (string line)
{
	//cout << "Time  =" << line  << endl ; 

	string ext_time = line ;  

	int i = 0 ; 

	int j = 0 ; 

	int num = 0 ;

	while ( num < 4  )	
	{
		if ( line [i] == '\"')
		{
			num ++ ; 
		}

		if (num == 3 )
		{
			ext_time = line . substr (i+1,i+16) ;
			break;
		}
		
		i++;
	}

	cout << "--------Modified Time = --------" << endl ;
	cout << ext_time << endl; 


	return ext_time;
}

