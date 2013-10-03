#ifndef __JSONVALUE_H__
#define __JSONVALUE_H__

#include <string>
#include "rapidjson/document.h"

const bool USE_HUMAN_READABLE_FLOATS = false;

class JsonValue
{
private:	// fields
	const rapidjson::Value* m_value;

private:	// methods
	float hexToFloat(const char* str) const;

public:		// methods
	explicit JsonValue(const rapidjson::Value& value);
	virtual ~JsonValue();

	const rapidjson::Value& operator()() const { return rapidjsonValue(); }
	const rapidjson::Value& rapidjsonValue() const { return *m_value; }

	JsonValue get(const char* member) const;

	template<typename T> T getAs(const T& defaultValue) const;

	template<typename T> T get(const char* member, const T& defaultValue) const
	{
		JsonValue value((*m_value)[member]);

		return value.getAs<T>(defaultValue);
	}


};

#endif // __JSONHELPER_H__
