#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupApplication.h"

#include "GroupApplicationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupApplicationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Json", DisplayName="GroupApplication To JSON String")
	static FString GroupApplicationToJsonString(const UGroupApplication* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make GroupApplication", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static UGroupApplication* Make(FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Break GroupApplication", meta=(NativeBreakFunc))
	static void Break(const UGroupApplication* Serializable, FOptionalInt64& SubGroup);
};