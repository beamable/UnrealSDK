#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiResponse.h"

#include "AttachExternalIdentityApiResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAttachExternalIdentityApiResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AttachExternalIdentityApiResponse To JSON String")
	static FString AttachExternalIdentityApiResponseToJsonString(const UAttachExternalIdentityApiResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AttachExternalIdentityApiResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="ChallengeToken, Outer", NativeMakeFunc))
	static UAttachExternalIdentityApiResponse* Make(FString Result, FOptionalString ChallengeToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AttachExternalIdentityApiResponse", meta=(NativeBreakFunc))
	static void Break(const UAttachExternalIdentityApiResponse* Serializable, FString& Result, FOptionalString& ChallengeToken);
};