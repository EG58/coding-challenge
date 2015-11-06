#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "b.h"

using namespace std;

int clean_text ( string input_string );
int hash_tag ( string line );

string creat_hash_entity ( string sub ,  string edge);
string extract_time (string line);


int compare_time ( string first, string second ) ;  // if first is less than 60 seconds before second
int compare_hour ( string time_1 , string time_2 ) ; 
int compare_date ( string  , string  , string  , string  , string  , string  , string  , string  );

int creat_edge_entity (string edge , int clique_size ); 

vector <hash_time> node_list;
vector <edge_time> edge_list ; 

string current_time ; 

int N , E ;

int main ()
{
	fstream in_tweet ;

	in_tweet.open ("../tweet_input/tweet.txt") ; 

	ofstream out_file  ("../tweet_output/ft2.txt");



	//-------------------------------
	node_list . clear() ;  
	edge_list . clear () ; 

	N = 0 ; 
	E = 0 ;
	// -------------------------

	string line;

	char * pch;

	int line_size = 0 ; 

	int i = 0 ; 
	string tweet_time ;

	float avg = 0 ; 

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
						 
						//cout << line  << endl ; 

						//cout << line . substr (i+6+2,line_size - i+6 ) << endl ; 

						//clean_text ( line . substr (i+6+2,line_size - i+6 ) );

						hash_tag ( line );
						cout << "-------------" << endl ;

						if (N)
						{
							cout << endl << "----------Average Degree is " << E / N << endl << endl ; 


							avg = float(E) / float(N) ; 

							//out_file << " N = "  << N << " E = " << E << " Avg = " << fixed << setprecision(2) << avg<< endl ; 

							out_file << fixed << setprecision(2) << avg << endl ;

						}		
					}

					else if ( (line [i+2] == 'c' && line [i+3] == 'r' && line [i+4] == 'e' && line [i+5] == 'a') && i == 0 ) // Created at 
					{
						tweet_time = extract_time (line);
						cout << "-------------" << endl ;

						current_time = tweet_time ; 
					}

				}

				
			}

			

		}

		

				
	}

	cout << endl << "Hello Wolrd" << endl << endl ; 

	return  0;
}


int clean_text ( string line )
{

	cout << line << endl ; 

	string modified = line ;  

	int i = 0 ; 

	int j = 0 ; 

	while (  i < line . size ()  )	
	{
		if ( line [i] != '\\')
		{
			modified [j] = line [i];
			i ++ ; 	
			j++ ;
		}
		if ( line [i] == '\\' && line [i+1] == 'u')
		{
			i = i + 6 ;
		}
	}

	cout << "--------Modified --------" << endl ;
	cout << modified << endl; 

	return 0 ;
}

int hash_tag ( string line )
{
	
    istringstream iss(line);

    string edge ; 	
 
    int clique_size = 0 ;

    do
    {
        string sub;
        iss >> sub;
        //cout << "Substring: " << sub << endl;

	if ( sub [0] == '#') // Hash tagh
	{
		if ( sub [sub.size()-1]  == '\"' )
		{	
			sub = sub . substr ( 0 , sub.size() -1 );
		}
		edge = creat_hash_entity ( sub , edge );
		clique_size ++ ; 
	} 


    } while (iss);

    //-------------Updating N -------------------------
    N = node_list . size (); 
    //-------------Updating N -------------------------	
	
    //cout << " EDGE CREATE IS = " << edge << endl ; 

    cout << "Clique size = " << clique_size << endl ; 	    
	
    if ( clique_size ) 
    {    
	creat_edge_entity ( edge , clique_size ) ;
    }

    cout << "N is " << N << " E is " << E << endl ; 

}

