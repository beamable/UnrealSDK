#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceTemplateView.h"

#include "ServiceTemplateViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceTemplateViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceTemplateView To JSON String")
	static FString ServiceTemplateViewToJsonString(const UServiceTemplateView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceTemplateView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Outer", NativeMakeFunc))
	static UServiceTemplateView* Make(FOptionalString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceTemplateView", meta=(NativeBreakFunc))
	static void Break(const UServiceTemplateView* Serializable, FOptionalString& Id);
};