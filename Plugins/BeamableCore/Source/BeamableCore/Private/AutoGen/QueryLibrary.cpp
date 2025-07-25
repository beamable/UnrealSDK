
#include "BeamableCore/Public/AutoGen/QueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UQueryLibrary::QueryToJsonString(const UQuery* Serializable, const bool Pretty)
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

UQuery* UQueryLibrary::Make(FString QueryId, UObject* Outer)
{
	auto Serializable = NewObject<UQuery>(Outer);
	Serializable->QueryId = QueryId;
	
	return Serializable;
}

void UQueryLibrary::Break(const UQuery* Serializable, FString& QueryId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		QueryId = Serializable->QueryId;
	}
		
}

