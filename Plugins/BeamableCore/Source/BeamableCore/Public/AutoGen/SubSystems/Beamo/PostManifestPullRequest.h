
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPullBeamoManifestRequestBody* Body;

	// Beam Base Request Declaration
	UPostManifestPullRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostManifestPullRequest* MakePostManifestPullRequest(FString _SourceRealmPid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestPullSuccess, FBeamRequestContext, Context, UPostManifestPullRequest*, Request, UManifestChecksums*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostManifestPullError, FBeamRequestContext, Context, UPostManifestPullRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostManifestPullComplete, FBeamRequestContext, Context, UPostManifestPullRequest*, Request);

using FPostManifestPullFullResponse = FBeamFullResponse<UPostManifestPullRequest*, UManifestChecksums*>;
DECLARE_DELEGATE_OneParam(FOnPostManifestPullFullResponse, FPostManifestPullFullResponse);