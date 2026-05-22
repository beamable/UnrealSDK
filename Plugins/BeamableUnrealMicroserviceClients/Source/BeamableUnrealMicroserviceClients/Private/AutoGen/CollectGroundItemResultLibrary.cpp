
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectGroundItemResultLibrary::CollectGroundItemResultToJsonString(const UCollectGroundItemResult* Serializable, const bool Pretty)
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

UCollectGroundItemResult* UCollectGroundItemResultLibrary::Make(FString GrantedContentId, int32 GrantedQuantity, FString Message, bool bSuccess, UObject* Outer)
{
	auto Serializable = NewObject<UCollectGroundItemResult>(Outer);
	Serializable->GrantedContentId = GrantedContentId;
	Serializable->GrantedQuantity = GrantedQuantity;
	Serializable->Message = Message;
	Serializable->bSuccess = bSuccess;
	
	return Serializable;
}

void UCollectGroundItemResultLibrary::Break(const UCollectGroundItemResult* Serializable, FString& GrantedContentId, int32& GrantedQuantity, FString& Message, bool& bSuccess)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GrantedContentId = Serializable->GrantedContentId;
		GrantedQuantity = Serializable->GrantedQuantity;
		Message = Serializable->Message;
		bSuccess = Serializable->bSuccess;
	}
		
}

