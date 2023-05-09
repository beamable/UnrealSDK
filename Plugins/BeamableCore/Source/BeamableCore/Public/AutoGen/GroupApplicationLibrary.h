#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupApplication.h"

#include "GroupApplicationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupApplicationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GroupApplication To JSON String")
	static FString GroupApplicationToJsonString(const UGroupApplication* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GroupApplication", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static UGroupApplication* Make(FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GroupApplication", meta=(NativeBreakFunc))
	static void Break(const UGroupApplication* Serializable, FOptionalInt64& SubGroup);
};