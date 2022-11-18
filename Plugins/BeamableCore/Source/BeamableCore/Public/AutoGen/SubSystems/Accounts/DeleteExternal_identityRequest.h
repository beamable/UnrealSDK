
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/DeleteExternalIdentityApiRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteExternal_identityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteExternal_identityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteExternalIdentityApiRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteExternal_identityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make DeleteExternal_identity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UDeleteExternal_identityRequest* Make(FString _ProviderAddress, FString _UserId, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteExternal_identitySuccess, FBeamRequestContext, Context, UDeleteExternal_identityRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteExternal_identityError, FBeamRequestContext, Context, UDeleteExternal_identityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteExternal_identityComplete, FBeamRequestContext, Context, UDeleteExternal_identityRequest*, Request);

using FDeleteExternal_identityFullResponse = FBeamFullResponse<UDeleteExternal_identityRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteExternal_identityFullResponse, FDeleteExternal_identityFullResponse);
