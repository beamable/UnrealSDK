
#include "BeamableCore/Public/AutoGen/ObjectsMetadataResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UObjectsMetadataResponseLibrary::ObjectsMetadataResponseToJsonString(const UObjectsMetadataResponse* Serializable, const bool Pretty)
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

UObjectsMetadataResponse* UObjectsMetadataResponseLibrary::Make(TArray<UObjectMetadataResponse*> Response, UObject* Outer)
{
	auto Serializable = NewObject<UObjectsMetadataResponse>(Outer);
	Serializable->Response = Response;
	
	return Serializable;
}

void UObjectsMetadataResponseLibrary::Break(const UObjectsMetadataResponse* Serializable, TArray<UObjectMetadataResponse*>& Response)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Response = Serializable->Response;
	}
		
}

