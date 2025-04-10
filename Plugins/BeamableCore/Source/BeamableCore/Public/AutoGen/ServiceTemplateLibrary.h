#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceTemplate.h"

#include "ServiceTemplateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceTemplateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceTemplate To JSON String")
	static FString ServiceTemplateToJsonString(const UServiceTemplate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceTemplate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceTemplate* Make(FString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceTemplate", meta=(NativeBreakFunc))
	static void Break(const UServiceTemplate* Serializable, FString& Id);
};