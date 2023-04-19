
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfDatabaseMeasurement.h"

FOptionalArrayOfDatabaseMeasurement::FOptionalArrayOfDatabaseMeasurement()
{
	Val = TArray<UDatabaseMeasurement*>();
	IsSet = false;
}

FOptionalArrayOfDatabaseMeasurement::FOptionalArrayOfDatabaseMeasurement(TArray<UDatabaseMeasurement*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfDatabaseMeasurement::GetAddr() const { return &Val; }

void FOptionalArrayOfDatabaseMeasurement::Set(const void* Data)
{
	Val = *((TArray<UDatabaseMeasurement*>*)Data);
	IsSet = true;
}