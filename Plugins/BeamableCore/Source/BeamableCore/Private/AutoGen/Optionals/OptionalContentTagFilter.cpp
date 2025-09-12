
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContentTagFilter.h"

FOptionalContentTagFilter::FOptionalContentTagFilter()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalContentTagFilter::FOptionalContentTagFilter(UContentTagFilter* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalContentTagFilter::GetAddr() const { return &Val; }

void FOptionalContentTagFilter::Set(const void* Data)
{
	Val = *((UContentTagFilter**)Data);
	IsSet = true;
}