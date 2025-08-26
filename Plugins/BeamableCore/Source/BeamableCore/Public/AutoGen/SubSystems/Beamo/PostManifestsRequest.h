
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeamoV2PostManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ManifestChecksum.h"

#include "PostManifestsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeamoV2PostManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostManifestsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostManifests",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bAutoDeploy,_Comments,_Manifest,_StorageReferences,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostManifestsRequest* Make(FOptionalBool _bAutoDeploy, FOptionalString _Comments, FOptionalArrayOfBeamoV2ServiceReference _Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference _StorageReferences, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsSuccess, FBeamRequestContext, Context, UPostManifestsRequest*, Request, UBeamoV2ManifestChecksum*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsError, FBeamRequestContext, Context, UPostManifestsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestsComplete, FBeamRequestContext, Context, UPostManifestsRequest*, Request);

using FPostManifestsFullResponse = FBeamFullResponse<UPostManifestsRequest*, UBeamoV2ManifestChecksum*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestsFullResponse, FPostManifestsFullResponse);
