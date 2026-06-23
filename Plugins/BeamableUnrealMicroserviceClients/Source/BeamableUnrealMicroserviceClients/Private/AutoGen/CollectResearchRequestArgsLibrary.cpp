
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectResearchRequestArgsLibrary::CollectResearchRequestArgsToJsonString(const UCollectResearchRequestArgs* Serializable, const bool Pretty)
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

UCollectResearchRequestArgs* UCollectResearchRequestArgsLibrary::Make(int64 ItemInstanceId, FString ItemContentId, UObject* Outer)
{
	auto Serializable = NewObject<UCollectResearchRequestArgs>(Outer);
	Serializable->ItemInstanceId = ItemInstanceId;
	Serializable->ItemContentId = ItemContentId;
	
	return Serializable;
}

void UCollectResearchRequestArgsLibrary::Break(const UCollectResearchRequestArgs* Serializable, int64& ItemInstanceId, FString& ItemContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ItemInstanceId = Serializable->ItemInstanceId;
		ItemContentId = Serializable->ItemContentId;
	}
		
}

