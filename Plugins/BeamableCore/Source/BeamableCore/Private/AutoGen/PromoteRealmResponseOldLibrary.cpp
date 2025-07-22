
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOldLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromoteRealmResponseOldLibrary::PromoteRealmResponseOldToJsonString(const UPromoteRealmResponseOld* Serializable, const bool Pretty)
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

UPromoteRealmResponseOld* UPromoteRealmResponseOldLibrary::Make(FString SourcePid, TArray<URealmPromotion*> Promotions, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteRealmResponseOld>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Promotions = Promotions;
	
	return Serializable;
}

void UPromoteRealmResponseOldLibrary::Break(const UPromoteRealmResponseOld* Serializable, FString& SourcePid, TArray<URealmPromotion*>& Promotions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePid = Serializable->SourcePid;
		Promotions = Serializable->Promotions;
	}
		
}

