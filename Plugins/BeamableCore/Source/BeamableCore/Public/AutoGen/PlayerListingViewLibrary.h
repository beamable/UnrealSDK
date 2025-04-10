#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerListingView.h"

#include "PlayerListingViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerListingViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="PlayerListingView To JSON String")
	static FString PlayerListingViewToJsonString(const UPlayerListingView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PlayerListingView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Cooldown, PurchasesRemain, SecondsRemain, Outer", NativeMakeFunc))
	static UPlayerListingView* Make(bool bActive, bool bQueryAfterPurchase, FString Symbol, int64 SecondsActive, UPlayerOfferView* Offer, TArray<UClientDataEntry*> ClientDataList, TMap<FString, FString> ClientData, FOptionalInt32 Cooldown, FOptionalInt32 PurchasesRemain, FOptionalInt64 SecondsRemain, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break PlayerListingView", meta=(NativeBreakFunc))
	static void Break(const UPlayerListingView* Serializable, bool& bActive, bool& bQueryAfterPurchase, FString& Symbol, int64& SecondsActive, UPlayerOfferView*& Offer, TArray<UClientDataEntry*>& ClientDataList, TMap<FString, FString>& ClientData, FOptionalInt32& Cooldown, FOptionalInt32& PurchasesRemain, FOptionalInt64& SecondsRemain);
};