
#pragma once

#include "CoreMinimal.h"
#include "MailSuccessResponse.h"

#include "MailSuccessResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailSuccessResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailSuccessResponse To JSON String")
	static FString MailSuccessResponseToJsonString(const UMailSuccessResponse* Serializable, const bool Pretty);		
};