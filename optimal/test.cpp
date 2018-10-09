#include <bits/stdc++.h>

using namespace std;

map<string, vector<int> > vec;

int  main()
{
	vec["abc"].push_back(0);

	vec["abc"].push_back(1);

	vec["abc"].push_back(2);

	cout<<vec["abc"][2]<<"\n";

	return 0;
}