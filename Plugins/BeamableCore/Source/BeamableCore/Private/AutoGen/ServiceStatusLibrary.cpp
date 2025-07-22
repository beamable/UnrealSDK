
#include "BeamableCore/Public/AutoGen/ServiceStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UServiceStatus* UServiceStatusLibrary::Make(bool bIsCurrent, bool bRunning, FString ServiceName, FString ImageId, FOptionalArrayOfServiceDependencyReference ServiceDependencyReferences, UObject* Outer)
{
	auto Serializable = NewObject<UServiceStatus>(Outer);
	Serializable->bIsCurrent = bIsCurrent;
	Serializable->bRunning = bRunning;
	Serializable->ServiceName = ServiceName;
	Serializable->ImageId = ImageId;
	Serializable->ServiceDependencyReferences = ServiceDependencyReferences;
	
	return Serializable;
}

void UServiceStatusLibrary::Break(const UServiceStatus* Serializable, bool& bIsCurrent, bool& bRunning, FString& ServiceName, FString& ImageId, FOptionalArrayOfServiceDependencyReference& ServiceDependencyReferences)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsCurrent = Serializable->bIsCurrent;
		bRunning = Serializable->bRunning;
		ServiceName = Serializable->ServiceName;
		ImageId = Serializable->ImageId;
		ServiceDependencyReferences = Serializable->ServiceDependencyReferences;
	}
		
}

