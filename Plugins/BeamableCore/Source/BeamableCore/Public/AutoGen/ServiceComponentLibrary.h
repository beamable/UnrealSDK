#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceComponent.h"

#include "ServiceComponentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceComponentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceComponent To JSON String")
	static FString ServiceComponentToJsonString(const UServiceComponent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceComponent", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceComponent* Make(FString Name, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceComponent", meta=(NativeBreakFunc))
	static void Break(const UServiceComponent* Serializable, FString& Name);
};