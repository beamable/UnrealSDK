#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/IsoChronology.h"

#include "IsoChronologyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UIsoChronologyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - IsoChronology To JSON String")
	static FString IsoChronologyToJsonString(const UIsoChronology* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make IsoChronology", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UIsoChronology* Make(FString CalendarType, FString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break IsoChronology", meta=(NativeBreakFunc))
	static void Break(const UIsoChronology* Serializable, FString& CalendarType, FString& Id);
};