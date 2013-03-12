//============================================================================
// Name        : cpp-duckduckgo.cpp
// Author      : Jonathan Drake
// Version     : 1.awesome
// License	   : GPLv3
// Description : Example of DuckDuckGo API Usage
//============================================================================

#include <iostream>
#include <stdio.h>
#include <map>
#include <list>
//#include "json/json.h"

#include "API.h"
using namespace std;
using namespace DuckDuckGo;

int main() {
	map<string, string> options;

	options["q"] = "Answer to the Ultimate Question of Life, the Universe, and Everything";
	options["format"] = "json";
	options["no_html"] = '1';
	options["skip_disambig"] = '0';

	ZeroClickInfo *zci;
//	return 0;

	API *api = new API();
	api->secure = true;
	zci = api->zeroClickQuery("apple");

	cout << zci->definition << endl;

	//int i=0;
	map<string,list<Result> >::iterator it;

	for ( it=zci->relatedTopics.begin() ; it != zci->relatedTopics.end(); it++ )
	{
		cout << (*it).first << endl;
	}

//	json_object_object_foreach(obj, key, val)
//	{
//		cout << string(key) << endl;
//	}

	delete zci;
	delete api;

	return 0;
}
