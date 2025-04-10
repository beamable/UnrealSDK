#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SearchAccountsRequestBody.h"

#include "SearchAccountsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USearchAccountsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="SearchAccountsRequestBody To JSON String")
	static FString SearchAccountsRequestBodyToJsonString(const USearchAccountsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make SearchAccountsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USearchAccountsRequestBody* Make(FString Query, int32 Page, int32 Pagesize, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break SearchAccountsRequestBody", meta=(NativeBreakFunc))
	static void Break(const USearchAccountsRequestBody* Serializable, FString& Query, int32& Page, int32& Pagesize);
};