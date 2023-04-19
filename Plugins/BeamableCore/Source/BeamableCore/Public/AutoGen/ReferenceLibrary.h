
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Reference.h"

#include "ReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Reference To JSON String")
	static FString ReferenceToJsonString(const UReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Reference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UReference* Make(UObject* Outer);

	
};