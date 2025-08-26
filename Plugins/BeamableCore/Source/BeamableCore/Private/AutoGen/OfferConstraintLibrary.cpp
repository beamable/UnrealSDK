
#include "BeamableCore/Public/AutoGen/OfferConstraintLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOfferConstraintLibrary::OfferConstraintToJsonString(const UOfferConstraint* Serializable, const bool Pretty)
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

UOfferConstraint* UOfferConstraintLibrary::Make(FString Constraint, int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UOfferConstraint>(Outer);
	Serializable->Constraint = Constraint;
	Serializable->Value = Value;
	
	return Serializable;
}

void UOfferConstraintLibrary::Break(const UOfferConstraint* Serializable, FString& Constraint, int32& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Constraint = Serializable->Constraint;
		Value = Serializable->Value;
	}
		
}

