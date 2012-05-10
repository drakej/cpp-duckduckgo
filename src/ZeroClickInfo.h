/*
 * ZeroClickInfo.h
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#ifndef ZEROCLICKINFO_H_
#define ZEROCLICKINFO_H_

#include "APIResult.h"
#include "json/json.h"
#include <map>
#include <list>

using namespace std;

namespace DuckDuckGo
{
	struct Result
	{
		string description;
		string URL;
		string iconURL;
	};

	class ZeroClickInfo : public virtual DuckDuckGo::APIResult
	{
		public:
			ZeroClickInfo(json_object *data);
			//virtual ~ZeroClickInfo();

			static const int TYPE_NONE = 0;
			static const int TYPE_ARTICLE = 1;
			static const int TYPE_CATEGORY = 2;
			static const int TYPE_DISAMBIGUATION = 3;
			static const int TYPE_EXCLUSIVE = 4;
			static const int TYPE_NAME = 5;

			string heading;
			string summary;
			string textSummary;
			string summarySource;
			string summarySourceURL;
			string imageURL;
			string answer;
			string answerType;
			string definition;
			string definitionSource;
			string definitionSourceURL;
			map<string, list<Result> > relatedTopics;
			list<Result> results;
			int type;

		protected:
			// static member functions to initiliaze the maps once before runtime
			static map<char,int> fillResultTypeMap();

			static map<char,int> resultTypeMapping;
			map<string,string*> directMappings;
	};
}

#endif /* ZEROCLICKINFO_H_ */
