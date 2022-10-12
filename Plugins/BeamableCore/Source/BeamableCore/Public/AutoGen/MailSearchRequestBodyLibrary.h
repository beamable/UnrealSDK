
#pragma once

#include "CoreMinimal.h"
#include "MailSearchRequestBody.h"

#include "MailSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailSearchRequestBody To JSON String")
	static FString MailSearchRequestBodyToJsonString(const UMailSearchRequestBody* Serializable, const bool Pretty);		
};