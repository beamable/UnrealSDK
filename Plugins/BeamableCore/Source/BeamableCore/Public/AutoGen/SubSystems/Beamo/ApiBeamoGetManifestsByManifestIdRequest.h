
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#include "ApiBeamoGetManifestsByManifestIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiBeamoGetManifestsByManifestIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Id", Category="Beam")
	FGuid ManifestId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiBeamoGetManifestsByManifestIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoGetManifestsByManifestId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bArchived,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiBeamoGetManifestsByManifestIdRequest* Make(FGuid _ManifestId, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetManifestsByManifestIdSuccess, FBeamRequestContext, Context, UApiBeamoGetManifestsByManifestIdRequest*, Request, UBeamoV2Manifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiBeamoGetManifestsByManifestIdError, FBeamRequestContext, Context, UApiBeamoGetManifestsByManifestIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiBeamoGetManifestsByManifestIdComplete, FBeamRequestContext, Context, UApiBeamoGetManifestsByManifestIdRequest*, Request);

using FApiBeamoGetManifestsByManifestIdFullResponse = FBeamFullResponse<UApiBeamoGetManifestsByManifestIdRequest*, UBeamoV2Manifest*>;
DECLARE_DELEGATE_OneParam(FOnApiBeamoGetManifestsByManifestIdFullResponse, FApiBeamoGetManifestsByManifestIdFullResponse);
