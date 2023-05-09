#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AvailabilityRequestBody.h"

#include "AvailabilityRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAvailabilityRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AvailabilityRequestBody To JSON String")
	static FString AvailabilityRequestBodyToJsonString(const UAvailabilityRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AvailabilityRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bSubGroup, Name, Tag, Outer", NativeMakeFunc))
	static UAvailabilityRequestBody* Make(EGroupType Type, FOptionalBool bSubGroup, FOptionalString Name, FOptionalString Tag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AvailabilityRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAvailabilityRequestBody* Serializable, EGroupType& Type, FOptionalBool& bSubGroup, FOptionalString& Name, FOptionalString& Tag);
};