
#include "BeamableCore/Public/AutoGen/ServiceStatusLibrary.h"

#include "CoreMinimal.h"


FString UServiceStatusLibrary::ServiceStatusToJsonString(const UServiceStatus* Serializable, const bool Pretty)
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

UServiceStatus* UServiceStatusLibrary::Make(FOptionalBool bIsCurrent, FOptionalBool bRunning, FOptionalString ServiceName, FOptionalString ImageId, FOptionalArrayOfServiceDependencyReference ServiceDependencyReferences, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bRunning = bRunning;
	Serializable->ServiceName = ServiceName;
	Serializable->ImageId = ImageId;
	Serializable->ServiceDependencyReferences = ServiceDependencyReferences;
	
	return Serializable;
}

void UServiceStatusLibrary::Break(const UServiceStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bRunning, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalArrayOfServiceDependencyReference& ServiceDependencyReferences)
{
	bIsCurrent = Serializable->bIsCurrent;
	bRunning = Serializable->bRunning;
	ServiceName = Serializable->ServiceName;
	ImageId = Serializable->ImageId;
	ServiceDependencyReferences = Serializable->ServiceDependencyReferences;
		
}

