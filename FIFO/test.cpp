#include <bits/stdc++.h>

using namespace std;

int main()
{
	queue<int>foo,goo;

	foo.push(4);

	foo.push(3);

	foo.push(5);

	goo=foo;

	cout<<goo.size()<<"\n";

	while(!goo.empty())
	{
		cout<<goo.front()<<"\n";

		goo.pop();
	}

	return 0;
}