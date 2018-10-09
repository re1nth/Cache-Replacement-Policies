#include <bits/stdc++.h>

#define pi pair<int,string>
#define mp make_pair

using namespace std; 

string hoo(string str)
{	
	string app="";

	for(int i=0;i<str.size();i++)
	{
		if(str[i]!='.')app+=str[i];
		
		else break;
	}

	return app;
}

int con(string str)
{
	int fin=0;

	for(int i=0;i<str.size();i++)
	{
		fin*=10;

		fin+=int(str[i]-'0');
	}

	return fin;
}

int main(int argc, char** argv) 
{ 
   	string out_file ="ES16BTECH11027_";
    out_file+=string(argv[1])+"_";
    out_file+=(hoo(string(argv[2]))+"_");
    out_file+=(string(argv[3])+".out");

    //./binaryName LRU AddressSequenceFile.txt NumberOfCacheEntries
    string inp;
    vector < string > addr;
    // argv[2] is the file name
    string in_file=string(argv[2]);
    // argv[3] is the number of cache entries
    int cache_entries=con(string(argv[3]));
    // open the file and traverse through the entries
    ifstream inFile;
    inFile.open(in_file);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }   
    while (inFile >> inp) {
       	addr.push_back(inp);	
    }
    inFile.close();

    // addr has the all items
    int total_accesses=addr.size();
    int total_misses=0;
    int compulsory_misses=0;
    int capacity_misses=0;
    // process here only to get the final stats
    vector<string> ans;
    // code for FIFO replacement data structure
    queue<string> foo,goo;
    set<string>dir;
    set<string>::iterator it;
    
    for(int i=0;i<addr.size();i++)
    {
    	goo=foo;

    	if(foo.size()<cache_entries)
		{	
			bool vis=0;

			while(!goo.empty())
			{
				if(addr[i]==goo.front()) 
				{
					vis=1;

					break;	
				}

				goo.pop();
			}

			if(vis) ans.push_back("HIT");

			else
			{
				compulsory_misses++;

				ans.push_back("MISS");

				foo.push(addr[i]);
			}
		} 

		else
		{
			bool vis=0;

			while(!goo.empty())
			{
				if(addr[i]==goo.front()) 
				{
					vis=1;

					break;	
				}

				goo.pop();
			}

			if(vis) ans.push_back("HIT");

			else
			{
				ans.push_back("MISS");

				it= dir.find(addr[i]);

				if(it!=dir.end())
				{
					capacity_misses++;	
				}

				else
				{
					compulsory_misses++;
				}

				foo.pop();

				foo.push(addr[i]);
			}
		}
   
    	dir.insert(addr[i]);
    }	

    // write to a file
    ofstream myfile;
	myfile.open (out_file);	
	// File writing goes here
	myfile<<"TOTAL_ACCESSES = "<<total_accesses<<"\n";	
	myfile<<"TOTAL_MISSES = "<<compulsory_misses+capacity_misses<<"\n";
	myfile<<"COMPULSORY_MISSES = "<<compulsory_misses<<"\n";
	myfile<<"CAPACITY_MISSES = "<<capacity_misses<<"\n";

	for(int i=0;i<addr.size();i++)		
	{
		myfile << ans[i]<<"\n";
    }
    myfile.close();

    return 0; 
}

// g++ LRU.cpp -o foo
// ./foo LRU AddressTrace_CacheBlocking.txt 18
// ./foo LRU AddressTrace_WithoutCacheBlocking.txt 18