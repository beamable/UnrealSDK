
#include "BeamableCore/Public/AutoGen/CommitImageRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCommitImageRequestBodyLibrary::CommitImageRequestBodyToJsonString(const UCommitImageRequestBody* Serializable, const bool Pretty)
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

UCommitImageRequestBody* UCommitImageRequestBodyLibrary::Make(UBeamoBasicReference* Service, UObject* Outer)
{
	auto Serializable = NewObject<UCommitImageRequestBody>(Outer);
	Serializable->Service = Service;
	
	return Serializable;
}

void UCommitImageRequestBodyLibrary::Break(const UCommitImageRequestBody* Serializable, UBeamoBasicReference*& Service)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
	}
		
}

