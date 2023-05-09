#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TransferThirdPartyAssociation.h"

#include "TransferThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTransferThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TransferThirdPartyAssociation To JSON String")
	static FString TransferThirdPartyAssociationToJsonString(const UTransferThirdPartyAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TransferThirdPartyAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTransferThirdPartyAssociation* Make(int64 FromAccountId, UThirdPartyAssociation* ThirdParty, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TransferThirdPartyAssociation", meta=(NativeBreakFunc))
	static void Break(const UTransferThirdPartyAssociation* Serializable, int64& FromAccountId, UThirdPartyAssociation*& ThirdParty);
};