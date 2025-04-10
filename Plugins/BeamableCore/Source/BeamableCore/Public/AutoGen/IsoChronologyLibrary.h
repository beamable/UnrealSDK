#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/IsoChronology.h"

#include "IsoChronologyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UIsoChronologyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|4 - Json", DisplayName="IsoChronology To JSON String")
	static FString IsoChronologyToJsonString(const UIsoChronology* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|3 - Backend", DisplayName="Make IsoChronology", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UIsoChronology* Make(FString CalendarType, FString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|3 - Backend", DisplayName="Break IsoChronology", meta=(NativeBreakFunc))
	static void Break(const UIsoChronology* Serializable, FString& CalendarType, FString& Id);
};