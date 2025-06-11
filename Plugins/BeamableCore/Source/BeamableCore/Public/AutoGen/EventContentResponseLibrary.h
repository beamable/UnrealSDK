#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventContentResponse.h"

#include "EventContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventContentResponse To JSON String")
	static FString EventContentResponseToJsonString(const UEventContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventContentResponse* Make(TArray<UEvent*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventContentResponse", meta=(NativeBreakFunc))
	static void Break(const UEventContentResponse* Serializable, TArray<UEvent*>& Content);
};