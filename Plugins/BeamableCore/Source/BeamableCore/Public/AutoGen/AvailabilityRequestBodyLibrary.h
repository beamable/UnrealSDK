#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AvailabilityRequestBody.h"

#include "AvailabilityRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAvailabilityRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="AvailabilityRequestBody To JSON String")
	static FString AvailabilityRequestBodyToJsonString(const UAvailabilityRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make AvailabilityRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bSubGroup, Name, Tag, Outer", NativeMakeFunc))
	static UAvailabilityRequestBody* Make(EBeamGroupType Type, FOptionalBool bSubGroup, FOptionalString Name, FOptionalString Tag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break AvailabilityRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAvailabilityRequestBody* Serializable, EBeamGroupType& Type, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalString& Tag);
};