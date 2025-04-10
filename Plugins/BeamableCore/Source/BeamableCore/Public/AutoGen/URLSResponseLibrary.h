#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#include "URLSResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UURLSResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|4 - Json", DisplayName="URLSResponse To JSON String")
	static FString URLSResponseToJsonString(const UURLSResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|3 - Backend", DisplayName="Make URLSResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UURLSResponse* Make(TArray<UCloudsavingBasicURLResponse*> Response, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|3 - Backend", DisplayName="Break URLSResponse", meta=(NativeBreakFunc))
	static void Break(const UURLSResponse* Serializable, TArray<UCloudsavingBasicURLResponse*>& Response);
};