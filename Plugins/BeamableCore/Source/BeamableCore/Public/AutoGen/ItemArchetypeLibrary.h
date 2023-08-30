#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ItemArchetype.h"

#include "ItemArchetypeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemArchetypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ItemArchetype To JSON String")
	static FString ItemArchetypeToJsonString(const UItemArchetype* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ItemArchetype", meta=(DefaultToSelf="Outer", AdvancedDisplay="External, ClientPermission, Outer", NativeMakeFunc))
	static UItemArchetype* Make(FString Symbol, FOptionalArchetypeProxy External, FOptionalBeamClientPermission ClientPermission, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ItemArchetype", meta=(NativeBreakFunc))
	static void Break(const UItemArchetype* Serializable, FString& Symbol, FOptionalArchetypeProxy& External, FOptionalBeamClientPermission& ClientPermission);
};