
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/GetManifestResponse.h"

#include "BasicBeamoGetManifestRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoGetManifestRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicBeamoGetManifestRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoGetManifest",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bArchived,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoGetManifestRequest* Make(FString _Id, FOptionalBool _bArchived, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetManifestSuccess, FBeamRequestContext, Context, UBasicBeamoGetManifestRequest*, Request, UGetManifestResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoGetManifestError, FBeamRequestContext, Context, UBasicBeamoGetManifestRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoGetManifestComplete, FBeamRequestContext, Context, UBasicBeamoGetManifestRequest*, Request);

using FBasicBeamoGetManifestFullResponse = FBeamFullResponse<UBasicBeamoGetManifestRequest*, UGetManifestResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoGetManifestFullResponse, FBasicBeamoGetManifestFullResponse);
