
#include "BeamableCore/Public/AutoGen/GetStatusResponseLibrary.h"

#include "CoreMinimal.h"


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

UGetStatusResponse* UGetStatusResponseLibrary::Make(FOptionalBool bIsCurrent, FOptionalArrayOfServiceStatus Services, FOptionalArrayOfServiceStorageStatus StorageStatuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetStatusResponse>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->Services = Services;
	Serializable->StorageStatuses = StorageStatuses;
	
	return Serializable;
}

void UGetStatusResponseLibrary::Break(const UGetStatusResponse* Serializable, FOptionalBool& bIsCurrent, FOptionalArrayOfServiceStatus& Services, FOptionalArrayOfServiceStorageStatus& StorageStatuses)
{
	bIsCurrent = Serializable->bIsCurrent;
	Services = Serializable->Services;
	StorageStatuses = Serializable->StorageStatuses;
		
}

