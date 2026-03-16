
#include "BeamableCore/Public/AutoGen/ApiSessionsStatusGetSessionResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiSessionsStatusGetSessionResponseLibrary::ApiSessionsStatusGetSessionResponseToJsonString(const UApiSessionsStatusGetSessionResponse* Serializable, const bool Pretty)
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

UApiSessionsStatusGetSessionResponse* UApiSessionsStatusGetSessionResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiSessionsStatusGetSessionResponse>(Outer);
	
	return Serializable;
}



