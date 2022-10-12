
#pragma once

#include "CoreMinimal.h"
#include "URLSResponse.h"

#include "URLSResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UURLSResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize URLSResponse To JSON String")
	static FString URLSResponseToJsonString(const UURLSResponse* Serializable, const bool Pretty);		
};