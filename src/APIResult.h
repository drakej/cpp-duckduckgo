/*
 * APIResult.h
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#ifndef APIRESULT_H_
#define APIRESULT_H_

#include <map>
#include <string>

using namespace std;

namespace DuckDuckGo
{
	class APIResult
	{
		public:
			APIResult();
			virtual ~APIResult();
		protected:
			static map<string, string> directMappings;
	};
}

#endif /* APIRESULT_H_ */
