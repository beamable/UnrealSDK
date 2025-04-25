#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Period.h"

#include "PeriodLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPeriodLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="Period To JSON String")
	static FString PeriodToJsonString(const UPeriod* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make Period", meta=(DefaultToSelf="Outer", AdvancedDisplay="End, Outer", NativeMakeFunc))
	static UPeriod* Make(FString Start, FOptionalString End, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break Period", meta=(NativeBreakFunc))
	static void Break(const UPeriod* Serializable, FString& Start, FOptionalString& End);
};