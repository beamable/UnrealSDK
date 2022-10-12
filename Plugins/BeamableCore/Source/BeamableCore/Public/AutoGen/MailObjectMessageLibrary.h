
#pragma once

#include "CoreMinimal.h"
#include "MailObjectMessage.h"

#include "MailObjectMessageLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailObjectMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailObjectMessage To JSON String")
	static FString MailObjectMessageToJsonString(const UMailObjectMessage* Serializable, const bool Pretty);		
};