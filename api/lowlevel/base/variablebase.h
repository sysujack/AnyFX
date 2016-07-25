#pragma once
//------------------------------------------------------------------------------
/**
	Describes the base for a variable.
	
	(C) 2016 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "annotable.h"
#include <EASTL/string.h>
namespace AnyFX
{
struct VarblockBase;
struct SamplerBase;
struct VariableBase : public Annotable
{
public:
	/// constructor
	VariableBase();
	/// destructor
	virtual ~VariableBase();

	eastl::string name;
	eastl::string signature;
	eastl::string defaultValueString;

	int format;
	int access;

	SamplerBase* sampler;
	VarblockBase* parentBlock;
	bool isInVarblock;
	bool isSubroutine;
	bool isArray;
	VariableType type;
	int arraySize;	
	int byteSize;
	
	unsigned binding;
	unsigned set;

	bool bindless;
	bool hasDefaultValue;
	char* currentValue;

protected:
	friend class VariableLoader;

	/// callback for when program is done loading
	virtual void OnLoaded();

	/// sets up default value
	void SetupDefaultValue(const eastl::string& string);
};
} // namespace AnyFX