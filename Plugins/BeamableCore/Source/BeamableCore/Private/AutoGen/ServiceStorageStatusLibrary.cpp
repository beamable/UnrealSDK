
#include "BeamableCore/Public/AutoGen/ServiceStorageStatusLibrary.h"

#include "CoreMinimal.h"


FString UServiceStorageStatusLibrary::ServiceStorageStatusToJsonString(const UServiceStorageStatus* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UServiceStorageStatus* UServiceStorageStatusLibrary::Make(FOptionalBool bIsCurrent, FOptionalBool bIsRunning, FOptionalString Id, FOptionalString StorageType, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStorageStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bIsRunning = bIsRunning;
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	
	return Serializable;
}

void UServiceStorageStatusLibrary::Break(const UServiceStorageStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bIsRunning, FOptionalString& Id, FOptionalString& StorageType)
{
	bIsCurrent = Serializable->bIsCurrent;
	bIsRunning = Serializable->bIsRunning;
	Id = Serializable->Id;
	StorageType = Serializable->StorageType;
		
}

