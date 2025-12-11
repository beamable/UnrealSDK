
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfTagList.h"

FOptionalMapOfTagList::FOptionalMapOfTagList()
{
	Val = TMap<FString, UTagList*>();
	IsSet = false;
}

FOptionalMapOfTagList::FOptionalMapOfTagList(TMap<FString, UTagList*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfTagList::GetAddr() const { return &Val; }

void FOptionalMapOfTagList::Set(const void* Data)
{
	Val = *((TMap<FString, UTagList*>*)Data);
	IsSet = true;
}