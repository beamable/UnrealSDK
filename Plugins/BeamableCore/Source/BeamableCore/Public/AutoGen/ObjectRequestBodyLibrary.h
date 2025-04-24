#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ObjectRequestBody.h"

#include "ObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="ObjectRequestBody To JSON String")
	static FString ObjectRequestBodyToJsonString(const UObjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make ObjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UObjectRequestBody* Make(FString ObjectKey, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break ObjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const UObjectRequestBody* Serializable, FString& ObjectKey);
};