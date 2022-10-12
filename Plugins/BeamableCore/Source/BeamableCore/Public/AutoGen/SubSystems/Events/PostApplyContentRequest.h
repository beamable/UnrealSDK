
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/EventApplyRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostApplyContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostApplyContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UEventApplyRequestBody* Body;

	// Beam Base Request Declaration
	UPostApplyContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostApplyContentRequest* MakePostApplyContentRequest(UEvent* _Content, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplyContentSuccess, FBeamRequestContext, Context, UPostApplyContentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplyContentError, FBeamRequestContext, Context, UPostApplyContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostApplyContentComplete, FBeamRequestContext, Context, UPostApplyContentRequest*, Request);

using FPostApplyContentFullResponse = FBeamFullResponse<UPostApplyContentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostApplyContentFullResponse, FPostApplyContentFullResponse);
