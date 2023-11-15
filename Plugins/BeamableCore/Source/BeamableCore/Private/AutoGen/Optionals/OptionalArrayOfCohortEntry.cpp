
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCohortEntry.h"

FOptionalArrayOfCohortEntry::FOptionalArrayOfCohortEntry()
{
	Val = TArray<UCohortEntry*>();
	IsSet = false;
}

FOptionalArrayOfCohortEntry::FOptionalArrayOfCohortEntry(TArray<UCohortEntry*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCohortEntry::GetAddr() const { return &Val; }

void FOptionalArrayOfCohortEntry::Set(const void* Data)
{
	Val = *((TArray<UCohortEntry*>*)Data);
	IsSet = true;
}