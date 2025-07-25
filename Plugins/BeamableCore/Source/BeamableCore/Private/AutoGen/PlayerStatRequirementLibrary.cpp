
#include "BeamableCore/Public/AutoGen/PlayerStatRequirementLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerStatRequirementLibrary::PlayerStatRequirementToJsonString(const UPlayerStatRequirement* Serializable, const bool Pretty)
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

UPlayerStatRequirement* UPlayerStatRequirementLibrary::Make(FString Stat, FString Constraint, FString Value, FOptionalString Domain, FOptionalString Access, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerStatRequirement>(Outer);
	Serializable->Stat = Stat;
	Serializable->Constraint = Constraint;
	Serializable->Value = Value;
	Serializable->Domain = Domain;
	Serializable->Access = Access;
	
	return Serializable;
}

void UPlayerStatRequirementLibrary::Break(const UPlayerStatRequirement* Serializable, FString& Stat, FString& Constraint, FString& Value, FOptionalString& Domain, FOptionalString& Access)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Stat = Serializable->Stat;
		Constraint = Serializable->Constraint;
		Value = Serializable->Value;
		Domain = Serializable->Domain;
		Access = Serializable->Access;
	}
		
}

