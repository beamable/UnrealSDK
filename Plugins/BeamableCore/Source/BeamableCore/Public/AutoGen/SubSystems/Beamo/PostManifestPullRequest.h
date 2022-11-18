
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/PullBeamoManifestRequestBody.h"
#include "AutoGen/ManifestChecksums.h"

#include "PostManifestPullRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestPullRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPullBeamoManifestRequestBody* Body;

	// Beam Base Request Declaration
	UPostManifestPullRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Beamo", DisplayName="Beam - Make PostManifestPull",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UPostManifestPullRequest* Make(FString _SourceRealmPid, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestPullSuccess, FBeamRequestContext, Context, UPostManifestPullRequest*, Request, UManifestChecksums*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestPullError, FBeamRequestContext, Context, UPostManifestPullRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestPullComplete, FBeamRequestContext, Context, UPostManifestPullRequest*, Request);

using FPostManifestPullFullResponse = FBeamFullResponse<UPostManifestPullRequest*, UManifestChecksums*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestPullFullResponse, FPostManifestPullFullResponse);
