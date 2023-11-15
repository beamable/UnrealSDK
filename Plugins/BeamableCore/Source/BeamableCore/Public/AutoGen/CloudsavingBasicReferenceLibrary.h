#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReference.h"

#include "CloudsavingBasicReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCloudsavingBasicReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CloudsavingBasicReference To JSON String")
	static FString CloudsavingBasicReferenceToJsonString(const UCloudsavingBasicReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CloudsavingBasicReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCloudsavingBasicReference* Make(UObject* Outer);

	
};