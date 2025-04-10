
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PostManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/PostManifestResponse.h"

#include "BasicBeamoPostManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoPostManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPostManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicBeamoPostManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoPostManifest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAutoDeploy,_Comments,_StorageReferences,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoPostManifestRequest* Make(TArray<UServiceReference*> _Manifest, FOptionalBool _bAutoDeploy, FOptionalString _Comments, FOptionalArrayOfServiceStorageReference _StorageReferences, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoPostManifestSuccess, FBeamRequestContext, Context, UBasicBeamoPostManifestRequest*, Request, UPostManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoPostManifestError, FBeamRequestContext, Context, UBasicBeamoPostManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoPostManifestComplete, FBeamRequestContext, Context, UBasicBeamoPostManifestRequest*, Request);

using FBasicBeamoPostManifestFullResponse = FBeamFullResponse<UBasicBeamoPostManifestRequest*, UPostManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoPostManifestFullResponse, FBasicBeamoPostManifestFullResponse);
