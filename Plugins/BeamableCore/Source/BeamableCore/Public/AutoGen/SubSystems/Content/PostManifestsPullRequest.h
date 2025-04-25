
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PullAllManifestsRequestBody.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#include "PostManifestsPullRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestsPullRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPullAllManifestsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostManifestsPullRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PostManifestsPull",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostManifestsPullRequest* Make(FBeamPid _SourceRealmPid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsPullSuccess, FBeamRequestContext, Context, UPostManifestsPullRequest*, Request, UManifestChecksums*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestsPullError, FBeamRequestContext, Context, UPostManifestsPullRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestsPullComplete, FBeamRequestContext, Context, UPostManifestsPullRequest*, Request);

using FPostManifestsPullFullResponse = FBeamFullResponse<UPostManifestsPullRequest*, UManifestChecksums*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestsPullFullResponse, FPostManifestsPullFullResponse);
