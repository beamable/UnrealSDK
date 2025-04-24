
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteLaunchMessageRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLaunchMessageRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URemoveLaunchMessageRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteLaunchMessageRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make DeleteLaunchMessage",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteLaunchMessageRequest* Make(FString _File, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLaunchMessageSuccess, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLaunchMessageError, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLaunchMessageComplete, FBeamRequestContext, Context, UDeleteLaunchMessageRequest*, Request);

using FDeleteLaunchMessageFullResponse = FBeamFullResponse<UDeleteLaunchMessageRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLaunchMessageFullResponse, FDeleteLaunchMessageFullResponse);
