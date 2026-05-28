
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStartResearchRequestArgsLibrary::StartResearchRequestArgsToJsonString(const UStartResearchRequestArgs* Serializable, const bool Pretty)
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

UStartResearchRequestArgs* UStartResearchRequestArgsLibrary::Make(int64 ItemInstanceId, FString ItemContentId, UObject* Outer)
{
	auto Serializable = NewObject<UStartResearchRequestArgs>(Outer);
	Serializable->ItemInstanceId = ItemInstanceId;
	Serializable->ItemContentId = ItemContentId;
	
	return Serializable;
}

void UStartResearchRequestArgsLibrary::Break(const UStartResearchRequestArgs* Serializable, int64& ItemInstanceId, FString& ItemContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ItemInstanceId = Serializable->ItemInstanceId;
		ItemContentId = Serializable->ItemContentId;
	}
		
}

