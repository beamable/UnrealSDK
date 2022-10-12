
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RemoveLaunchMessageRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteLaunchMessageRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLaunchMessageRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URemoveLaunchMessageRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteLaunchMessageRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteLaunchMessageRequest* MakeDeleteLaunchMessageRequest(FString _File, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLaunchMessageSuccess, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLaunchMessageError, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLaunchMessageComplete, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request);

using FDeleteLaunchMessageFullResponse = FBeamFullResponse<UDeleteLaunchMessageRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLaunchMessageFullResponse, FDeleteLaunchMessageFullResponse);
