
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/EventApplyRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostApplyContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostApplyContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEventApplyRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostApplyContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", DisplayName="Make PostApplyContent",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostApplyContentRequest* Make(UEvent* _Content, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplyContentSuccess, FBeamRequestContext, Context, UPostApplyContentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostApplyContentError, FBeamRequestContext, Context, UPostApplyContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostApplyContentComplete, FBeamRequestContext, Context, UPostApplyContentRequest*, Request);

using FPostApplyContentFullResponse = FBeamFullResponse<UPostApplyContentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostApplyContentFullResponse, FPostApplyContentFullResponse);
