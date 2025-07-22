
#include "BeamableCore/Public/AutoGen/RealmPromotionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmPromotionLibrary::RealmPromotionToJsonString(const URealmPromotion* Serializable, const bool Pretty)
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

URealmPromotion* URealmPromotionLibrary::Make(FString Name, UPromotable* Source, UPromotable* Destination, UObject* Outer)
{
	auto Serializable = NewObject<URealmPromotion>(Outer);
	Serializable->Name = Name;
	Serializable->Source = Source;
	Serializable->Destination = Destination;
	
	return Serializable;
}

void URealmPromotionLibrary::Break(const URealmPromotion* Serializable, FString& Name, UPromotable*& Source, UPromotable*& Destination)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Source = Serializable->Source;
		Destination = Serializable->Destination;
	}
		
}

