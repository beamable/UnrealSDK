
#pragma once

#include "CoreMinimal.h"
#include "MailSearchClause.h"

#include "MailSearchClauseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailSearchClauseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailSearchClause To JSON String")
	static FString MailSearchClauseToJsonString(const UMailSearchClause* Serializable, const bool Pretty);		
};