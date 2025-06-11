#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailSearchRequestBody.h"

#include "MailSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailSearchRequestBody To JSON String")
	static FString MailSearchRequestBodyToJsonString(const UMailSearchRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailSearchRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailSearchRequestBody* Make(TArray<UMailSearchClause*> Clauses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailSearchRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMailSearchRequestBody* Serializable, TArray<UMailSearchClause*>& Clauses);
};