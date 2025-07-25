
#include "BeamableCore/Public/AutoGen/SendFriendRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendFriendRequestBodyLibrary::SendFriendRequestBodyToJsonString(const USendFriendRequestBody* Serializable, const bool Pretty)
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

USendFriendRequestBody* USendFriendRequestBodyLibrary::Make(FBeamGamerTag GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<USendFriendRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void USendFriendRequestBodyLibrary::Break(const USendFriendRequestBody* Serializable, FBeamGamerTag& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
	}
		
}

