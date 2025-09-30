#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "EmptyMessageLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmptyMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="EmptyMessage To JSON String")
	static FString EmptyMessageToJsonString(const UEmptyMessage* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make EmptyMessage", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEmptyMessage* Make(UObject* Outer);

	
};