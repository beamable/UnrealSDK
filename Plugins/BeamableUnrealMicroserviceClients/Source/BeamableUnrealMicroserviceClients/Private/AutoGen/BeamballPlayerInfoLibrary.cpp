
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballPlayerInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamballPlayerInfoLibrary::BeamballPlayerInfoToJsonString(const UBeamballPlayerInfo* Serializable, const bool Pretty)
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

UBeamballPlayerInfo* UBeamballPlayerInfoLibrary::Make(FString GamerTag, int32 Life, UObject* Outer)
{
	auto Serializable = NewObject<UBeamballPlayerInfo>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->Life = Life;
	
	return Serializable;
}

void UBeamballPlayerInfoLibrary::Break(const UBeamballPlayerInfo* Serializable, FString& GamerTag, int32& Life)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
		Life = Serializable->Life;
	}
		
}