string creat_hash_entity ( string sub , string edge )
{
	if (sub [sub. size()-1] == ',')
	{
		sub = sub . substr (0,sub .size()-2);
	}

	hash_time new_entry ;

	int was_in_list = 0 ; 

	if ( node_list . size () == 0 )
	{
		new_entry . _hash_tag = sub; 
		new_entry . _time = current_time ; 
		
		node_list . push_back (new_entry);

		cout << "Hash Tag " << sub << " Created  " << endl ; 
	}
	else // the list was not empty 
	{

		for ( int i = 0 ; i < node_list .size () ; i ++ )
		{
			if ( node_list . at (i) . _hash_tag == sub )
			{
				was_in_list = 1 ; 
				
				node_list . at (i) . _time = current_time ; 	

				cout << "Hash Tag " << sub << " UPDATED  " << endl ; 
			}
		
			else if ( !compare_time ( node_list . at (i) . _time , current_time ) ) // if it is older than 60 sec
			{
				 node_list . erase ( node_list . begin () + i )  ;
			}
	

		}
		
		if ( was_in_list == 0  )
		{
			new_entry . _hash_tag = sub; 
			new_entry . _time = current_time ; 
			
			node_list . push_back (new_entry);
			
			cout << "Hash Tag " << sub << " Created  " << endl ; 
		}

	}

	string out_edge;

	out_edge = edge + " " + sub ; 
	
	return out_edge ; 
}

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



int creat_edge_entity ( string edge , int clique_size )
{
    cout << " Creating Edge " << edge << " clique_size = " << clique_size <<  endl ;  ; 

    istringstream iss(edge);

    vector <string> clique ; 

    int condition ; 

    do
    {

        string sub;
        iss >> sub;


	if (sub . size () >= 2 )
	{
		//cout << " __ " << sub ;
		clique . push_back ( sub ) ; 

		cout << " CL" << sub << " " ;  
	}

    }
    while  ( iss ) ;
	
    cout << endl ; 

    edge_time new_edge ;

    string first_node , second_node ;

    int k , i , j ; 	

    for (  i = 0 ; i < clique_size -1  ; i ++ )
    {
	first_node = clique . at (i); 	

	cout << " first_node = " << i << endl ;
	cout << " second range is " << i+1 << " to " << clique_size - 1 << " ^^^^"<< endl ; 

	for (  j = i+1 ; j < clique_size ; j ++ )	
	{
	
		second_node = clique . at (j); 	

		cout << " first_node = " << first_node << " second_node " << second_node << endl ; 

		if ( edge_list . size () == 0 )
		{
			new_edge . _tag1 = first_node ;
			new_edge . _tag2 = second_node ;
			new_edge . _time = current_time ; 

			edge_list . push_back ( new_edge ) ; 
			E = E + 2 ; 

			cout << "&&& Creating " << first_node << "<__>" << second_node << endl ;
			
		}

		else 
		{
			condition = 0 ; 

			for ( k = 0 ; k < edge_list . size () ; k ++ )
			{
				//cout << "edge_list . at (k) . _tag1 " << edge_list . at (k) . _tag1  ;
				
				//cout << " edge_list . at (k) . _tag2 " << edge_list . at (k) . _tag2   << endl ; 

				if (  condition == 0 )
				condition =  (( edge_list . at (k) . _tag1 == first_node && edge_list . at (k) . _tag2 == second_node ) || ( edge_list . at (k) . _tag2 == first_node && edge_list . at (k) . _tag1 == second_node )) ; 
				
				if ( condition )
				{
				 	edge_list . at (k)  . _time = current_time ; // Update Edge

					cout << "#### this is the case" << endl;

				}
			}

				
			if ( condition == 0   )
			{
					new_edge . _tag1 = first_node ;
					new_edge . _tag2 = second_node ;
					new_edge . _time = current_time ; 

					cout << "&&& Adding " << first_node << "<__>" << second_node << " edge_list . size () = " << edge_list . size () << endl ;
	
					edge_list . push_back ( new_edge ) ; 

					E = E + 2 ; 

			}

			 

		} // else 

		
		
	} // for 

	cout << " ^^^^"<< endl ; 
    }		


    //--------------------------------------------------------------------	
    for ( int u = 0 ; u < edge_list . size (); u ++ )	
    {

		if ( ! compare_time ( edge_list . at (u) ._time , current_time) ) // if it is older than 60 sec
		{
			// ------------ Updating E --------------------	
			E = E - 2 ; 
			// ----------------------------------------------	
				
			edge_list . erase ( edge_list . begin () + u )  ; // Removing some of Edges
			
		}
    }
		
    return 0 ; 	 
} 


