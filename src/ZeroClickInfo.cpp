/*
 * ZeroClickInfo.cpp
 *
 *  Created on: May 4, 2012
 *      Author: drakej
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <list>
#include "json/json.h"
#include "utils.h"
//#include "curl/curl.h"
//#include "API.h"
#include "ZeroClickInfo.h"

//#include "utils.h"

using namespace std;

namespace DuckDuckGo
{
	ZeroClickInfo::ZeroClickInfo(json_object *data)
	{
		json_object * tmpObj;
		json_object * tmpObjLvl2;
		json_object * jvalue;
		const char * cstr_value;
		int arraylen = 0;
		int i;
		char charType;
		string value;

		// map the member variable addrs to their string key
		directMappings["Abstract"] = &summary;
		directMappings["AbstractText"] = &textSummary;
		directMappings["AbstractSource"] = &summarySource;
		directMappings["Image"] = &imageURL;
		directMappings["Heading"] = &heading;
		directMappings["Answer"] = &answer;
		directMappings["AnswerType"] = &answerType;
		directMappings["Definition"] = &definition;
		directMappings["DefinitionSource"] = &definitionSource;
		directMappings["DefinitionURL"] = &definitionSourceURL;

		/* Process direct mappings first. */
		for (map<string,string*>::iterator it = directMappings.begin(); it != directMappings.end(); ++it)
		{
			tmpObj = json_object_object_get(data, (it->first).c_str());
			value = jsonObjectToString(tmpObj);

			cout << value << endl;
			cout << it->first << endl;

			// Empty if string is "" so store the string and look for non empty
			if (value == "")
			{
				*it->second = value;
				//cout << it->first << endl;
			}
			else
				*it->second = "";
		}

		/* Now process special API fields. */

		/* The ZeroClickInfo type. */
		value = jsonObjectToString(json_object_object_get(data, "Type"));
		charType = value[1];

		if (charType != '"' && resultTypeMapping.find(charType) != resultTypeMapping.end())
			type = resultTypeMapping[charType];
		else
			type = TYPE_NONE;

		value = "";

		/* Related URLs. */
		tmpObj = json_object_object_get(data, "Results");
		value = string(json_object_to_json_string(tmpObj));

		//cout << value << endl;

		arraylen = json_object_array_length(tmpObj);
		cout << arraylen << endl;

		if (arraylen)
			for (i=0; i< arraylen; i++)
			{
				Result tmpResult;

				jvalue = json_object_array_get_idx(tmpObj, i);

				tmpResult.description = string(json_object_to_json_string(json_object_object_get(jvalue, "Text")));
				tmpResult.URL = json_object_to_json_string(json_object_object_get(jvalue, "FirstURL"));
				tmpResult.iconURL = json_object_to_json_string(json_object_object_get(json_object_object_get(jvalue, "Icon"), "URL"));
				results.push_back(tmpResult);

				//cout << json_object_get_string(jvalue) << endl;
			}

		tmpObj = json_object_object_get(data, "RelatedTopics");
		value = json_object_to_json_string(tmpObj);
		arraylen = json_object_array_length(tmpObj);

		list<Result> tmpList;
		relatedTopics["General"] = tmpList;

		if (arraylen)
			for (i=0; i< arraylen; i++)
			{
				jvalue = json_object_array_get_idx(tmpObj, i);

				tmpObjLvl2 = json_object_object_get(jvalue, "Name");

				if (tmpObjLvl2)
				{
					int arrayLen2 = 0;
					list<Result> tmpList;
					string name = json_object_to_json_string(tmpObjLvl2);
					tmpObjLvl2 = json_object_object_get(jvalue, "Topics");
					arrayLen2 = json_object_array_length(tmpObjLvl2);
					name = removeQuotes(name);

					relatedTopics[name] = tmpList;

					for (int j=0;j<arrayLen2;j++)
					{
						jvalue = json_object_array_get_idx(tmpObjLvl2, j);

						Result tmpResult;

						//cout << json_object_to_json_string(jvalue) << endl;

						tmpResult.description = string(json_object_to_json_string(json_object_object_get(jvalue, "Text")));
						tmpResult.URL = json_object_to_json_string(json_object_object_get(jvalue, "FirstURL"));
						tmpResult.iconURL = json_object_to_json_string(json_object_object_get(json_object_object_get(jvalue, "Icon"), "URL"));

						relatedTopics[name].push_back(tmpResult);
					}
				}
				else
				{
					Result tmpResult;

					tmpResult.description = removeQuotes(string(json_object_to_json_string(json_object_object_get(jvalue, "Text"))));
					tmpResult.URL = json_object_to_json_string(json_object_object_get(jvalue, "FirstURL"));
					tmpResult.iconURL = json_object_to_json_string(json_object_object_get(json_object_object_get(jvalue, "Icon"), "URL"));

					relatedTopics["General"].push_back(tmpResult);
				}
			}
	}

	map<char,int> ZeroClickInfo::fillResultTypeMap()
	{
		map<char,int> tempMap;

		tempMap['A'] = TYPE_ARTICLE;
		tempMap['C'] = TYPE_CATEGORY;
		tempMap['D'] = TYPE_DISAMBIGUATION;
		tempMap['E'] = TYPE_EXCLUSIVE;
		tempMap['N'] = TYPE_NAME;

		return tempMap;
	}

	map<char,int> ZeroClickInfo::resultTypeMapping(ZeroClickInfo::fillResultTypeMap());
}

