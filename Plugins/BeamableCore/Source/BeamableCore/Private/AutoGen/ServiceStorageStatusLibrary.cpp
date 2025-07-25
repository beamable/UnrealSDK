
#include "BeamableCore/Public/AutoGen/ServiceStorageStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UServiceStorageStatus* UServiceStorageStatusLibrary::Make(bool bIsCurrent, bool bIsRunning, FString Id, FString StorageType, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStorageStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bIsRunning = bIsRunning;
	Serializable->Id = Id;
	Serializable->StorageType = StorageType;
	
	return Serializable;
}

void UServiceStorageStatusLibrary::Break(const UServiceStorageStatus* Serializable, bool& bIsCurrent, bool& bIsRunning, FString& Id, FString& StorageType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		bIsRunning = Serializable->bIsRunning;
		Id = Serializable->Id;
		StorageType = Serializable->StorageType;
	}
		
}

