
#include "BeamableCore/Public/AutoGen/OfferRequirementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOfferRequirementLibrary::OfferRequirementToJsonString(const UOfferRequirement* Serializable, const bool Pretty)
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

UOfferRequirement* UOfferRequirementLibrary::Make(FString OfferSymbol, UOfferConstraint* Purchases, UObject* Outer)
{
	auto Serializable = NewObject<UOfferRequirement>(Outer);
	Serializable->OfferSymbol = OfferSymbol;
	Serializable->Purchases = Purchases;
	
	return Serializable;
}

void UOfferRequirementLibrary::Break(const UOfferRequirement* Serializable, FString& OfferSymbol, UOfferConstraint*& Purchases)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OfferSymbol = Serializable->OfferSymbol;
		Purchases = Serializable->Purchases;
	}
		
}

