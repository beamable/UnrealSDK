
#pragma once

#include "CoreMinimal.h"
#include "MailQueryResponse.h"

#include "MailQueryResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailQueryResponse To JSON String")
	static FString MailQueryResponseToJsonString(const UMailQueryResponse* Serializable, const bool Pretty);		
};