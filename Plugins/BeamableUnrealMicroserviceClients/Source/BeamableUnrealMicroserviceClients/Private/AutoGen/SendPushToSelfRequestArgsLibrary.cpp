
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToSelfRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendPushToSelfRequestArgsLibrary::SendPushToSelfRequestArgsToJsonString(const USendPushToSelfRequestArgs* Serializable, const bool Pretty)
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

USendPushToSelfRequestArgs* USendPushToSelfRequestArgsLibrary::Make(FString Title, FString Body, FString DeepLink, UObject* Outer)
{
	auto Serializable = NewObject<USendPushToSelfRequestArgs>(Outer);
	Serializable->Title = Title;
	Serializable->Body = Body;
	Serializable->DeepLink = DeepLink;
	
	return Serializable;
}

void USendPushToSelfRequestArgsLibrary::Break(const USendPushToSelfRequestArgs* Serializable, FString& Title, FString& Body, FString& DeepLink)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Title = Serializable->Title;
		Body = Serializable->Body;
		DeepLink = Serializable->DeepLink;
	}
		
}

