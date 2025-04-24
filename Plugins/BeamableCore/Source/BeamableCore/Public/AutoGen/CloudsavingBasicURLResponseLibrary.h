#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicURLResponse.h"

#include "CloudsavingBasicURLResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCloudsavingBasicURLResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="CloudsavingBasicURLResponse To JSON String")
	static FString CloudsavingBasicURLResponseToJsonString(const UCloudsavingBasicURLResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make CloudsavingBasicURLResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCloudsavingBasicURLResponse* Make(FString Url, FString ObjectKey, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break CloudsavingBasicURLResponse", meta=(NativeBreakFunc))
	static void Break(const UCloudsavingBasicURLResponse* Serializable, FString& Url, FString& ObjectKey);
};