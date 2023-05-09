#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Catalog.h"

#include "CatalogLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCatalogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Catalog To JSON String")
	static FString CatalogToJsonString(const UCatalog* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Catalog", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCatalog* Make(int64 Version, int64 Created, TArray<UStore*> Stores, TArray<UOfferDefinition*> OfferDefinitions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Catalog", meta=(NativeBreakFunc))
	static void Break(const UCatalog* Serializable, int64& Version, int64& Created, TArray<UStore*>& Stores, TArray<UOfferDefinition*>& OfferDefinitions);
};