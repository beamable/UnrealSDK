#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InventoryFiltersDTO.h"

#include "InventoryFiltersDTOLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInventoryFiltersDTOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="InventoryFiltersDTO To JSON String")
	static FString InventoryFiltersDTOToJsonString(const UInventoryFiltersDTO* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryFiltersDTO", meta=(DefaultToSelf="Outer", AdvancedDisplay="UpdatedAt, CreatedAt, ContentTagFilter, ProxyIds, PropertyFilters, Outer", NativeMakeFunc))
	static UInventoryFiltersDTO* Make(FOptionalTimeRange UpdatedAt, FOptionalTimeRange CreatedAt, FOptionalContentTagFilter ContentTagFilter, FOptionalArrayOfString ProxyIds, FOptionalArrayOfPropertyFilterDTO PropertyFilters, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryFiltersDTO", meta=(NativeBreakFunc))
	static void Break(const UInventoryFiltersDTO* Serializable, FOptionalTimeRange& UpdatedAt, FOptionalTimeRange& CreatedAt, FOptionalContentTagFilter& ContentTagFilter, FOptionalArrayOfString& ProxyIds, FOptionalArrayOfPropertyFilterDTO& PropertyFilters);
};