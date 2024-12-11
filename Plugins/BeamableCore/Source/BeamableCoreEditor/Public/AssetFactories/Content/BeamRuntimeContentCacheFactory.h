#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Factories/Factory.h"

#include "BeamRuntimeContentCacheFactory.generated.h"

class FBeamRuntimeContentCacheAssetTypeActions : public FAssetTypeActions_Base
{
public:
	virtual UClass* GetSupportedClass() const override { return UBeamContentCache::StaticClass(); }
	virtual FText GetName() const override { return INVTEXT("Cooked Content Manifest"); }
	virtual FColor GetTypeColor() const override { return FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF")).ToFColor(true); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};

/**
 * 
 */
UCLASS()
class BEAMABLECOREEDITOR_API UBeamRuntimeContentCacheFactory : public UFactory
{
	GENERATED_BODY()

public:
	UBeamRuntimeContentCacheFactory()
	{
		SupportedClass = UBeamContentCache::StaticClass();
		bCreateNew = true;
	}

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UBeamContentCache>(InParent, Class, Name, Flags, Context);
	}
};
