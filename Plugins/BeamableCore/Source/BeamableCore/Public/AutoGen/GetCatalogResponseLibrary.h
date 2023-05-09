#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetCatalogResponse.h"

#include "GetCatalogResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetCatalogResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetCatalogResponse To JSON String")
	static FString GetCatalogResponseToJsonString(const UGetCatalogResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetCatalogResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Catalog, Outer", NativeMakeFunc))
	static UGetCatalogResponse* Make(FOptionalCatalog Catalog, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetCatalogResponse", meta=(NativeBreakFunc))
	static void Break(const UGetCatalogResponse* Serializable, FOptionalCatalog& Catalog);
};