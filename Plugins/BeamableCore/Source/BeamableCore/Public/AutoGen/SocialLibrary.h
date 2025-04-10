#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Social.h"

#include "SocialLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USocialLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="Social To JSON String")
	static FString SocialToJsonString(const USocial* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make Social", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USocial* Make(FBeamGamerTag PlayerId, TArray<UFriend*> Friends, TArray<UPlayerId*> Blocked, TArray<UInvite*> Invites, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break Social", meta=(NativeBreakFunc))
	static void Break(const USocial* Serializable, FBeamGamerTag& PlayerId, TArray<UFriend*>& Friends, TArray<UPlayerId*>& Blocked, TArray<UInvite*>& Invites);
};