#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseView.h"

#include "EventPlayerPhaseViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPlayerPhaseViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventPlayerPhaseView To JSON String")
	static FString EventPlayerPhaseViewToJsonString(const UEventPlayerPhaseView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventPlayerPhaseView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventPlayerPhaseView* Make(FString Name, int64 DurationSeconds, TArray<UEventRule*> Rules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventPlayerPhaseView", meta=(NativeBreakFunc))
	static void Break(const UEventPlayerPhaseView* Serializable, FString& Name, int64& DurationSeconds, TArray<UEventRule*>& Rules);
};