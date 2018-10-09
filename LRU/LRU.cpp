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
    map<string,int> dir;
    set<pi>curr;
    set<pi>::iterator it;
    int tim_cnt=0;

    // code for LRU replacement data structure
    for(int i=0;i<addr.size();i++)
    {
    	string x=addr[i];
    	int y;
		
		if(dir.count(x)>0) y=dir[x];
		else y =-1;

		pi foo=mp(y,x);
		it = curr.find(foo);

		if(it!=curr.end())
		{
			ans.push_back("HIT");
			curr.erase(it);
		}

		else
		{
			ans.push_back("MISS");	

			total_misses++;

			if(curr.size()<cache_entries) compulsory_misses++;

			else
			{
				it=curr.begin();
				curr.erase(it);

				if(dir.count(x)>0) capacity_misses++;
		    	else compulsory_misses++;
		    }	
		}

	    curr.insert(mp(tim_cnt,x));
		dir[x]=tim_cnt;

		tim_cnt++;
    }	

    // write to a file
    ofstream myfile;
	myfile.open (out_file);	
	// File writing goes here
	myfile<<"TOTAL_ACCESSES = "<<total_accesses<<"\n";	
	myfile<<"TOTAL_MISSES = "<<total_misses<<"\n";
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