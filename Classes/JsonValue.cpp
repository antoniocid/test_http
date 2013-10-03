#include "JsonValue.h"
#include "cocos2d.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Private methods

float JsonValue::hexToFloat(const char* str) const
{
	int strLen = 8; //32 bit float
	unsigned char bytes[4];
	int bptr = (strLen / 2) - 1;

	for (int i = 0; i < strLen; i++){
		unsigned char   c;
		c = str[i];
		if (c > '9') c -= 7;
		c <<= 4;
		bytes[bptr] = c;

		++i;
		c = str[i];
		if (c > '9') c -= 7;
		c -= '0';
		bytes[bptr] |= c;

		--bptr;
	}

	//return *((float*)bytes); dereferencing type-punned pointer will break strict-aliasing rules
	float* f = (float*)bytes;
	return *f;
}


////////////////////////////////////////////////////////////////////////////////
// Public methods

JsonValue::JsonValue(const rapidjson::Value& value) : m_value(&value) { }
JsonValue::~JsonValue() { }

JsonValue JsonValue::get(const char* member) const
{
	return JsonValue((*m_value)[member]);
}

template<> int JsonValue::getAs<int>(const int& defaultValue) const
{
	if (m_value->IsInt())
		return m_value->GetInt();

	return defaultValue;
}

template<> bool JsonValue::getAs<bool>(const bool& defaultValue) const
{
	if (m_value->IsBool())
		return m_value->GetBool();

	return defaultValue;
}

template<> double JsonValue::getAs<double>(const double& defaultValue) const
{
	if (m_value->IsDouble())
	{
		return m_value->GetDouble();
	}
	else if (!USE_HUMAN_READABLE_FLOATS && m_value->IsString())
	{
		return hexToFloat(m_value->GetString());
	}

	return defaultValue;
}

template<> float JsonValue::getAs<float>(const float& defaultValue) const
{
	return (float)getAs<double>(defaultValue);
}

template<> string JsonValue::getAs<string>(const string& defaultValue) const
{
	if (m_value->IsString())
		return m_value->GetString();

	return defaultValue;
}


