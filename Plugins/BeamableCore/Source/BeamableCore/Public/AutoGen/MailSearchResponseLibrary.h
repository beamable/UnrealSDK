
#pragma once

#include "CoreMinimal.h"
#include "MailSearchResponse.h"

#include "MailSearchResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailSearchResponse To JSON String")
	static FString MailSearchResponseToJsonString(const UMailSearchResponse* Serializable, const bool Pretty);		
};