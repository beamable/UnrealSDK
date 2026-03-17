#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthCode.h"

#include "AuthV2AuthCodeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2AuthCodeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2AuthCode To JSON String")
	static FString AuthV2AuthCodeToJsonString(const UAuthV2AuthCode* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2AuthCode", meta=(DefaultToSelf="Outer", AdvancedDisplay="CreatedAt, Ttl, Scopes, Outer", NativeMakeFunc))
	static UAuthV2AuthCode* Make(FString Code, int64 AccountId, FString RedirectUri, FOptionalDateTime CreatedAt, FOptionalDateTime Ttl, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2AuthCode", meta=(NativeBreakFunc))
	static void Break(const UAuthV2AuthCode* Serializable, FString& Code, int64& AccountId, FString& RedirectUri, FOptionalDateTime& CreatedAt, FOptionalDateTime& Ttl, FOptionalArrayOfString& Scopes);
};