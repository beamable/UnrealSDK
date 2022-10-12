
#pragma once

#include "CoreMinimal.h"
#include "AdminGetPlayerStatusResponse.h"

#include "AdminGetPlayerStatusResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAdminGetPlayerStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AdminGetPlayerStatusResponse To JSON String")
	static FString AdminGetPlayerStatusResponseToJsonString(const UAdminGetPlayerStatusResponse* Serializable, const bool Pretty);		
};