
#pragma once

#include "CoreMinimal.h"
#include "MailSearchResponseClause.h"

#include "MailSearchResponseClauseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailSearchResponseClauseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailSearchResponseClause To JSON String")
	static FString MailSearchResponseClauseToJsonString(const UMailSearchResponseClause* Serializable, const bool Pretty);		
};