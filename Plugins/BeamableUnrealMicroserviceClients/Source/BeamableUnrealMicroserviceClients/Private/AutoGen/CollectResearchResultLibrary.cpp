
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectResearchResultLibrary::CollectResearchResultToJsonString(const UCollectResearchResult* Serializable, const bool Pretty)
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

UCollectResearchResult* UCollectResearchResultLibrary::Make(FString OutputContentId, int32 OutputQuantity, FString OutputType, FString Message, bool bSuccess, UObject* Outer)
{
	auto Serializable = NewObject<UCollectResearchResult>(Outer);
	Serializable->OutputContentId = OutputContentId;
	Serializable->OutputQuantity = OutputQuantity;
	Serializable->OutputType = OutputType;
	Serializable->Message = Message;
	Serializable->bSuccess = bSuccess;
	
	return Serializable;
}

void UCollectResearchResultLibrary::Break(const UCollectResearchResult* Serializable, FString& OutputContentId, int32& OutputQuantity, FString& OutputType, FString& Message, bool& bSuccess)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OutputContentId = Serializable->OutputContentId;
		OutputQuantity = Serializable->OutputQuantity;
		OutputType = Serializable->OutputType;
		Message = Serializable->Message;
		bSuccess = Serializable->bSuccess;
	}
		
}

