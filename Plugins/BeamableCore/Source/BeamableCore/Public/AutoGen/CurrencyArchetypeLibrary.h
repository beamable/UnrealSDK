#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyArchetype.h"

#include "CurrencyArchetypeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyArchetypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CurrencyArchetype To JSON String")
	static FString CurrencyArchetypeToJsonString(const UCurrencyArchetype* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CurrencyArchetype", meta=(DefaultToSelf="Outer", AdvancedDisplay="External, ClientPermission, StartingAmount, Outer", NativeMakeFunc))
	static UCurrencyArchetype* Make(FString Symbol, FOptionalArchetypeProxy External, FOptionalBeamClientPermission ClientPermission, FOptionalInt64 StartingAmount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CurrencyArchetype", meta=(NativeBreakFunc))
	static void Break(const UCurrencyArchetype* Serializable, FString& Symbol, FOptionalArchetypeProxy& External, FOptionalBeamClientPermission& ClientPermission, FOptionalInt64& StartingAmount);
};