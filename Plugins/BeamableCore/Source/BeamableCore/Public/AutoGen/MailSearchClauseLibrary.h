#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailSearchClause.h"

#include "MailSearchClauseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailSearchClauseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailSearchClause To JSON String")
	static FString MailSearchClauseToJsonString(const UMailSearchClause* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailSearchClause", meta=(DefaultToSelf="Outer", AdvancedDisplay="ForSender, Start, Limit, Categories, States, Outer", NativeMakeFunc))
	static UMailSearchClause* Make(bool bOnlyCount, FString Name, FOptionalInt64 ForSender, FOptionalInt64 Start, FOptionalInt32 Limit, FOptionalArrayOfString Categories, FOptionalArrayOfString States, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailSearchClause", meta=(NativeBreakFunc))
	static void Break(const UMailSearchClause* Serializable, bool& bOnlyCount, FString& Name, FOptionalInt64& ForSender, FOptionalInt64& Start, FOptionalInt32& Limit, FOptionalArrayOfString& Categories, FOptionalArrayOfString& States);
};