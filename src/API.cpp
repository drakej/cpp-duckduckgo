/*
 * API.cpp
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#include <string>
#include <iostream>
#include "json/json.h"
#include "curl/curl.h"
#include "API.h"
#include "ZeroClickInfo.h"
#include "utils.h"

using namespace std;

namespace DuckDuckGo {

API::API()
{
	secure = false;
	noHTML = false;
	noDisambiguations = false;
	baseURL = "api.duckduckgo.com";
}
string API::constructURL(string section, map<string,string> options)
{
	string url = "";
	if (secure)
		url = "https://" + baseURL;
	else
		url = "https://" + baseURL;

	url += section;

	if (options.size() > 0)
	{
		map<string, string>::iterator ii=options.begin();

		url += "?" + urlencode((*ii).first) + '=' + urlencode((*ii).second);

		ii++;

		for (; ii != options.end(); ii++)
			url += '&' + urlencode((*ii).first) + '=' + urlencode((*ii).second);
	}

	// Debugging only
	cout << url << endl;

	return url;
}

string API::getAPIResult(string section, map<string, string> options)
{
	string url = constructURL(section, options);

	CURL *handle;
	//CURLcode res;

	//char errorBuffer[CURL_ERROR_SIZE];
	string buffer;

	handle = curl_easy_init();
	if (handle) {
		curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, API::writer);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer);

//		if (res != CURLE_OK) {
//			cerr << "Failed to set write data [" + string(errorBuffer) + "]" << endl;
//		}

		curl_easy_perform(handle);

		curl_easy_cleanup(handle);

		//cout << buffer << endl;
		return string(buffer);
	}
	else
		return "";
}

ZeroClickInfo* API::zeroClickQuery(string query)
{
	map<string, string> options;

	options["q"] = query;
	options["format"] = "json";
	options["no_html"] = (this->noHTML ? '1' : '0');
	options["no_redirect"] = '1';
	options["skip_disambig"] = (this->noDisambiguations ? '1' : '0');

	string result = this->getAPIResult("/", options);

	if (!result.size())
		throw "Empty results";

	json_object *obj = json_tokener_parse(result.c_str());

	return new ZeroClickInfo(obj);
}

API::~API()
{
	// TODO Auto-generated destructor stub
}

}
