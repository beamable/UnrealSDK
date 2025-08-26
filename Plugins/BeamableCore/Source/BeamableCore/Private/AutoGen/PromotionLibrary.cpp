
#include "BeamableCore/Public/AutoGen/PromotionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromotionLibrary::PromotionToJsonString(const UPromotion* Serializable, const bool Pretty)
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

UPromotion* UPromotionLibrary::Make(FString Id, UPromotable* Source, UPromotable* Destination, UObject* Outer)
{
	auto Serializable = NewObject<UPromotion>(Outer);
	Serializable->Id = Id;
	Serializable->Source = Source;
	Serializable->Destination = Destination;
	
	return Serializable;
}

void UPromotionLibrary::Break(const UPromotion* Serializable, FString& Id, UPromotable*& Source, UPromotable*& Destination)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Source = Serializable->Source;
		Destination = Serializable->Destination;
	}
		
}

