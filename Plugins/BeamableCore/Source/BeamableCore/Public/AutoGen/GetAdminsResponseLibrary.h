
#pragma once

#include "CoreMinimal.h"
#include "GetAdminsResponse.h"

#include "GetAdminsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAdminsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetAdminsResponse To JSON String")
	static FString GetAdminsResponseToJsonString(const UGetAdminsResponse* Serializable, const bool Pretty);		
};