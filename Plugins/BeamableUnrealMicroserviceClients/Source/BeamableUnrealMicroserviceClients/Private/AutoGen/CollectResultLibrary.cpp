
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectResultLibrary::CollectResultToJsonString(const UCollectResult* Serializable, const bool Pretty)
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

UCollectResult* UCollectResultLibrary::Make(bool bSuccess, FString HarvestedItemContentId, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<UCollectResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->HarvestedItemContentId = HarvestedItemContentId;
	Serializable->Message = Message;
	
	return Serializable;
}

void UCollectResultLibrary::Break(const UCollectResult* Serializable, bool& bSuccess, FString& HarvestedItemContentId, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		HarvestedItemContentId = Serializable->HarvestedItemContentId;
		Message = Serializable->Message;
	}
		
}

