#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Acknowledge.h"

#include "AcknowledgeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAcknowledgeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Acknowledge To JSON String")
	static FString AcknowledgeToJsonString(const UAcknowledge* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Acknowledge", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAcknowledge* Make(UObject* Outer);

	
};