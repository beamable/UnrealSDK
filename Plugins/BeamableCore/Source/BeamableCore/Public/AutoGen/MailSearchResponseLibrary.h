#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"

#include "MailSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailSearchResponse To JSON String")
	static FString MailSearchResponseToJsonString(const UMailSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailSearchResponse* Make(TArray<UMailSearchResponseClause*> Results, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UMailSearchResponse* Serializable, TArray<UMailSearchResponseClause*>& Results);
};