
#pragma once

#include "CoreMinimal.h"
#include "ConnectionString.h"

#include "ConnectionStringLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UConnectionStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ConnectionString To JSON String")
	static FString ConnectionStringToJsonString(const UConnectionString* Serializable, const bool Pretty);		
};