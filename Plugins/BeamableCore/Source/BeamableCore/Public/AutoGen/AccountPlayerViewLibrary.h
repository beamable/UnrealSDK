#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "AccountPlayerViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountPlayerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AccountPlayerView To JSON String")
	static FString AccountPlayerViewToJsonString(const UAccountPlayerView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AccountPlayerView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, Language, External, Outer", NativeMakeFunc))
	static UAccountPlayerView* Make(FBeamGamerTag Id, TArray<FString> DeviceIds, TArray<FString> Scopes, TArray<FString> ThirdPartyAppAssociations, FOptionalString Email, FOptionalString Language, FOptionalArrayOfBeamExternalIdentity External, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AccountPlayerView", meta=(NativeBreakFunc))
	static void Break(const UAccountPlayerView* Serializable, FBeamGamerTag& Id, TArray<FString>& DeviceIds, TArray<FString>& Scopes, TArray<FString>& ThirdPartyAppAssociations, FOptionalString& Email, FOptionalString& Language, FOptionalArrayOfBeamExternalIdentity& External);
};