int compare_time ( string first, string second ) // if first is less than 60 seconds before second
{
	cout << "Comparing ( " << first << " , " << second << " )" << endl ; 

	istringstream iss(first);
	istringstream iss2(second);

	string month_1 , month_2 ;
	string day_1   , day_2 ;
	string time_1 , time_2 ;
	string year_1 , year_2 ; 

	int i = 0 ; 

   	do
    	{
		i++; 

        	string sub;
        	iss >> sub;

		string sub2;
        	iss2 >> sub2;

		if ( i == 2 )
		{
			month_1 = sub;
			month_2 = sub2 ;

		}
		
		else if ( i == 3 )		
		{
			day_1 = sub;
			day_2 = sub2;
		}
		else if ( i == 4 )		
		{
			time_1 = sub;
			time_2 = sub2;
		}

		else if ( i == 6  )
		{
			year_1 = sub;
			year_2 = sub2;
		}

		
    	} while (iss);

	cout << "---------- month2 = "  << month_2 << " day2 = " << day_2 << " time2 = " << time_2  << " year2 = " << year_2 << endl ;

	string date_2 = month_2 + day_2 + year_2 ; 
	string date_1 = month_1 + day_1 + year_1 ; 

	cout << "data_1 = " << date_1 << " data_2 = " << date_2 << endl ; 

	if ( date_1 == date_2 )
	{
		return compare_hour ( time_1 , time_2  ) ; 
	}
	
	else
	{
		return compare_date ( month_1 , month_2 , day_1 , day_2 , year_1 , year_2 , time_1 , time_2  )  ;
	}
}

int compare_hour ( string time_1 , string time_2 ) 
{
	int h1 = atoi ( time_1 . substr (0,2) . c_str() ) ; 
	int h2 = atoi ( time_2 . substr (0,2) . c_str() ) ; 


	int m1 = atoi ( time_1 . substr (3,2) . c_str() ) ; 
	int m2 = atoi ( time_2 . substr (3,2) . c_str() ) ; 

	int s1 = atoi ( time_1 . substr (6,2) . c_str() ) ; 
	int s2 = atoi ( time_2 . substr (6,2) . c_str() ) ; 

 
	cout << "h1 = " << h1 << " m1 = " << m1 << " s1 = " << s1 << endl ;
	cout << "h2 = " << h2 << " m2 = " << m2 << " s2 = " << s2 << endl ;

	int t1 = h1 * 3600 + m1 * 60 + s1 ;
	int t2 = h2 * 3600 + m2 * 60 + s2 ;

	if ( t1 <= t2 - 60 )
	{
		return 0 ; 
	}
	else
		return 1 ;  // T1 is less than 60 second before T2

}

int compare_date ( string month_1 , string month_2 , string day_1 , string day_2 , string year_1 , string year2 ,   string time_1 , string time_2  )  
{
	// Jan Feb Mar
	// Apr May Jun
	// Jul Aug Sept 
        // Oct Nov Dec

	/*
	if ( year_1 != year_2 )
	{
		if ( month_1 == "Dec" && month_2 == "Jan" )
		{
			return 1 ; 
		}


	}

	else // years are equal 
	{

		if ( month_1 != month_2 )
		{
		}

		else  // year and month are equal 
		{
			if ( day_1 != day_2 ) 
			{
			}

			else // year month and day are equal 
			{
				return compare_hour ( time_1 , time_2 );
			}

		}
	}



	return 0 ;
	*/

	return 0 ; 
}
