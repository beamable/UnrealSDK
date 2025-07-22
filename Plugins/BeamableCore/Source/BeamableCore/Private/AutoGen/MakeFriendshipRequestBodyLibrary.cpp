
#include "BeamableCore/Public/AutoGen/MakeFriendshipRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMakeFriendshipRequestBodyLibrary::MakeFriendshipRequestBodyToJsonString(const UMakeFriendshipRequestBody* Serializable, const bool Pretty)
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

UMakeFriendshipRequestBody* UMakeFriendshipRequestBodyLibrary::Make(FBeamGamerTag GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UMakeFriendshipRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UMakeFriendshipRequestBodyLibrary::Break(const UMakeFriendshipRequestBody* Serializable, FBeamGamerTag& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
	}
		
}

