#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponseClause.h"

#include "MailSearchResponseClauseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailSearchResponseClauseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailSearchResponseClause To JSON String")
	static FString MailSearchResponseClauseToJsonString(const UMailSearchResponseClause* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailSearchResponseClause", meta=(DefaultToSelf="Outer", AdvancedDisplay="Content, Outer", NativeMakeFunc))
	static UMailSearchResponseClause* Make(FString Name, int64 Count, FOptionalArrayOfMessage Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailSearchResponseClause", meta=(NativeBreakFunc))
	static void Break(const UMailSearchResponseClause* Serializable, FString& Name, int64& Count, FOptionalArrayOfMessage& Content);
};