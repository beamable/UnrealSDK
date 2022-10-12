
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CreateLaunchMessageRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostLaunchMessageRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLaunchMessageRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCreateLaunchMessageRequestBody* Body;

	// Beam Base Request Declaration
	UPostLaunchMessageRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostLaunchMessageRequest* MakePostLaunchMessageRequest(FString _Name, FString _Body, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLaunchMessageSuccess, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLaunchMessageError, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLaunchMessageComplete, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request);

using FPostLaunchMessageFullResponse = FBeamFullResponse<UPostLaunchMessageRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLaunchMessageFullResponse, FPostLaunchMessageFullResponse);
