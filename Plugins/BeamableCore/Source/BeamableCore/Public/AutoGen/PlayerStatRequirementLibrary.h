#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerStatRequirement.h"

#include "PlayerStatRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerStatRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="PlayerStatRequirement To JSON String")
	static FString PlayerStatRequirementToJsonString(const UPlayerStatRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make PlayerStatRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Domain, Access, Outer", NativeMakeFunc))
	static UPlayerStatRequirement* Make(FString Stat, FString Constraint, FString Value, FOptionalString Domain, FOptionalString Access, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break PlayerStatRequirement", meta=(NativeBreakFunc))
	static void Break(const UPlayerStatRequirement* Serializable, FString& Stat, FString& Constraint, FString& Value, FOptionalString& Domain, FOptionalString& Access);
};