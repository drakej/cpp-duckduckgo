/*
 * utils.h
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

using namespace std;

namespace DuckDuckGo
{
	string urlencode(const string &s);
	string jsonObjectToString(json_object * tmpObj);
	string removeQuotes(string s);
}

#endif /* UTILS_H_ */
