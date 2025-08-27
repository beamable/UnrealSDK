
#include "BeamableCore/Public/AutoGen/PromotionScopeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromotionScopeLibrary::PromotionScopeToJsonString(const UPromotionScope* Serializable, const bool Pretty)
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

UPromotionScope* UPromotionScopeLibrary::Make(FString Name, TArray<UPromotion*> Promotions, UObject* Outer)
{
	auto Serializable = NewObject<UPromotionScope>(Outer);
	Serializable->Name = Name;
	Serializable->Promotions = Promotions;
	
	return Serializable;
}

void UPromotionScopeLibrary::Break(const UPromotionScope* Serializable, FString& Name, TArray<UPromotion*>& Promotions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Promotions = Serializable->Promotions;
	}
		
}

