
#include "BeamableCore/Public/AutoGen/KickRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UKickRequestBodyLibrary::KickRequestBodyToJsonString(const UKickRequestBody* Serializable, const bool Pretty)
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

UKickRequestBody* UKickRequestBodyLibrary::Make(int64 GamerTag, FOptionalInt64 SubGroup, UObject* Outer)
{
	auto Serializable = NewObject<UKickRequestBody>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->SubGroup = SubGroup;
	
	return Serializable;
}

void UKickRequestBodyLibrary::Break(const UKickRequestBody* Serializable, int64& GamerTag, FOptionalInt64& SubGroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
		SubGroup = Serializable->SubGroup;
	}
		
}

