#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Item.h"

#include "ItemLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="Item To JSON String")
	static FString ItemToJsonString(const UItem* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make Item", meta=(DefaultToSelf="Outer", AdvancedDisplay="UpdatedAt, ProxyId, Proxy, CreatedAt, Outer", NativeMakeFunc))
	static UItem* Make(int64 Id, TArray<UItemProperty*> Properties, FOptionalInt64 UpdatedAt, FOptionalString ProxyId, FOptionalFederationInfo Proxy, FOptionalInt64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break Item", meta=(NativeBreakFunc))
	static void Break(const UItem* Serializable, int64& Id, TArray<UItemProperty*>& Properties, FOptionalInt64& UpdatedAt, FOptionalString& ProxyId, FOptionalFederationInfo& Proxy, FOptionalInt64& CreatedAt);
};