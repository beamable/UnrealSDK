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

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make InventoryFiltersDTO", meta=(DefaultToSelf="Outer", AdvancedDisplay="ContentTagFilter, CreatedAt, UpdatedAt, Properties, Outer", NativeMakeFunc))
	static UInventoryFiltersDTO* Make(FOptionalContentTagFilter ContentTagFilter, FOptionalTimeRange CreatedAt, FOptionalTimeRange UpdatedAt, FOptionalArrayOfPropertyFilterDTO Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break InventoryFiltersDTO", meta=(NativeBreakFunc))
	static void Break(const UInventoryFiltersDTO* Serializable, FOptionalContentTagFilter& ContentTagFilter, FOptionalTimeRange& CreatedAt, FOptionalTimeRange& UpdatedAt, FOptionalArrayOfPropertyFilterDTO& Properties);
};