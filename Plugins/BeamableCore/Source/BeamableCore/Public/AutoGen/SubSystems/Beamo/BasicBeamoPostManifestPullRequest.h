
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PullBeamoManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#include "BasicBeamoPostManifestPullRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicBeamoPostManifestPullRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPullBeamoManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicBeamoPostManifestPullRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BasicBeamoPostManifestPull",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicBeamoPostManifestPullRequest* Make(FString _SourceRealmPid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoPostManifestPullSuccess, FBeamRequestContext, Context, UBasicBeamoPostManifestPullRequest*, Request, UManifestChecksums*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicBeamoPostManifestPullError, FBeamRequestContext, Context, UBasicBeamoPostManifestPullRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicBeamoPostManifestPullComplete, FBeamRequestContext, Context, UBasicBeamoPostManifestPullRequest*, Request);

using FBasicBeamoPostManifestPullFullResponse = FBeamFullResponse<UBasicBeamoPostManifestPullRequest*, UManifestChecksums*>;
DECLARE_DELEGATE_OneParam(FOnBasicBeamoPostManifestPullFullResponse, FBasicBeamoPostManifestPullFullResponse);
