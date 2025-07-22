
#include "BeamableCore/Public/AutoGen/GetStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetStatusResponseLibrary::GetStatusResponseToJsonString(const UGetStatusResponse* Serializable, const bool Pretty)
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

UGetStatusResponse* UGetStatusResponseLibrary::Make(bool bIsCurrent, TArray<UServiceStatus*> Services, FOptionalArrayOfServiceStorageStatus StorageStatuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetStatusResponse>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->Services = Services;
	Serializable->StorageStatuses = StorageStatuses;
	
	return Serializable;
}

void UGetStatusResponseLibrary::Break(const UGetStatusResponse* Serializable, bool& bIsCurrent, TArray<UServiceStatus*>& Services, FOptionalArrayOfServiceStorageStatus& StorageStatuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		Services = Serializable->Services;
		StorageStatuses = Serializable->StorageStatuses;
	}
		
}

