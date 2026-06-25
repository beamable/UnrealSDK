
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToPlayerRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendPushToPlayerRequestArgsLibrary::SendPushToPlayerRequestArgsToJsonString(const USendPushToPlayerRequestArgs* Serializable, const bool Pretty)
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

USendPushToPlayerRequestArgs* USendPushToPlayerRequestArgsLibrary::Make(int64 PlayerId, FString Title, FString Body, FString DeepLink, UObject* Outer)
{
	auto Serializable = NewObject<USendPushToPlayerRequestArgs>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Title = Title;
	Serializable->Body = Body;
	Serializable->DeepLink = DeepLink;
	
	return Serializable;
}

void USendPushToPlayerRequestArgsLibrary::Break(const USendPushToPlayerRequestArgs* Serializable, int64& PlayerId, FString& Title, FString& Body, FString& DeepLink)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Title = Serializable->Title;
		Body = Serializable->Body;
		DeepLink = Serializable->DeepLink;
	}
		
}

