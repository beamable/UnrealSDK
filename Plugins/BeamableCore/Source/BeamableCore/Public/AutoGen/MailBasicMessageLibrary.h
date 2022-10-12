
#pragma once

#include "CoreMinimal.h"
#include "MailBasicMessage.h"

#include "MailBasicMessageLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailBasicMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailBasicMessage To JSON String")
	static FString MailBasicMessageToJsonString(const UMailBasicMessage* Serializable, const bool Pretty);		
};