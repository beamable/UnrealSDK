
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PullManifestRequestBody.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#include "BasicContentPostManifestPullRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicContentPostManifestPullRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPullManifestRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicContentPostManifestPullRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BasicContentPostManifestPull",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Id,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicContentPostManifestPullRequest* Make(FBeamPid _SourceRealmPid, FOptionalBeamContentManifestId _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentPostManifestPullSuccess, FBeamRequestContext, Context, UBasicContentPostManifestPullRequest*, Request, UContentBasicManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicContentPostManifestPullError, FBeamRequestContext, Context, UBasicContentPostManifestPullRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicContentPostManifestPullComplete, FBeamRequestContext, Context, UBasicContentPostManifestPullRequest*, Request);

using FBasicContentPostManifestPullFullResponse = FBeamFullResponse<UBasicContentPostManifestPullRequest*, UContentBasicManifest*>;
DECLARE_DELEGATE_OneParam(FOnBasicContentPostManifestPullFullResponse, FBasicContentPostManifestPullFullResponse);
