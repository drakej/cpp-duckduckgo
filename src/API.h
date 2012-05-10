/*
 * API.h
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#ifndef API_H_
#define API_H_

#include <string>
#include <map>
#include "curl/curl.h"
#include "ZeroClickInfo.h"

using namespace std;

namespace DuckDuckGo
{
	class API
	{
		public:
			string baseURL;
			bool secure;
			bool noHTML;
			bool noDisambiguations;

			API();
			virtual ~API();
			ZeroClickInfo* zeroClickQuery(string query);
			static int writer(char *data, size_t size, size_t nmemb, string *buffer_in)
			{
				if (buffer_in == NULL)
					return 0;

				buffer_in->append(data, size*nmemb);

				return size * nmemb;
			}
			string getAPIResult(string section, map<string,string> options);
		protected:

			string constructURL(string section, map<string,string> options);

	};
}

#endif /* API_H_ */
